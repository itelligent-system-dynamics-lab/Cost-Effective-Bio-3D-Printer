#Within printer terminal create a new service file
#Service files starts up moonraker each time the printer boots
sudo nano /etc/systemd/system/flow-sensor.service

#Paste the following into the terminal


[Unit]
Description=Klipper Flow Sensor to Arduino
# Wait for the network and Klipper/Moonraker to be ready
After=network-online.target moonraker.service

[Service]
# Replace 'sovol' with your actual username
User=sovol
WorkingDirectory=/home/pi/printer_data/config
# Full path to python and your script
#Replace 'flow_sensor' with your file name for moonraker
ExecStart=/usr/bin/python3 /home/pi/printer_data/config/flow_sensor.py
Restart=always
RestartSec=5

[Install]
WantedBy=multi-user.target


##Back in terminal
sudo systemctl daemon-reload
sudo systemctl enable flow-sensor.service
sudo systemctl start flow-sensor.service

#Verify service file is running
sudo systemctl status flow-sensor.service
