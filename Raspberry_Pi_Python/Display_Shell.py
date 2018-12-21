# Initialisierung
import lcddriver
import sys

lcd = lcddriver.lcd()
lcd.lcd_clear()

paramOne = str(sys.argv[1])
paramTwo = str(sys.argv[2])

if paramOne == "command":
    if paramTwo == "off":
        lcd.lcd_backlight("off")

    elif paramTwo == "on":
        lcd.lcd_backlight("on")

    elif paramTwo == "clear":
        lcd.lcd_clear()

elif paramOne == "line1":
    lcd.lcd_display_string(paramTwo, 1)

elif paramOne == "line2":
    lcd.lcd_display_string(paramTwo, 2)
