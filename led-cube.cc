#include <chrono>
#include <fstream>
#include <iostream>
#include <thread>

#include "GPIO.hh"

int main(){
  GPIO gpio(18, IOState::Output);
  gpio.SetHigh(true);
  std::this_thread::sleep_for( std::chrono::seconds(1) );
  gpio.SetHigh(false);

  // std::fstream value("/sys/class/gpio/gpio18/value");
  // std::fstream direction("/sys/class/gpio/gpio18/direction");

  // direction << "out" << std::flush;

  // value << 1 << std::flush;
  // std::this_thread::sleep_for( std::chrono::seconds(1) );
  // value << 0 << std::flush;
  // std::this_thread::sleep_for( std::chrono::seconds(1) );
}
