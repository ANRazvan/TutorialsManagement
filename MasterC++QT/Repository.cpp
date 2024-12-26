#pragma once
#include "Repository.h"
#include "RepositoryExceptions.h"
#include <fstream>
using namespace std;
Repository::Repository(const std::string& filename)
{
	this->filename = filename;
	this->readFromFile();
}

Repository::~Repository()
{
}

void Repository::add_repo(const std::string& title, const std::string& presenter, const std::string& link, const Duration& dur, int like)
{
	Tutorial t{ title, presenter, link, dur, like };
	this->elements.push_back(t);
	this->writeToFile();
}

void Repository::add_watchlist(Tutorial t)
{
	this->watchlist.push_back(t);
}

void Repository::remove_from_index(int index)
{
	this->elements.erase(this->elements.begin() + index);
	this->writeToFile();
}

void Repository::remove_from_index_wl(int index)
{
	this->watchlist.erase(this->watchlist.begin() + index);
}

void Repository::update_repo(int pos, const std::string& title, const std::string& presenter, const std::string& link, const Duration& dur, int like)
{
	Tutorial t{ title, presenter, link, dur, like };
	this->elements[pos] = t;
	this->writeToFile();
}

Tutorial Repository::getElem(int index)
{
	return this->elements[index];
}

vector<Tutorial> Repository::get_watchlist()
{
	return this->watchlist;
}

vector<Tutorial> Repository::get_elements()
{
	return this->elements;
}

int Repository::size()
{
	return this->elements.size();
}

void Repository::like(int pos) {
	this->elements[pos].increaseLikes();
	this->writeToFile();
}

void Repository::readFromFile()
{
	ifstream file(this->filename);

	if (!file.is_open())
		throw FileException("The file could not be opened!");

	Tutorial t;
	while (file >> t)
		this->elements.push_back(t);

	file.close();
}

void Repository::writeToFile()
{
	ofstream file(this->filename);
	if (!file.is_open())
		throw FileException("The file could not be opened!");

	for (const auto& t : this->elements) {
		file << t;
	}

	file.close();
}

void Repository::addTutorial(const Tutorial& t)
{
	this->elements.push_back(t);
	this->writeToFile();
}

void Repository::removeTutorial(const Tutorial& t)
{
	auto it = find(this->elements.begin(), this->elements.end(), t);
	if (it != this->elements.end())
	{
		this->elements.erase(it);
		this->writeToFile();
	}
}

void Repository::updateTutorial(const Tutorial& old_t, const Tutorial& new_t)
{
	auto it = find(this->elements.begin(), this->elements.end(), old_t);
	if (it != this->elements.end())
	{
		*it = new_t;
		this->writeToFile();
	}
}	
