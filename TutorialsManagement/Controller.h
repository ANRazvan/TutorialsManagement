#pragma once
#include "Repository.h"
#include "FilePlaylist.h"
#include <map>
#include <memory>
#include "Action.h"
using std::make_unique;
using std::unique_ptr;

class Controller
{
private:

	Repository repo;
	FilePlayList* wl;

public:
	//vector <unique_ptr<Action>> undoActions;
	//vector <unique_ptr<Action>> redoActions;
	vector <unique_ptr<Action>> undoActions;
	vector <unique_ptr<Action>> redoActions;
	vector <Action*> undoActionss;
	vector <Action*> redoActionss;
	Controller(const Repository& repo);
	Controller(const Repository& repo, FilePlayList* pl);
	~Controller();
	void add_tutorials();
	int add(const std::string& title, const std::string& presenter,const std::string& link, const Duration& dur, int likes);
	void remove(const std::string& title, const std::string& presenter);
	void update(const std::string& title,const std::string& presenter,const std::string& link, const Duration& dur, int likes);
	vector <Tutorial> list_all();
	vector <Tutorial> list_presenter(const std::string& presenter);
	void add_wl(Tutorial t);
	void remove_wl(const std::string& title, const std::string& presenter, const std::string& answer);
	FilePlayList* list_wl();
	void updatePlayList(FilePlayList* new_pl);
	std::map<std::string, int> get_by_presenter();
	void undo();
	void redo();
};
