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
//  int LED2 = 3; //Trava Roda

//Valores para PiR
const int pinPiR = 6;        // value read from the port 6
//int outputValue = PIND;        // value output to the PWM (analog out)
//int outputValue;  
void setup()
{
  //Define os pinos dos leds/Rodas como Saída
  pinMode(LED1, OUTPUT);
//pinMode(LED2, OUTPUT); //     Porta NO do Relé para Sensor PiR interromper o carro quando alguém passar em sua frente.

  //Inicializa a serial
  Serial.begin(57600);
  
  //Inicializa a comunicacao
  radio.begin();
  //Entra em modo de recepcao
  radio.openReadingPipe(1,pipe);
  radio.startListening();

  //Define PIN PiR - STOP CAR TIMER

   //DDRD = DDRD & B10111111;              // sets pin 6 as input - PiR
   pinMode (pinPiR,INPUT);
   
  //DDRD = DDRD | B10000000;              //sets pin 7 as Output - LeD ou NO do Relé
 
 //Timer1.initialize(1000000);            // set a timer of length 100000 microseconds (or 0.1 sec - or 10Hz =>
 //Timer1.attachInterrupt( timerIsr );    //Interrompe a rotina timerIsr
}

void loop()
{
//delay (1000);
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
    
    
                          // } 
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
      
      //Programming Sensor PiR Para Travar as Rodas ao Passar Alguém na Frente do Carro

     

      }
    

  }
  else
  {
  Serial.println("Aguardando dados...");
  }

     
}
//void timerIsr()                         //Timer Baseado nos dados recebidos
//{
//  if (recebidos[0] == 1) {
//  digitalWrite (LED1,HIGH);
//}
//}
