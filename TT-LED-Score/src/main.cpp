#include <Arduino.h>
#include <SPI.h>

int latch = D8;
// int clk = D5;
// int data = D7;
int p1Push = D1;
int p2Push = D2;
int clearPush = D3;

#define DELAY 4

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
//set the led panel we are writing to
const byte whichDigit[4] = {B11110111, B11111011, B11111101, B11111110};

const uint16_t p1Units[] =
    {
        whichDigit[1] * 256 + numTable[0],
        whichDigit[1] * 256 + numTable[1],
        whichDigit[1] * 256 + numTable[2],
        whichDigit[1] * 256 + numTable[3],
        whichDigit[1] * 256 + numTable[4],
        whichDigit[1] * 256 + numTable[5],
        whichDigit[1] * 256 + numTable[6],
        whichDigit[1] * 256 + numTable[7],
        whichDigit[1] * 256 + numTable[8],
        whichDigit[1] * 256 + numTable[9],
        whichDigit[1] * 256 + numTable[10]};

const uint16_t p1Tens[] =
    {
        whichDigit[0] * 256 + numTable[0],
        whichDigit[0] * 256 + numTable[1],
        whichDigit[0] * 256 + numTable[2],
        whichDigit[0] * 256 + numTable[3],
        whichDigit[0] * 256 + numTable[4],
        whichDigit[0] * 256 + numTable[5],
        whichDigit[0] * 256 + numTable[6],
        whichDigit[0] * 256 + numTable[7],
        whichDigit[0] * 256 + numTable[8],
        whichDigit[0] * 256 + numTable[9],
        whichDigit[0] * 256 + numTable[10]};
const uint16_t p2Units[] =
    {
        whichDigit[3] * 256 + numTable[0],
        whichDigit[3] * 256 + numTable[1],
        whichDigit[3] * 256 + numTable[2],
        whichDigit[3] * 256 + numTable[3],
        whichDigit[3] * 256 + numTable[4],
        whichDigit[3] * 256 + numTable[5],
        whichDigit[3] * 256 + numTable[6],
        whichDigit[3] * 256 + numTable[7],
        whichDigit[3] * 256 + numTable[8],
        whichDigit[3] * 256 + numTable[9],
        whichDigit[3] * 256 + numTable[10]};

const uint16_t p2Tens[] =
    {
        whichDigit[2] * 256 + numTable[0],
        whichDigit[2] * 256 + numTable[1],
        whichDigit[2] * 256 + numTable[2],
        whichDigit[2] * 256 + numTable[3],
        whichDigit[2] * 256 + numTable[4],
        whichDigit[2] * 256 + numTable[5],
        whichDigit[2] * 256 + numTable[6],
        whichDigit[2] * 256 + numTable[7],
        whichDigit[2] * 256 + numTable[8],
        whichDigit[2] * 256 + numTable[9],
        whichDigit[2] * 256 + numTable[10]};

uint8_t p1Score[2] = {10, 10}; // P1Tens, P1Units
uint8_t p2Score[2] = {10, 10}; // P1Tens, P1Units,

void incScore(uint8_t player[]);
void clearScores();

void setup()
{
  pinMode(latch, OUTPUT);
  pinMode(p1Push, INPUT);
  pinMode(p2Push, INPUT);
  pinMode(clearPush, INPUT);
  SPI.begin();
  clearScores();
}

void loop()
{
  digitalWrite(latch, LOW);
  SPI.transfer16(p1Tens[p1Score[0]]); // led
  digitalWrite(latch, HIGH);
  delay(DELAY);

  digitalWrite(latch, LOW);
  SPI.transfer16(p1Units[p1Score[1]]); // led
  digitalWrite(latch, HIGH);
  delay(DELAY);

  digitalWrite(latch, LOW);
  SPI.transfer16(p2Tens[p2Score[0]]); // led
  digitalWrite(latch, HIGH);
  delay(DELAY);

  digitalWrite(latch, LOW);
  SPI.transfer16(p2Units[p2Score[1]]); // led
  digitalWrite(latch, HIGH);
  delay(DELAY);

  //check buttons
  int p1Pushed = 0;
  int p2Pushed = 0;
  int clearPushed = 0;
  p1Pushed = digitalRead(p1Push);
  p2Pushed = digitalRead(p2Push);
  clearPushed = digitalRead(clearPush);

  //do something if buttons have abeen pushed
  if (p1Pushed || p2Pushed || clearPushed)
  {
    if (p1Push)
    {
      incScore(p1Score);
    }
    else if (p2Push)
    {
      incScore(p2Score);
    }
    else
    {
      clearScores();
    }

    for (int i = 0; i < 100; i++) // clear display for a second(ish)
    {
      digitalWrite(latch, LOW);
      SPI.transfer16(p1Tens[10]); // led
      digitalWrite(latch, HIGH);
      delay(DELAY);

      digitalWrite(latch, LOW);
      SPI.transfer16(p1Units[10]); // led
      digitalWrite(latch, HIGH);
      delay(DELAY);

      digitalWrite(latch, LOW);
      SPI.transfer16(p2Tens[10]); // led
      digitalWrite(latch, HIGH);
      delay(DELAY);

      digitalWrite(latch, LOW);
      SPI.transfer16(p2Units[10]); // led
      digitalWrite(latch, HIGH);
      delay(DELAY);
    }
  }

  // for (int i = 0; i < 10; i++)
  // {

  //   digitalWrite(latch, LOW);
  //   SPI.transfer16(p1Units[i]); // led
  //   digitalWrite(latch, HIGH);
  //   delay(DELAY);

  //   digitalWrite(latch, LOW);
  //   SPI.transfer16(p1Tens[i]); // led
  //   digitalWrite(latch, HIGH);
  //   delay(DELAY);

  //   digitalWrite(latch, LOW);
  //   SPI.transfer16(p2Units[i]); // led
  //   digitalWrite(latch, HIGH);
  //   delay(DELAY);

  //   digitalWrite(latch, LOW);
  //   SPI.transfer16(p2Tens[i]); // led
  //   digitalWrite(latch, HIGH);
  //   delay(DELAY);
  // }
}

void incScore(uint8_t player[])
{
  if (player[0] = 9)
  {
    player[1]++;
    player[0] = 0;
  }
  else
  {
    player[0]++;
  }
}

void clearScores()
{
  p1Score[0] = 0;
  p1Score[1] = 0;
  p2Score[0] = 0;
  p2Score[1] = 0;
}
