/*
Library Button
Author: Van Huy
Version:1.0.0
Date:12/06/2022
*/
#include "Buttonlib.h"
Button_main::Button_main(unsigned char pin)
{
    _pin = pin;
    pinMode(_pin, INPUT_PULLUP);
    preState = HIGH;
    lastAfterFilterNoiseState = LOW;
}
bool Button_main::isClicked()
{
    if (state == 1)
        return true;
    return false;
}
bool Button_main::isPressed()
{
    if (state == 2)
        return true;
    return false;
}
bool Button_main::isReleased()
{
    if (state == 3)
        return true;
    return false;
}
void Button_main::begin_button()
{
    state = 0; // reset trang thai
    //đọc trạng thái nút nhấn
    currentState = digitalRead(_pin);
    // khi có nhiễu thì đoạn code này sẽ chạy liên tục
    if (currentState != lastAfterFilterNoiseState)
    {
        lastDebounceTime = millis();
        lastAfterFilterNoiseState = currentState;
    }
    // hết thời gian nhiễu sẽ thực hiện đoạn code dưới
    if ((millis() - lastDebounceTime) > DEBOUNCE_DELAY)
    {
        if (preState == HIGH && currentState == LOW)
        {

            pressedTime = millis();
            isLongDetected = false;
            isPressing == true;
        }
        else if (preState == LOW && currentState == HIGH)
        {
            isPressing = false;
            releasedTime = millis();

            state = 3;
            pressDuration = releasedTime - pressedTime;
        if (pressDuration < SHORT_PRESS_TIME)
            state = 1;
        else if (pressDuration > SHORT_PRESS_TIME)
            {
            state = 2;
            }
        }
        preState = currentState;
    }
}
