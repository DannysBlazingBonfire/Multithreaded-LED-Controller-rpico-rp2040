/*
* Author: Danny Gazic (DannysBlazingBonfire)
* 2024-06-13
*/


#include "StatusLEDController.h"

// PWM values (byte)
#define MAX_BRIGHTNESS 255
#define LOWEST_BRIGHTNESS 0

// status
#define SUCCESS 0
#define LOADING 1
#define FAILURE 2
#define STOP 3

StatusLEDController::StatusLEDController(const int redPin, const int bluePin, const int greenPin) noexcept : redLED(redPin), blueLED(bluePin), greenLED(greenPin)
{
  pinMode(redLED, OUTPUT);
  pinMode(blueLED, OUTPUT);
  pinMode(greenLED, OUTPUT);
}

StatusLEDController::~StatusLEDController() noexcept {}

void StatusLEDController::start(int& state) noexcept
{
  int currentState = state;
  bool stopFlag = false;
  while(1)
  {
    if(currentState != state)
    {
      switch (state) 
      {
      case SUCCESS:
        blinkLED(greenLED, 500, state);
        break;
      case LOADING:
        rPulse(blueLED, state);
        break;
      case FAILURE:
        blinkLED(redLED, 250, state);
        break;
      case STOP:
        stopFlag = true;
        break;
      default:
        turnAllOFF();
        break;
      }
    }
    else 
    {
      delay(100);
    }
    if(stopFlag){break;}
  }
}

void StatusLEDController::blinkLED(const int& PIN, const int& speed, int& state) noexcept
{
  int compareState = state;
  while(1)
  {
    if(compareState != state) {break;}
    digitalWrite(PIN, HIGH);
    delay(speed);
    digitalWrite(PIN, LOW);
    delay(speed);
  }
}

void StatusLEDController::pulse(const int& PIN, int& state) noexcept
{
  int compareState = state;
  while(1)
  {
    for(int i = LOWEST_BRIGHTNESS; i < MAX_BRIGHTNESS; i++)
    {
      analogWrite(PIN, i);
      delay(5);
    }
    if(compareState != state) 
    {
      analogWrite(PIN, LOWEST_BRIGHTNESS);
      break;
    }
    for(int j = MAX_BRIGHTNESS; j > LOWEST_BRIGHTNESS; j--)
    {
      analogWrite(PIN, j);
      delay(5);
    }
    if(compareState != state) 
    {
      analogWrite(PIN, LOWEST_BRIGHTNESS);
      break;
    }
  }
}

void StatusLEDController::rPulse(const int& PIN, int& state) noexcept
{
  int compareState = state;
  while(1)
  {
    for(int i = MAX_BRIGHTNESS; i > LOWEST_BRIGHTNESS; i--)
    {
      analogWrite(PIN, i);
      delay(5);
    }
    if(compareState != state) 
    {
      analogWrite(PIN, LOWEST_BRIGHTNESS);
      break;
    }
    for(int j = LOWEST_BRIGHTNESS; j < MAX_BRIGHTNESS; j++)
    {
      analogWrite(PIN, j);
      delay(5);
    }
    if(compareState != state) 
    {
      analogWrite(PIN, LOWEST_BRIGHTNESS);
      break;
    }
  }
}

void StatusLEDController::turnAllOFF() noexcept
{
  digitalWrite(redLED, LOW);
  digitalWrite(blueLED, LOW);
  digitalWrite(greenLED, LOW);
}