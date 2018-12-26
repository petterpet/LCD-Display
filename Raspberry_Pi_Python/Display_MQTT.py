# Initialisierung
import time
import lcddriver
import paho.mqtt.client as mqtt

lcd = lcddriver.lcd()
lcd.lcd_clear()

# MQTT
def on_connect(client, userdata, flags, rc):
    print("Connected with result code " + str(rc))

    client.subscribe("LCD-Display/#")

def on_message(client, userdata, msg):

    # message
    msg_len = (len(str(msg.payload)))-3
    message = msg.payload

    topic_len = len(str(msg.topic))

    # command
    if str(msg.topic)[topic_len-1] == "d":
        if message == "off":
            lcd.lcd_backlight("off")

        elif message == "on":
            lcd.lcd_backlight("on")

        elif message == "clear":
            lcd.lcd_clear()

    # Text anzeigen
    elif int(str(msg.topic)[topic_len-1]) in range(1,5):
        line = int(str(msg.topic)[topic_len-1])
        lcd.lcd_display_string(message, line)

client = mqtt.Client()
client.on_connect = on_connect
client.on_message = on_message

client.connect("192.168.x.x", 1883, 60)

client.loop_forever()
