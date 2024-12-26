#include "Domain.h"
#include <Windows.h>
#include <shellapi.h>
#include "Utils.h"
#include <iostream>
using namespace std;


Tutorial::Tutorial(): title{""}, presenter{""}, link{""}, duration{Duration()}, likes{0}
{}

Tutorial::Tutorial(const std::string& title, const std::string& presenter,const std::string& link, const Duration& dur, int like): title{title}, presenter{presenter}, link{link}, duration{dur}, likes{like}
{}

void Tutorial::play()
{
	ShellExecuteA(NULL, NULL, "chrome.exe", this->getLink().c_str(), NULL, SW_SHOWMAXIMIZED);
}

bool Tutorial::operator==(const Tutorial& t)
{
	return this->title == t.title && this->presenter == t.presenter;
}

void Tutorial::increaseLikes()
{
	this->likes++;
}

istream & operator>>(istream & is, Tutorial& t)
{
	string line;
	getline(is, line);

	vector<string> tokens = tokenize(line, ',');
	if (tokens.size() != 5)
		return is;

	t.title = tokens[0];
	t.presenter = tokens[1];
	t.link = tokens[2];
	vector <string> dur = tokenize(tokens[3], ':');
	if(dur.size() != 2)
		return is;
	t.duration = Duration{stod(dur[0]), stod(dur[1])};
	t.likes = stoi(tokens[4]);
	return is;
}

ostream& operator<<(ostream& os, const Tutorial& t)
{
	os << t.title << "," << t.presenter << "," << t.link << "," << t.duration.getMinutes() << ":" << t.duration.getSeconds() << "," << t.likes << "\n";
	return os;
}

Duration::Duration()
{
	this->minutes = 0;
	this->seconds = 0;
}
