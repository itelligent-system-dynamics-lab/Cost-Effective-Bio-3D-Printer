# Configure Flow Sensor as a Linux System Service

This guide configures the flow-sensor Python script to run automatically as a **systemd service** when the printer starts. The service is configured to start after the network and Moonraker are available and will automatically restart if the Python script stops unexpectedly.

> **Note:** The commands below are intended to be run from the printer's Linux terminal.

---

## 1. Create the Service File

Create a new systemd service file:

```bash
sudo nano /etc/systemd/system/flow-sensor.service
```

Paste the following configuration into the file:

```ini
[Unit]
Description=Klipper Flow Sensor to Arduino

# Start after the network and Moonraker are available
After=network-online.target moonraker.service

[Service]
# Replace 'sovol' with the Linux username used by your printer
User=sovol

# Directory containing the Python script
WorkingDirectory=/home/pi/printer_data/config

# Start the flow sensor Python script
# Replace 'flow_sensor.py' with your actual Python script filename
ExecStart=/usr/bin/python3 /home/pi/printer_data/config/flow_sensor.py

# Automatically restart the service if the script stops
Restart=always
RestartSec=5

[Install]
# Start the service during normal system boot
WantedBy=multi-user.target
```

### Important: Verify Your Username and File Name

The `User=` and `ExecStart=` paths must match your printer's configuration.

To find the current Linux username, run:

```bash
whoami
```

For example, if the terminal returns:

```text
sovol
```

then use:

```ini
User=sovol
```

Verify that your Python script exists in the specified directory:

```bash
ls /home/pi/printer_data/config/
```

If your script has a different filename, change:

```ini
ExecStart=/usr/bin/python3 /home/pi/printer_data/config/flow_sensor.py
```

to match the actual filename.

For example:

```ini
ExecStart=/usr/bin/python3 /home/pi/printer_data/config/my_flow_sensor.py
```

> **Note:** If your printer uses a different home directory than `/home/pi`, update both `WorkingDirectory` and `ExecStart` accordingly.

---

## 2. Save the Service File

If using `nano`:

1. Press **Ctrl + O** to save.
2. Press **Enter** to confirm the filename.
3. Press **Ctrl + X** to exit.

---

## 3. Reload systemd

Tell Linux to reload its service configuration:

```bash
sudo systemctl daemon-reload
```

---

## 4. Enable the Service at Boot

Enable the service so that it automatically starts whenever the printer boots:

```bash
sudo systemctl enable flow-sensor.service
```

You should see a message indicating that a symbolic link was created.

---

## 5. Start the Service

Start the service without rebooting the printer:

```bash
sudo systemctl start flow-sensor.service
```

---

## 6. Verify the Service is Running

Check the service status:

```bash
sudo systemctl status flow-sensor.service
```

A successful service should show:

```text
Active: active (running)
```

Press **Q** to exit the status screen.

---

## 7. View Service Logs

If the service does not start correctly, view the Python script's output using:

```bash
sudo journalctl -u flow-sensor.service
```

To view the most recent entries:

```bash
sudo journalctl -u flow-sensor.service -n 50
```

To continuously monitor the service logs:

```bash
sudo journalctl -u flow-sensor.service -f
```

Press **Ctrl + C** to stop following the logs.

---

## 8. Restart the Service

After making changes to the Python script, restart the service:

```bash
sudo systemctl restart flow-sensor.service
```

Then verify that it is running:

```bash
sudo systemctl status flow-sensor.service
```

---

## 9. Stop the Service

To manually stop the flow-sensor service:

```bash
sudo systemctl stop flow-sensor.service
```

---

## 10. Disable Automatic Startup

If the service should no longer start automatically when the printer boots:

```bash
sudo systemctl disable flow-sensor.service
```

---

## Service Command Reference

| Command                                      | Function                     |
| -------------------------------------------- | ---------------------------- |
| `sudo systemctl start flow-sensor.service`   | Start the service            |
| `sudo systemctl stop flow-sensor.service`    | Stop the service             |
| `sudo systemctl restart flow-sensor.service` | Restart the service          |
| `sudo systemctl status flow-sensor.service`  | Check service status         |
| `sudo systemctl enable flow-sensor.service`  | Start automatically at boot  |
| `sudo systemctl disable flow-sensor.service` | Disable automatic startup    |
| `sudo systemctl daemon-reload`               | Reload systemd configuration |
| `sudo journalctl -u flow-sensor.service`     | View service logs            |
| `sudo journalctl -u flow-sensor.service -f`  | Continuously monitor logs    |

---

## Troubleshooting

### Service fails to start

Check the service status:

```bash
sudo systemctl status flow-sensor.service
```

Then check the logs:

```bash
sudo journalctl -u flow-sensor.service -n 50
```

### Python script cannot be found

Verify that the script exists:

```bash
ls -l /home/pi/printer_data/config/flow_sensor.py
```

If the filename or location is different, update the `ExecStart=` line in the service file.

### Permission errors

Verify that the configured user can access the script:

```bash
ls -l /home/pi/printer_data/config/flow_sensor.py
```

If necessary, verify the user specified in the service file:

```bash
whoami
```

### Changes to the service file are not taking effect

After modifying `/etc/systemd/system/flow-sensor.service`, always run:

```bash
sudo systemctl daemon-reload
```

Then restart the service:

```bash
sudo systemctl restart flow-sensor.service
```

---

## Verify Automatic Startup

After confirming that the service works, reboot the printer:

```bash
sudo reboot
```

Once the printer has restarted, check the service:

```bash
sudo systemctl status flow-sensor.service
```

The expected result is:

```text
Active: active (running)
```

This confirms that the flow-sensor Python script is configured to launch automatically when the printer boots.

##Back in terminal
sudo systemctl daemon-reload
sudo systemctl enable flow-sensor.service
sudo systemctl start flow-sensor.service

#Verify service file is running
sudo systemctl status flow-sensor.service
