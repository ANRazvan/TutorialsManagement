#include "FilePlayList.h"
#include <fstream>
#include <Windows.h>
#include <shellapi.h>

FilePlayList::FilePlayList(std::string filename) : filename{ filename } {

}

CSVPlayList::CSVPlayList(std::string filename) : FilePlayList(filename) {

}

void CSVPlayList::writeToFile() {
	std::ofstream out(filename);
	for (auto t : tutorials) {
		out << t;
	}
	out.close();
}

void CSVPlayList::displayPlaylist() {
	ShellExecuteA(NULL, "open", "excel.exe", filename.c_str(), NULL, SW_SHOWMAXIMIZED);
}

HTMLPlayList::HTMLPlayList(std::string filename) : FilePlayList(filename) {

}

void HTMLPlayList::writeToFile() {
	std::ofstream out(filename);
	out << "<!DOCTYPE html>\n<html>\n<head>\n<title>Playlist</title>\n</head>\n<body>\n<table border=\"1\">\n<tr>\n<td>Title</td>\n<td>Presenter</td>\n<td>Duration</td>\n<td>Link</td>\n</tr>\n";
	for (auto t : tutorials) {
		out << "<tr>\n<td>" << t.getTitle() << "</td>\n<td>" << t.getPresenter() << "</td>\n<td>" << t.getDuration().getMinutes() << ":" << t.getDuration().getSeconds() << "</td>\n<td><a href=\"" << t.getLink() << "\">Link</a></td>\n</tr>\n";
	}
	out << "</table>\n</body>\n</html>";
	out.close();
}

void HTMLPlayList::displayPlaylist() {
	//"D:/Facultate/OOP/oop-a8-9-ANRazvan/MasterC++QT/MasterC++QT/playlist.html"
	std::string path = "file:///D:/Facultate/OOP/oop-a8-9-ANRazvan/MasterC++QT/MasterC++QT/playlist.html";
	ShellExecuteA(NULL, "open", "msedge.exe", path.c_str(), NULL, SW_SHOWMAXIMIZED);
}

