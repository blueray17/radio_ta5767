#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <TEA5767N.h>

TEA5767N radio = TEA5767N();
LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27, 16, 2);
int jmlst = 40,  i = 11;
String st[40] = {
  "87.70 -HardRock",
  "88.10 -SouthEast",
  //"88.50 -MoraFM",
  "88.90 -Auto",
  "89.30 -ElShinta",
  "89.70 -Global",
  "90.50 -Cakra",
  "90.90 -X-Channel",
  "91.30 -Trijaya",//??
  "91.70 -Nyimas",
  "92.10 -SuaraIndh",
  "92.50 -Maestro",
//  "93.30 -Sonora",
  "93.70 -Paramuda",
  "94.40 -DeltaFM",
  "94.80 -FitFM",
  "95.20 -Bandung",
  "95.60 -B-Radio",
  "96.40 -Bobotoh",
  "96.80 -Eight",
  "97.20 -NewShinta",
  "97.60 -RRI Pro1",
  "98.00 -MayaFM",
  "98.40 -Prambors",
  "98.80 -Raka",
  "99.20 -Mom&Kids", //
  "100.00-99ers",
  "100.40-KLCBS",
  "101.10-MGT",
  "101.50-Dahlia",
  "101,90-Cosmo",
  "102.30-RaseFM",
  "102.70-MQFM",
  "103.10-OzRadio",
  //"103.90-UNIKOM",
  "104.30-RodjaFM",
  "104.70-RamaFM",
  "105.10-I-Radio",
  "105.50-Garuda",
  "105.90-Ardan",
  "106.30-UrbanFM",
  //"106.70-Mara FM",
  "107.10-K-lite",
  "107.50-PRFM"
  };


float frequency = 0;
bool backlightState = true;
int mode=1;

void setup() {
  lcd.init();
  lcd.backlight();
  setRadio(st[i].substring(0,5).toFloat());
  frequency = st[i].substring(0,5).toFloat();
  cetak(st[i].substring(0,6), radio , st[i].substring(7,16));
}

void loop() {
  if (digitalRead(7) == HIGH) {
    gantist(1);
  } else if (digitalRead(6) == HIGH) {
    gantist(-1);
  } else if (digitalRead(5) == HIGH) {
    if (mode == 5) {
      mode = 1;
    } else {
      mode += 1;
    }
    lcd.clear(); lcd.setCursor(0, 0); lcd.print("Mode"); lcd.setCursor(5, 0); lcd.print(mode);
    lcd.setCursor(0, 1);
    delay(1500);
    cetak(String(frequency), radio , "xxxxxxx");
  } else if (digitalRead(4) == HIGH) {
    
    if (mode == 1) {
      gantist(5);
    } else if (mode == 2) {
      gantistManual(0.1);
    } else if (mode == 3) {
      gantistManual(1);
    } else if (mode == 4) {
      gantistManual(-0.1);
    } else if (mode == 5) {
      gantistManual(-1);
    }
  } else if (digitalRead(3) == HIGH) {
    backlighttogle();
  }
  refStatStrength();
}

void gantist(int j) {
  i = i + j;
  if (i == -1) {
    i = jmlst - 1;
  } else if (i >= jmlst) {
    i = 0;
  }
  setRadio(st[i].substring(0,5).toFloat());
  frequency = st[i].substring(0,5).toFloat();
  cetak(st[i].substring(0,6), radio , st[i].substring(7,16));
}

void gantistManual(float j) {
  frequency += j;
  setRadio(frequency);
  cetak(String(frequency), radio , "Manual");
}

void cetak(String stat, TEA5767N radio, String namastat) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(namastat);
  lcd.setCursor(0, 1);
  lcd.print(stat);
  lcd.setCursor(7, 1);
  lcd.print("MHz");
  lcd.setCursor(15, 1);
  lcd.print("%");
  refStatStrength();
}

void refStatStrength() {
  lcd.setCursor(10, 0);
  if (radio.isStereo() == 1) {
    lcd.print("Stereo");
  } else {
    lcd.print(" Mono ");
  }
  lcd.setCursor(12, 1);
  lcd.print(((radio.getSignalLevel() * 100) / 15) - 1);
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

void setRadio(float st) {
  radio.selectFrequency(st);
//  radio.setMonoReception();
//  radio.setStereoNoiseCancellingOn();
}
