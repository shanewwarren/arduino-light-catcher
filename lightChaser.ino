#include <Bounce.h>

// define the led constants
const unsigned int LED1 = 0; //  red
const unsigned int LED2 = 1; //  red
const unsigned int LED3 = 2; //  yellow
const unsigned int LED4 = 3; //  green - the middle led 
const unsigned int LED5 = 4; //  yellow
const unsigned int LED6 = 5; //  red
const unsigned int LED7 = 6; //  red

// define the button constant
const unsigned int BUTTON_PIN = 10;

// debounce delay - amount of time to wait before reading additional
// button updates.
const unsigned int DEBOUNCE_DELAY = 20;

//  create a bounce object and initialize it with the button pin
//  and debounce delay.  
Bounce guess_button(BUTTON_PIN, DEBOUNCE_DELAY);

void setup(){
  // initialize the leds and button
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);
  pinMode(LED5, OUTPUT);
  pinMode(LED6, OUTPUT);
  pinMode(LED7, OUTPUT);
  pinMode(BUTTON_PIN, INPUT);
  
  // initially light the first led
  displaySingleLED(0);
}

// pin of the currently lit led
int current_light = 0;

// delay time set when initializing a new game (milliseconds)
int LIGHT_DELAY_MAX = 1000;
// minimum delay time till game is won (milliseconds)
int LIGHT_DELAY_MIN = 25;

int current_light_delay = LIGHT_DELAY_MAX;

// used to calculate time elapsed
unsigned long previous_milliseconds = 0;
unsigned long current_milliseconds = 0;

void loop(){
  
    //  check the button for updates
    if(guess_button.update() && guess_button.read() == HIGH){
       // since we will be showing some sort of notification,
       // clear the existing leds.
       clearAll();
      
       if(current_light == LED4) // pressed the button at the correct time
       {  
          // if the delay is still over 250, take another 250 off.   
          if(current_light_delay > 250) current_light_delay = current_light_delay - 250;
          // otherwise if 250 or under only take 50 off at a time.
          else current_light_delay = current_light_delay - 50;
          
          // if the delay is lower than the min the game is won!
          if(current_light_delay < LIGHT_DELAY_MIN) {
            showGameWin();
            current_light_delay = LIGHT_DELAY_MAX;
          }
          else { // if not over yet, show round won
            showWin();
          }
       }
       else // didn't press button at the right time, lose
       {
          showLose();
          current_light_delay = LIGHT_DELAY_MAX;
       }
       
       resetPosition();
   } 
  
   current_milliseconds = millis(); // millis get's time elapsed since program has started running.
   
   // since we need to query the button state at any time we need to make sure we don't have
   // any delays that could cause us to miss reading the button.  by keeping track of a 
   // timestamp (previous_milliseconds) and comparing it to the current timestamp (current_milliseconds)
   // we can calculate how much time has elasped.
   if(current_milliseconds - previous_milliseconds > current_light_delay)
   {
      previous_milliseconds = current_milliseconds;
      
      // advance to the next led
      current_light++;
      if(current_light > 6) current_light = 0;
      displaySingleLED(current_light);
   }
}

void resetPosition(){
  // reset the light
  current_light = 0;
          
  // display the first light again..
  displaySingleLED(current_light);
  previous_milliseconds = millis(); 
}

void  clearAll(){
  digitalWrite(LED1, LOW);
  digitalWrite(LED2, LOW);
  digitalWrite(LED3, LOW);
  digitalWrite(LED4, LOW);
  digitalWrite(LED5, LOW);
  digitalWrite(LED6, LOW);
  digitalWrite(LED7, LOW);
}


void displaySingleLED(int number)
{
  // clear the existing leds
  clearAll();
  
  // set the appropriate led
  if(number == 0)
    digitalWrite(LED1, HIGH);
  else if (number == 1)
    digitalWrite(LED2, HIGH);
  else if(number == 2)
    digitalWrite(LED3, HIGH);
  else if(number == 3)
  digitalWrite(LED4, HIGH);
  else if (number == 4)
    digitalWrite(LED5, HIGH);
  else if(number == 5)
  digitalWrite(LED6, HIGH);
  else if (number == 6)
    digitalWrite(LED7, HIGH);
}

void showWin(){
  // blink the middle led!
  for(int i = 0; i < 50; i++){
      digitalWrite(LED4, HIGH);
      delay(25);
      digitalWrite(LED4, LOW);
      delay(25);
  }
}



void showGameWin(){
    // blink all the leds! ( a huge acheivement truly! )
    for(int i = 0; i < 50; i++){
      digitalWrite(LED1, HIGH);
      digitalWrite(LED2, HIGH);
      digitalWrite(LED3, HIGH);
      digitalWrite(LED4, HIGH);
      digitalWrite(LED5, HIGH);
      digitalWrite(LED6, HIGH);
      digitalWrite(LED7, HIGH);
      delay(25);
      clearAll();
      delay(25);
  }
}

void showLose(){
  // blink the outermost leds
  for(int i = 0; i < 50; i++){
      digitalWrite(LED1, HIGH);
      digitalWrite(LED7, HIGH);
      delay(25);
      digitalWrite(LED1, LOW);
      digitalWrite(LED7, LOW);
      delay(25);
  }
  
}


