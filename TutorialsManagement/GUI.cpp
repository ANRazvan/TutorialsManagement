#include "GUI.h"
#include <qlabel.h>
#include <qmessagebox.h>
#include <qheaderview.h>
#include <qtabwidget.h>
#include <Windows.h>
#include <QTableView>
#include <TableModel.h>


GUI::GUI(Controller& c) : controller{ c }
{
	this->buildGUI();
	this->populateList();

	this->iterateTutorials = this->controller.list_all();
	this->currentTutorialIndex = 0;

	connect(this->addButton, &QPushButton::clicked, this, &GUI::addButtonHandler);
	connect(this->removeButton, &QPushButton::clicked, this, &GUI::deleteButtonHandler);
	connect(this->updateButton, &QPushButton::clicked, this, &GUI::updateButtonHandler);

	connect(this->nextButton, &QPushButton::clicked, this, &GUI::nextButtonHandler);

	connect(this->seePresenterButton, &QPushButton::clicked, this, &GUI::seePresenterButtonHandler);
	connect(this->seeWathclistButton, &QPushButton::clicked, this, &GUI::seeWatchlistButtonHandler);
	connect(this->removetutorialButton, &QPushButton::clicked, this, &GUI::removeTutorialButtonHandler);
	connect(this->seePlaylistButton, &QPushButton::clicked, this, &GUI::seePlaylistButtonHandler);
	connect(this->addwlButton, &QPushButton::clicked, this, &GUI::addwlButtonHandler);
	connect(this->openTutorialButton, &QPushButton::clicked, this, &GUI::openTutorial);
	connect(this->undoButton, &QPushButton::clicked, this, &GUI::undoButtonHandler);
	connect(this->redoButton, &QPushButton::clicked, this, &GUI::redoButtonHandler);

	this->undoShortcut = new QShortcut(QKeySequence(Qt::CTRL | Qt::Key_Z), this);
	this->redoShortcut = new QShortcut(QKeySequence(Qt::CTRL | Qt::Key_Y), this);


	connect(this->undoShortcut, &QShortcut::activated, this, &GUI::undoButtonHandler);
	connect(this->redoShortcut, &QShortcut::activated, this, &GUI::redoButtonHandler);

	connect(this->seeWLTableView, &QPushButton::clicked, this, &GUI::seeWLTableViewHandler);

}

//void GUI::clearLayout(QLayout* layout) {
//	if (!layout)
//		return;
//	while (QLayoutItem* item = layout->takeAt(0)) {
//		if (QWidget* widget = item->widget()) {
//			delete widget;
//		}
//		delete item;
//	}
//
//}

void GUI::buildGUI()
{
	this->tabWidget = new QTabWidget{ this };
	this->tabWidget->setFixedSize(800, 600);

	this->buildAdminGUI(tabWidget);
	this->buildUserGUI(tabWidget);
	this->buildPanelGUI(tabWidget);

	QObject::connect(tabWidget, &QTabWidget::currentChanged, this, &GUI::tabChanged);
}


void GUI::populateList()
{
	this->tutorialsListWidget->setRowCount(0);

	int i = 0;
	for (auto p : this->controller.list_all())
	{
		this->tutorialsListWidget->insertRow(i);

		this->tutorialsListWidget->setItem(i, 0, new QTableWidgetItem(QString::fromStdString(p.getTitle())));
		this->tutorialsListWidget->setItem(i, 1, new QTableWidgetItem(QString::fromStdString(p.getPresenter())));
		Duration d = p.getDuration();
		this->tutorialsListWidget->setItem(i, 2, new QTableWidgetItem(QString::fromStdString(std::to_string(d.getMinutes()) + ":" + std::to_string(d.getSeconds()))));
		this->tutorialsListWidget->setItem(i, 3, new QTableWidgetItem(QString::fromStdString(std::to_string(p.getLikes()))));
		this->tutorialsListWidget->setItem(i, 4, new QTableWidgetItem(QString::fromStdString(p.getLink())));

	}

	this->tutorialsListWidget->resizeColumnsToContents();
}

void GUI::buildAdminGUI(QTabWidget* tabWidget)
{
	QWidget* mainWidget = new QWidget{};
	QVBoxLayout* mainLayout = new QVBoxLayout{};
	this->tutorialsListWidget = new QTableWidget{};
	this->tutorialsListWidget->setColumnCount(5);
	this->tutorialsListWidget->setShowGrid(true);
	this->tutorialsListWidget->setSelectionMode(QAbstractItemView::SingleSelection);
	this->tutorialsListWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
	this->tutorialsListWidget->setHorizontalHeaderLabels(QStringList() << QString("Title") << QString("Presenter") << QString("Duration")  << QString("Likes") << QString("Link"));
	this->tutorialsListWidget->horizontalHeader()->setStretchLastSection(true);

	mainLayout->addWidget(this->tutorialsListWidget);

	QGridLayout* bottomLayout = new QGridLayout{};

	this->addButton = new QPushButton{ "Add" };
	this->removeButton = new QPushButton{ "Remove" };
	this->updateButton = new QPushButton{ "Update" };
	this->undoButton = new QPushButton{ "Undo" };
	this->redoButton = new QPushButton{ "Redo" };

	bottomLayout->addWidget(this->addButton, 4, 0);
	bottomLayout->addWidget(this->removeButton, 4, 1);
	bottomLayout->addWidget(this->updateButton, 4, 2);
	bottomLayout->addWidget(this->undoButton, 4, 3);
	bottomLayout->addWidget(this->redoButton, 4, 4);

	mainLayout->addLayout(bottomLayout);

	mainWidget->setLayout(mainLayout);

	tabWidget->addTab(mainWidget, "Admin");
}

void GUI::buildUserGUI(QTabWidget* tabWidget)
{
	QWidget* mainWidget = new QWidget{};
	this->mainUserLayout = new QHBoxLayout{};
	QGridLayout* leftLayout = new QGridLayout{};

	this->titleinfo = new QLabel{ "Title: " };
	this->presenterinfo = new QLabel{ "Presenter: " };
	this->durationinfo = new QLabel{ "Duration: " };
	this->likesinfo= new QLabel{ "likes: " };

	leftLayout->addWidget(this->titleinfo, 0, 0);
	leftLayout->addWidget(this->presenterinfo, 1, 0);
	leftLayout->addWidget(this->durationinfo, 2, 0);
	leftLayout->addWidget(this->likesinfo, 3, 0);

	this->nextButton = new QPushButton{ "Next" };
	this->addwlButton = new QPushButton{ "Add to Watchlist" };
	this->seePresenterButton = new QPushButton{ "See Presenter" };
	this->seeWathclistButton = new QPushButton{ "See Watchlist" };
	this->removetutorialButton = new QPushButton{ "Remove Tutorial" };
	this->seePlaylistButton = new QPushButton{ "See Playlist" };
	this->openTutorialButton = new QPushButton{ "Open Tutorial" };
	this->seeWLTableView = new QPushButton{ "See Watchlist Table" };

	/*this->adoptButton = new QPushButton{ "Adopt" };
	this->filterButton = new QPushButton{ "Filter" };
	this->nextButton = new QPushButton{ "Next" };
	this->viewAllButton = new QPushButton{ "View All" };
	this->viewAdoptButton = new QPushButton{ "View Adoption List" };*/

	this->likeremove = new QLineEdit{};
	QLabel* likeremoveLabel = new QLabel{ "Like? yes/no: " };
	leftLayout->addWidget(seePresenterButton, 4, 0);
	leftLayout->addWidget(seeWathclistButton, 4, 1);
	leftLayout->addWidget(openTutorialButton, 5, 0);
	leftLayout->addWidget(seePlaylistButton, 5, 1);
	leftLayout->addWidget(nextButton, 6, 0);
	leftLayout->addWidget(addwlButton, 6, 1);
	leftLayout->addWidget(removetutorialButton, 7, 0);
	leftLayout->addWidget(likeremoveLabel, 7, 1);
	leftLayout->addWidget(this->likeremove, 7, 2);
	leftLayout->addWidget(seeWLTableView, 8, 0);


	/*this->imageLabel = new QLabel{};
	this->imageLabel->setFixedSize(400, 400);*/
	this->updateLabel();

	this->mainUserLayout->addLayout(leftLayout);
	//this->mainUserLayout->addWidget(this->imageLabel);

	mainWidget->setLayout(this->mainUserLayout);

	tabWidget->addTab(mainWidget, "User");
}

void GUI::buildPanelGUI(QTabWidget* mainWidget)
{
	this->plot = new QCustomPlot{};
	this->updatePlot();

	mainWidget->addTab(this->plot, "Data Panel");
}


void GUI::addButtonHandler()
{
	this->addDialog = new QWidget{};
	addDialog->setFixedSize(300, 300);
	addDialog->setWindowTitle("Add Tutorial");

	this->titleEdit = new QLineEdit{};
	this->presenterEdit = new QLineEdit{};
	this->likesEdit = new QLineEdit{};
	this->durationEdit = new QLineEdit{};
	this->linkEdit = new QLineEdit{};

	QLabel* titleLabel = new QLabel{ "Title: " };
	QLabel* presenterLabel = new QLabel{ "Presenter: " };
	QLabel* durationLabel = new QLabel{ "Duration: " };
	QLabel* likesLabel = new QLabel{ "Likes: " };
	QLabel* linkLabel = new QLabel{ "Link: " };

	QVBoxLayout* layout = new QVBoxLayout{};

	layout->addWidget(titleLabel);
	layout->addWidget(titleEdit);
	layout->addWidget(presenterLabel);
	layout->addWidget(presenterEdit);
	layout->addWidget(durationLabel);
	layout->addWidget(durationEdit);
	layout->addWidget(likesLabel);
	layout->addWidget(likesEdit);
	layout->addWidget(linkLabel);
	layout->addWidget(linkEdit);

	QPushButton* confirmButton = new QPushButton{ "Confirm" };

	layout->addWidget(confirmButton);

	addDialog->setLayout(layout);
	addDialog->show();

	connect(confirmButton, &QPushButton::clicked, this, &GUI::confirmAddButtonHandler);

}

void GUI::addwlButtonHandler()
{
	this->controller.add_wl(this->iterateTutorials[this->currentTutorialIndex]);
	this->currentTutorialIndex++;
	this->updateLabel();
}

void GUI::confirmAddButtonHandler() {
	try {
		// duration has mm:ss , where mm and ss are double
		std::string duration = this->durationEdit->text().toStdString();
		std::string title = this->titleEdit->text().toStdString();
		std::string presenter = this->presenterEdit->text().toStdString();
		std::string link = this->linkEdit->text().toStdString();
		int likes = std::stoi(this->likesEdit->text().toStdString());
		std::string minutes = duration.substr(0, duration.find(":"));
		std::string seconds = duration.substr(duration.find(":") + 1, duration.size());
		Duration d{ std::stod(minutes), std::stod(seconds) };
		this->controller.add(title, presenter, link, d,likes);
		/*this->controller.addController(this->breedLineEdit->text().toStdString(),
			this->nameLineEdit->text().toStdString(),
			std::stoi(this->ageLineEdit->text().toStdString()),
			this->photoLineEdit->text().toStdString());*/
		this->populateList();
	}
	catch (const std::exception& e) {
		QMessageBox messageBox;
		messageBox.critical(0, "Error", e.what());
		messageBox.setFixedSize(500, 200);
		messageBox.show();
		this->addDialog->close();
	}
	this->addDialog->close();

}

void GUI::deleteButtonHandler()
{
	this->removeDialog = new QWidget{};
	removeDialog->setFixedSize(300, 300);
	removeDialog->setWindowTitle("Remove Tutorial");

	this->titleEdit = new QLineEdit{};
	this->presenterEdit = new QLineEdit{};

	QLabel* titleLabel = new QLabel{ "Title: " };
	QLabel* presenterLabel = new QLabel{ "Presenter: " };

	QVBoxLayout* layout = new QVBoxLayout{};

	layout->addWidget(titleLabel);
	layout->addWidget(titleEdit);

	layout->addWidget(presenterLabel);
	layout->addWidget(presenterEdit);
	QPushButton* confirmButton = new QPushButton{ "Confirm" };

	layout->addWidget(confirmButton);

	removeDialog->setLayout(layout);
	removeDialog->show();

	connect(confirmButton, &QPushButton::clicked, this, &GUI::confirmDeleteButtonHandler);
}

void GUI::confirmDeleteButtonHandler()
{
	try {
		std::string title = this->titleEdit->text().toStdString();
		std::string presenter = this->presenterEdit->text().toStdString();
		this->controller.remove(title,presenter);
		this->populateList();
	}
	catch (const std::exception& e) {
		QMessageBox messageBox;
		messageBox.critical(0, "Error", e.what());
		messageBox.setFixedSize(500, 200);
		messageBox.show();
		this->removeDialog->close();
	}
	this->removeDialog->close();
}

void GUI::updateButtonHandler()
{
	this->updateDialog = new QWidget{};
	updateDialog->setFixedSize(300, 300);
	updateDialog->setWindowTitle("Update Tutorial");

	this->titleEdit = new QLineEdit{};
	this->presenterEdit = new QLineEdit{};
	this->likesEdit = new QLineEdit{};
	this->durationEdit = new QLineEdit{};
	this->linkEdit = new QLineEdit{};

	QLabel* titleLabel = new QLabel{ "Title: " };
	QLabel* presenterLabel = new QLabel{ "Presenter: " };
	QLabel* durationLabel = new QLabel{ "Duration: " };
	QLabel* likesLabel = new QLabel{ "Likes: " };
	QLabel* linkLabel = new QLabel{ "Link: " };

	QVBoxLayout* layout = new QVBoxLayout{};

	layout->addWidget(titleLabel);
	layout->addWidget(titleEdit);
	layout->addWidget(presenterLabel);
	layout->addWidget(presenterEdit);
	layout->addWidget(durationLabel);
	layout->addWidget(durationEdit);
	layout->addWidget(likesLabel);
	layout->addWidget(likesEdit);
	layout->addWidget(linkLabel);
	layout->addWidget(linkEdit);

	QPushButton* confirmButton = new QPushButton{ "Confirm" };

	layout->addWidget(confirmButton);

	updateDialog->setLayout(layout);
	updateDialog->show();

	connect(confirmButton, &QPushButton::clicked, this, &GUI::confirmUpdateButtonHandler);
}

void GUI::confirmUpdateButtonHandler()
{
	try {
		std::string title = this->titleEdit->text().toStdString();
		std::string presenter = this->presenterEdit->text().toStdString();
		std::string duration = this->durationEdit->text().toStdString();
		std::string link = this->linkEdit->text().toStdString();
		int likes = std::stoi(this->likesEdit->text().toStdString());
		std::string minutes = duration.substr(0, duration.find(":"));
		std::string seconds = duration.substr(duration.find(":") + 1, duration.size());
		Duration d{ std::stod(minutes), std::stod(seconds) };
		this->controller.update(title, presenter, link, d, likes);
		this->populateList();
	}
	catch (const std::exception& e) {
		QMessageBox messageBox;
		messageBox.critical(0, "Error", e.what());
		messageBox.setFixedSize(500, 200);
		messageBox.show();
		this->updateDialog->close();
	}
	this->updateDialog->close();
}

void GUI::undoButtonHandler()
{
	try {
		this->controller.undo();
		this->populateList();
	}
	catch (const std::exception& e){
		QMessageBox messageBox;
		messageBox.critical(0, "Error", "No more undos!");
		messageBox.setFixedSize(500, 200);
		messageBox.show();
	}

}

void GUI::redoButtonHandler()
{
	try {
		this->controller.redo();
		this->populateList();
	}
	catch (const std::exception& e) {
		QMessageBox messageBox;
		messageBox.critical(0, "Error", "No more redos!");
		messageBox.setFixedSize(500, 200);
		messageBox.show();
	}
}

void GUI::nextButtonHandler()
{
	this->currentTutorialIndex++;
	if(this->currentTutorialIndex == this->iterateTutorials.size())
		this->currentTutorialIndex = 0;
	this->updateLabel();
}

void GUI::seePresenterButtonHandler()
{
	this->filterDialogWidget = new QWidget{};
	filterDialogWidget->setFixedSize(300, 300);
	filterDialogWidget->setWindowTitle("Filter tutorials");

	this->presenterEdit = new QLineEdit{};

	QLabel* presenterLabel = new QLabel{ "Presenter" };

	QVBoxLayout* layout = new QVBoxLayout{};

	layout->addWidget(presenterLabel);
	layout->addWidget(presenterEdit);


	QPushButton* confirmButton = new QPushButton{ "Confirm" };

	layout->addWidget(confirmButton);

	filterDialogWidget->setLayout(layout);
	filterDialogWidget->show();

	QObject::connect(confirmButton, &QPushButton::clicked, this, &GUI::filterConfirmButtonHandler);
}

void GUI::filterConfirmButtonHandler() {
	//this->iterateTutorials = this->controller.list_presenter(this-);
	//this->currentPet = this->iteratePets.begin();
	//this->updateLabel();
	//this->filterDialog->close();

	this->iterateTutorials = this->controller.list_presenter(this->presenterEdit->text().toStdString());
	int currentTutorialIndex = 0;
	this->updateLabel();

	std::string presenter = this->presenterEdit->text().toStdString();
	this->filterDialogWidget->close();
}

void GUI::seeWatchlistButtonHandler()
{
	FilePlayList* fp = this->controller.list_wl();
	this->iterateTutorials = fp->getTutorials();
	this->currentTutorialIndex = 0;
	this->updateLabel();
}

void GUI::removeTutorialButtonHandler()
{
	// check if the tutorial is in the watchlist
	// if it is, remove it
	FilePlayList* fp = this->controller.list_wl();
	if(fp->size() == 0)
		return;
	std::string answer = this->likeremove->text().toStdString();
	this->controller.remove_wl(this->iterateTutorials[this->currentTutorialIndex].getTitle(), this->iterateTutorials[this->currentTutorialIndex].getPresenter(), answer);
	this->iterateTutorials = this->controller.list_wl()->getTutorials();
	this->currentTutorialIndex = 0;
	this->updateLabel();
}

void GUI::seePlaylistButtonHandler()
{
	FilePlayList* p = this->controller.list_wl();
	p->displayPlaylist();
}

void GUI::seeWLTableViewHandler()
{
	this->seeWLDialogWidget = new QWidget{};
	QVBoxLayout* layout = new QVBoxLayout{};
	seeWLDialogWidget->setFixedSize(500, 500);
	seeWLDialogWidget->setWindowTitle("Watchlist");

	// get the watchlist from the service
	std::vector<Tutorial> watchlist = this->controller.list_wl()->getTutorials();

	// create the watchlist model
	TableModel* model = new TableModel(*this->controller.list_wl());

	// create the table view and set the model
	QTableView* watchlistView = new QTableView{};
	watchlistView->setModel(model);
	watchlistView->setSelectionMode(QAbstractItemView::SingleSelection);
	watchlistView->setSelectionBehavior(QAbstractItemView::SelectRows);
	watchlistView->horizontalHeader()->setStretchLastSection(true);

	// add the table view to the layout
	layout->addWidget(watchlistView);
	this->seeWLDialogWidget->setLayout(layout);
	this->seeWLDialogWidget->show();

}

//void GUI::viewAdoptButtonHandler()
//{
//	this->adoptDialog = new QWidget{};
//	QVBoxLayout* layout = new QVBoxLayout{};
//	adoptDialog->setFixedSize(500, 500);
//	adoptDialog->setWindowTitle("Adoption list");
//
//	/*
//	this->adoptionListWidget = new QTableWidget{};
//	this->adoptionListWidget->setColumnCount(4);
//	this->adoptionListWidget->setShowGrid(true);
//	this->adoptionListWidget->setSelectionMode(QAbstractItemView::SingleSelection);
//	this->adoptionListWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
//	this->adoptionListWidget->setHorizontalHeaderLabels(QStringList() << QString("Breed") << QString("Name") << QString("Age") << QString("Photo Link"));
//	this->adoptionListWidget->horizontalHeader()->setStretchLastSection(true);
//
//
//	int i = 0;
//	std::vector<Dog> adoptionList = this->service.get_all_adopted()->getDogs();
//	for (auto p : adoptionList)
//	{
//		this->adoptionListWidget->insertRow(i);
//
//		this->adoptionListWidget->setItem(i, 0, new QTableWidgetItem(QString::fromStdString(p.get_breed())));
//		this->adoptionListWidget->setItem(i, 1, new QTableWidgetItem(QString::fromStdString(p.get_name())));
//		this->adoptionListWidget->setItem(i, 2, new QTableWidgetItem(QString::fromStdString(std::to_string(p.get_age()))));
//		this->adoptionListWidget->setItem(i, 3, new QTableWidgetItem(QString::fromStdString(p.get_photo())));
//		i++;
//	}
//
//	this->adoptionListWidget->resizeColumnsToContents();
//	layout->addWidget(this->adoptionListWidget);
//	this->adoptDialog->setLayout(layout);
//	this->adoptDialog->show();
//
//	*/
//
//	// get the adoption list from the service
//	std::vector<Dog> adoptionList = this->service.get_all_adopted()->getDogs();
//
//	// create the adoption list model
//	TableModel* model = new TableModel(*this->service.get_all_adopted());
//
//	// create the table view and set the model
//	QTableView* adoptionListView = new QTableView{};
//	adoptionListView->setModel(model);
//	adoptionListView->setSelectionMode(QAbstractItemView::SingleSelection);
//	adoptionListView->setSelectionBehavior(QAbstractItemView::SelectRows);
//	adoptionListView->horizontalHeader()->setStretchLastSection(true);
//
//	// add the table view to the layout
//	layout->addWidget(adoptionListView);
//	this->adoptDialog->setLayout(layout);
//	this->adoptDialog->show();
//}


void GUI::tabChanged()
{
	if (this->tabWidget->currentIndex() == 1) {
		qDebug() << "User tab selected";
		this->iterateTutorials = this->controller.list_all();
		this->currentTutorialIndex = 0;
		this->updateLabel();
	}
	else if (this->tabWidget->currentIndex() == 0) {
		qDebug() << "Admin tab selected";
		this->populateList();
	}
	else if (this->tabWidget->currentIndex() == 2) {
		qDebug() << "Panel tab selected";
		this->updatePlot();
	}
}



/*
Create a graphical representation of the data in your application. You have an example below: a bar chart representing the number of songs for each artist. 
Your representations can be a bar chart, a pie chart or another type of chart.
You can even use circles or rectangles or any other geometric shapes to represent the data.
*/


void GUI::updatePlot()
{
	std::map<std::string, int> tutorials = this->controller.get_by_presenter();

	QVector<double> ticks;
	QVector<QString> labels;
	QVector<double> data;

	int i = 0;
	for (const auto& t : tutorials)
	{
		ticks << i + 1;
		labels << QString::fromStdString(t.first);
		data << t.second;
		i++;
	}

	this->plot->clearPlottables(); // clear existing bars
	this->plot->legend->clearItems(); // clear existing legend items

	QVector<QColor> colors = {
		QColor(66, 133, 244),    // Blue
		QColor(219, 68, 55),     // Red
		QColor(244, 180, 0),     // Yellow
		QColor(15, 157, 88),     // Green
		QColor(171, 71, 188),    // Purple
		QColor(0, 172, 193),     // Cyan
		QColor(255, 87, 34),     // Deep Orange
		QColor(158, 158, 158)    // Grey
	};
	int colorIndex = 0;

	for (int j = 0; j < ticks.size(); j++)
	{
		QCPBars* bar = new QCPBars(this->plot->xAxis, this->plot->yAxis);
		QColor color = colors[colorIndex % colors.size()];
		bar->setBrush(QBrush(color));
		bar->setPen(QPen(color));

		QVector<double> singleTick;
		QVector<double> singleData;
		singleTick << ticks[j];
		singleData << data[j];
		bar->setData(singleTick, singleData);
		bar->setWidth(0.5);
		bar->setName(labels[j]);
		//this->plot->addPlottable(bar);

		colorIndex++;
	}

	this->plot->legend->setVisible(true);
	this->plot->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignTop | Qt::AlignLeft);

	// x-axis

	//QSharedPointer<QCPAxisTickerText> textTicker(new QCPAxisTickerText);
	//textTicker->addTicks(ticks, labels);
	//this->plot->xAxis->setTicker(textTicker);
	//QSharedPointer<QCPAxisTicker> numberTicker(new QCPAxisTicker);

	QSharedPointer<QCPAxisTickerFixed> numberTicker(new QCPAxisTickerFixed);
	numberTicker->setTickStep(1);
	numberTicker->setScaleStrategy(QCPAxisTickerFixed::ssNone);
	this->plot->xAxis->setTicker(numberTicker);
	this->plot->xAxis->setRange(0, i + 1);
	this->plot->xAxis->setTickLabelRotation(0);
	this->plot->xAxis->setSubTicks(true);
	this->plot->xAxis->setTickLength(0, 2);
	this->plot->xAxis->setBasePen(QPen(Qt::black));
	this->plot->xAxis->setTickPen(QPen(Qt::black));
	this->plot->xAxis->grid()->setVisible(true);
	this->plot->xAxis->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));
	this->plot->xAxis->setTickLabelColor(Qt::black);
	this->plot->xAxis->setLabelColor(Qt::black);

	// y-axis
	int maxCount = *std::max_element(data.constBegin(), data.constEnd());
	this->plot->yAxis->setRange(0, maxCount + 1);
	this->plot->yAxis->setPadding(5);
	this->plot->yAxis->setLabel("Number of tutorials");
	this->plot->yAxis->setBasePen(QPen(Qt::black));
	this->plot->yAxis->setTickPen(QPen(Qt::black));
	this->plot->yAxis->setSubTickPen(QPen(Qt::white));
	this->plot->yAxis->grid()->setSubGridVisible(true);
	this->plot->yAxis->setTickLabelColor(Qt::black);
	this->plot->yAxis->setLabelColor(Qt::black);
	this->plot->yAxis->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::SolidLine));
	this->plot->yAxis->grid()->setSubGridPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));

	this->plot->replot();
}

//void GUI::updatePlot()
//{
//	//QVector<double> x(10), y(10);
//	//for (int i = 0; i < 10; i++)
//	//{
//	//	x[i] = i;
//	//	y[i] = i * i;
//	//}
//	//this->plot->addGraph();
//	//this->plot->graph(0)->setData(x, y);
//	//this->plot->xAxis->setLabel("x");
//	//this->plot->yAxis->setLabel("y");
//	//this->plot->xAxis->setRange(0, 10);
//	//this->plot->yAxis->setRange(0, 100);
//	//this->plot->replot();
//	// graphical repres
//    std::vector<Tutorial> tutorials = this->controller.list_all();
//	std::map<std::string, int> presenterTutorials;
//	for (auto t : tutorials)
//	{
//		if (presenterTutorials.find(t.getPresenter()) == presenterTutorials.end())
//			presenterTutorials[t.getPresenter()] = 0;
//		presenterTutorials[t.getPresenter()]++;
//	}
//	QVector<QString> labels;
//	QVector<double> values;
//	for (auto it : presenterTutorials)
//	{
//		labels << QString::fromStdString(it.first);
//		values << it.second;
//	}
//	QCPBars* bars = new QCPBars(this->plot->xAxis, this->plot->yAxis);
//	this->plot->addPlottable(bars);
//	bars->setData(values);
//	this->plot->xAxis->setAutoTicks(false);
//	this->plot->xAxis->setAutoTickLabels(false);
//	this->plot->xAxis->setTickVectorLabels(labels);
//	this->plot->xAxis->setSubTickCount(0);
//	this->plot->xAxis->setTickLength(0, 4);
//	this->plot->xAxis->grid()->setVisible(true);
//	this->plot->yAxis->setLabel("Number of tutorials");
//	this->plot->xAxis->setLabel("Presenter");
//	this->plot->rescaleAxes();
//	this->plot->replot();
//}

void GUI::updatePlaylist(FilePlayList* newpl)
{
	this->controller.updatePlayList(newpl);
	this->iterateTutorials = this->controller.list_wl()->getTutorials();
	this->currentTutorialIndex = 0;
	this->updateLabel();
}


void GUI::updateLabel()
{

	if(this->currentTutorialIndex == this->iterateTutorials.size())
		this->currentTutorialIndex = 0;

	if (this->iterateTutorials.size() == 0)
	{
		this->titleinfo->setText(QString::fromStdString("Title: -" ));
		this->presenterinfo->setText(QString::fromStdString("Presenter: -"));
		this->durationinfo->setText(QString::fromStdString("Duration: -"));
		this->likesinfo->setText(QString::fromStdString("Likes: -"));
		return;
	}

	Tutorial t = this->iterateTutorials[this->currentTutorialIndex];
	 
	this->titleinfo->setText(QString::fromStdString("Title: " + t.getTitle()));
	this->presenterinfo->setText(QString::fromStdString("Presenter: " + t.getPresenter()));
	this->durationinfo->setText(QString::fromStdString("Duration: " + std::to_string(t.getDuration().getMinutes()) + ":" + std::to_string(t.getDuration().getSeconds())));
	this->likesinfo->setText(QString::fromStdString("Likes: " + std::to_string(t.getLikes())));

}

void GUI::createPlaylist(const std::string& type)
{
	if (type == "CSV" || type == "csv")
	{
		FilePlayList* p = new CSVPlayList{ "playlist.csv" };
		this->updatePlaylist(p);
	}
	else if (type == "HTML" || type == "html")
	{
		FilePlayList* p = new HTMLPlayList{ "playlist.html" };
		this->updatePlaylist(p);
	}
}

void GUI::openTutorial()
{
	Tutorial t = this->iterateTutorials[this->currentTutorialIndex];
	std::string link = t.getLink();
	//ShellExecuteA(NULL, "open", link.c_str(), NULL, NULL, SW_SHOWNORMAL);
	system(("start " + t.getLink()).c_str());
}

