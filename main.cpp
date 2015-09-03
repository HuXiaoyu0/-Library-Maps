#include <iostream>
#include <map>
#include <cassert>
#include <string>
#include <vector>

using namespace std;

// two data structures store all of the information for efficiency
typedef map<string, int> LIBRARY_TYPE;
typedef map<string, vector<string> > PEOPLE_TYPE;
typedef map<string, vector<string> > BOOK_TYPE;


// prototypes for the helper functions
void addItem(LIBRARY_TYPE& library);
void checkoutItem(LIBRARY_TYPE& library, PEOPLE_TYPE& people);
void returnItems(LIBRARY_TYPE& library, PEOPLE_TYPE& people);
void lookup(LIBRARY_TYPE& library);
void printPeople(PEOPLE_TYPE& people);


int main() {
  LIBRARY_TYPE library;
  PEOPLE_TYPE people;
  char c;
  while (std::cin >> c) {
    if (c == 'a') {
      addItem(library);
    } else if (c == 'c') {
      checkoutItem(library,people);
    } else if (c == 'r') {
      returnItems(library,people);
    } else if (c == 'l') {
      lookup(library);
    } else if (c == 'p') {
      printPeople(people);
    } else {
      std::cerr << "error unknown char " << c << std::endl;
      exit(0);
    }
  }
}


void addItem(LIBRARY_TYPE& library) {
  std::string title;
  int num;
  std::cin >> num >> title;
  for (int i = 0; i < num; i++)
  ++library[title];
  cout<<"added "<<num<<" copies of "<<title<<endl;
}


void checkoutItem(LIBRARY_TYPE& library, PEOPLE_TYPE& people, BOOK_TYPE& book) {
  std::string name;
  std::string title;
  std::cin >> name >> title;
  LIBRARY_TYPE::iterator ite;
  PEOPLE_TYPE::iterator itr;

  ite = library.find(title);
  itr = people.find(name);

  if (ite != library.end()){
  --library[title];
  cout<<name<<" checked out "<<title;
  people[name].push_back(title);
  book[title].push_back(name);
  }
  else
  cout<<"don't have "<<title<<" in library"<<endl;
}


void returnItems(LIBRARY_TYPE& library, PEOPLE_TYPE& people, BOOK_TYPE& book) {
  std::string name;
  std::cin >> name;
  PEOPLE_TYPE::iterator itr;
  itr = people.find(name);
  if (itr == people.end() || itr->second.size() == 0)
	  cout<<name<<" has no items checked out"<<endl;
  else{
  vector<string>::iterator ite;
  ite = itr->second.begin();
  for (; ite != itr->second.end(); ite++){
      itr->second.erase(ite);
	  ++library[*ite];

	  BOOK_TYPE::iterator i = book.find(*ite);
	  vector<string>::iterator j;
	  for (j = i->second.begin(); j != i->second.end(); i++)
		  if (*j == name)
			  i->second.erase(j);  
  }
  cout<<name<<" returned "<<itr->second.size()<<" item"<<endl;
  }
}


void lookup(LIBRARY_TYPE& library,  BOOK_TYPE& book) {
  std::string title;
  std::cin >> title;
  LIBRARY_TYPE::iterator ite;
  BOOK_TYPE::iterator itr;
  ite = library.find(title);
  itr = book.find(title);
  if (ite == library.end())
	  cout<<"don't have "<<title<<" in library"<<endl;
  else{
	  cout<<"library info for: "<<title<<endl;
	  cout<<"  "<<ite->second<<"copies available"<<endl;
	  cout<<"  "<<itr->second.size()<<"checked out by:"<<endl;
	  
	  for (int i = 0; i < itr->second.size(); i++)
	  cout<<"    "<<(itr->second)[i]<<endl;
  }
}


void printPeople(PEOPLE_TYPE& people) {
	//empty people???

	PEOPLE_TYPE::iterator ite;
	for (ite = people.begin(); ite != people.end(); ite++){
		cout<<ite->first<<" has this item checked out:"<<endl;
		for (int i = 0; i < ite->second.size(); i++)
			cout<<"  "<<(ite->second)[i]<<endl;
	}
}

