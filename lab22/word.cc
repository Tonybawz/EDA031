#include <string>
#include <vector>
#include "word.h"

using namespace std;

Word::Word(const string& w, const vector<string>& t): word(w), trigrams(t) {}

Word::Word() {}

string Word::get_word() const {
	return word;
}

//är nog inte färdig
unsigned int Word::get_matches(const vector<string>& t) const {

	unsigned int found = 0;
	
	/*vector<string>::const_iterator it, wt;
	wt = trigrams.begin();
	for (it = t.begin(); it != t.end(); ++it) {
		if ((*wt).compare(*it) == 0) {
			++wt;
			++found;
			if (wt == trigrams.end())
				break;
		}
	}
	return found; */

	unsigned int t_counter = 0;
	unsigned int tri_counter = 0;
	while(trigrams.size() > tri_counter && t.size() > t_counter) {
		if (trigrams[tri_counter] == t[t_counter]) {
			found++;
			t_counter++;
			tri_counter++;
		} else if (trigrams[tri_counter] > t[t_counter]) {
			t_counter++;
		} else {
			tri_counter++;
		}
	}
	return found;
}

bool Word::operator <(const Word& w) const {
	return word < w.get_word();
}
