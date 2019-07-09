//Code teilweise aus FastLed Fire Example übernommen und für unsere Zwecke angepasst


#include <FastLED.h>
#include <IRremote.h>
#include <IRremoteInt.h>

#define LED_PIN     5
#define COLOR_ORDER GRB
#define CHIPSET     WS2812B
#define NUM_LEDS    150


#define BRIGHTNESS 245
#define FRAMES_PER_SECOND 60
int m = 0;
int RECV_PIN = 7;
int NUM_LED=150;
//int laserPin = 8;

// Arduino-IRremote library will be initialized
IRrecv irrecv(RECV_PIN);
decode_results results;

bool gReverseDirection = false;

CRGB leds[NUM_LEDS];


void setup() {
  delay(3000); // sanity delay
  FastLED.addLeds<CHIPSET, LED_PIN, COLOR_ORDER>(leds, NUM_LED).setCorrection( TypicalLEDStrip );
  FastLED.setBrightness( BRIGHTNESS );
  irrecv.enableIRIn();
  Serial.begin(9600);
}

void loop()
{
  // Add entropy to random number generator; we use a lot of it.
  // random16_add_entropy( random());

  Fire2012(); // run simulation frame
  
  FastLED.show(); // display this frame
  FastLED.delay(1000 / FRAMES_PER_SECOND);
}


// Fire2012 by Mark Kriegsman, July 2012
// as part of "Five Elements" shown here: http://youtu.be/knWiGsmgycY
//// 
// This basic one-dimensional 'fire' simulation works roughly as follows:
// There's a underlying array of 'heat' cells, that model the temperature
// at each point along the line.  Every cycle through the simulation, 
// four steps are performed:
//  1) All cells cool down a little bit, losing heat to the air
//  2) The heat from each cell drifts 'up' and diffuses a little
//  3) Sometimes randomly new 'sparks' of heat are added at the bottom
//  4) The heat from each cell is rendered as a color into the leds array
//     The heat-to-color mapping uses a black-body radiation approximation.
//
// Temperature is in arbitrary units from 0 (cold black) to 255 (white hot).
//
// This simulation scales it self a bit depending on NUM_LEDS; it should look
// "OK" on anywhere from 20 to 100 LEDs without too much tweaking. 
//
// I recommend running this simulation at anywhere from 30-100 frames per second,
// meaning an interframe delay of about 10-35 milliseconds.
//
// Looks best on a high-density LED setup (60+ pixels/meter).
//
//
// There are two main parameters you can play with to control the look and
// feel of your fire: COOLING (used in step 1 above), and SPARKING (used
// in step 3 above).
//
// COOLING: How much does the air cool as it rises?
// Less cooling = taller flames.  More cooling = shorter flames.
// Default 50, suggested range 20-100 
#define COOLING  55

// SPARKING: What chance (out of 255) is there that a new spark will be lit?
// Higher chance = more roaring fire.  Lower chance = more flickery fire.
// Default 120, suggested range 50-200.
#define SPARKING 120


void Fire2012()
{
  if (irrecv.decode(&results)) {
    Serial.println(m);
    
    m = m + 1;
    
    //if (m > 5) {
       // NUM_LED=149;
       //Serial.println("its5");
      //}
      
    if (m == 5) {
        NUM_LED=150;
        FastLED.clear ();
       Serial.println("its5");
      }
      if (m == 8) {
      NUM_LED=140;
      FastLED.clear ();
      Serial.println("its10");
      }
      if (m == 11) {
      NUM_LED=130;
      FastLED.clear ();
      Serial.println("its10");
      }
      if (m == 14) {
      NUM_LED=120; 
      FastLED.clear ();
      Serial.println("its15");
      }
      if (m == 17) {
      NUM_LED=110; 
      FastLED.clear ();
      Serial.println("its15");
      }
      if (m == 20) {
      NUM_LED=100; 
      FastLED.clear ();
      Serial.println("its15");
      }
      if (m == 23) {
      NUM_LED=90;
      Serial.println("its20");
      FastLED.clear ();
      }
      if (m == 25) {
      NUM_LED=80; 
      FastLED.clear ();
      Serial.println("its15");
      
      }
      if (m == 27) {
      NUM_LED=70; 
      FastLED.clear ();
      Serial.println("its15");
      
      }
      if (m == 29) {
      NUM_LED=70; 
      FastLED.clear ();
      Serial.println("its15");
      
      }
      if (m == 31) {
      NUM_LED=60; 
      FastLED.clear ();
      Serial.println("its15");
      
      }
      if (m == 33) {
      NUM_LED=50; 
      FastLED.clear ();
      Serial.println("its15");
      
      }
      if (m == 34) {
      NUM_LED=40; 
      FastLED.clear ();
      Serial.println("its15");
      
      }
      if (m == 35) {
      NUM_LED=30; 
      FastLED.clear ();
      Serial.println("its15");
      
      }
      if (m == 36) {
      NUM_LED=20; 
      FastLED.clear ();
      Serial.println("its15");
      
      }
      if (m == 37) {
      NUM_LED=10; 
      FastLED.clear ();
      Serial.println("its15");
      
      }
      if (m == 38) {
      NUM_LED=1; 
      FastLED.clear ();
      Serial.println("its15");
      m = 1;
      m = m + 1;
      }
    //if (results.value == 0xFF02FD){
    //hash: D7E84B1B
    //real: FF02FD
    //At signal input, the received and decoded signal will show via serial console.
    Serial.println(results.value, HEX);
    //i= i+1;
    //Serial.println(i);
    irrecv.resume();
  }
  else {
    m = m + 3;
    
    }
    
    

// Array of temperature readings at each simulation cell
  static byte heat[NUM_LEDS];

  // Step 1.  Cool down every cell a little
    for( int i = 0; i < NUM_LED; i++) {
      heat[i] = qsub8( heat[i],  random8(0, ((COOLING * 10) / NUM_LED) + 2));
    }
  
    // Step 2.  Heat from each cell drifts 'up' and diffuses a little
    for( int k= NUM_LED - 1; k >= 2; k--) {
      heat[k] = (heat[k - 1] + heat[k - 2] + heat[k - 2] ) / 3;
    }
    
    // Step 3.  Randomly ignite new 'sparks' of heat near the bottom
    if( random8() < SPARKING ) {
      int y = random8(7);
      heat[y] = qadd8( heat[y], random8(160,255) );
    }

    // Step 4.  Map from heat cells to LED colors
    for( int j = 0; j < NUM_LED; j++) {
      CRGB color = HeatColor( heat[j]);
      int pixelnumber;
      if( gReverseDirection ) {
        pixelnumber = (NUM_LED-1) - j;
      } else {
        pixelnumber = j;
      }
      leds[pixelnumber] = color;
    }
}
