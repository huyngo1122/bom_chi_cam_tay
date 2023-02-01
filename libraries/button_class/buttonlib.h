/*
Library Button
Author: Van Huy
Version:1.0.0
Date:12/06/2022
*/
#ifndef _BUTTON_H
#define _BUTTON_H
#include "Arduino.h"
class Button_main
{
public:
	Button_main(unsigned char pin);
	bool isClicked();	 // nhan nut
	bool isPressed();	 // giu nut
	bool isReleased();	 // nha nut
	void begin_button(); // khoi tao
	long pressDuration;
private:
	unsigned char _pin;
	const int DEBOUNCE_DELAY = 20;
	bool preState;						  // bien luu trang thai truoc day
	bool lastAfterFilterNoiseState = LOW; // bien khu nhieu
	bool currentState;					  // bien trang thai hien tai
	unsigned long lastDebounceTime;
	unsigned char state;
	bool isPressing = false; // nếu nhấn nút isPressing = true
	bool isLongDetected = false;
	unsigned long pressedTime = 0;
	unsigned long releasedTime = 0;
	const int SHORT_PRESS_TIME = 500; // thoi gian nhan nha phim <SHORT_PRESS_TIME thi la nhan nha
	const int LONG_PRESS_TIME = 500;  // thoi gian mac dinh la nhan giu phim
	long delay_button = 200;
	
};
#endif