#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include "eratosthenes.h"

using namespace std;
using string = std::basic_string<char>;

Eratosthenes::Eratosthenes(const int& max) : m(max), find(1),primes(max, 'p'){
 if (m>1){
   primes[0] = 'c';
   primes[1] = 'c';
 }
}
void Eratosthenes::printPrimes(){

  mark();
  cout << primes << endl;


}
void Eratosthenes::printLastPrime(){

  mark();
  //cout << primes <<;
  cout<<primes.find_last_of("p")<<endl;
  //cout << primes << endl;

}

int Eratosthenes::nextFind(){
  ++find;
    while(find < m && primes.at(find) != 'p'){
      ++find;
    }
    if(find < m ){
      //cout << find << endl;
    }
  return find;
}
void Eratosthenes::mark(){
  int temp = nextFind();

  while(temp < m){
  for (int i = temp*2; i < m; i+=temp){
    primes.replace(i,1,"c");
  }
  temp = nextFind();
}
}
int main(){
  Eratosthenes es(10000);
  es.printLastPrime();
}
