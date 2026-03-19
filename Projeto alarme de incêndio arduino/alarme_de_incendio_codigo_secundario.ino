#include <EEPROM.h>


#define MQ_PIN A0
#define LED_VERDE A1
#define LED_VERMELHO 7
#define PIEZO 12
#define PIN_SAIDA_ARDU_PRINCIPAL 6 
#define PIN_INTERRUPTOR 2          


int limiteFumaca;         
unsigned long ultimoTempo = 0;
const unsigned long intervalo = 200; 

volatile bool emergencia = false; 


void ISR_emergencia() {
  emergencia = true; 
}

void setup() {
  pinMode(LED_VERDE, OUTPUT);
  pinMode(LED_VERMELHO, OUTPUT);
  pinMode(PIEZO, OUTPUT);
  pinMode(PIN_SAIDA_ARDU_PRINCIPAL, OUTPUT);

  pinMode(PIN_INTERRUPTOR, INPUT_PULLUP); 

  
  Serial.begin(9600);

  
  attachInterrupt(digitalPinToInterrupt(PIN_INTERRUPTOR), ISR_emergencia, FALLING);

  
  limiteFumaca = EEPROM.read(0);
  if (limiteFumaca < 100 || limiteFumaca > 900) {
    limiteFumaca = 700; 
  }

  Serial.print("Limite carregado: ");
  Serial.println(limiteFumaca);
}

void loop() {
  unsigned long agora = millis();

  
  if (agora - ultimoTempo >= intervalo) {
    ultimoTempo = agora;

    int valor = analogRead(MQ_PIN);
    Serial.print("Valor sensor: ");
    Serial.println(valor);

    
    if (!emergencia) {
      if (valor > limiteFumaca) {
       
        digitalWrite(LED_VERMELHO, HIGH);
        digitalWrite(LED_VERDE, LOW);
        digitalWrite(PIEZO, HIGH);
        digitalWrite(PIN_SAIDA_ARDU_PRINCIPAL, HIGH);
      } else {
       
        digitalWrite(LED_VERMELHO, LOW);
        digitalWrite(LED_VERDE, HIGH);
        digitalWrite(PIEZO, LOW);
        digitalWrite(PIN_SAIDA_ARDU_PRINCIPAL, LOW);
      }
    }
   
    else {
      digitalWrite(LED_VERMELHO, HIGH);
      digitalWrite(LED_VERDE, LOW);
      digitalWrite(PIEZO, HIGH);
      digitalWrite(PIN_SAIDA_ARDU_PRINCIPAL, HIGH);

      Serial.println(" INTERRUPÇÃO: EMERGÊNCIA ATIVADA ");
      emergencia = false; 
    }
  }
}
