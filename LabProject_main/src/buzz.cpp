#include"buzz.h"
void beep(int count)
{

    ledcSetup(BUZZ_CHANNEL, 5000, 10);
    ledcAttachPin(BUZZ_PIN, BUZZ_CHANNEL);
    for (size_t j = 0; j < count; j++)
    {
        if(j!=0)
        delay(300);
        for (int i = 200; i < 1000; i++)
        {
            ledcWrite(BUZZ_CHANNEL, i);
            delayMicroseconds(30);
        }
    ledcWrite(BUZZ_CHANNEL, 0);
    }
    ledcDetachPin(BUZZ_PIN);
    pinMode(BUZZ_PIN,INPUT);
}