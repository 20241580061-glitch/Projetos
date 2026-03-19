#include <LiquidCrystal.h>


#define LCD_RS 12
#define LCD_E  11
#define LCD_D4 5
#define LCD_D5 4
#define LCD_D6 3
#define LCD_D7 2
LiquidCrystal lcd(LCD_RS, LCD_E, LCD_D4, LCD_D5, LCD_D6, LCD_D7);


#define PIN_GAS A2
#define PIN_TMP36 A1


#define LED_VERDE A3
#define LED_AMARELO A4
#define LED_VERMELHO A5


#define SINAL_FUMACA 8 


#define BUZZER_TEMP 13
#define BUZZER_FUMACA 12


float lerTMP36() {
  int leitura = analogRead(PIN_TMP36);
  float voltagem = leitura * 5.0 / 1023.0;
  return (voltagem - 0.5) * 100.0; // °C
}

void setup() {
  pinMode(LED_VERDE, OUTPUT);
  pinMode(LED_AMARELO, OUTPUT);
  pinMode(LED_VERMELHO, OUTPUT);

  pinMode(SINAL_FUMACA, INPUT); 

  pinMode(BUZZER_TEMP, OUTPUT);
  pinMode(BUZZER_FUMACA, OUTPUT);

  lcd.begin(16, 2);
  lcd.print("Alarme Incendio");
  delay(1000);
}

void loop() {
  float temperatura = lerTMP36();

 
  if (temperatura <= 30) {
    digitalWrite(LED_VERDE, HIGH);
    digitalWrite(LED_AMARELO, LOW);
    digitalWrite(LED_VERMELHO, LOW);
    noTone(BUZZER_TEMP);
  } 
  else if (temperatura <= 50) {
    digitalWrite(LED_VERDE, LOW);
    digitalWrite(LED_AMARELO, HIGH);
    digitalWrite(LED_VERMELHO, LOW);
    noTone(BUZZER_TEMP);
  } 
  else {
    digitalWrite(LED_VERDE, LOW);
    digitalWrite(LED_AMARELO, LOW);
    digitalWrite(LED_VERMELHO, HIGH);
    tone(BUZZER_TEMP, 1000);
  }

  
  bool fumacaDetectada = digitalRead(SINAL_FUMACA) == HIGH;

 
  if (fumacaDetectada) {
    tone(BUZZER_FUMACA, 1500);
  } else {
    noTone(BUZZER_FUMACA);
  }

  
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.print(temperatura, 1);
  lcd.print((char)223);
  lcd.print("C");

  lcd.setCursor(0, 1);
  if (fumacaDetectada) {
    lcd.print("INCENDI DETECTAD");
  } else {
    lcd.print("NENHUM INCENDI");
  }

  delay(200);
}
