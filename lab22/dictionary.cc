#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <sstream>
#include "word.h"
#include "dictionary.h"

#define path string("words.txt")

using namespace std;

Dictionary::Dictionary() {
	//ifstream infile;
	//infile.open("words.txt");
	ifstream infile(path);
	string line;
	/*
	//while (infile.getline(line)) {
	while(getline(infile, line)){
		stringstream ss;
		ss << line;
		string word;
		ss >> word;
		allwords.insert(word);
		// todo: kolla tris här.
		unsigned int wordlength = word.length();
			if (wordlength < MAX_SIZE) {
				vector<string> tris;
				// why do we even add the number?
				string number;
				ss >> number;

				string tri;
				while (ss >> tri) {
					tris.push_back(tri);
				}
				Word w(word, tris);
				// Kan det vara fel vektor?
				words[wordlength].push_back(w);
			}

	} */
		if (infile) {
			int nTrig = 0;
			while (infile >> line) {
				nTrig = 0;
				infile >> nTrig;
				vector<string> trigrams;

				for (int i =0; i < nTrig; i++) {
					string triagram;
					infile >> triagram;
					trigrams.push_back(triagram);
				}

				sort(trigrams.begin(), trigrams.end());

				if (line.size() < MAX_SIZE) {
					allwords.insert(line);
					words[line.size()].emplace_back(line, trigrams);
				}
			}
			}else {
				cerr << "File " << path << " not found!" << endl;
			}
}

bool Dictionary::contains(const string& word) const {

	unordered_set<string>::const_iterator got = allwords.find(word);
	if (got == allwords.end()){
		return false;
	}
	else return true; 
}

vector<string> Dictionary::get_suggestions(const string& word) const {
	vector<Word> suggestions;
	add_trigram_suggestions(suggestions, word);
	rank_suggestions(suggestions, word);
	trim_suggestions(suggestions);
	
	vector<string> temp;

	for (Word suggestion : suggestions) {
		temp.push_back(suggestion.get_word());
	}
	return temp;
}

vector<string> Dictionary::get_trigrams(const string& word) const {
		vector<string> trigrams;
	for (string::size_type j = 0; j < word.size() -2; ++j){
			string trigram = word.substr(j, 3);
			trigrams.push_back(trigram);
	}
	sort(trigrams.begin(), trigrams.end());
	return trigrams;
}

void Dictionary::add_trigram_suggestions(std::vector<Word>& suggestions, const std::string& word) const {

		if (word.size() < MAX_SIZE) {
			const vector<Word>& same_size_words = words[word.size()];
			for (Word same_size_word : same_size_words) {
			suggestions.push_back(same_size_word);
			}
		if (word.size() > 1) {
			const vector<Word>& smaller_size_words = words[word.size()-1];
			for (Word smaller_size_word : smaller_size_words) {
				suggestions.push_back(smaller_size_word);
			}
		}
		if (word.size() < MAX_SIZE - 1) {
			const vector<Word>& bigger_size_words = words[word.size()+1];
		for (Word bigger_size_word : bigger_size_words) {
			suggestions.push_back(bigger_size_word);
			}
		}
		vector<string> trigrams = get_trigrams(word);
		vector<Word> filter;

		for(Word suggestion : suggestions) {
			if (suggestion.get_matches(trigrams)*2 >= trigrams.size()) {
				filter.push_back(suggestion);
			}
		}
		suggestions.swap(filter);
	}
}
void Dictionary::rank_suggestions(vector<Word>& suggestions, const string& word) const {
	/* vector<string>::iterator it;
	vector<pair<int,string>> parr;
	for (it = suggestions.begin(); it != suggestions.end(); ++it) {
		pair<int,string> p(edit_distance(*it, word), *it);
		parr.push_back(p);
	}

	sort(parr.begin(), parr.end());

	for (size_t i = 0; i < suggestions.size(); ++i){
		suggestions.at(i) = parr.at(i).second;
	} */

	int d[MAX_SIZE+1][MAX_SIZE+1];

		for (int i = 0; i != (MAX_SIZE+1); ++i){
			d[i][0] = i;
			d[0][i] = i;
		}
		vector<pair<int, Word>> rank_suggestions;
		for (Word suggestion : suggestions) {
			for (unsigned int j = 1; j < suggestion.get_word().size()+1; j++) {
				for (unsigned int i = 1; i < word.size()+1; i++) {
					int distance = min(d[i-1][j] + 1, d[i][j-1] + 1);
					if(word[i-1] == suggestion.get_word()[j-1]) {
						distance = min(distance, d[i-1][j-1]);
					} else {
						distance = min(distance, d[i-1][j-1] + 1);
					}
					d[i][j] = distance;
				}
			}
			unsigned int cost = d[word.size()][suggestion.get_word().size()];
        rank_suggestions.push_back(make_pair(cost, suggestion));
		}
		sort(rank_suggestions.begin(), rank_suggestions.end());

		vector<Word> sorted_ranked_suggestions;
   		 for (pair<int, Word> pair : rank_suggestions) {
      	  sorted_ranked_suggestions.push_back(pair.second);
  	  }

   	 suggestions.swap(sorted_ranked_suggestions);
}

void Dictionary::trim_suggestions(vector<Word>& suggestions) const {
	//if-sats
	if (suggestions.size() > 5) {
		suggestions.resize(5);
	}
}
/*
int Dictionary::edit_distance(const std::string& w1, const std::string& w2) const {

	  // for all i and j, d[i,j] will hold the Levenshtein distance between
	  // the first i characters of s and the first j characters of t;
	  // note that d has (m+1)*(n+1) values
		int d[MAX_SIZE+1][MAX_SIZE+1];

	  // source prefixes can be transformed into empty string by
	  // dropping all characters

		for (int i = 0; i != (MAX_SIZE+1); ++i){
			d[i][0] = i;
			d[0][i] = i;
		}

	  // target prefixes can be reached from empty source prefix
	  // by inserting every character

		//unsigned int substitutionCost = 0;
		for (int j = 1; j != (w2.length() + 1); ++j) {
			for (int i = 1; i != (w1.length() + 1); ++i){
				if (w1.at(i - 1) == w2.at(j - 1)){
								d[i][j] = d[i-1][j-1];
				}
				else {

					unsigned int del = d[i-1][j] + 1;
					unsigned int ins = d[i][j-1] + 1;
					unsigned int sub  = d[i-1][j-1] +1;

					unsigned int min = ins;
					if (del < min){
						min = del;
					}
					else if (sub < min){
						min = sub;
					}
					d[i][j] = min;
				}
		}

	}

	  return d[w1.length()][w2.length()];
} */
