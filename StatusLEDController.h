#ifndef STATUS_LED_CONTROLLER_H
#define STATUS_LED_CONTROLLER_H

#include "Arduino.h"

class StatusLEDController
{
  public:
    // LED controller for controlling 3 LEDs, Constructs with Pins to these 3 LEDs
    StatusLEDController(const int redPin, const int bluePin, const int greenPin) noexcept;
    ~StatusLEDController() noexcept;

    //start controller
    void start(int& state) noexcept;

  private:
    // Blinks red Light
    void blinkLED(const int& PIN, const int& speed, int& state) noexcept;
    // Pulse light from OFF to bright
    void pulse(const int& PIN, int& state) noexcept;
    // Pulse light from bright to OFF
    void rPulse(const int& PIN, int& state) noexcept;
    // turn off all LEDs
    void turnAllOFF() noexcept;
    // method for pulsing a light, takes pin as argument
    const int redLED;
    const int blueLED;
    const int greenLED;
};
#endif