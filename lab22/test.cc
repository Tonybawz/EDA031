#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "dictionary.h"
#include "word.h"


using namespace std;

int main() {

Dictionary* d = new Dictionary();

bool contains = false;
const string hej = "abactinally";
contains = d->contains(hej);
cout << contains << endl;
}
