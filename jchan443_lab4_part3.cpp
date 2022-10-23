// The following global variables are used to implement SynchSM
// functionality using the Arduino API. In contrast the zyBook,
// the Arduino API does not provide the programmer with direct
// access to Timer Interrupt functions. 
/* Name: Joseph Chang
   Email: jchan443@ucr.edu
   I acknowledge all content contained herein, excluding template or example code, is my own original work.
   Demo Vid: https://youtu.be/OEqI4-6tmNs
*/
const unsigned long period = 500; 
unsigned long lastRan;

const int b_size = 7;
const int b[b_size] = {2, 3, 4, 5, 9, 10, 11};
int rlp = 11;
int blp = 9;
int glp = 10;
int t = 1;
int val = 0;
int nval = 0;
int digit = 0;
int rmap = 0;
int bmap = 0;
int gmap = 0;
void setup(){

  // Default Arduino Function

    // Initialize LEDs
    for(int i = 0; i < b_size; i++)
    {
        pinMode(b[i], OUTPUT);
    }
  pinMode(rlp, OUTPUT);
  pinMode(blp, OUTPUT);
  pinMode(glp, OUTPUT);
    Serial.begin(9600);
    lastRan = 0;
}
int getBit(int x, int k){
    return ((x & (0x01 << k)) !=0);
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
        val = analogRead(A1);
        Serial.println(val);
        val = map(val, 58, 750, 0, 15);
        Serial.println(val);
        nval = analogRead(A0);
        //int rval = nval;
        int bval = nval;
        int gval = nval;
        // Serial.println(bval);
        rmap = 255;
        if(bval > 50) {
          bmap = map(bval, 70, 570, 0, 255);
        }
        else{
          bmap = 0;
        }
        if(gval >=600){
          gmap = map(gval, 500, 1026, 0, 255);
        }
        else{
          gmap = 0;
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
            digitalWrite(b[i], LOW);
        }
        for(int i = 0; i < 4; i++){
            if(getBit(val, i)==1){
                digitalWrite(b[i], HIGH);
            }
            else{
                digitalWrite(b[i], LOW);
            }
        }
        analogWrite(rlp, 255);
        analogWrite(blp, bmap);
        analogWrite(glp, gmap);
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
