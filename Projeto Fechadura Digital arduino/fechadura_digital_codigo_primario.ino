
#include <Keypad.h>
#include <LiquidCrystal.h>


// PRINCIPAIS VARIÁVEIS 
int ledsenhacorreta = 15;
int ledsenhaincorreta = 16;

LiquidCrystal lcd(5, 4, 3, 2, 17, 18);

// KEYPAD:
const byte numRows = 4;
const byte numCols = 4;

char keys[numRows][numCols] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

byte rowPins[numRows] = {13, 12, 11, 10};
byte colPins[numCols] = {9, 8, 7, 6};

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, numRows, numCols);


// BIBLIOTECA DE MENSAGENS PARA O LCD:
const char* mensagens[] = {
  "DIGITE A SENHA",     
  "SENHA CORRETA!",     
  "DESBLOQUEANDO...",   
  "SENHA INCORRETA",    
  "Tentativas:",        
  "ALARME ATIVADO!"     
};


// VARIÁVEIS DA SENHA:
String senha = "1234";
String senhadigitada = "";
int limitetentativa = 3;


// FUNÇÃO PARA ESCREVER NO LCD:
void escreverMensagem(const char* mensagem) {
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(mensagem);
}

// FUNÇÃO PARA ENVIAR O CÓDIGO SERIAL:
void enviarAlerta(char* codigo) {   
  Serial.println(*codigo);          
}


// FUNÇÃO PARA REINICIAR TELA
void resetarTela() {
  escreverMensagem(mensagens[0]); 
  lcd.setCursor(0,1);
}



// SETUP
void setup() {
  pinMode(ledsenhacorreta, OUTPUT);
  pinMode(ledsenhaincorreta, OUTPUT);
  
  Serial.begin(9600);

  lcd.begin(16, 2);
  resetarTela();
}


// LOOP PRINCIPAL
void loop() {

  char tecla = keypad.getKey();


 
  // ESTABELECENDO  UMA CONDIÇÃO PARA APARECER OS NUMEROS DO KEYPAD NO LCD
  if (tecla >= '0' && tecla <= '9') {
    senhadigitada += tecla;
    lcd.print("*");
  }


  
  // CONFIRMAR SENHA (#)
  if (tecla == '#') {

    if (senha == senhadigitada) {

      digitalWrite(ledsenhacorreta, HIGH);
      digitalWrite(ledsenhaincorreta, LOW);

      char codigo = 'A';      
      enviarAlerta(&codigo);   

      escreverMensagem(mensagens[1]); 
      lcd.setCursor(0,1);
      lcd.print(mensagens[2]);        

      delay(2000);

      digitalWrite(ledsenhacorreta, LOW);
      digitalWrite(ledsenhaincorreta, LOW);
      senhadigitada = "";
      resetarTela();
    } 


    else {
      limitetentativa--;

      digitalWrite(ledsenhacorreta, LOW);
      digitalWrite(ledsenhaincorreta, HIGH);

      char codigo = 'B';
      enviarAlerta(&codigo);

      escreverMensagem(mensagens[3]); 
      delay(2000);

      digitalWrite(ledsenhacorreta, LOW);
      digitalWrite(ledsenhaincorreta, LOW);

      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print(mensagens[4]);   
      lcd.print(limitetentativa);

      delay(2000);

      senhadigitada = "";
      resetarTela();


      // ATIVAR ALARME
      if (limitetentativa <= 0) {
        escreverMensagem(mensagens[5]); 

        char codigo = 'C';
        enviarAlerta(&codigo);
      }
    }
  }



  // APAGAR SENHA (*)
  if (tecla == '*') {
    senhadigitada = "";
    resetarTela();
  }
}
