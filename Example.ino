#include "StatusLEDController.h"

#include "pico/mutex.h"
#include "pico/multicore.h"

#define RED_LED 15
#define BLUE_LED 13
#define GREEN_LED 11

// LED status
#define SUCCESS 0
#define LOADING 1
#define FAILURE 2
#define STOP 3
#define LED_OFF -1

int LED_status = -1; // global status for LED

StatusLEDController LEDController(RED_LED,BLUE_LED,GREEN_LED); // states, -1 = OFF, 0 = Success, 1 = Loading, 2 = Failure

void setup() 
{
  multicore_reset_core1();
  multicore_launch_core1([](){LEDController.start(LED_status);});
}

//Core 0 Loop
void loop() 
{  
  LED_status = SUCCESS;
  delay(5000);
  LED_status = LOADING;
  delay(5000);
  LED_status = FAILURE;
  delay(5000);
  LED_status = LED_OFF;
  delay(5000);
}