#pragma once

#include "Watchlist.h"

class FilePlayList : public Watchlist {
protected:
	std::string filename;
public:
	FilePlayList(std::string filename);

	virtual void writeToFile() = 0;
	virtual void displayPlaylist() = 0;
};

class CSVPlayList : public FilePlayList {
public:
	CSVPlayList(std::string filename);
	void writeToFile();
	void displayPlaylist();
};

class HTMLPlayList : public FilePlayList {
public:
	HTMLPlayList(std::string filename);
	void writeToFile();
	void displayPlaylist();
};

class JSONPlayList : public FilePlayList {
public:
	JSONPlayList(std::string filename) : FilePlayList(filename) {};
	void writeToFile() {};
	void displayPlaylist() {};
};