#include <Arduino.h>
// #include <SPI.h>

int latch = D8;
int clk = D5;
int data = D7;

#define DELAY 2

void shiftOut(int mydataPin, int myClockPin, byte mydataOut);

//This is the hex value of each number stored in an array by index num
const byte numTable[] =
    {
        B01111110, //0
        B00010010, //1
        B10111100, //2
        B10110110, //3
        B11010010, //4
        B11100110, //5
        B11101110, //6
        B01110010, //7
        B11111110, //8
        B11110010, //9
        B00000000  //clear

};
byte whichDigit[4] = {B11110111, B11111011, B11111101, B11111110};

int i;

void setup()
{
  // SPI.begin();
  pinMode(latch, OUTPUT);
  pinMode(clk, OUTPUT);
  pinMode(data, OUTPUT);
}

void loop()
{

  //  for(int i=0; i<4; i++){
  //    for(int j=0; j<10; j++){
  //      digitalWrite(latch, LOW);
  //      shiftOut(data, clk, whichDigit[i]); // digitOne
  //      shiftOut(data, clk, numTable[j]); // digitTwo
  //      digitalWrite(latch, HIGH);
  //      delay(500);
  //    }
  //  }

  //  digitalWrite(latch, LOW);
  //  shiftOut(data, clk, B11111110); // led
  //  shiftOut(data, clk, B11101110); // number
  //  digitalWrite(latch, HIGH);
  //  delay(10);

  // digitalWrite(latch, LOW);
  // SPI.transfer(whichDigit[0]); // led
  // // SPI.transfer(numTable[9]);   // number
  // digitalWrite(latch, HIGH);
  // delay(DELAY);

  // digitalWrite(latch, LOW);
  // SPI.transfer(whichDigit[1]); // led
  // // SPI.transfer(numTable[8]);   // number
  // digitalWrite(latch, HIGH);
  // delay(DELAY);

  // digitalWrite(latch, LOW);
  // SPI.transfer(whichDigit[2]); // led
  // // SPI.transfer(numTable[7]);   // number
  // digitalWrite(latch, HIGH);
  // delay(DELAY);

  // digitalWrite(latch, LOW);
  // SPI.transfer(whichDigit[3]); // led
  // // SPI.transfer(numTable[6]);   // number
  // digitalWrite(latch, HIGH);
  // delay(DELAY);

  digitalWrite(latch, LOW);
  shiftOut(data, clk, whichDigit[0]); // led
  shiftOut(data, clk, numTable[1]);   // number
  digitalWrite(latch, HIGH);
  delay(DELAY);

  digitalWrite(latch, LOW);
  shiftOut(data, clk, whichDigit[1]); // led
  shiftOut(data, clk, numTable[1]);   // number
  digitalWrite(latch, HIGH);
  delay(DELAY);

  digitalWrite(latch, LOW);
  shiftOut(data, clk, whichDigit[2]); // led
  shiftOut(data, clk, numTable[2]);   // number
  digitalWrite(latch, HIGH);
  delay(DELAY);

  digitalWrite(latch, LOW);
  shiftOut(data, clk, whichDigit[3]); // led
  shiftOut(data, clk, numTable[2]);   // number
  digitalWrite(latch, HIGH);
  delay(DELAY);
}

// the heart of the program
void shiftOut(int mydataPin, int myClockPin, byte mydataOut)
{
  // This shifts 8 bits out MSB first,
  //on the rising edge of the clock,
  //clock idles low

  //internal function setup
  int i = 0;
  int pinState;
  //  pinMode(myClockPin, OUTPUT);
  //  pinMode(mydataPin, OUTPUT);

  //clear everything out just in case to
  //prepare shift register for bit shifting
  digitalWrite(mydataPin, 0);
  digitalWrite(myClockPin, 0);

  //for each bit in the byte mydataOut�
  //NOTICE THAT WE ARE COUNTING DOWN in our for loop
  //This means that %00000001 or "1" will go through such
  //that it will be pin Q0 that lights.
  for (i = 7; i >= 0; i--)
  {
    digitalWrite(myClockPin, 0);

    //if the value passed to mydataOut and a bitmask result
    // true then... so if we are at i=6 and our value is
    // %11010100 it would the code compares it to %01000000
    // and proceeds to set pinState to 1.
    if (mydataOut & (1 << i))
    {
      pinState = 1;
    }
    else
    {
      pinState = 0;
    }

    //Sets the pin to HIGH or LOW depending on pinState
    digitalWrite(mydataPin, pinState);
    //register shifts bits on upstroke of clock pin
    digitalWrite(myClockPin, 1);
    //zero the data pin after shift to prevent bleed through
    digitalWrite(mydataPin, 0);
  }

  //stop shifting
  digitalWrite(myClockPin, 0);
}
