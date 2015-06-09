#include "GPIO.hh"

#include <chrono>
#include <sstream>
#include <thread>

#include "Exceptions.hh"

GPIO::GPIO(int id, IOState state)
  : id(id), io_state(IOState::Null) {
  std::fstream export_file("/sys/class/gpio/export");
  export_file << id << std::flush;

  std::stringstream ss;
  ss << "/sys/class/gpio/gpio" << id << "/direction";
  auto direction_filename = ss.str();
  ss.str("");

  for(int tries=0; tries<10; tries++) {
    if(direction_file.is_open()){
      break;
    }
    direction_file.open(direction_filename);
    std::this_thread::sleep_for( std::chrono::milliseconds(10) );
  }

  if(!direction_file.is_open()){
    throw GPIOException("Unable to open direction file.");
  }


  ss << "/sys/class/gpio/gpio" << id << "/value";
  value_filename = ss.str();

  SetState(state);
}

GPIO::~GPIO(){
  std::fstream unexport_file("/sys/class/gpio/unexport");
  unexport_file << id << std::flush;
}

void GPIO::SetState(IOState new_state){
  if(new_state == io_state){
    return;
  }

  if(value_file.is_open()){
    value_file.close();
  }

  switch(new_state){
  case IOState::Input:
    direction_file << "in" << std::flush;
    value_file.open(value_filename);

  case IOState::Output:
    direction_file << "out" << std::flush;
    value_file.open(value_filename);

  case IOState::Null:
    ;
  }

  io_state = new_state;
}

IOState GPIO::GetState(){
  return io_state;
}

bool GPIO::IsHigh(){
  switch(io_state){
  case IOState::Input:
  {
    int buf;
    value_file >> buf;
    return buf;
  }

  case IOState::Output:
    return value;

  default:
    return 0;
  }
}

void GPIO::SetHigh(bool high){
  if(io_state == IOState::Output){
    value_file << high << std::flush;
    value = high;
  }
}
