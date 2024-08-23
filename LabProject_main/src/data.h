#ifndef _DATA_H_
#define _DATA_H_

#include<Arduino.h>
#include"buzz.h"
#include <LiquidCrystal_I2C.h>
#include <HTTPClient.h>
#include"port.h"
#include <MFRC522.h>
#include<ESP32Servo.h>
void handleDataFromGoogle(String data);
void getGoogleData();
void send_receive();


#endif