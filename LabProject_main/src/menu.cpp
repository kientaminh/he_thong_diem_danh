#include"menu.h"
extern int cnt;
extern int menu;
extern LiquidCrystal_I2C lcd;
void menu_tong()
{
  lcd.clear();
  if(cnt % 3 == 0)
  {
    lcd.setCursor(0, 0);
    lcd.print(">Diem Danh");
    lcd.setCursor(0, 1);
    lcd.print("Them the");
  }
  else if(cnt % 3 == 1)
  {
    lcd.setCursor(0, 0);
    lcd.print("Diem Danh");
    lcd.setCursor(0, 1);
    lcd.print(">Them the");
  }
  else if(cnt % 3 == 2)
  {
    lcd.setCursor(0, 0);
    lcd.print("Them the");
    lcd.setCursor(0, 1);
    lcd.print(">Xoa the");
  }
}
void menu_diemdanh()
{
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Moi quet the");
  lcd.setCursor(0, 1);
  lcd.print(">Quay lai");
}

void menu_them()
{
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(" Moi quet the");
  lcd.setCursor(0, 1);
  lcd.print(">Quay lai");
}

void menu_xoa()
{
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Moi quet the");
  lcd.setCursor(0, 1);
  lcd.print(">Quay lai");
}