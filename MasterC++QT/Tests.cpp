#include "Tests.h"
#include "Domain.h"
#include <assert.h>
#include <iostream>
#include "Repository.h"
#include "Controller.h"
using namespace std;

Tests::Tests()
{
}

Tests::~Tests()
{
}

void Tests::test_dynamic_array()
{
	vector <Tutorial> d;
	assert(d.size() == 0);
	Tutorial t1{ "title1", "presenter1", "link1", Duration(10,23), 20};
	d.push_back(t1);
	assert(d.size() == 1);
	vector <Tutorial> d2;
	d2 = d;
	assert(d2.size() ==1);
	d.erase(d.begin() + 0); 
	assert(d.size() == 0);
	d2 = d2;

}

void Tests::test_domain()
{
	Tutorial t1{ "title1", "presenter1", "link1", Duration(10,23), 20 };
	assert(t1.getTitle() == "title1");
	assert(t1.getPresenter() == "presenter1");
	assert(t1.getLink() == "link1");
	assert(t1.getDuration().getMinutes() == 10);
	assert(t1.getDuration().getSeconds() == 23);
	assert(t1.getLikes() == 20);
}

void Tests::test_repo() {
	Repository r = Repository("tests.txt");
	FilePlayList* w  = new CSVPlayList{ "test.csv" };
	Controller ctrl = Controller(r, w);
	assert(r.size() == 0);
	Tutorial t1{ "title1", "presenter1", "link1", Duration(10, 23), 20 };
	r.add_repo("title1", "presenter1", "link1", Duration(10, 23), 20);
	assert(r.size() == 1);
	r.remove_from_index(0);
	assert(r.size() == 0);
	w->add(t1);
	assert(w->size() == 1);
	w->remove(0);
}

void Tests::test_controller() {
	Repository r = Repository("tests.txt");
	FilePlayList* w = new CSVPlayList{ "test.csv" };
	Controller c = Controller(r,w) ;
	c.add("title1", "presenter1", "link1", Duration(10, 23), 20);
	c.add("title2", "presenter2", "link2", Duration(10, 23), 30);
	c.add("title3", "presenter3", "link3", Duration(10, 23), 40);
	c.add("title3", "presenter3", "link3", Duration(10, 23), 40);
	c.add("title4", "presenter4", "link4", Duration(10, 23), 40);
	assert(c.list_presenter("").size() == 4);
	assert(c.list_all().size() == 4);
	c.update("title2", "presenter2", "link2", Duration(10, 23), 30);
	c.remove("title3", "presenter3");
	assert(c.list_all().size() == 3);
	c.add_tutorials();
	assert(c.list_all().size() == 13);
	c.remove("c++ tutorial beginners", "freecodecamp.org");
	c.remove("python tutorial", "derek banas");
	c.remove("cooking with gordan ramsay", "gordan ramsay");
	c.remove("guitar", "justinguitar");
	c.remove("OOP in 7 minutes", "mosh");
	c.remove("python2 tutorial", "mosh");
	c.remove("web development", "traversy media");
	c.remove("digital photography", "adorama");
	c.remove("machine learning", "andrew ng");
	c.remove("spanish beginners", "languagetransfer");
	assert(c.list_presenter("presenter4").size() == 1);
	c.remove("title4", "presenter4");
	c.remove("title1", "presenter1");
	c.remove("title2", "presenter2");
	c.add_wl(Tutorial("title2", "presenter2", "link2", Duration(10, 23), 30));
	c.add_wl(Tutorial("title3", "presenter3", "link3", Duration(10, 23), 40));
	c.remove_wl("title4", "presenter4", "no");

}

void Tests::test_all()
{
	test_dynamic_array();
	test_domain();
	test_repo();
	test_controller();
}