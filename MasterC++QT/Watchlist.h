#pragma once
#include <vector>
#include "Domain.h"
using std::vector;

class Watchlist
{
protected:
	std::vector <Tutorial> tutorials;
	int current;

public:
	Watchlist();
	~Watchlist();

	void add(const Tutorial& t);
	void play();
	Tutorial getCurrentTutorial();
	void next();
	int size();
	bool isEmpty();
	void remove(int pos);
	vector <Tutorial> getTutorials();

};

