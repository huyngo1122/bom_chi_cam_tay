const int BUTTON_PIN = 11;

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "buttonlib.h"
LiquidCrystal_I2C lcd(0x27, 20, 4);

int count_in = 0;
int count;
Button_main button1(BUTTON_PIN);

void setup()
{
    count = count_in;
    lcd.init();
    lcd.backlight();
    lcd.setCursor(1, 0);
    lcd.print("hello Huy");
    lcd.setCursor(1, 1);
    Serial.begin(9600);
    Serial.println("heloo");
}
void loop()
{

    button1.begin_button();
    if (button1.isClicked())
    {
        count_in++;
        count = count_in;
        lcd.setCursor(2, 1);
        lcd.print(count);
        Serial.println(count);
    }
    else if (button1.isPressed())
    {
        lcd.setCursor(2, 3);
        Serial.println("nhan giu");
        Serial.println(button1.pressDuration);
    }
    else
        (button1.isReleased());
}