#Python Script to be uploaded to printer firmware
#In this use uploading to Config folder makes access and modifications easier
#Current Moonraker script outputs values but seems to be scaled and has delay resulting in improper control at the end of a print

import asyncio
import websockets
import json
import serial  # Requires: pip install pyserial

#Configuration modify as needed
PRINTER_IP = "192.168.50.10"
ARDUINO_PORT = "/dev/ttyACM0" 
BAUD_RATE = 115200

LINE_WIDTH = 0.42            
LAYER_HEIGHT = 0.2           
URI = f"ws://{PRINTER_IP}:7125/websocket"

#Arduino Serial Setup
ser = serial.Serial(ARDUINO_PORT, BAUD_RATE, timeout=1)

async def listen_and_forward():
    async with websockets.connect(URI) as ws:
        print(f"Connected to SV08 and Arduino on {ARDUINO_PORT}")

        subscribe_msg = 
        {
            "jsonrpc": "2.0",
            "method": "printer.objects.subscribe",
            "params": {"objects": {"gcode_move": ["speed", "extrude_factor"]}},
            "id": 1
        }
        await ws.send(json.dumps(subscribe_msg))

        current_speed = 0.0
        extrude_factor = 1.0

        async for message in ws:
            data = json.loads(message)
            if "method" in data and data["method"] == "notify_status_update":
                move = data["params"].get("gcode_move", {})
                current_speed = move.get("speed", current_speed)
                extrude_factor = move.get("extrude_factor", extrude_factor)

                # Calculate Flow
                flow = current_speed * LINE_WIDTH * LAYER_HEIGHT * extrude_factor
                
                # Send ONLY the flow rate to Arduino (formatted to 2 decimal places)
                flow_msg = f"{flow:.2f}\n"
                ser.write(flow_msg.encode('ascii')) 
                print(f"Sent to Arduino: {flow_msg.strip()} mm³/s")

if __name__ == "__main__":
    try:
        asyncio.run(listen_and_forward())
    except KeyboardInterrupt:
        ser.close()
        print("\nDisconnected.")

