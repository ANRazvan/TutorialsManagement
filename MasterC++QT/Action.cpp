#include "Action.h"

Action::Action()
{
}


ActionAdd::ActionAdd(Repository& repo,Tutorial addedTutorial) : repo{ repo }, addedTutorial{ addedTutorial }
{
}


void ActionAdd::executeUndo()
{
	qDebug() << "executeUndo 1";
	this->repo.removeTutorial(this->addedTutorial);
	this->repo.writeToFile();
	//this->repo.re((this->addedTutorial.getTitle(), this->addedTutorial.getPresenter());
}

void ActionAdd::executeRedo()
{
	this->repo.addTutorial(this->addedTutorial);
}

ActionRemove::ActionRemove(Repository& repo, const Tutorial& removedTutorial) : repo{ repo }, removedTutorial{ removedTutorial }
{
}


void ActionRemove::executeUndo()
{
	//this->repo.add_repo(removedTutorial.getTitle(), removedTutorial.getPresenter(), removedTutorial.getLink(), removedTutorial.getDuration(), removedTutorial.getLikes());
	this->repo.addTutorial(this->removedTutorial);
}

void ActionRemove::executeRedo()
{
	this->repo.removeTutorial(this->removedTutorial);
}

ActionUpdate::ActionUpdate(Repository& repo, const Tutorial& oldTutorial, const Tutorial& newTutorial) : repo{ repo }, oldTutorial{ oldTutorial }, newTutorial{ newTutorial }
{
}

//ActionUpdate::~ActionUpdate()
//{
//}

void ActionUpdate::executeUndo()
{
	this->repo.updateTutorial(this->newTutorial, this->oldTutorial);
}

void ActionUpdate::executeRedo()
{
	this->repo.updateTutorial(this->oldTutorial, this->newTutorial);
}

