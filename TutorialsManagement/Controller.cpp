#include "Controller.h"
#include <iostream>
#include <vector>

Controller::Controller(const Repository& repo) :repo{ repo } {
}

Controller::Controller(const Repository& repo, FilePlayList* pl) : repo{ repo }, wl{ pl } {
}

Controller::~Controller() {
}

void Controller::add_tutorials() {
    this->repo.add_repo("c++ tutorial beginners", "freecodecamp.org", "https://www.youtube.com/watch?v=vLnPwxZdW4Y", Duration(18, 20), 1000);
    this->repo.add_repo("python tutorial", "derek banas", "https://www.youtube.com/watch?v=Rub-JsjMhWY", Duration(20, 14), 1000);
    this->repo.add_repo("cooking with gordan ramsay", "gordan ramsay", "https://www.youtube.com/watch?v=AmC9SmCBUj4", Duration(2, 04), 1000);
    this->repo.add_repo("guitar", "justinguitar", "https://www.youtube.com/watch?v=_QCt3UBTS1Y&list=PLlwfspJqZ126JHOY5rTkKCSAp2Ua907-v&ab_channel=JustinGuitar", Duration(1, 14), 1000);
    this->repo.add_repo("OOP in 7 minutes", "mosh", "https://www.youtube.com/watch?v=pTB0EiLXUC8&ab_channel=ProgrammingwithMosh", Duration(7, 33), 1000);
    this->repo.add_repo("python2 tutorial", "mosh", "https://www.youtube.com/watch?v=_uQrJ0TkZlc", Duration(2, 43), 1000);
    this->repo.add_repo("web development", "traversy media", "https://www.youtube.com/watch?v=pB0WvcxTbCA", Duration(12, 45), 1000);
    this->repo.add_repo("digital photography", "adorama", "https://www.youtube.com/watch?v=gXO3iD5pfGI", Duration(20, 45), 1000);
    this->repo.add_repo("machine learning", "andrew ng", "https://www.youtube.com/watch?v=IpGxLWOIZy4", Duration(19, 20), 1000);
    this->repo.add_repo("spanish beginners", "languagetransfer", "https://www.youtube.com/watch?v=6Lby55-5Pm0", Duration(14, 28), 1000);
}

int Controller::add(const std::string& title, const std::string& presenter, const std::string& link, const Duration& dur, int likes) {
    for (const Tutorial& e : this->repo.get_elements()) {
        if (e.getTitle() == title && e.getPresenter() == presenter) {
            return 1;
        }
    }
    this->repo.add_repo(title, presenter, link, dur, likes);
    Tutorial t = Tutorial{ title, presenter, link, dur, likes };


    this->undoActions.push_back(make_unique<ActionAdd>(this->repo, t));
    //this->undoActions.push_back(std::move(make_unique<ActionAdd>(this->repo, t)));
    // with make_unique, the object is created and then moved into the vector
    ActionAdd* a = new ActionAdd{ this->repo, t };
    //this->undoActions.push_back(a);
    return 0;
}

void Controller::remove(const std::string& title, const std::string& presenter) {
    int i = 0;
    for (const Tutorial& e : this->repo.get_elements()) {
        if (e.getTitle() == title && e.getPresenter() == presenter) {
            break;
        }
        i++;
    }
    Tutorial t = this->repo.getElem(i);
    this->repo.remove_from_index(i);
    ActionRemove* a = new ActionRemove{ this->repo, t };
    //this->undoActions.push_back(a);
    this->undoActions.push_back(make_unique<ActionRemove>(this->repo, t));
    //this->undoActions.push_back(std::move(make_unique<ActionRemove>(this->repo, t)));



}

void Controller::update(const std::string& title, const std::string& presenter, const std::string& link, const Duration& dur, int likes) {
    int i = 0;
    for (const Tutorial& e : this->repo.get_elements()) {
        if (e.getTitle() == title && e.getPresenter() == presenter) {
            break;
        }
        i++;
    }
    Tutorial t = this->repo.getElem(i);
    //ActionUpdate a{ this->repo,Tutorial{title, presenter, t.getLink(),t.getDuration(),t.getLikes() } , Tutorial{title, presenter, link, dur, likes} };
    this->repo.update_repo(i, title, presenter, link, dur, likes);

    ActionUpdate* a = new ActionUpdate{ this->repo, Tutorial{title, presenter, t.getLink(),t.getDuration(),t.getLikes() }, Tutorial{title, presenter, link, dur, likes} };
    //this->undoActions.push_back(a);
    this->undoActions.push_back(make_unique<ActionUpdate>(this->repo, t, Tutorial{title, presenter, link, dur, likes}));
    //this->undoActions.push_back(std::move(make_unique<ActionUpdate>(this->repo, t, Tutorial{title, presenter, link, dur, likes})));

}

vector<Tutorial> Controller::list_all() {
    return this->repo.get_elements();
}

vector<Tutorial> Controller::list_presenter(const std::string& presenter) {
    const vector<Tutorial>& all_tutorials = this->repo.get_elements();

    vector<Tutorial> new_arr;
    std::copy_if(all_tutorials.begin(), all_tutorials.end(), std::back_inserter(new_arr),
        [&presenter](const Tutorial& e) {
            return e.getPresenter() == presenter || presenter.empty();
        });

    return new_arr;
}


void Controller::add_wl(Tutorial t) {
    this->wl->add(t);
    this->wl->writeToFile();

}

FilePlayList* Controller::list_wl() {
    return this->wl;
}

void Controller::updatePlayList(FilePlayList* new_pl)
{
	this->wl = new_pl;
}

std::map<std::string, int> Controller::get_by_presenter()
{
    std::map<std::string, int> m;
    for (const Tutorial& e : this->repo.get_elements()) {
        if (m.find(e.getPresenter()) == m.end()) {
			m[e.getPresenter()] = 1;
		} 
        else {
			m[e.getPresenter()]++;
		}
	}
	return m;
}

void Controller::undo()
{
    if (this->undoActions.empty())
    {
		throw std::exception("No more undo actions!");
	}
    this->undoActions.back()->executeUndo();
    //this->redoActions.push_back(move(this->undoActions.back()));
    this->redoActions.push_back(std::move(this->undoActions.back()));
    //this->redoActions.push_back(this->undoActions.back());
    this->undoActions.pop_back();
}

void Controller::redo() {
    if (this->redoActions.empty())
    {
		throw std::exception("No more redo actions!");
	}
    this->redoActions.back()->executeRedo();
    //this->undoActions.push_back(move(this->redoActions.back()));
    this->undoActions.push_back(std::move(this->redoActions.back()));
    //this->undoActions.push_back(this->redoActions.back());
    this->redoActions.pop_back();
}

void Controller::remove_wl(const std::string& title, const std::string& presenter, const std::string& answer) {
    int i = 0;
    for (const Tutorial& e : this->repo.get_elements()) {
        if (e.getTitle() == title && e.getPresenter() == presenter) {
            if (answer == "yes") {
                this->repo.like(i);
            }
            break;
        }
        i++;
    }
    i = 0;
    for (const Tutorial& e : this->wl->getTutorials() ){
        if (e.getTitle() == title && e.getPresenter() == presenter) {
			break;
		}
		i++;
	}

    this->wl->remove(i);
    this->wl->writeToFile();

}
