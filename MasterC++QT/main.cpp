//#include "MasterC_QT.h"
//#include <QtWidgets/QApplication>
//
//int main(int argc, char *argv[])
//{
//    QApplication a(argc, argv);
//    MasterC_QT w;
//    w.show();
//    return a.exec();
//}

#include <QApplication>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QDebug>
#include "GUI.h"
#include "UI.h"
#include "FilePlaylist.h"
#include "RepositoryExceptions.h"
#include <iostream>
using namespace std;

int main(int argc, char* argv[]){
    // THIS IS WORKING
    QApplication app(argc, argv);
    FilePlayList* p = nullptr;
    Repository repo("Tutorials.txt");
    Controller ctrl(repo);
    GUI gui(ctrl);
    /*gui.show();
    delete p;*/


    // Create widgets
    QLabel label("What type of file would you like to use to store the playlist ?");
    QLineEdit fileTypeEdit;
    QPushButton startButton("Start");

    // Layout setup
    QVBoxLayout layout;
    layout.addWidget(&label);
    layout.addWidget(&fileTypeEdit);
    layout.addWidget(&startButton);

    // Signal-slot connections
    QObject::connect(&startButton, &QPushButton::clicked, [&]() {
        QString fileType = fileTypeEdit.text().trimmed().toLower();
        if (fileType == "csv" || fileType == "html")
        {
            // Start the application
            // For now, let's just print the file type
            try {
                /*Repository repo("Tutorials.txt");
                FilePlayList* p = nullptr;*/
                /*Controller ctrl(repo, p);
                qDebug() << "Debug message: ";*/
                //GUI gui(ctrl);

                // WHY IS THIS NOT WORKING ?
                // THE WINDOW OPENS AND CLOSES IMMEDIATELY
                std::string type = fileType.toStdString();
                gui.createPlaylist(type);
                gui.show();
                delete p;
            }
            catch (FileException&)
            {
                cout << "Repository file could not be opened! The application will terminate." << endl;
            }
            qDebug() << "File type selected:" << fileType;
        }
        else
        {
            QMessageBox::critical(nullptr, "Error", "Invalid file type. Please enter CSV or HTML.");
        }
        });

    //// Create a main window
    QWidget window;
    window.setLayout(&layout);
    window.show();

    return app.exec();
}

