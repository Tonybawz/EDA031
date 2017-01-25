#include "date.h"
#include <sstream>
#include <iostream>
#include <string>

template <typename T>
std::string toString(const T& t1){
  std::stringstream ss;
  ss << t1;
  return ss.str();
}

template std::string toString<double>(const double&);
template std::string toString<Date>(const Date&);

int main(){
  double d = 1.234;
  Date today;
  std::string sd = toString(d);
  std::string st = toString(today);
  std::cout << "Double: " << sd << " Date: " << st << std::endl;
  return 0;
}
