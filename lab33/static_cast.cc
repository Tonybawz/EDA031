#include "date.h"
#include <sstream>
#include <stdexcept>


template <typename T>
T string_cast(const std::string& s) throw (std::invalid_argument){
  std::stringstream ss(s);
  T temp;
  ss >> temp;

  if(ss.fail()){
    throw std::invalid_argument("Error");
  }

  return temp;
}
int main(){
  try{
    int i = string_cast<int>("123");
      double d = string_cast<double>("12.34");
      Date date = string_cast<Date>("2015-01-10");
  		std::cout << "I: " << i << " D: " << d << " Date: " << date << std::endl;
    }catch (std::invalid_argument& e){
      std::cout << "Error: " << e.what() << std::endl;
    }
  }
