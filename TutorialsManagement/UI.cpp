//#include "UI.h"
//#include <iostream>
//#include <string>
//
//using namespace std;
//
//UI::UI(const Controller& c) : controller{ c } {}
//
//UI::~UI() {}
//
//int readIntNumber(const std::string& message) {
//    int number;
//    cout << message;
//    while (!(std::cin >> number)) {
//        cout << "Invalid input. Please enter a number: ";
//        cin.clear(); // Clear the error state
//        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
//    }
//    return number;
//}
//
//void print_menu_admin() {
//    cout << "1. Add a new tutorial" << endl;
//    cout << "2. Delete a tutorial" << endl;
//    cout << "3. Update a tutorial" << endl;
//    cout << "4. List all tutorials" << endl;
//    cout << "0. Exit" << endl;
//}
//
//void print_menu_user() {
//    cout << "1. See the tutorials of a presenter" << endl;
//    cout << "2. See the watch list" << endl;
//    cout << "3. Remove tutorial" << endl;
//    cout << "4. See the watch list " << endl;
//    cout << "0. Exit" << endl;
//}
//
//void print_menu_wl() {
//    cout << "1. Add tutorial to watch list" << endl;
//    cout << "2. Next tutorial" << endl;
//    cout << "0. Exit" << endl;
//}
//
//void UI::add_tutorials_ui() {
//    this->controller.add_tutorials();
//}
//
//void UI::add_tutorial_ui() {
//    string title, presenter, link;
//    Duration duration;
//    int likes;
//    cout << "You are adding a new tutorial!" << endl;
//    cin.ignore();
//    cout << "Enter the title: ";
//    getline(cin, title);
//    cout << "Enter the presenter: ";
//    getline(cin, presenter);
//    cout << "Enter the link: ";
//    getline(cin, link);
//    cout << "Enter the duration: ";
//    int minutes, seconds;
//    minutes = readIntNumber("Enter the minutes: ");
//    seconds = readIntNumber("Enter the seconds: ");
//    duration.setMinutes(minutes);
//    duration.setSeconds(seconds);
//    likes = readIntNumber("Enter the likes: ");
//    int ok = this->controller.add(title, presenter, link, duration, likes);
//    if (ok == 1)
//        cout << "Tutorial already exists!" << endl;
//}
//
//void UI::delete_tutorial_ui() {
//    string title, presenter;
//    cin.ignore();
//    cout << "Enter the title: ";
//    getline(cin, title);
//    cout << "Enter the presenter: ";
//    getline(cin, presenter);
//    this->controller.remove(title, presenter);
//}
//
//void UI::update_tutorial_ui() {
//    string title, presenter, link;
//    Duration duration;
//    int likes;
//    cin.ignore();
//    cout << "Enter the title: ";
//    getline(cin, title);
//    cout << "Enter the presenter: ";
//    getline(cin, presenter);
//    cout << "Enter the link: ";
//    getline(cin, link);
//    cout << "Enter the duration: ";
//    int minutes, seconds;
//    minutes = readIntNumber("Enter the minutes: ");
//    seconds = readIntNumber("Enter the seconds: ");
//    duration.setMinutes(minutes);
//    duration.setSeconds(seconds);
//    duration.setMinutes(minutes);
//    duration.setSeconds(seconds);
//    likes = readIntNumber("Enter the likes: ");
//    this->controller.update(title, presenter, link, duration, likes);
//}
//
//void UI::list_all_ui() {
//    vector<Tutorial> arr = this->controller.list_all();
//    if (arr.empty()) {
//        cout << "No tutorials" << endl;
//    }
//    for (const auto& t : arr) {
//        cout << t.getTitle() << " " << t.getPresenter() << " " << t.getLink() << " " << t.getDuration().getMinutes() << ":" << t.getDuration().getSeconds() << " " << t.getLikes() << endl;
//    }
//}
//
//void UI::list_presenter_ui() {
//    string presenter;
//    cout << "Enter presenter: ";
//    cin.ignore();
//    getline(cin, presenter);
//    vector <Tutorial> arr = this->controller.list_presenter(presenter);
//    if (arr.empty()) {
//        cout << "No tutorials" << endl;
//        return;
//    }
//    int i = 0, poz = 1;
//    Tutorial current = arr[i];
//    cout << poz << ". " << current.getTitle() << " " << current.getPresenter() << " " << current.getLink() << " " << current.getDuration().getMinutes() << ":" << current.getDuration().getSeconds() << " " << current.getLikes() << endl;
//    //system(("start "+ current.getLink()).c_str());
//    while (1) {
//        print_menu_wl();
//        int option;
//        cout << "Enter option: ";
//        cin >> option;
//        cin.ignore();
//        cout << endl;
//        switch (option)
//        {
//        case 1:
//            this->controller.add_wl(current);
//            arr.erase(arr.begin() + i);
//            poz++;
//            if(arr.size() == 0) {
//				cout << "No more tutorials" << endl;
//				return;
//			}
//            if (i >= arr.size() - 1) {
//				i = 0;
//				current = arr[i];
//				cout << poz << ". " << current.getTitle() << " " << current.getPresenter() << " " << current.getLink() << " " << current.getDuration().getMinutes() << ":" << current.getDuration().getSeconds() << " " << current.getLikes() << endl;
//			}
//			else {
//				current = arr[i];
//				cout << poz << ". " << current.getTitle() << " " << current.getPresenter() << " " << current.getLink() << " " << current.getDuration().getMinutes() << ":" << current.getDuration().getSeconds() << " " << current.getLikes() << endl;
//				//system(("start " + current.getLink()).c_str());
//			}
//            break;
//        case 2:
//            if (i >= arr.size() - 1) {
//                i = 0;
//                poz = 1;
//                current = arr[i];
//                cout << poz << ". " << current.getTitle() << " " << current.getPresenter() << " " << current.getLink() << " " << current.getDuration().getMinutes() << ":" << current.getDuration().getSeconds() << " " << current.getLikes() << endl;
//            }
//            else {
//                i++;
//                poz++;
//                current = arr[i];
//                cout << poz << ". " << current.getTitle() << " " << current.getPresenter() << " " << current.getLink() << " " << current.getDuration().getMinutes() << ":" << current.getDuration().getSeconds() << " " << current.getLikes() << endl;
//                //system(("start " + current.getLink()).c_str());
//            }
//            break;
//        case 0:
//            return;
//            break;
//        default:
//            cout << "Invalid option" << endl;
//            break;
//        }
//    }
//}
//
//void UI::list_all_wl() {
//    cout << "Watch list: " << endl;
//    FilePlayList* wl = this->controller.list_wl();
//    if (wl->isEmpty()) {
//        cout << "No tutorials" << endl;
//        return;
//    }
//    vector <Tutorial> arr = wl->getTutorials();
//
//    for (const auto& t : arr) {
//        cout << t.getTitle() << " " << t.getPresenter() << " " << t.getLink() << " " << t.getDuration().getMinutes() << ":" << t.getDuration().getSeconds() << " " << t.getLikes() << endl;
//    }
//}
//
//void UI::remove_wl_ui() {
//    string title, presenter;
//    cin.ignore();
//    cout << "Enter the title: ";
//    getline(cin, title);
//    cout << "Enter the presenter: ";
//    getline(cin, presenter);
//    cout << "Did you like the tutorial? (yes/no)" << endl;
//    string answer;
//    cin >> answer;
//    this->controller.remove_wl(title, presenter, answer);
//}
//
//void UI::openPlaylist_ui() {
//	FilePlayList* p = this->controller.list_wl();
//	p->displayPlaylist();
//
//}
//
//void UI::run() {
//    while (1) {
//        cout << "Choose mode: " << endl;
//        cout << "1. Admin mode" << endl;
//        cout << "2. User mode" << endl;
//        cout << "0. Exit" << endl;
//        int option;
//        option = readIntNumber("Enter the option: ");
//        cout << endl;
//        switch (option) {
//        case 1:
//            run_admin();
//            break;
//        case 2:
//            run_user();
//            break;
//        case 0:
//            return;
//            break;
//        default:
//            cout << "Invalid option" << endl;
//            run();
//            break;
//        }
//    }
//}
//
//void UI::run_admin() {
//    while (1) {
//        print_menu_admin();
//        int option;
//        option = readIntNumber("Enter the option: ");
//        switch (option) {
//        case 1:
//            add_tutorial_ui();
//            break;
//        case 2:
//            delete_tutorial_ui();
//            break;
//        case 3:
//            update_tutorial_ui();
//            break;
//        case 4:
//            list_all_ui();
//            break;
//        case 0:
//            return;
//            break;
//        default:
//            cout << "Invalid option" << endl;
//            break;
//        }
//    }
//}
//
//void UI::run_user() {
//    while (1) {
//        print_menu_user();
//        int option;
//        option = readIntNumber("Enter the option: ");
//        switch (option) {
//        case 1:
//            list_presenter_ui();
//            break;
//        case 2:
//            list_all_wl();
//            break;
//        case 3:
//            remove_wl_ui();
//            break;
//        case 4:
//            openPlaylist_ui();
//			break;
//        case 0:
//            return;
//            break;
//        default:
//            cout << "Invalid option" << endl;
//            break;
//        }
//    }
//}
