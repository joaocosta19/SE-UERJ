#include <TimerOne.h> //TIMER FUNCTION FOR PIR SENSOR
#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"

//Armazena os dados recebidos
int recebidos [1];

//Inicializa a placa nos pinos 9 (CE) e 10 (CS) do Arduino
RF24 radio(9,10);

//Define o endereco para comunicacao entre os modulos
const uint64_t pipe = 0xE14BC8F482LL;

//Define os pinos dos leds = Rodas
int LED1 = 5;  //Continua Andando

//Valores para PiR
//const int pinPiR = 6;        // value read from the port 6

void setup() {

//Define os pinos dos leds/Rodas como Saída
  pinMode(LED1, OUTPUT);

//Inicializa a serial
  Serial.begin(57600);

//Inicializa a comunicacao
  radio.begin();
  
//Entra em modo de recepcao
  radio.openReadingPipe(1,pipe);
  radio.startListening();

// initialize timer1 
  noInterrupts();           // disable all interrupts
  TCCR1A = 0;
  TCCR1B = 0;

  TCNT1 = 65536;            // preload timer 65536-16MHz/256/2Hz /34286
  TCCR1B |= (1 << CS12);    // 256 prescaler 
  TIMSK1 |= (1 << TOIE1);   // enable timer overflow interrupt
  //interrupts();             // enable all interrupts

}

//Timer1.initialize(1000000);            // set a timer of length 100000 microseconds (or 0.1 sec - or 10Hz =>
//Timer1.attachInterrupt( timerIsr );    //Interrompe a rotina timerIsr

void timerIsr()        // rotina de serviço de interrupção que envolve uma função definida pelo usuário fornecida pelo attachInterrupt
{
  TCNT1 = 65536;            // preload timer / 34286
  digitalWrite(LED1, HIGH);
}

void loop() {

  //Verifica se ha sinal de radio
  if (radio.available())
  {
    
    bool done = false;    
    while (!done)
    {
      radio.read(recebidos,1);                  //Havia erro de sintaxe retirado "done = radio.read(recebidos,1)"
      Serial.print("Dados recebidos : ");    
      Serial.println(recebidos[0]);
      
      //Se recebeu o numero 1, acende o LED1/IN do Relé para acionamento das Rodas
      if (recebidos[0] == 1)
      {
        delay(10);
        digitalWrite(LED1, HIGH);
      }
      else 
      {
        digitalWrite(LED1, LOW);
       }
       
      delay(100);
      
       }
   
  }
  else
  {
  Serial.println("Aguardando dados...");
  }
}
