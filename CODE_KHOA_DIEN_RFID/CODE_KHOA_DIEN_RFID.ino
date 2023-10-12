#include <SPI.h>
#include <MFRC522.h>
#include <Thread.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <SoftwareSerial.h>

#define SS_PIN 10
#define RST_PIN 9
#define Rx A1            
#define Tx A2 
#define FAN 2

int GAS = A0; //Cảm biến nối chân số 5 Arduino
int ppm;

MFRC522 mfrc522(SS_PIN, RST_PIN);   
SoftwareSerial mySerial(Rx, Tx); //Tạo cổng serial 

LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup()
{
  mySerial.begin(9600);
  Serial.begin(9600);   
  SPI.begin();    
  mfrc522.PCD_Init();   
  Serial.println("Dua the vao...");
  Serial.println();

  lcd.init();
  lcd.backlight();
  lcd.setCursor(3, 0);
  lcd.print("KHOA DIEN");
  lcd.setCursor(3, 1);
  lcd.print("RFID RC522");
  delay(1000);
  lcd.clear();
  pinMode(FAN, OUTPUT);
  pinMode(GAS, INPUT);
  // pinMode(CBM, INPUT);
  // pinMode(CBAS, INPUT);
}
void loop() {
  rfid();
  CBGAS();  
  // CBAS();
}

void CBGAS(){
  ppm = digitalRead(GAS);
  Serial.println(ppm);
  if (ppm == HIGH){
    digitalWrite(FAN, HIGH);
  }
  else {
    digitalWrite(FAN, LOW);
  }
}
void rfid() {
  lcd.setCursor(2, 0);
  lcd.print("MOI QUET THE ");
  // Tìm thẻ
  if ( ! mfrc522.PICC_IsNewCardPresent())
  {
    return;
  }
  //  chọn 1 thẻ
  if ( ! mfrc522.PICC_ReadCardSerial())
  {
    return;
  }
  Serial.print("UID tag :");
  String content = "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++)
  {
    Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
    Serial.print(mfrc522.uid.uidByte[i], HEX);
    content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
    content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println();
  Serial.print("Message : ");
  content.toUpperCase();

  if (content.substring(1) == "F3 B1 9D 92" || content.substring(1) == "F3 B1 9D 92"  ) // dán ID của thẻ vừa đọc được từ trước
  {//33 FE 47 9F
    Serial.println("DUNG THE");
    Serial.println();
    lcd.setCursor(0, 1);
    lcd.print("***  MO CUA  ***");
    mySerial.print("dooron");
    delay(2000);                   // Thời gian mở cửa
    lcd.setCursor(0, 1);
    lcd.print("                ");
    mySerial.print("dooroff");
  }
  else
  {
    Serial.println("SAI THE");
    Serial.println();
    lcd.setCursor(0, 1);
    lcd.print("***  SAI THE ***");
    delay(1000);
    lcd.setCursor(0, 1);
    lcd.print("                ");
  }
}
