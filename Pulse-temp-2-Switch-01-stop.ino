
#define pinLedVm 13
#define pinBotao1 2
#define pinBotao 7

boolean estadoBotao = true;
boolean estAntBotao = true;
boolean estadoPisca = false;

unsigned long lastTime;
unsigned long speeding = 500;         //Velocidade do Pisca

void setup() {

  lastTime = millis();
  
  pinMode(pinLedVm, OUTPUT);
  pinMode(pinBotao, INPUT_PULLUP);
  pinMode(pinBotao1, INPUT_PULLUP);
}

void loop() {

  if(    !(digitalRead(pinBotao))   ){
    // Diminui a frequencia do Pisca
    speeding = speeding - 1;
  }
  if(    !(digitalRead(pinBotao1))   ){
    // Aumenta a frequencia do Pisca
    speeding = speeding + 1;
  }
  if(   !(digitalRead(pinBotao)) && !(digitalRead(pinBotao1))   ){
    // Parar pisca em menos de 500ms Pressionando botao1&2
    speeding;
    digitalWrite( pinLedVm, HIGH);
  }
  if ( (millis() - lastTime) >= speeding) {
      estadoPisca = !estadoPisca;
      digitalWrite( pinLedVm, estadoPisca);
      lastTime=millis();
  }
 

  delay(10);
}
