
int PinoVelocidade = 6; 
int Entrada1 = 7;       
int Entrada2 = 5;       
int buzzer = 4;


void acionarMotor(char *cmd) {
  if (*cmd == 'A') {
    analogWrite(PinoVelocidade, 5);
    digitalWrite(Entrada1, LOW);
    digitalWrite(Entrada2, HIGH);

    delay(3000);

    digitalWrite(Entrada1, LOW);
    digitalWrite(Entrada2, LOW);
    analogWrite(PinoVelocidade, 0);
  }
}



void beepSimples() {
  tone(buzzer, 1000);
  delay(1000);
  noTone(buzzer);
}


void sirene() {
  int notas[] = {300, 600, 900, 300, 600, 900};
  int total = sizeof(notas) / sizeof(notas[0]);

  for (int i = 0; i < total; i++) {
    tone(buzzer, notas[i]);
    delay(200);
  }
  noTone(buzzer);
}

// SETUP:
void setup() {
  Serial.begin(9600);

  pinMode(PinoVelocidade, OUTPUT);
  pinMode(Entrada1, OUTPUT);
  pinMode(Entrada2, OUTPUT);
  pinMode(buzzer, OUTPUT);
}



void loop() {

  if (Serial.available()) {
    char D = Serial.read();


    if (D == 'A') {
      acionarMotor(&D);
    }

    if (D == 'B') {
      beepSimples();
    }

    if (D == 'C') {
      sirene();
    }
  }
}
