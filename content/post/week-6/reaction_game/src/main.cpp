#include <Arduino.h>

#define LED1 D0
#define LED2 D6
#define LED3 D7
#define BTN D1

bool led1State = HIGH; // HIGH, true and 1 mean the same
bool led2State = HIGH;
bool led3State = HIGH;

int targetLED = 0;

bool btnState = HIGH; // button is high as it is connected to 3.3V via a pull-up resistor

void setup() {
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(BTN, INPUT);

  // set initial state of LEDs
  digitalWrite(LED1, led1State);
  digitalWrite(LED3, led2State);
  digitalWrite(LED2, led3State);
}

void loop() {
  bool btnReading = digitalRead(BTN);

  // we want to do something only if the reading and the state are different
  // in this case they are the same and we exit the loop immediatly
  if(btnReading == btnState){
    return; 
  }
 
  if(btnReading == LOW){ // LOW means button is pressed on Tarantino
    btnState = LOW;
    targetLED++;

    switch(targetLED % 3){
      case 0: 
        led1State = LOW;
        led2State = LOW;
        led3State = HIGH;
        break;
      case 1: 
        led1State = HIGH;
        led2State = LOW;
        led3State = LOW;
        break;
      case 2: 
        led1State = LOW;
        led2State = HIGH;
        led3State = LOW;
        break;
    }
  }else{
    btnState = HIGH;
  }

  digitalWrite(LED1, led1State);
  digitalWrite(LED2, led2State);
  digitalWrite(LED3, led3State);
  delay(10);
}