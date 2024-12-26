#include "Watchlist.h"

Watchlist::Watchlist()
{
	this->current = 0;
}

Watchlist::~Watchlist()
{
}

void Watchlist::add(const Tutorial& t)
{
	this->tutorials.push_back(t);
}

void Watchlist::play()
{
	if (this->tutorials.size() == 0)
		return;
	this->current = 0;
	Tutorial currentTutorial = this->tutorials[this->current];
	currentTutorial.play();
}

Tutorial Watchlist::getCurrentTutorial()
{
	if (this->tutorials.size() == 0)
		return Tutorial{};
	return this->tutorials[this->current];
}

vector <Tutorial> Watchlist::getTutorials()
{
	return this->tutorials;
}

void Watchlist::next()
{
	if (this->tutorials.size() == 0)
		return;
	this->current++;
	this->current = this->current % this->tutorials.size();
}

int Watchlist::size()
{
	return this->tutorials.size();
}

bool Watchlist::isEmpty()
{
	return this->tutorials.size() == 0;
}

void Watchlist::remove(int pos)
{
		this->tutorials.erase(this->tutorials.begin() + pos);
}
