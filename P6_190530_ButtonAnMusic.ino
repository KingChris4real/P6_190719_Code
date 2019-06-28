#include <IRremote.h>  
#include "SD.h"
#define SD_ChipSelectPin 4
#include "TMRpcm.h"
#include "SPI.h"   
TMRpcm tmrpcm;
IRsend irsend;
// constants won't change. They're used here to set pin numbers:
const int buttonPin = 2;     // the number of the pushbutton pin
//const int ledPin =  13;      // the number of the LED pin

// variables will change:
int buttonState = 0;         // variable for reading the pushbutton status

void setup() {
  pinMode(buttonPin, INPUT);
  tmrpcm.speakerPin = 9;
  Serial.begin(9600);
  if (!SD.begin(SD_ChipSelectPin)) {
  Serial.println("SD fail");
  return;
}
}

void loop() {
  // read the state of the pushbutton value:
  buttonState = digitalRead(buttonPin);

  // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
  if (buttonState == HIGH) {
      //tmrpcm.setVolume(5);
      //tmrpcm.play("6.wav"); 
    // turn LED on:
    //digitalWrite(ledPin, HIGH);
     //irsend.sendNEC(0xFF02FD, 32);   //The code 'FF02FD' is the received infrared code  
                  //if you need to use other functions, please 
                                  //use the receiving tube read the correct encoding value.  
    //delay(1000);  
  } else {
     tmrpcm.setVolume(5);
     tmrpcm.play("6.wav"); 
    //irsend.sendNEC(0xFF02FD, 32);
    //tmrpcm.disable();
    // turn LED off:
    //digitalWrite(ledPin, LOW);
  }
}
