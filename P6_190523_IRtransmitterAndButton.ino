
#include <IRremote.h> 
#include <IRremote.h>
#include <IRremoteInt.h>  
int RECV_PIN = 7;
IRsend irsend;
IRrecv irrecv(RECV_PIN);
decode_results results;
// constants won't change. They're used here to set pin numbers:
const int buttonPin = 2;  
// the number of the pushbutton pin
//const int ledPin =  13;      // the number of the LED pin

// variables will change:
int buttonState = 0;         // variable for reading the pushbutton status


void setup() {
  // initialize the LED pin as an output:
  //pinMode(ledPin, OUTPUT);
  // initialize the pushbutton pin as an input:
  pinMode(buttonPin, INPUT);
  Serial.begin(9600);
  irrecv.enableIRIn();

}

void loop() {
  // read the state of the pushbutton value:
  buttonState = digitalRead(buttonPin);
  
  if (buttonState == HIGH) {
    irsend.sendNEC(0xFF02FD, 32);
    delay(1000);
  } else {
      //irsend.sendNEC(0xFF02FD, 32);
      //delay(1000);
  }
}
