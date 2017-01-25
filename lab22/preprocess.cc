#include <iostream>
#include <string>
#include <fstream>
#include <vector>

using namespace std;

int main() {

ifstream infile;
ofstream outfile;
infile.open("/usr/share/dict/words");
outfile.open("words.txt");

string word;
char ch;

while (infile.get(ch) >> word) {
	int tricounter = 0;
			transform(word.begin(), word.end(), word.begin(), ::tolower);

			if (word.length() > 2){
				vector<string> trigrams;
				string tri;
				bool trisleft = true;
				int i = 0;
				while(trisleft){
					tri = word.substr(i, 3);
					++i;
					if (tri.length() > 2) {
						++tricounter;
						trigrams.push_back(tri);
					} else {
						trisleft = false;
					}
				}

				sort(begin(trigrams), end(trigrams));

				outfile << word << " " << tricounter;
				for (string& trias : trigrams) {
					outfile << " " << trias;
				}
				outfile << endl;
			}
			else {
				outfile << word << " " << tricounter << endl;
			}


			}


}
