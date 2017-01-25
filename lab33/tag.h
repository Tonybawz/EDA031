#ifndef TAG_H
#define TAG_H

#include <iostream>
#include <fstream>
using namespace std;

class TagRemover {
public:
  TagRemover(istream& input) : is(input){};
  void print(ostream& output);
private:
  istream& is;
};


#endif
