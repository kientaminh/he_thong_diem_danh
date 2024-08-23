#include "data.h"
extern LiquidCrystal_I2C lcd;
MFRC522 rfid(SS_PIN, RST_PIN); 
Servo servo;
extern char command[20];
const char *mainLinkForSpr = "https://script.google.com/macros/s/AKfycbyBIdpuHMsy8C1ii1F_G8TtYMjwF-HAZ8FFs5sCFvpuY-DHvkiTcJXUW2xjrMlwCrwZkw/exec";
const char *root_ca =
    "-----BEGIN CERTIFICATE-----\n"
    "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\n"
    "bP6MvPJwNQzcmRk13NfIRmPVNnGuV/u3gm3c\n"
    "-----END CERTIFICATE-----\n";
bool flag = false;
void setUp(){
  servo.setPeriodHertz(50);
  servo.attach(DOOR_PIN);
  SPI.begin();
  rfid.PCD_Init();
}

void handleDataFromGoogle(String data)
{
  int colonIndex = data.indexOf(":");
  String text = data.substring(0, colonIndex);
  int nextColonIndex = data.indexOf(":", colonIndex + 1);
  String num = data.substring(colonIndex + 1, nextColonIndex);
  String name = data.substring(nextColonIndex + 1, data.length());
  if (text != "Success")
  {
    lcd.setCursor(0, 0);
    lcd.print("Fail");
    lcd.setCursor(0, 1);
    lcd.print(text);
    beep(5);
  }
  else
  {
    lcd.setCursor(0, 0);
    lcd.print("Succes");
    lcd.setCursor(0, 1);
    if (num == "0")
    {
      lcd.print("Hi " + name);
      beep(5);
      servo.write(180);
      delay(3000);
      servo.write(0);
      delay(500);
    }
  }
}
void getGoogleData()
{
  HTTPClient http;
  String data;

  lcd.clear();
  uint64_t time = esp_timer_get_time();
  char url[150];
  int pointerShift = sprintf(url, "%s?uid=", mainLinkForSpr);

  for (size_t i = 0; i < rfid.uid.size; i++)
  {
    pointerShift += sprintf(url + pointerShift, "%X", rfid.uid.uidByte[i]);
  }

  pointerShift += sprintf(url + pointerShift, "&command=%s", command);

  Serial.println(url);
  Serial.println(F("Connecting to google"));
  lcd.print(F("Connecting to"));
  lcd.setCursor(7, 1);
  lcd.print(F("Google"));

  // you need to make two request, the second request to a redirected url
  // to get redirect url you need to read "Location" header
  http.begin(url, root_ca);

  const char *location = "Location";
  const char *headerKeys[] = {location};
  http.collectHeaders(headerKeys, 1);
  int code = http.GET();
  Serial.printf("code %d\n", code);
  // 302 code means redirect
  if (code == 302)
  {
    String newUrl = http.header(location);

    http.end();

    Serial.println(newUrl);
    http.begin(newUrl, root_ca);
    code = http.GET();
    Serial.printf("status code %d\n", code);

    data = http.getString();
    Serial.println(data);

    lcd.clear();
    lcd.setCursor(0, 0);

    lcd.setCursor(0, 1);
  }
  else
  {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(code);
    if (code == 403 || code == -1)
    {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print(F("Err open terminl"));
      lcd.setCursor(0, 1);
      lcd.print("for help");
      if (code == -1)
      {
        Serial.println(F("If it says somethink like start_ssl_clien error"));
        Serial.print(F("try to update the ssl CERTIFICATE"));
      }
      else
      {
        Serial.print(F("Open this link in any browser "));
        Serial.println(url);
        Serial.println(F("If it says Authorization is ...."));
        Serial.println(F("Open the google script and republish it"));
      }
    }

    else
    {
      lcd.print(F("Something wrong"));
      lcd.setCursor(0, 1);
    }
  }

  if (!data.isEmpty() && data.length() > 1)
  {
    handleDataFromGoogle(data);
  }
  Serial.printf("time=%d\n", esp_timer_get_time() - time);
}

void send_receive()
{
  if(!flag){
    setUp();
    flag = !flag;
  }
  if (!rfid.PICC_IsNewCardPresent())
  {
    return;
  }
  if (!rfid.PICC_ReadCardSerial())
  {
    return;
  }
  beep(1);
  lcd.backlight();

  for (size_t i = 0; i < rfid.uid.size; i++)
  {
    Serial.printf("%X", rfid.uid.uidByte[i]);
  }
  getGoogleData();

  rfid.PICC_HaltA();

  rfid.PCD_StopCrypto1();
  beep(1);
}