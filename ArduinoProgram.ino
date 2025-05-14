#include<LiquidCrystal_I2C.h>
#include<SoftwareSerial.h>

#define RX_Pin 9
#define TX_Pin 10

LiquidCrystal_I2C lcd(0x27, 16, 2);
SoftwareSerial mySerial(RX_Pin, TX_Pin);

#define ledPin 3
#define RelayPompa 8
#define sensorPIR 5
#define Buzzer 6
#define RelayNutrisi 7
#define SP_tanahPin A1
#define SP_PHPin A2
#define sensorPin A3

#define adaGerakan 1

int setPH = 7;
int SP_tanah,
    SP_PH,
    kelembabantanah,
    PH;

int tanahbasah = 500,
    tanahkering = 750,
    PH_Basa,
    PH_Asam;

byte sendd = 0,
     senddd = 0;

String data;
char CharData;
String StringData, dataSubs;
int index1, index2;

int Data;

unsigned long hitungan_milis;
unsigned long milis_sekarang;
const unsigned long nilai = 100;

int readSensor() {
  int val = analogRead(sensorPin);
  return val;
}

int readSP_tanah() {
  int val1 = analogRead(SP_tanahPin);
  int setPoint_PH = val1;
  return setPoint_PH;
}

int readSP_PH() {
  int val2 = analogRead(SP_PHPin);
  int setPoint_tanah = map(val2, 0, 1023, 0, 14);
  return setPoint_tanah;
}

int readPIR() {
  milis_sekarang = millis();
  if (milis_sekarang - hitungan_milis >= nilai)
  {
    if (digitalRead(sensorPIR) == adaGerakan) {
      Serial.println(digitalRead(sensorPIR));
      digitalWrite(Buzzer, HIGH);
      digitalWrite(ledPin, HIGH);
      delay(100);
      digitalWrite(Buzzer, LOW);
      digitalWrite(ledPin, LOW);
      delay(100);
    }
  }
}

void Display() {
  lcd.setCursor(0, 0);
  lcd.print("SP1:");
  lcd.print(SP_PH);
  lcd.print("   ");
  lcd.setCursor(7, 0);
  lcd.print("SP2:");
  lcd.print(SP_tanah);
  lcd.print("   ");
}


void setup() {
  Serial.begin(9600);
  mySerial.begin(115200);

  lcd.init();
  lcd.backlight();

  pinMode(Buzzer, OUTPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(RelayPompa,  OUTPUT);
  pinMode(RelayNutrisi,  OUTPUT);
  pinMode(SP_tanahPin, INPUT);
  pinMode(SP_PHPin, INPUT);
  pinMode(sensorPIR, INPUT_PULLUP);
  digitalWrite(Buzzer, LOW);
  digitalWrite(ledPin, LOW);
  digitalWrite(RelayPompa, HIGH);
  digitalWrite(RelayNutrisi, HIGH);

  for (int i = 0; i <= 10; i++) {
    tanahbasah = readSP_tanah();
    lcd.setCursor(0, 0);
    lcd.print("Tanah(B) :");
    lcd.print(tanahbasah);
    lcd.print("   ");
    lcd.setCursor(0, 1);
    lcd.print("Setting");
    delay(1000);
  }
  lcd.clear();
  delay(100);
  for (int i = 0; i <= 10; i++) {
    tanahkering = readSP_tanah();
    lcd.setCursor(0, 0);
    lcd.print("Tanah(K) :");
    lcd.print(tanahkering);
    lcd.print("   ");
    lcd.setCursor(0, 1);
    lcd.print("Setting");
    delay(1000);
  }
  lcd.clear();
  delay(100);
  for (int i = 0; i <= 10; i++) {
    PH_Asam = readSP_PH();
    lcd.setCursor(0, 0);
    lcd.print("PH(A) :");
    lcd.print(PH_Asam);
    lcd.print("   ");
    lcd.setCursor(0, 1);
    lcd.print("Setting");
    delay(1000);
  }
  lcd.clear();
  delay(100);
  for (int i = 0; i <= 10; i++) {
    PH_Basa = readSP_PH();
    lcd.setCursor(0, 0);
    lcd.print("PH(B) :");
    lcd.print(PH_Basa);
    lcd.print("   ");
    lcd.setCursor(0, 1);
    lcd.print("Setting");
    delay(1000);
  }
  lcd.clear();
  delay(100);
}

void loop() {

  /* BACA DATA DARI ARDUINO */
  while (mySerial.available() > 0)
  {
    delay(10);
    CharData = mySerial.read();
    StringData += CharData;

    /* PARSING DATA MASUK */
    if (StringData.length() > 0 && CharData == '?')
    {
      index1 = StringData.indexOf('#');
      index2 = StringData.indexOf('?', index1 + 1);
      dataSubs = StringData.substring(index1 + 1, index2);
      StringData = "";

      //Mengubah Data String ke Float
      char buf[dataSubs.length()];
      dataSubs.toCharArray(buf, dataSubs.length() + 1);
      float Data1 = atof(buf);

      /* DATA MASUK */
      Data = Data1;
      Serial.print("Data Masuk : ");
      Serial.println(Data);

      if (Data == 1) {
        if (kelembabantanah < tanahbasah) {
          mySerial.print("#1!"); // Tanah Basah
        }
        else if (kelembabantanah >= tanahbasah && kelembabantanah <= tanahkering) {
          mySerial.print("#2!"); // Tanah Normal
        }
        else if (kelembabantanah > tanahkering) {
          mySerial.print("#3!"); // Tanah Kering
        }

        if (PH < PH_Asam) {
          mySerial.print("#11!"); // Asam
        }
        else if (PH >= PH_Asam && PH <= PH_Basa) {
          mySerial.print("#22!"); // Normal
        }
        else if (PH > PH_Basa) {
          mySerial.print("#33!"); // Basa
        }

        mySerial.print("#" + String(PH) + "@");

        Data = "";
      }
    }
  }

  milis_sekarang = millis();
  if (milis_sekarang - hitungan_milis >= nilai)
  {
    if (digitalRead(sensorPIR) == adaGerakan) {
      Serial.print(digitalRead(sensorPIR));
      digitalWrite(Buzzer, HIGH);
      digitalWrite(ledPin, HIGH);
      delay(100);
      digitalWrite(Buzzer, LOW);
      digitalWrite(ledPin, LOW);
      delay(100);
    }
  }

  PH = readSP_PH();
  kelembabantanah = readSensor();
  SP_tanah = readSP_tanah();

  lcd.setCursor(12, 0);
  lcd.print(kelembabantanah);
  lcd.print(" ");
  lcd.setCursor(12, 1);
  lcd.print(PH);
  lcd.print(" ");

  Serial.print(digitalRead(sensorPIR));
  Serial.print("\t\tADC Soil : ");
  Serial.print(kelembabantanah);
  Serial.print("\t\tSP Tanah : ");
  Serial.print(SP_tanah);
  Serial.print("\t\tSP PH : ");
  Serial.println(SP_PH);

  if (kelembabantanah < tanahbasah) {
    Serial.println("Status: Tanah Basah");
    digitalWrite(RelayPompa, HIGH);
    lcd.setCursor(0, 0);
    lcd.print("Tanah Basah ");
    sendd = 1;
  } else if (kelembabantanah >= tanahbasah && kelembabantanah <= tanahkering) {
    Serial.println("Status: Tanah Normal");
    digitalWrite(RelayPompa, HIGH);
    lcd.setCursor(0, 0);
    lcd.print("Tanah Normal");
    sendd = 1;
  } else if (kelembabantanah > tanahkering) {
    Serial.println("Status: Tanah Kering");
    digitalWrite(RelayPompa, LOW);
    lcd.setCursor(0, 0);
    lcd.print("Tanah Kering");
    while (sendd <= 1) {
      if (sendd == 2) break;
      mySerial.print("#1?");
      sendd = 2;
    }
  }

  if (PH < PH_Asam) {
    Serial.println("Status: PH Asam");
    digitalWrite(RelayNutrisi, LOW);
    lcd.setCursor(0, 1);
    lcd.print("PH Asam  ");
    senddd = 1;
  }
  else if (PH >= PH_Asam && PH <= PH_Basa) {
    Serial.println("Status: PH Normal");
    digitalWrite(RelayNutrisi, HIGH);
    lcd.setCursor(0, 1);
    lcd.print("PH Normal");
    senddd = 1;
  }
  else if (PH > PH_Basa) {
    Serial.println("Status: PH Basa");
    digitalWrite(RelayNutrisi, LOW);
    lcd.setCursor(0, 1);
    lcd.print("PH Basa  ");
    while (senddd <= 1) {
      if (senddd == 2) break;
      mySerial.print("#2?");
      senddd = 2;
    }
  }
  delay(100);
  Serial.println();
}
