#pragma once
#include <vector>
#include <qwidget.h>
#include <qlayout.h>
#include <qpushbutton.h>
#include <qlistwidget.h>
#include <qtablewidget.h>
#include <qlineedit.h>
#include <QCoreApplication>
#include <QtNetwork\qnetworkaccessmanager.h>
#include <QtNetwork\qnetworkrequest.h>
#include <QtNetwork\qnetworkreply.h>
#include <qlabel.h>
#include <qimage.h>
#include <qfile.h>
#include <qcustomplot.h>
#include "Controller.h"
#include <QKeySequence>
#include <QShortcut>


class GUI : public QWidget
{
private:

	std::vector<Tutorial> iterateTutorials;
	int currentTutorialIndex;
	Controller& controller;

	QTableWidget* tutorialsListWidget;
	QTableWidget* playlistWidget;
	QTabWidget* tabWidget;

	QLineEdit* titleEdit;
	QLineEdit* presenterEdit;
	QLineEdit* durationEdit;
	QLineEdit* likesEdit;
	QLineEdit* linkEdit;
	QLineEdit* likeremove;

	QPushButton* addButton;
	QPushButton* removeButton;
	QPushButton* updateButton;

	QPushButton* undoButton;
	QPushButton* redoButton;

	QWidget* addDialog;
	QWidget* removeDialog;
	QWidget* updateDialog;

	QLabel* titleinfo;
	QLabel* presenterinfo;
	QLabel* durationinfo;
	QLabel* likesinfo;
	QLabel* linkinfo;

	QPushButton* nextButton;
	QPushButton* addwlButton; // add to watchlist button
	QPushButton* seePresenterButton; // see the tutorials of a presenter
	QPushButton* seeWathclistButton; // see the watchlist
	QPushButton* removetutorialButton; // remove a tutorial from the watchlist
	QPushButton* seePlaylistButton; // see the playlist (CSV /HTML)
	QPushButton* openTutorialButton; // open the tutorial in the browser
	QPushButton* seeWLTableView; // see the watchlist

	QHBoxLayout* mainUserLayout;

	QCustomPlot* plot;

	QWidget* addwlDialogWidget;
	QWidget* filterDialogWidget;
	QWidget* seeWLDialogWidget;

	QShortcut* undoShortcut;
	QShortcut* redoShortcut;

public:
	GUI(Controller& controller);
	void createPlaylist(const std::string& type);
	void updatePlaylist(FilePlayList* p);

private:
	void buildGUI();
	void populateList();

	void buildAdminGUI(QTabWidget* mainWidget);
	void buildUserGUI(QTabWidget* mainWidget);
	void buildPanelGUI(QTabWidget* mainWidget);

	void addButtonHandler();
	void addwlButtonHandler();
	void confirmAddButtonHandler();
	void deleteButtonHandler();
	void confirmDeleteButtonHandler();
	void updateButtonHandler();
	void confirmUpdateButtonHandler();

	void undoButtonHandler();
	void redoButtonHandler();

	void nextButtonHandler();

	void seePresenterButtonHandler();

	void filterConfirmButtonHandler();

	void seeWatchlistButtonHandler();
	void removeTutorialButtonHandler();
	void seePlaylistButtonHandler();

	void seeWLTableViewHandler();

	void updateLabel();

	void tabChanged();

	void updatePlot();

	void openTutorial();



};