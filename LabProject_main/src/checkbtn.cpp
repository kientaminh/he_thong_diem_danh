#include"checkbtn.h"
#include"port.h"
unsigned long lastDebounceTime1 = 0;
unsigned long lastDebounceTime2 = 0;

bool buttonState1 = LOW;
bool buttonState2 = LOW;

bool lastButtonState1 = LOW;
bool lastButtonState2 = LOW;

const unsigned long debounceDelay = 30;
bool check_btn1()
{
  bool reading1 = digitalRead(btn_down);
  if (reading1 != lastButtonState1) {
    lastDebounceTime1 = millis();
  }

  if ((millis() - lastDebounceTime1) > debounceDelay) {
    if (reading1 != buttonState1) {
      buttonState1 = reading1;
      if (buttonState1 == HIGH) {
        return true;
      }
    }
  }
    lastButtonState1 = reading1;
    return false;
}

bool check_btn2()
{
  bool reading2 = digitalRead(btn_slc);
  if (reading2 != lastButtonState2) {
    lastDebounceTime2 = millis();
  }

  if ((millis() - lastDebounceTime2) > debounceDelay) {
    if (reading2 != buttonState2) {
      buttonState2 = reading2;
      if (buttonState2 == HIGH) {
        return true;
      }
    }
  }
  lastButtonState2 = reading2;
  return false;
}