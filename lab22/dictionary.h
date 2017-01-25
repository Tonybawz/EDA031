#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <string>
#include <vector>
#include <unordered_set>

#include "word.h"



class Dictionary {
public:
	Dictionary();
	bool contains(const std::string& word) const;
	std::vector<std::string> get_suggestions(const std::string& word) const;
private:
	static const unsigned int MAX_SIZE = 25;
	void add_trigram_suggestions(std::vector<Word>& suggestions,
					const std::string& word) const;
	std::vector<Word> words[MAX_SIZE];
	std::unordered_set<std::string> allwords;
	void rank_suggestions(std::vector<Word>& suggestions, const std::string& word) const;
	void trim_suggestions(std::vector<Word>& suggestions) const;
	//int edit_distance(const std::string& suggestions, const std::string& word) const;
	std::vector<std::string> get_trigrams(const std::string& word) const;
};

#endif
