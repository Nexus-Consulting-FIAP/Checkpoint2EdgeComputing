#include <LiquidCrystal_I2C.h>
#include "DHT.h"
#include <RTClib.h>
#include <EEPROM.h>


#define I2C_ADDR    0x27
#define LCD_COLUMNS 20
#define LCD_LINES   4

LiquidCrystal_I2C lcd(I2C_ADDR, LCD_COLUMNS, LCD_LINES);

const short int red = 11;
const short int green = 10;
const short int blue = 9;

const short int buzzer = 6;

const int ldr = A3;

const int dhtPin = 5;
DHT dht(dhtPin, DHT11); //MUDA PRA DHT11 DEPOIS!!!

#define UTC_OFFSET -3
RTC_DS1307 RTC;

const int analogClickPin = 4;
const int analogVertPin = A1;
const int analogHorzPin = A2;

const int maxRecords = 100;
const int recordSize = 10; // Tamanho de cada registro em bytes
int endrInicial = 0;
int endrFinal = maxRecords * recordSize;
int endrAtual = 0;


int conf_inicial = 0;
int lastInput = 9;
float luminosidade = 0;
const float temperatura = 13.0f;
const int umidade = 70;
int ultimo_min_reg = -1;

//Abstração dos dados dos módulos
void ledChangeColor(short int value) {
  switch (value) {
    //ANTES DE MUDAR DE COR, USE ledChangeColor(4) para resetar a cor, ai mude
    case 1: //red
      digitalWrite(red, 1023);
      digitalWrite(green, 0);
      digitalWrite(blue, 0);
      break;
    case 2: //yellow
      digitalWrite(red, 1023);
      digitalWrite(green, 1023);
      digitalWrite(blue, 0);
      break;
    case 3: //green
      digitalWrite(red, 0);
      digitalWrite(green, 1023);
      digitalWrite(blue, 0);
      break;
    case 4: //turn off
      digitalWrite(red, 0);
      digitalWrite(green, 0);
      digitalWrite(blue, 0);
      break;
  }
}

int ldrNowValue() {
  return map(analogRead(ldr), 0, 1023, 100, 0);
}

int analogXaxis() {
  return map(analogRead(analogHorzPin), 0, 1023, 100, -100);
}

int analogYaxis() {
  return map(analogRead(analogVertPin), 0, 1023, -100, 100);
}
//Funções do sistema

//ANIMAÇÃO INICIAL
void animInicio1() {
  byte fullBlock[] = {  // █
    B11111,
    B11111,
    B11111,
    B11111,
    B11111,
    B11111,
    B11111,
    B11111
  }; lcd.createChar(0, fullBlock);

  lcd.clear();
  for (int y = 0; y < 2; y++) {
    for (int x = 0; x < 16; x++) {
      lcd.setCursor(x, y);
      lcd.write((uint8_t)0);
      delay(30);
    }
  }
}
void animInicio2() {
  byte fullBlock[] = {  // █
    B11111,
    B11111,
    B11111,
    B11111,
    B11111,
    B11111,
    B11111,
    B11111
  }; lcd.createChar(0, fullBlock);
  byte vazio[8] = { //
    B00000,
    B00000,
    B00000,
    B00000,
    B00000,
    B00000,
    B00000,
    B00000
  }; lcd.createChar(1, vazio);
  byte halfBlock[8] = {  // Bloco cheio na esquerda
    B11000,
    B11000,
    B11000,
    B11000,
    B11000,
    B11000,
    B11000,
    B11000
  }; lcd.createChar(2, halfBlock);
  byte halfBlock2[8] = {  // Bloco cheio na esquerda
    B00011,
    B00011,
    B00011,
    B00011,
    B00011,
    B00011,
    B00011,
    B00011
  }; lcd.createChar(3, halfBlock2);
  byte diag[8] = {  // \ (diagonal do "N")
    B11000,
    B01100,
    B01100,
    B00110,
    B00110,
    B00011,
    B00011,
    B00001
  }; lcd.createChar(4, diag);
  byte halfDiagRight[8] = {  // Diagonal com bloco cheio na esquerda
    B11000,
    B11100,
    B11100,
    B11110,
    B11110,
    B11011,
    B11011,
    B11001
  }; lcd.createChar(5, halfDiagRight);
  byte halfDiagLeft[8] = {  // Diagonal com bloco cheio na direita
    B11011,
    B01111,
    B01111,
    B00111,
    B00111,
    B00011,
    B00011,
    B00011
  }; lcd.createChar(6, halfDiagLeft);
  for (int x = 0; x <= 8; x++) {
    if (x < 7) {
      lcd.setCursor(x, 0); lcd.write((uint8_t)3);
      lcd.setCursor(x, 1); lcd.write((uint8_t)3);
      lcd.setCursor(15 - x, 0); lcd.write((uint8_t)2);
      lcd.setCursor(15 - x, 1); lcd.write((uint8_t)2);

      lcd.setCursor(x - 1, 0); lcd.write((uint8_t)1);
      lcd.setCursor(x - 1, 1); lcd.write((uint8_t)1);
      lcd.setCursor(16 - x, 0); lcd.write((uint8_t)1);
      lcd.setCursor(16 - x, 1); lcd.write((uint8_t)1);
    }
    if (x == 6) {
      lcd.setCursor(x, 0); lcd.write((uint8_t)3);
      lcd.setCursor(x, 1); lcd.write((uint8_t)3);
    }
    if (x == 7) {
      lcd.setCursor(x, 0); lcd.write((uint8_t)6);
      lcd.setCursor(x, 1); lcd.write((uint8_t)3);
      lcd.setCursor(15 - x, 1); lcd.write((uint8_t)5);
      lcd.setCursor(15 - x, 0); lcd.write((uint8_t)2);
    }
    if (x == 8) {
      lcd.setCursor(x, 0); lcd.write((uint8_t)1);
      lcd.setCursor(x, 1); lcd.write((uint8_t)4);
      lcd.setCursor(15 - x, 1); lcd.write((uint8_t)1);
      lcd.setCursor(15 - x, 0); lcd.write((uint8_t)4);
    }
    delay(75);
  }
}
void animInicio3() {
  byte fullBlock[] = {  // █
    B11111,
    B11111,
    B11111,
    B11111,
    B11111,
    B11111,
    B11111,
    B11111
  }; lcd.createChar(0, fullBlock);
  byte vazio[8] = { //
    B00000,
    B00000,
    B00000,
    B00000,
    B00000,
    B00000,
    B00000,
    B00000
  }; lcd.createChar(1, vazio);
  byte halfBlock[8] = {  // Bloco cheio na esquerda
    B11000,
    B11000,
    B11000,
    B11000,
    B11000,
    B11000,
    B11000,
    B11000
  }; lcd.createChar(2, halfBlock);
  byte halfBlock2[8] = {  // Bloco cheio na esquerda
    B00011,
    B00011,
    B00011,
    B00011,
    B00011,
    B00011,
    B00011,
    B00011
  }; lcd.createChar(3, halfBlock2);
  byte halfDiagLeft[8] = {  // Diagonal com bloco cheio na direita
    B11011,
    B01111,
    B01111,
    B00111,
    B00111,
    B00011,
    B00011,
    B00011
  }; lcd.createChar(6, halfDiagLeft);
  for (int x = 0; x < 18; x++) {
    lcd.setCursor(15 - x, 0); lcd.write((uint8_t)3);
    lcd.setCursor(15 - x, 1); lcd.write((uint8_t)3);
    lcd.setCursor(16 - x, 0); lcd.write((uint8_t)2);
    lcd.setCursor(16 - x, 1); lcd.write((uint8_t)2);
    lcd.setCursor(17 - x, 0); lcd.write((uint8_t)1);
    lcd.setCursor(17 - x, 1); lcd.write((uint8_t)1);

    if (x == 6) {
      lcd.setCursor(15 - x, 0); lcd.write((uint8_t)0);
      lcd.setCursor(15 - x, 1); lcd.write((uint8_t)0);
    }
    if (x == 7) {
      lcd.setCursor(15 - x, 1); lcd.write((uint8_t)6);
    }
    if (x == 8) {
      lcd.setCursor(15 - x, 0); lcd.write((uint8_t)6);
    }
    delay(25);
  }
}

void msgInicial() {
  lcd.setCursor(0, 0);
  lcd.print("LIGHT ON, THEN");
  lcd.setCursor(0, 1);
  lcd.print("ANALOG CLICK!");
}

int analogInput() {
  if (analogXaxis() > 50) { //Direita
    return 1;
  }
  if (analogXaxis() < -50) { //Esquerda
    return 2;
  }
  if (analogYaxis() > 50) { //Cima
    return 3;
  }
  if (analogYaxis() < -50) { //Baixo
    return 4;
  }
  if (digitalRead(analogClickPin) == LOW) { //Click
    return 5;
  }
  return 0;
}

void msgMenu() {
  byte arrowUp[] = {
    B00000,
    B00100,
    B01110,
    B11111,
    B00100,
    B00100,
    B00100,
    B00000,
  }; lcd.createChar(0, arrowUp);
  byte arrowLeft[] = {
    B00000,
    B00000,
    B00100,
    B01100,
    B11111,
    B01100,
    B00100,
    B00000,
  }; lcd.createChar(1, arrowLeft);
  byte arrowRight[] = {
    B00000,
    B00000,
    B00100,
    B00110,
    B11111,
    B00110,
    B00100,
    B00000,
  }; lcd.createChar(2, arrowRight);
  byte center[] = {
    B00000,
    B00100,
    B01110,
    B11111,
    B11111,
    B01110,
    B00100,
    B00000,
  }; lcd.createChar(3, center);
  byte temperature[] = {
    B00100,
    B01010,
    B01010,
    B01010,
    B01010,
    B11111,
    B01110,
    B00000,
  }; lcd.createChar(4, temperature);
  byte luminosity[] = {
    B00100,
    B10101,
    B01110,
    B11111,
    B01110,
    B10101,
    B00100,
    B00000,
  }; lcd.createChar(5, luminosity);
  byte humidity[] = {
    B00100,
    B00100,
    B01110,
    B01110,
    B11111,
    B11111,
    B01110,
    B00000,
  }; lcd.createChar(6, humidity);
  byte backlog[] = {
    B11100,
    B11110,
    B10001,
    B11111,
    B10001,
    B11111,
    B10001,
    B11111,
  }; lcd.createChar(7, backlog);

  lcd.setCursor(2, 0);
  lcd.write((uint8_t)4);
  delay(20);
  lcd.write((uint8_t)1);
  delay(20);
  lcd.setCursor(5, 0);
  lcd.write((uint8_t)5);
  delay(20);
  lcd.write((uint8_t)0);
  delay(20);
  lcd.setCursor(8, 0);
  lcd.write((uint8_t)6);
  delay(20);
  lcd.write((uint8_t)2);
  delay(20);
  lcd.setCursor(12, 0);
  lcd.write((uint8_t)7);
  delay(20);
  lcd.write((uint8_t)3);
  delay(20);

  while (analogInput() == 0) {
    detectarProblemas();
    //TEMPERATURA
    float temp = dht.readTemperature();
    if (temp < (temperatura - 3.0f) || temp > (temperatura + 3.0f)) {
      lcd.setCursor(2, 0);
      lcd.print(" ");
      delay(300);
      lcd.setCursor(2, 0);
      lcd.write((uint8_t)4);
      delay(300);
    } else {
      lcd.setCursor(2, 0);
      lcd.write((uint8_t)4);
      delay(300);
    }

    //LUMINOSIDADE
    int luz = ldrNowValue();
    if (luz > luminosidade && luz > (luminosidade / 2)) {
      lcd.setCursor(5, 0);
      lcd.print(" ");
      delay(300);
      lcd.setCursor(5, 0);
      lcd.write((uint8_t)5);
      delay(300);
    } else {
      lcd.setCursor(5, 0);
      lcd.write((uint8_t)5);
      delay(300);
    }

    //UMIDADE
    float umi = dht.readHumidity();
    if (umi > (umidade + 10) || umi < (umidade - 10)) {
      lcd.setCursor(8, 0);
      lcd.print(" ");
      delay(300);
      lcd.setCursor(8, 0);
      lcd.write((uint8_t)6);
      delay(300);
    } else {
      lcd.setCursor(8, 0);
      lcd.write((uint8_t)6);
      delay(300);
    }
  }
}

void mostrarTemperaturaLcd() {
  int tempAnterior = -1000;
  String statusAnterior = "";

  while (analogInput() == 2) {
    detectarProblemas ();
    float tempAtual = dht.readTemperature();
    String statusAtual;

    if (tempAtual > (temperatura + 3.0f)) {
      statusAtual = "ALTA!";
    } else if (tempAtual < (temperatura - 3.0f)) {
      statusAtual = "BAIXA!";
    } else {
      statusAtual = "OK.";
    }

    lcd.setCursor(0, 0);
    lcd.print("Temp. ");
    lcd.setCursor(6, 0);
    lcd.setCursor(6, 0);
    lcd.print(statusAtual);
    lcd.print("     ");

    lcd.setCursor(0, 1);
    lcd.print("Temp = ");

    lcd.setCursor(7, 1);
    lcd.setCursor(7, 1);
    lcd.print(tempAtual, 1);
    lcd.print("C");
    lcd.print("     ");
  }
}

void mostrarUmidadeLcd() {
  while (analogInput() == 1) {
    detectarProblemas ();
    int umidadeAtual = dht.readHumidity();

    String statusAtual;
    if (umidadeAtual > (umidade + 10)) {
      statusAtual = "ALTA!";
    } else if (umidadeAtual < (umidade - 10)) {
      statusAtual = "BAIXA!";
    } else {
      statusAtual = "OK.";
    }

    lcd.setCursor(0, 0);
    lcd.print("Umidade ");
    lcd.setCursor(8, 0);
    lcd.print(statusAtual);
    lcd.print("       ");

    lcd.setCursor(0, 1);
    lcd.print("Umidade = ");
    lcd.setCursor(10, 1);

    lcd.print(umidadeAtual);
    lcd.print("%");
    lcd.print(" ");
  }
}

void mostrarLuminosidadeLcd() {
  while (analogInput() == 3) {
    detectarProblemas ();
    int luzAtual = ldrNowValue();

    String statusAtual;
    if (luzAtual > luminosidade) {
      statusAtual = "MUITO CLARO!";
    } else if (luzAtual > (luminosidade / 2)) {
      statusAtual = "CLARO";
    } else {
      statusAtual = "ESCURO";
    }

    lcd.setCursor(0, 0);
    lcd.print("Luminosidade ");

    lcd.setCursor(0, 1);
    lcd.print(statusAtual);
    lcd.print("           ");
    delay(300);
  }
}


int temperaturaStatus() {
  float tempAtual = dht.readTemperature();
  return tempAtual < (temperatura - 3.0f) || tempAtual > (temperatura + 3.0f);
}

int umidadeStatus() {
  return dht.readHumidity() < (umidade - 10) || dht.readHumidity() > (umidade + 10);
}

int luminosidadeVermelhoStatus() {
  return ldrNowValue() > luminosidade;
}

int luminosidadeAmareloStatus() {
  return ldrNowValue() <= luminosidade && ldrNowValue() > luminosidade / 2;
}

void gravarEeprom(long tempounix, int luminosidade, float temperatura, float umidade) {
  Serial.println("Gravando problema na vinheria...");
  EEPROM.put(endrAtual, tempounix);
  EEPROM.put(endrAtual + 4, luminosidade);
  EEPROM.put(endrAtual + 6, (int)temperatura);
  EEPROM.put(endrAtual + 8, (int)umidade);
  proximoEndereco();
}

void proximoEndereco() {
  endrAtual += recordSize;
  if (endrAtual == endrFinal) {
    endrAtual = 0;
  }
}

void mostrarEepromLcd() {
  int index = 0;
  int lastIndex = -1;
  long tempo;
  int lumi, temp, umi;

  lcd.setCursor(0, 0);
  lcd.print("Entering log...");
  delay(1500);
  lcd.clear();

  while (1 == 1) {
    if (index != lastIndex) {
      EEPROM.get(index, tempo);
      EEPROM.get(index + 4, lumi);
      EEPROM.get(index + 6, temp);
      EEPROM.get(index + 8, umi);
      lcd.clear();
      lcd.setCursor(0, 0);

      if (lumi == -1 || temp == -1 || umi == -1) {
        lcd.print("Sem dados");
      } else {
        lcd.clear();
        mostrarDataNoLcd(tempo);
        lcd.setCursor(0, 1);
        lcd.print("L");
        lcd.setCursor(1,1);
        lcd.print(lumi);
        lcd.setCursor(6, 1);
        lcd.print("T");
        lcd.setCursor(7, 1);
        lcd.print((int)temp);
        lcd.print("             ");
        lcd.setCursor(11, 1);
        lcd.print("U");
        lcd.setCursor(12, 1);
        lcd.print((int)umi);
        lcd.print("             ");
      }
      lastIndex = index;

    }
    if (analogInput() == 5) {
      break;
    }
    if (analogInput() == 1) {
      delay(100);
      index = index + recordSize;
    }
    if (analogInput() == 2) {
      delay(100);
      index = index - recordSize;
    }
    if(index == -7){
      index = 700;
    }
    if(index == 707) {
      index = 0;
    }
  }
  //MUDAR INDEX E ANDAR 7 BYTES.
}

void mostrarDataNoLcd(long tempounix) {
  DateTime adjustedTime = DateTime(tempounix);

  lcd.print(adjustedTime.day());
  lcd.print("/");
  lcd.print(adjustedTime.month());
  lcd.print(" ");
  lcd.print(adjustedTime.hour() < 10 ? "0" : "");
  lcd.print(adjustedTime.hour());
  lcd.print(":");
  lcd.print(adjustedTime.minute() < 10 ? "0" : "");
  lcd.print(adjustedTime.minute());
  lcd.print(":");
  lcd.print(adjustedTime.second() < 10 ? "0" : "");
  lcd.print(adjustedTime.second());
}

void detectarProblemas () {
  DateTime now = RTC.now();
  int offsetSegundos = UTC_OFFSET * 3600;
  DateTime adjustedTime = DateTime(now.unixtime() + offsetSegundos);
  if (temperaturaStatus() || umidadeStatus() || luminosidadeVermelhoStatus()) {
    ledChangeColor(4);
    ledChangeColor(1);
    tone(buzzer, 131, 1000);
    if (ultimo_min_reg != adjustedTime.minute()) {
      gravarEeprom(adjustedTime.unixtime(), ldrNowValue(), dht.readTemperature(), dht.readHumidity());
      ultimo_min_reg = adjustedTime.minute();
    }
  } else if (luminosidadeAmareloStatus()) {
    ledChangeColor(4);
    ledChangeColor(2);
  } else {
    ledChangeColor(4);
    ledChangeColor(3);
  }
}

void setup() {
  Serial.begin(9600);

  //led
  pinMode(red, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(blue, OUTPUT);

  //buzzer
  pinMode(buzzer, OUTPUT);

  //DHT
  dht.begin();

  //RTC
  RTC.begin();
  RTC.adjust(DateTime((__DATE__), (__TIME__)));

  //ANALOG
  pinMode(analogClickPin, INPUT_PULLUP);
  pinMode(analogVertPin, INPUT);
  pinMode(analogHorzPin, INPUT);

  //EEPROM
  EEPROM.begin();

  lcd.init();
  lcd.backlight();

  animInicio1(); delay(500);
  animInicio2(); delay(500);
  animInicio3(); delay(500);
  delay(1500);
}

void loop() {
  if (conf_inicial == 0) {
    msgInicial();
    if (analogInput() == 5) {
      int soma = 0;

      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Wait...");

      for (int i = 0; i < 10; i++) {
        soma = soma + ldrNowValue();
        delay(1000); //VOLTA AQUI PRA 1000!!!

      }
      luminosidade = (soma / 10) * 0.9;

      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Done!");
      delay(3000);

      conf_inicial = 1;
    }
  }
  if (conf_inicial == 1) {
    if (lastInput != analogInput()) {
      lcd.clear();
      switch (analogInput()) {
        case 0:
          lastInput = 0;
          msgMenu();
          break;
        case 1:
          mostrarUmidadeLcd();
          lastInput = 1;
          break;
        case 2:
          mostrarTemperaturaLcd();
          lastInput = 2;
          break;
        case 3:
          mostrarLuminosidadeLcd();
          lastInput = 3;
          break;
        case 5:
          mostrarEepromLcd();
          lastInput = 5;
          break;
      }
    }
    lcd.clear();
  }
}
