# LCD-Display

Die in diesem Repository enthaltenen Dateien ermöglichen das Ansteuern eines HD44780 LCD-Displays.
Die Daten werden per MQTT an das Display übertragen.

## Raspberry Pi
Die Ansteuerung erfolgt mit Python über I²C.

Dazu wird folgendes benötigt:
  * LCD-Display
  * I²C Display Adapter
  * I²C Logik Level Konverter

### Schaltplan:
![Schaltplan](/Raspberry_Pi_Python/schaltplan.png)

### Software:
  * Pakete installieren`sudo apt-get install python-smbus i2c-tools`
  * I²C in der `raspi-config` freischalten
  * In der Datei `/etc/modules` am Ende folgende Zeilen eintragen:
    * `i2c-bcm2708`
    * `i2c-dev`
  * Neustarten `sudo reboot`

  * mit `sudo i2cdetect -y 1` die I²C-Adresse herausfinden und in `lcddriver.py` bei `ADDRESS` eintragen

## Arduino
Die Ansteuerung kann mit und ohne I²C erfolgen.

### Schaltplan:
  * mit I²C:
  ![Schaltplan](/Arduino/schaltplan_i2c.png)
  * ohne I²C:
  ![Schaltplan](/Arduino/schaltplan.png)

## Nutzung:
Als Default hört das Skript auf dem Topic `LCD-Display/#`.
Zur __Steuerung__ wird auf `LCD-Display/command` _on_, _off_ oder _clear_ gepublished.
Der __Text__ für jede Zeile ist der Payload in den Topics `LCD-Display/line1`und `LCD-Display/line2`, bzw. bis _line4_.


Für weitere Informationen siehe [hier](https://tutorials-raspberrypi.de/hd44780-lcd-display-per-i2c-mit-dem-raspberry-pi-ansteuern/).
Die I²C Library für Python stammt von [hier](https://github.com/CaptainStouf/raspberry_lcd4x20_I2C).
