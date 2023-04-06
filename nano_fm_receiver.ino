#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <TEA5767Radio.h>

TEA5767Radio radio = TEA5767Radio();
LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27, 16, 2);
int jmlst,  i = 14;
const char * const st[][2] = {
  "87.70","HardRock",
  "88.10","SouthEast",
  "88.50","MoraFM",
  "88.90","Auto",
  "89.30","ElShinta",
  "89.70","Global",
  "90.10","Urban Bdg",
  "90.50","Cakra",
  "90.90","X-Channel",
  "91.30","Trijaya",//1
  "91.70","Nyimas",
  "92.10","SuaraIndh",
  "92.50","Maestro",
  "93.30","Sonora",
  "93.70","Paramuda",
  "94.40","DeltaFM",
  "94.80","FitFM",
  "95.20","Bandung",
  "95.60","B-Radio",
  "96.40","Bobotoh",//2
  "96.80","Eight",
  //"97.20","NewShinta",
  "97.60","RRI Pro1",
  "98.00","MayaFM",
  "98.40","Prambors",
  "98.80","Raka",
  //"99.20","Mom&Kids", 
  "100.00","99ers",
  "100.40","KLCBS",
  "100.80","Kandaga",//3
  "101.10","MGT",
  "101.50","Dahlia",
  //"101.90","Cosmo",
  "102.30","RaseFM",
  "102.70","MQFM",
  "103.10","OzRadio",
  "103.40","Gak Tau",
  "103.90","UNIKOM",
  "104.30","RodjaFM",
  "104.70","RamaFM",//4
  "105.10","I-Radio",
  "105.50","Garuda",
  "105.90","Ardan",
  "106.30","UrbanFM",
  "106.70","Mara FM",
  "107.10","K-lite",
  "107.50","PRFM",
  "108.00","Arduino"
  };


float frequency = 0;
bool backlightState = true;
int mode=1;

void setup() {
  lcd.begin();
  lcd.backlight();
  setradio(i);
  frequency = atof(st[i][0]);
  cetak(st[i][0] , st[i][1]);
  jmlst=sizeof(st)/sizeof(st[0]);
}

void loop() {
  if (digitalRead(5) == HIGH) {
    delay(100);
    if (mode == 1) {
      gantist(-1);
    } else if (mode == 2) {
      gantist(-5);
    } else if (mode == 3) {
      gantistManual(-0.1);
    } else if (mode == 4) {
      gantistManual(-1);
    }
  }  else if (digitalRead(6) == HIGH) {
    delay(100);
    if (mode == 1) {
      gantist(1);
    } else if (mode == 2) {
      gantist(5);
    } else if (mode == 3) {
      gantistManual(0.1);
    } else if (mode == 4) {
      gantistManual(1);
    }
  } else if (digitalRead(4) == HIGH) {
    delay(100);
    if (mode == 4) {
      mode = 1;
    } else {
      mode += 1;
    }
    lcd.clear(); lcd.setCursor(0, 0); lcd.print("Mode"); lcd.setCursor(5, 0); lcd.print(mode);
    lcd.setCursor(0, 1);
    delay(500);
    cetak(String(frequency) , "Manual");
  }else if (digitalRead(3) == HIGH) {
    delay(500);
    backlighttogle();
  }
}

void gantist(int j) {
  i = i + j;
  if (i <= -1) {
    i = jmlst - 1;
  } else if (i >= jmlst) {
    i = 0;
  }
  setradio(i);
  frequency = atof(st[i][0]);
  cetak(st[i][0] , st[i][1]);
}

void gantistManual(float j) {
  frequency += j;
  radio.setFrequency(frequency);
  cetak(String(frequency) , "Mode "+String(mode));
}

void cetak(String stat, String namastat) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Name : ");
  lcd.print(namastat);
  lcd.setCursor(0, 1);
  lcd.print("Freq : ");
  lcd.print(stat);
  lcd.print(" MHz");
}

void backlighttogle() {
  if (backlightState) {
    lcd.noBacklight();
    backlightState = false;
  } else {
    lcd.backlight();
    backlightState = true;
  }
}

void setradio(int a){
  radio.setFrequency(atof(st[a][0]));   
}
