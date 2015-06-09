#ifndef _EXCEPTIONS_H_
#define _EXCEPTIONS_H_

#include <stdexcept>

struct GPIOException : public std::runtime_error {
  using std::runtime_error::runtime_error;
};

#endif /* _EXCEPTIONS_H_ */
