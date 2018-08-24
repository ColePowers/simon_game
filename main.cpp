#include "mbed.h"
#include "stdlib.h"
#include "Speaker.h"

DigitalOut myled1(p5);
DigitalIn pb1(p6);
DigitalOut myled3(p8);
DigitalIn pb3(p9);
DigitalIn pb4(p12);
DigitalOut myled4(p13);
DigitalIn pb2(p15);
DigitalOut myled2(p16);

void display(int ledNum, float waitTime);
int getUserGuess(void);

Speaker mySpeaker(p21);

int main() {
    
//this is some code I found online. rand() does not work properly without this
//because the seed is the same everytime since it is generated on reset.
//this uses some random noise/static observed by an AnalogIn pin to make
//a random seed for rand(). pretty cool stuff
//////////////////////////////////////
AnalogIn noise(p20);
uint32_t seed =0;
const int loops = 1; // increase if LSB has a bias. 
for (int i=0;i<(32*loops);i++) {
  seed ^= noise.read_u16();
  if (seed & 1<31) { // shift left and wrap.
    seed <<= 1;
    seed |= 1;
  } else
    seed <<= 1;
}
srand(seed);
//////////////////////////////////////

    pb1.mode(PullDown);
    pb2.mode(PullDown);
    pb3.mode(PullDown);
    pb4.mode(PullDown);
    
    float waitTime = 0.2;
    int turnCount = 0;
    int sequence[100];
    bool loser = false;
    int userGuess;
    
    
    while(!loser) {
        
        sequence[turnCount]=rand() % 4 + 1;     //add 1 to sequence
        
        if(turnCount==2){
            waitTime = 0.15;
        }
        if(turnCount==5){
            waitTime = 0.125;
        }
        if(turnCount==8){
            waitTime = 0.1;
        }
        
        
        for(int i=0; i<=turnCount; i++){     //display sequence
            display(sequence[i], waitTime);
        }
            
        for(int i=0; i<=turnCount; i++){     //get input from user and compare
            userGuess=getUserGuess();
            if(userGuess!=sequence[i]){
                loser=true;
                myled1 = 1;
                myled2 = 1;
                myled3 = 1;
                myled4 = 1;
                mySpeaker.PlayNote(164.814,1.0,0.2);
                break;
            }                 //if wrong then user is loser and ends
        }
        
        turnCount++;    //increment turn count
        wait(0.5);
    }
}
    
    void display (int ledNum, float waitTime) {     //display LED
        switch (ledNum) {
            case 1 : {
                    myled1 = 1;
                    mySpeaker.PlayNote(164.814,waitTime,0.1);
                    wait(waitTime);
                    myled1 = 0;
                    wait(waitTime);
                    }
                    break;
            case 2 : {
                    myled2 = 1;
                    mySpeaker.PlayNote(220.000,waitTime,0.1);
                    wait(waitTime);
                    myled2 = 0;
                    wait(waitTime);
                    }
                    break;
            case 3 : {
                    myled3 = 1;
                    mySpeaker.PlayNote(277.180,waitTime,0.1);
                    wait(waitTime);
                    myled3 = 0;
                    wait(waitTime);
                    }
                    break;
            case 4 : {
                    myled4 = 1;
                    mySpeaker.PlayNote(329.628,waitTime,0.1);
                    wait(waitTime);
                    myled4 = 0;
                    wait(waitTime);
                    }
                    break;
        }
    }

    //get user input via pushbutton
    int getUserGuess(void){
        while(1){
            if(pb1){
                myled1 = 1;
                mySpeaker.PlayNote(164.814,0.2,0.3);
                wait(0.1);
                while(pb1);
                myled1 = 0;
                wait(0.1);
                return 1;
            }
            if(pb2){
                myled2 = 1;
                mySpeaker.PlayNote(220.000,0.2,0.3);
                wait(0.1);
                while(pb2);
                myled2 = 0;
                wait(0.1);
                return 2;
            }
            if(pb3){
                myled3 = 1;
                mySpeaker.PlayNote(277.180,0.2,0.3);
                wait(0.1);
                while(pb3);
                myled3 = 0;
                wait(0.1);
                return 3;
            }
            if(pb4){
                myled4 = 1;
                mySpeaker.PlayNote(329.628,0.2,0.3);
                wait(0.1);
                while(pb4);
                myled4 = 0;
                wait(0.1);
                return 4;
            }
        }
    }
        