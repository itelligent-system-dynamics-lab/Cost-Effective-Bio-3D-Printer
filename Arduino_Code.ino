/*
Upload code to Arduino Nano R4 using Arduino IDE and import following libraries
*/

#include <Wire.h>
#include <Adafruit_ADS1X15.h>
#include <MCP4725.h>
#include <Arduino.h>
#include <U8g2lib.h>

/*
HARDWARE SETUP/PIN DECLARATIONS
*/
                                          //3 RELAY pins
#define RELAY_VENT 5
#define RELAY_GATE   6
#define RELAY_ISO  7
#define PLUG_PIN         10
#define MODE_SWITCH_PIN  9
#define LED_PIN          LED_BUILTIN

U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);
Adafruit_ADS1115 ads;
MCP4725 dac(0x60);

/*
GLOBAL VARIABLES
*/

int16_t adc[4];
float volts[4];

float Pressure1 = 0, Pressure2 = 0, potValue = 0, vrefValue = 0;
float pressureRange1 = 100.0f;
float pressureRange2 = 15.0f;
float voltageRange1  = 4.0f;
float voltageRange2  = 4.0f;
  char P1S[12];
  char P2S[12];
  char DACS[12];

bool polling = false;
byte pollStep = 0;   // IMPORTANT: initialize

float auto_mA_cmd;
float flow_sent;
float check;
float pressureFactor1 = 0 ,pressureFactor2 = 0;
float targetVoltage = 0.0f;
float setPointPSI   = 0.0f;
float Vref          = 5.05f;
float VrefOffset    = 1.0f;

int CALLIBRATION_OFFSET1 = 108; // raw ADC counts at 0 PSI
int CALLIBRATION_OFFSET2 = 97;

bool relayState1 = false;
bool relayState2 = false;
bool relayState3 = false;
bool manualMode  = true;
bool haveAutoCmd = false;
// Relay override: when true, UART commands control relays; ioHandler won't overwrite
bool relayOverride = false;

bool PluggedIn = false;
byte challengePass = 11;
byte plugChallengeCount = challengePass;

long t_now = 0, t_prev = 0;
const int timer = 250;
bool LED_STATE = false;
long lastPoll = 0;

// UART failsafe timing
unsigned long lastUartCommand = 0;
const unsigned long UART_TIMEOUT_MS = 10000; // 10 seconds
bool timeoutTripped = false;

/*
PLUG CHALLENGE
*/
void plugChallenge() {
  pinMode(PLUG_PIN, INPUT_PULLUP);
  while (true) {
    PluggedIn = !digitalRead(PLUG_PIN);
    if (PluggedIn) plugChallengeCount++;
    else           plugChallengeCount--;

    if (plugChallengeCount > (challengePass * 2)) { PluggedIn = true; break; }
    if (plugChallengeCount == 0)                  { PluggedIn = false; break; }
  }
  PluggedIn = plugChallengeCount > challengePass;
  pinMode(PLUG_PIN, OUTPUT);
  digitalWrite(PLUG_PIN, LOW);
}

/*
OLED
*/
void initializeOLED() {
  u8g2.setFont(u8g2_font_fub17_tr);	// Choose a font
  u8g2.drawStr(0,20,"Bio-Printer");
  u8g2.drawStr(0,40,"Ready");
}

void updateOLED() {
  
  u8g2.clearBuffer();					// Clear internal memory
  u8g2.setFont(u8g2_font_fub17_tr);	// Choose a font
  //dtostrf(Pressure1, 2,2,P1S);
  dtostrf(check, 2,2,P1S);
  //dtostrf(Pressure2, 2,2,P2S);
  dtostrf(flow_sent, 2,2,P2S);
  dtostrf(targetVoltage, 2,2,DACS);

  u8g2.drawStr(0,20,"P1: ");
  u8g2.drawStr(35,20,P1S);


  u8g2.drawStr(0,40,"P2: ");
  u8g2.drawStr(35,40,P2S);


  u8g2.drawStr(0,60,"DAC: ");
  u8g2.drawStr(55,60,DACS);


  u8g2.sendBuffer();					// Transfer buffer to display
  delay(100);
  
 
}

/*
DAC + ADS
*/
void dacTest() {
  if (dac.isConnected() < 1) Serial.println(F("DAC UNRESPONSIVE"));
  else {
    Serial.print(F("DAC CONNECTED — V="));
    Serial.println(dac.getVoltage(), 3);
  }
}

void setCurrentMA(float curr) {
  long current = long(curr * 1000.0f);
  current = constrain(current, 4000, 20000);
  float voltage = float(map(current, 4000, 20000,
                            (long)(00 * VrefOffset),
                            (long)(5000 * VrefOffset)) / 1000.0f);              //changed dac voltage   Seems to work as mapped
  setPointPSI = float(map(current, 4000, 20000, 0, 15000) / 1000.0f);
  targetVoltage = voltage;
  dac.setVoltage(voltage);
}

void setupMath() {
  ads.setGain(GAIN_TWOTHIRDS);
  Serial.println(F("ADS1115 initializing..."));
  for (int i = 0; i < 10; i++) {
    if (!ads.begin()) { Serial.println(F("ADS1115 waiting...")); delay(100); }
    else { Serial.println(F("ADS1115 ready.")); break; }
  }
  pressureFactor1 = pressureRange1 / voltageRange1;
  pressureFactor2 = pressureRange2 / voltageRange2;
}

// Poll one ADS channel each call
int continuousPollHandler() {
  if (polling) {
    if (millis() - lastPoll < 10) return -1;
    if (ads.conversionComplete()) {
      adc[pollStep] = ads.getLastConversionResults();
      volts[pollStep] = ads.computeVolts(adc[pollStep]);
      polling = false;
    }
  } else {
    ads.startADCReading(MUX_BY_CHANNEL[pollStep], false);
    polling = true;
    pollStep = (pollStep + 1) % 4;
    lastPoll = millis();
  }
  return 0;
}

void collectSample() {
  // Convert stored raw zero offsets -> volts (GAIN_TWOTHIRDS ~ 6.144V full scale)
  float offV1 = (CALLIBRATION_OFFSET1 / 32768.0f) * 6.144f;
  float offV2 = (CALLIBRATION_OFFSET2 / 32768.0f) * 6.144f;

  Pressure1 = (volts[3] - offV1) * pressureFactor1;   // P1 on A3
  Pressure2 = (volts[0] - offV2) * pressureFactor2;   // P2 on A0
  potValue  = volts[2];                               // pot on A2
  vrefValue = volts[1];                               // vref on A1

  if (Pressure1 < 0) Pressure1 = 0;
  if (Pressure2 < 0) Pressure2 = 0;
}

/*
IOHANDLER
*/
void ioHandler() 
{
  manualMode = (digitalRead(MODE_SWITCH_PIN) == LOW);

  // Control current output (manual uses pot, auto uses pot/vref ratio here)
  if (manualMode) 
  {
    float mA = 4.0f + (potValue / 5.0f) * 16.0f;
    setCurrentMA(mA);
  } 
  else 
    {
      if(haveAutoCmd)
      {
        setCurrentMA(auto_mA_cmd);
      }
    //float ratio = (vrefValue > 0.01f) ? (potValue / vrefValue) : 0.0f;
    //ratio = constrain(ratio, 0.0f, 1.0f);
    //float mA = 4.0f + ratio * 16.0f;
    //setCurrentMA(mA);
  }

  

  // UI timing
  t_now = millis();
  if (t_now - t_prev > timer) 
  {
    LED_STATE = !LED_STATE;
    digitalWrite(LED_PIN, LED_STATE);
    t_prev = t_now;
    updateOLED();
  }

  // Apply relays
  digitalWrite(RELAY_VENT, relayState1);
  digitalWrite(RELAY_GATE, relayState2);
  digitalWrite(RELAY_ISO,relayState3);
}

/*
CALIBRATION (relearn)
Assumes sensors are vented to atmosphere (0 PSI).
Stores offsets as RAW ADC counts.
*/
void relearn()                                                          //check sensor calibration code
{
  Serial.println(F("CAL: Make sure 0 PSI (vented). Sampling..."));
  const int N = 500;
  long s1 = 0, s2 = 0;

  for (int i = 0; i < N; i++) {
    s1 += ads.readADC_SingleEnded(3); // P1
    s2 += ads.readADC_SingleEnded(0); // P2
    delay(2);
  }

  CALLIBRATION_OFFSET1 = (int)(s1 / N);
  CALLIBRATION_OFFSET2 = (int)(s2 / N);

  Serial.print(F("CAL DONE P1_OFF="));
  Serial.print(CALLIBRATION_OFFSET1);
  Serial.print(F(" P2_OFF="));
  Serial.println(CALLIBRATION_OFFSET2);
}

/*
USB SERIAL UART HANDLER (Pi -> Arduino over USB)
*/
 float fmap(float x, float in_min, float in_max, float out_min, float out_max) 
  {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
  }
void uartHandler() 
{
  static String cmd;

  float flowFactor = 0.0;    //chnaged from 1.0
  float flowIn = 0.0;
  float psi;
 

  if (Serial.available()) 
  {
    // Read the raw flow rate from the Pi
    String incomingData = Serial.readStringUntil('\n');
    flowIn = incomingData.toFloat();
    if(flowIn > 800 || flowIn <100)
    {
      flow_sent = 0;
    }
    else
    flow_sent = 3.0527*exp(flowIn * 0.0015);

   flowFactor = flow_sent;

    check = 1.0;

    

   //Conversion from updated flow rate to psi
   if(flowFactor > 0)
   {
    psi = 1.071 * exp(0.2126 * flowFactor) +9 ;
   }
    else
    psi = 0;
   auto_mA_cmd = psi;
   //auto_mA_cmd = flowFactor + 3;

       haveAutoCmd = true;
    Serial.print("Flow:");
    Serial.println(flowFactor);
    Serial.print(" | PSI: ");
    Serial.println(psi);
    Serial.println(flowFactor);
  }
  else
  check = 4;
  
  if(psi > 1)
  {
    relayState1 = false;
    relayState2 = true;
    relayState3 = true;
  }
  else if(psi < 1)
  {
    relayState1 = false;
    relayState2 = true;
    relayState3 = true;
  }
  
  

  /*while (Serial.available()) {
    char c = (char)Serial.read();

    if (c == '\n' || c == '\r') {
      if (cmd.length() == 0) continue;
      cmd.trim();
      cmd.toUpperCase();

      lastUartCommand = millis();
      timeoutTripped = false; // clear timeout state when any command arrives

      if (cmd.startsWith("P")) {
        float psi = cmd.substring(1).toFloat();
        //psi = constrain(psi, 0.0f, 150.0f);
        //auto_mA_cmd = 4.0f + (psi / 150.0f) * 16.0f;
        psi = constrain(psi, 1.0f, 17.0f);
        auto_mA_cmd = 4.0f + (psi - 1.0f);
       haveAutoCmd = true;

        Serial.print("ACK:P=");
        Serial.println(psi, 2);
      }
      else if (cmd == "S") {
        Serial.print("P1="); Serial.print(Pressure1, 2);
        Serial.print(",P2="); Serial.print(Pressure2, 2);
        Serial.print(",DAC="); Serial.print(targetVoltage, 2);
        Serial.println("V OK");
      }
      else if (cmd == "PURGE ON") {
        relayOverride = true;
        relayState1 = true;
        Serial.println("ACK:PURGE ON");
      }
      else if (cmd == "PURGE OFF") {
        relayOverride = true;
        relayState1 = false;
        Serial.println("ACK:PURGE OFF");
      }
      else if (cmd == "ISO ON") {
        relayOverride = true;
        relayState2 = true;
        Serial.println("ACK:ISO ON");
      }
      else if (cmd == "ISO OFF") {
        relayOverride = true;
        relayState2 = false;
        Serial.println("ACK:ISO OFF");
      }
      else if (cmd == "REL AUTO") {                                             //DELETE
        // return relay control to automatic logic
        relayOverride = false;
        Serial.println("ACK:REL AUTO");
      }
      else if (cmd == "CAL") {
        Serial.println("ACK:CALIBRATING...");
        relearn();
        Serial.println("ACK:CAL DONE");
      }
      else if (cmd == "RST") {
        dac.setVoltage(0.0f);
        targetVoltage = 0.0f;
        Serial.println("ACK:DAC RESET");
      }
      else {
        Serial.print("ERR:UNKNOWN CMD ");
        Serial.println(cmd);
      }

      cmd = "";
    } else {
      if (cmd.length() < 80) cmd += c;
    }
  }
  */
}

/*
UART FAILSAFE
*/
void uartFailsafe() 
{
  if(manualMode)
  return;
  if (millis() - lastUartCommand > UART_TIMEOUT_MS) 
  {
    if (!timeoutTripped) 
    {
      // Only print once per timeout event
      Serial.println(F("UART TIMEOUT — Safety shutdown triggered."));
      Serial.println(F("WARN:UART TIMEOUT — OUTPUTS DISABLED"));
      timeoutTripped = true;
    }

    // Safe outputs
    dac.setVoltage(0.0f);
    targetVoltage = 0.0f;
    relayState1 = false;
    relayState2 = false;
    relayState3 = false;
    relayOverride = false; // optionally drop relay override on timeout
    digitalWrite(RELAY_GATE, LOW);
    digitalWrite(RELAY_ISO, LOW);
    digitalWrite(RELAY_VENT, LOW);
  }
}

/*
SETUP / LOOP
*/
void setup() 
{
  Serial.begin(115200);
  u8g2.begin();
  plugChallenge();

  pinMode(RELAY_VENT, OUTPUT);
  pinMode(RELAY_ISO, OUTPUT);
  pinMode(RELAY_VENT,OUTPUT);
  pinMode(LED_PIN, OUTPUT);
  pinMode(MODE_SWITCH_PIN, INPUT_PULLUP);

  if (PluggedIn) 
  {
    dac.begin();
    initializeOLED();
    dacTest();
    setCurrentMA(4.0f);
    setupMath();
  } else 
  {
    Serial.println(F("\nMCU NOT IN SOCKET — External functions disabled.\n"));
    manualMode = false;
  }

  lastUartCommand = millis(); // IMPORTANT: prevent immediate timeout
  Serial.println(F("System initialized. Commands: P#, S, PURGE ON/OFF, ISO ON/OFF, REL AUTO, CAL, RST"));
}


void loop() 
{
  if (PluggedIn) 
  {
    continuousPollHandler();
    collectSample();
  }
  uartHandler();
  //uartFailsafe();
  ioHandler();
   
}

