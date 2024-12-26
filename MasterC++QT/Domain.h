#pragma once
#include <string>
#include <QDebug>

class Duration
{
private:
	double minutes;
	double seconds;
public:
	Duration();
	Duration(double min, double sec) :minutes(min), seconds(sec) {};
	double getMinutes() const { return minutes; };
	double getSeconds() const { return seconds; };
	void setMinutes(double min) { minutes = min; };
	void setSeconds(double sec) { seconds = sec; };
};

class Tutorial
{
private:
	std::string title, presenter, link;
	Duration duration;
	int likes;

public:

	Tutorial();
	Tutorial(const std::string& title, const std::string& presenter,const std::string& link, const Duration& dur, int like);
	void increaseLikes();
	std::string getTitle() const { return title; }
	std::string getPresenter() const { return presenter; }
	std::string getLink() const { return link; }
	Duration getDuration() const { return duration; }
	int getLikes() const { return likes; }

	void play();

	friend std::istream& operator>>(std::istream& is, Tutorial& t);
	friend std::ostream& operator<<(std::ostream& os, const Tutorial& t);

	bool operator==(const Tutorial& t);

};

