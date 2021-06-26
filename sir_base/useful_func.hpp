#ifndef FUNC_HPP
#define FUNC_HPP
#include <string>
int char_to_int(char a)
{
  switch (a) {
    case '0':
      return 0;
      break;
    case '1':
      return 1;
      break;
    case '2':
      return 2;
      break;
    case '3':
      return 3;
      break;
    case '4':
      return 4;
      break;
    case '5':
      return 5;
      break;
    case '6':
      return 6;
      break;
    case '7':
      return 7;
      break;
    case '8':
      return 8;
      break;
    case '9':
      return 9;
      break;
    default:
      return 0;
  }
}
int string_to_int(std::string& a)
{
  int j = a.size();
  int z = 0;
  for (int i = 0; i < j; ++i) {
    int exponent = j - i - 1;
    int pow = 1;
    for (int m = 0; m < exponent; ++m) {
      pow = pow * 10;
    }
    int e = char_to_int(a[i]) * pow;
    z += e;
  }
  return z;
}

bool valid_string(std::string& input)
{
  int size = input.size();
  bool a = true;
  
  int dots = 0;
  for (int i = 0; i < size; ++i) {
    if (a == false) {
      break;
    }

    switch (input[i]) {
      case '0':

        break;
      case '1':

        break;
      case '2':

        break;
      case '3':

        break;
      case '4':

        break;
      case '5':

        break;
      case '6':

        break;
      case '7':

        break;
      case '8':

        break;
      case '9':

        break;
      case '.':
        ++dots;
        if (dots > 1) {
          a = false;
        }
        break;
      default:
        a = false;
        break;
    }
  }
  return a;
}
double string_to_decimal(std::string& input)
{  // turns in a number between 0 and 1
  int int_value = string_to_int(input);
  int size = input.size() - 2;
  if (input[0] == '.') {
    ++size;
  }
  if (size < 0) {
    size = 0;
  }
  double div = 1.;
  for (int i = 0; i < size; ++i) {
    div = div * 10.;
  }
  double d_value = int_value / div;
  return d_value;
}
#endif