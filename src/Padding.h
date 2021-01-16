#ifndef PADDING_h
#define PADDING_h

#include <ArduinoSTL.h>

class Padding
{
public:
  size_t t;
  size_t r;
  size_t b;
  size_t l;

  Padding(size_t pad)
  {
    this->t = pad;
    this->r = pad;
    this->b = pad;
    this->l = pad;
  }

  Padding(size_t tb, size_t lr)
  {
    this->t = tb;
    this->r = lr;
    this->b = tb;
    this->l = lr;
  }

  Padding(size_t t, size_t r, size_t b, size_t l)
  {
    this->t = t;
    this->r = r;
    this->b = b;
    this->l = l;
  }
};

#endif