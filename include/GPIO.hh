#ifndef _GPIO_H_
#define _GPIO_H_

#include <fstream>
#include <string>

enum class IOState { Input, Output, Null };

class GPIO {
public:
  GPIO(int id, IOState io_state);
  ~GPIO();

  void SetState(IOState new_state);
  IOState GetState();
  bool IsHigh();
  void SetHigh(bool high);

private:
  int id;
  IOState io_state;
  bool value;

  std::fstream direction_file;
  std::string value_filename;
  std::fstream value_file;
};

#endif /* _GPIO_H_ */
