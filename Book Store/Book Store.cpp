// Book Store.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iterator>
#include <sstream>
#include <map>
#include <algorithm>
#include <cctype>

using namespace std;

vector<string> split(string str, char delim);

class Book
{
public:
	string id;
	string name;
	string date_published;
};

map<string, Book> bookstore;
void load();
void commit();
void add_book();
Book find_book();
void search();
void view_all_books();
void update_book();

int Startup()
{
	system("cls");
	char Choice;
	cout << "Simple Book Store " << endl << endl;
	cout << "Select one of the following:" << endl << endl;

	cout << "1. Add a new book " << endl;
	cout << "2. Delete a book " << endl;
	cout << "3. Find a book " << endl;
	cout << "4. View all book " << endl;
	cout << "5. Update book " << endl;
	cout << "6. Search book " << endl;
	cout << "7. Exit" << endl << endl;

	cout << "Enter your Choice: ";
	cin >> Choice;

	if (!isdigit(Choice) || atoi(&Choice) > 7) {
		return -1;
	}

	return atoi(&Choice);

}

void add_book() {
	string line;

	Book book;
	cout << "Name of book: ";
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	getline(cin, book.name);
	cout << "Date published: ";
	getline(cin, book.date_published);
	//cin >> book.date_published;
	cout << "Id: ";
	cin >> book.id;
	map<string, Book>::iterator itr;
	itr = bookstore.find(book.id);
	if (itr != bookstore.end()) {
		cout << "Could not add book! ID already exists!" << endl;
		system("pause");
	}
	else {
		//bookstore.insert(pair<string, Book>(book.id, book));
		bookstore.emplace(book.id, book);
		commit();
	}
	//thefile << name << "," << date_published << "," << id << endl;
	//thefile.flush();


}

void delete_book() {
	map<string, Book>::iterator itr;
	string id;
	cout << "What is the id of the book you want to delete? ";
	cin >> id;
	itr = bookstore.find(id);
	if (itr == bookstore.end()) {
		cout << "Could not find book!" << endl;
		system("pause");
		return;
	}
	bookstore.erase(itr);
	commit();

}

Book find_book() {
	map<string, Book>::iterator itr;
	string id;
	Book book;
	cout << "What is the id of the book you want to find? ";
	cin >> id;
	itr = bookstore.find(id);
	if (itr == bookstore.end()) {
		//cout << "Could not find book.";
		book.name = "No Book Found";
		book.date_published = "Null";
		book.id = "Null";
		return book;
	}
	else {
		book.name = itr->second.name;
		book.date_published = itr->second.date_published;
		book.id = itr->second.id;
		return book;
	}

}

void search() {
	string searchCri;
	cout << "Search for? " << endl;
	getline(cin, searchCri);
	getline(cin, searchCri);
	std::locale loc;
	map<string, Book>::iterator itr = bookstore.begin();
	while (itr != bookstore.end()) {
		string id = itr->first;
		Book book = itr->second;
		string name = book.name;
		transform(name.begin(), name.end(), name.begin(), [](unsigned char c) { return std::tolower(c); });
		transform(searchCri.begin(), searchCri.end(), searchCri.begin(), [](unsigned char c) { return std::tolower(c); });
		if (book.id.find(searchCri) != string::npos || book.date_published.find(searchCri) != string::npos || name.find(searchCri) != string::npos) {
			cout << "Name: " << book.name << endl;
			cout << "Date Published: " << book.date_published << endl;
			cout << "ID: " << book.id << endl;
			cout << endl;
		}

		itr++;
	}
	system("pause");
}

void view_all_books() {
	map<string, Book>::iterator itr = bookstore.begin();
	while (itr != bookstore.end()) {
		string id = itr->first;
		Book book = itr->second;
		if (book.id != "id") {
			cout << "Name: " << book.name << endl;
			cout << "Date Published: " << book.date_published << endl;
			cout << "ID: " << book.id << endl;
			cout << endl;
		}

		itr++;
	}
	system("pause");
}

void update_book() {
	map<string, Book>::iterator itr;
	string id;
	Book book;
	int choice;
	cout << "What is the id of the book you want to update? ";
	cin >> id;
	itr = bookstore.find(id);
	if (itr == bookstore.end()) {
		cout << "Could not find book by id given." << endl;
		system("pause");
	}
	else {
		book.name = itr->second.name;
		book.date_published = itr->second.date_published;
		book.id = itr->second.id;
		cout << "What would you like to update?" << endl;
		cout << "1. Name" << endl;
		cout << "2. Date" << endl;
		cin >> choice;
		if (choice == 1) {
			string name;
			cout << "Name: ";
			getline(cin, name);
			getline(cin, name);
			itr->second.name = name;
		}
		else if (choice == 2) {
			string date;
			cout << "Date: ";
			getline(cin, date);
			getline(cin, date);
			itr->second.date_published = date;
		}
		commit();
	}

}


int main()
{
	load();
	while (true)
	{
		int Choice = Startup();
		while (Choice == -1) {
			Choice = Startup();
		}
		if (Choice == 1)
		{
			// Add Book
			add_book();
		}
		else if (Choice == 2)
		{
			// Delete Book
			delete_book();
		}
		else if (Choice == 3)
		{
			// Find Book
			Book book = find_book();
			cout << "Name: " << book.name << endl;
			cout << "Date Published: " << book.date_published << endl;
			system("pause");
		}
		else if (Choice == 4)
		{
			// View all book
			view_all_books();
		}
		else if (Choice == 5)
		{
			//Update book
			update_book();
		}
		else if (Choice == 6)
		{
			//Search book
			search();
		}
		else if (Choice == 7)
		{
			cout << "Goodbye";
			exit(0);
		}
	}
}

vector<string> split(string str, char delim) {
	vector<string> result;
	stringstream s_stream(str); //create string stream from the string
	while (s_stream.good()) {
		string substr;
		getline(s_stream, substr, delim); //get first string delimited by comma
		result.push_back(substr);
	}
	return result;
}

void load() {
	fstream thefile("data.csv");

	string line;

	while (getline(thefile, line)) {
		vector<string> csv = split(line, ',');
		Book book;
		book.name = csv.at(0);
		book.date_published = csv.at(1);
		book.id = csv.at(2);
		bookstore.insert(pair<string, Book>(book.id, book));
	}
}

void commit() {
	ofstream thefile;
	thefile.open("data.csv", fstream::out);
	map<string, Book>::iterator itr = bookstore.begin();
	thefile << "name,date_published,id" << endl;
	while (itr != bookstore.end()) {
		string id = itr->first;
		Book book = itr->second;
		thefile << book.name << "," << book.date_published << "," << book.id << endl;
		itr++;
	}


	thefile.close();
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
