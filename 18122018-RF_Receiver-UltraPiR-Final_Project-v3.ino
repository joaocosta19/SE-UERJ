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

//Define os pinos dos leds
int LED1 = 5;
//int LED2 = 3;

//Valores para PiR
//int sensorValue;        // value read from the port
//int outputValue;        // value output to the PWM (analog out)

void setup()
{
  //Define os pinos dos leds como saida
  pinMode(LED1, OUTPUT);
  //pinMode(LED2, OUTPUT);

  //Inicializa a serial
  Serial.begin(57600);
  
  //Inicializa a comunicacao
  radio.begin();
  //Entra em modo de recepcao
  radio.openReadingPipe(1,pipe);
  radio.startListening();

  //Define PIN PiR - STOP CAR TIMER

   // DDRD = DDRD & B10111111;              // sets pin 6 as input - PiR
  //DDRD = DDRD | B10000000;              //sets pin 7 as Output - LeD ou NO do Relé
 
 //Timer1.initialize(1000000000);            // set a timer of length 100000 microseconds (or 0.1 sec - or 10Hz =>
 //Timer1.attachInterrupt( timerIsr );    //Interrompe a rotina timerIsr
}

void loop()
{
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
//Programming Sensor PiR Para Travar as Rodas ao Passar Alguém na Frente do Carro

      //if(PIND = PIND & B01000000 ){           //SE A LEITURA DO PINO 6 FOR IGUAL A HIGH, FAZ                           //if(PIND = PIND & B01000000){ 
      //(PORTD = B00100000);              //ACENDE O LED/Bloqueio dos Atuadores (Rodas) através de pulso no IN do Relé  // ;        
      // }else{
      // (PORTD = B00000000); 
      //}   
      //Se recebeu o numero 2, acende o LED2
      //if (recebidos[0] == 2)
      //{
      //delay(10);
      //digitalWrite(LED2, HIGH);
      //}
      //else 
      //{
        //digitalWrite(LED2, LOW);
      //}
      delay(100);
    }
    
  }
  else
  {
  Serial.println("Aguardando dados...");
  }
}
//void timerIsr()
//{
//outputValue=map(PIND, 0, 1023, 0, 255);
//Serial.println(outputValue);
//}
