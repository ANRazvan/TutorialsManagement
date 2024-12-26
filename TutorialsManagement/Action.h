#pragma once
#include "Repository.h"
#include "Domain.h"

class Action
{
private:

public:
	Action();
	virtual ~Action() = default;
	virtual void executeUndo() {};
	virtual void executeRedo() {};

};

class ActionAdd : public Action {
private:
	Repository& repo;
	Tutorial addedTutorial;
public:
	ActionAdd(Repository& repo,Tutorial addedTutorial);
	//~ActionAdd() override;
	void executeUndo() ;
	void executeRedo() ;

};

class ActionRemove : public Action {
private:
	Repository& repo;
	Tutorial removedTutorial;
public:
	ActionRemove(Repository& repo, const Tutorial& removedTutorial);
	//~ActionRemove() override;
	void executeUndo() ;
	void executeRedo() ;
};


class ActionUpdate : public Action {
private:
	Repository& repo;
	Tutorial oldTutorial;
	Tutorial newTutorial;
public:
	ActionUpdate(Repository& repo, const Tutorial& oldTutorial, const Tutorial& newTutorial);
	//~ActionUpdate() override;
	void executeUndo() ;
	void executeRedo() ;
};

