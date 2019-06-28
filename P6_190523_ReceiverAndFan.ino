// Arduino-IRremote library will be added
#include <IRremote.h>
#include <IRremoteInt.h>
  
// You can declare the input pin for the signal output of the KY-022 here
int RECV_PIN = 7;

//int laserPin = 8;

// Arduino-IRremote library will be initialized
IRrecv irrecv(RECV_PIN);
decode_results results;
  //int i = 0;
  
void setup(){
  pinMode(9, OUTPUT);
  Serial.begin(9600);
  //pinMode(laserPin, OUTPUT);
  //digitalWrite(laserPin, HIGH);
  
  irrecv.enableIRIn(); // Infrared receiver will start
  
}
  
// main program loop
void loop() {
  // It will be checked if the receiver has gotten a signal.
  if (irrecv.decode(&results)) {
    //if (results.value == 0xFF02FD){
    //hash: D7E84B1B
    //real: FF02FD
    //At signal input, the received and decoded signal will show via serial console.
    Serial.println(results.value, HEX);
    //i= i+1;
    //Serial.println(i);
    digitalWrite(9, HIGH);
    delay(2000);
    digitalWrite(9, LOW);
    
    irrecv.resume();
    //} 
  
  }
  //if(i==5){
      
      //i= 0;//turn on /turn off LEDS or VEntilator
    }
