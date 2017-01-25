#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include "tag.h"

using namespace std;

void TagRemover::print(ostream& out){
  char ch;

  //Läser in char för chard
  bool hit = false;
  bool special = false;
  int count =0;
  stringstream ss;
  string temp;
  while(is.get(ch)){

    if(ch == '<'){
      hit = true;
    }
    else if (ch == '>'){
      hit = false;
    }
    else if (ch == '\n'){
        out << ch;
      }
    else{
      if (ch == '&' || special){
        //cout<<"special: "<<ch<<endl;
        special = true;
        ss << ch;
        ++count;
        if (ch == ';' || count >= 6){
          special = false;
          count =0;
          ss >> temp;
         if (temp.compare("&lt;") == 0){
           out << "<";
         }
         if (temp.compare("&gt;") == 0){
           out << ">";
         }
         if (temp.compare("&nbsp;") == 0){
           out << " ";
           ss.str("");
         }
         if (temp.compare("&amp;") == 0){
           out << "&";

         }
        ss.str(string());
        ss.clear();
        continue;
        }

    }
    if (!hit && !special){
      out << ch;
    }
  }

  }
  out << endl;
}
int main(){
  ifstream in("test.html");
  TagRemover tr(in);
  tr.print(cout);
}
