#ifndef ERATOSTHENES_H
#define ERATOSTHENES_H

using namespace std;
class Eratosthenes {
public:
  Eratosthenes(const int& max);
  void printPrimes();
  void printLastPrime();
//  printLargest(const int& largest);


private:
int nextFind();
void mark();
const int& m;
int find;
string primes;
};

#endif
