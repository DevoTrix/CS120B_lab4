// The following global variables are used to implement SynchSM
// functionality using the Arduino API. In contrast the zyBook,
// the Arduino API does not provide the programmer with direct
// access to Timer Interrupt functions. 
const unsigned long period = 1000; 
unsigned long lastRan;

const int b_size = 7;
const int b[b_size] = {2, 3, 4, 5, 9, 10, 11};
int t = 1;
void setup(){

  // Default Arduino Function

    // Initialize LEDs
    for(int i = 0; i < b_size; i++)
    {
        pinMode(b[i], OUTPUT);
    }
    Serial.begin(9600);
    lastRan = 0;
}

enum States{INIT, S0} state = INIT;

// The Tick() function is similar in principle to zyBooks
// If you find it confusing, draw the corresponding SynchSM
// diagram. 
void Tick(){


    // State Transitions
    switch(state){
      case INIT:  
        state = S0;  
        break;
      case S0:
        t = t++;
        if(t > 4){
            t = 1;
        }
        state = S0;
        break;
      default: // should never get here
        break;
    }

    // State Actions
    switch(state){ 
      case INIT:
        break;
      case S0:
        for(int i = 0; i < 4; i++){
            digitalWrite(B[i], LOW);
        }
        digitalWrite(B[t-1], HIGH);
        break;
     default: // should never get here
        break;
    }
}

void loop(){ 

   // Default Arduino function
  
  // We track time explicitly in the loop() function,
  // which is different that the Timer Interrupt
  // mechanism introduced in the zyBook
  if ((millis() - lastRan) > period) {
    Tick(); 
    lastRan = millis();
  }  
}