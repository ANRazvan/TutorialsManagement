#pragma once
#include <vector>
#include "Domain.h"
#include <algorithm>
using std::vector;

class Repository
{
private:
		vector <Tutorial> elements;
		vector <Tutorial> watchlist;
		std::string filename;

public:
	Repository(const std::string& filename);
	~Repository();
	void addTutorial(const Tutorial& t);
	void removeTutorial(const Tutorial& t);
	void updateTutorial(const Tutorial& old_t, const Tutorial& new_t);
	void add_repo(const std::string& title, const std::string& presenter,const std::string& link, const Duration& dur, int like);
	void add_watchlist(Tutorial t);
	void remove_from_index(int index);
	void remove_from_index_wl(int index);
	void update_repo(int pos, const std::string& title, const std::string& presenter,const std::string& link, const Duration& dur, int like);
	int size();
	vector <Tutorial> get_elements();
	vector <Tutorial> get_watchlist();
	Tutorial getElem(int index);
	void like(int index);
	void readFromFile();
	void writeToFile();
};

