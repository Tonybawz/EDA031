#include <iostream>
#include <fstream>
#include <string>
#include "coding.h"
using namespace std;

char coding::encode(char c){
	char crypt = c + 5;
	return crypt;
}
/* For any character c, decode(encode(c)) == c */
char coding::decode(char c){
	char decrypt = c - 5;
	return decrypt;
};

int main(int argc, char ** argv) {

	//slog samman till en klass
	//körs som ./codingRun encode/decode file
if (argc != 3) {
	cout << "Wrong number of arguments, exiting" << endl;
	exit(0);
}

string argv1 = argv[1];
bool encode = false;
if (argv1.compare("encode") == 0) {
	encode = true;
} else if (argv1.compare("decode") == 0) {
	encode = false;
} else{
	cout << "Exit on errorstring" << endl;
	exit(0);
}

ifstream infile;
char ch;
string outputstring = argv[2];
infile.open(outputstring);

if(encode){
	outputstring += ".enc";
} else
{
	outputstring += ".dec";
}

ofstream output;
output.open(outputstring);

if(!infile) {
	cout << "Could not open file " << argv[2] << endl;
	exit(0);
}

while(infile.get(ch)) {
	if (encode) {
	output.put(coding::decode(ch));
 }
	else{
	output.put(coding::encode(ch));
	}
}
infile.close();
output.close();

}
