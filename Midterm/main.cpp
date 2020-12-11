#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <exception>
using namespace std;

/* Constants */
#define BOOK_MAX_BORROW_TIME 10;
#define REFERENCE_MAX_BORROW_TIME 5;
#define MAGAZINE_MAX_BORROW_TIME 2
#define STUDENT_MAX__BOOK_BORROW 2
#define PROFESSOR_MAX__BOOK_BORROW 5
#define MAX_EXTEND_TIME 2

/* Exceptions */
class RepetitiveNameException : public std::exception
{
public:
    const char* what() const throw();
};
const char* RepetitiveNameException::what() const throw()
{
    return "Repetitive name error\n";
}

class RepetitiveStudentIDException : public std::exception
{
public:
    const char* what() const throw();
};
const char* RepetitiveStudentIDException::what() const throw()
{
    return "Repetitive student id error!\n";
}

class EmptyArgumentException : public std::exception
{
public:
    const char* what() const throw();
};
const char* EmptyArgumentException::what() const throw()
{
    return "Empty Argument Error.\n";
}

class AlreadyExtendedException : public std::exception
{
public:
    const char* what() const throw();
};
const char* AlreadyExtendedException::what() const throw()
{
    return "Error : the member has already extended the document twice\n";
}

class CannotBorrowException : public std::exception
{
public:
    const char* what() const throw();
};
const char* CannotBorrowException::what() const throw()
{
    return "The member cannot borrow the requested book at this time!\n";
}

class MemeberDoesNotExistException : public std::exception
{
public:
    const char* what() const throw();
};
const char* MemeberDoesNotExistException::what() const throw()
{
    return "The member does not exists!\n";
}

class DocumentDoesNotExistException : public std::exception
{
public:
    const char* what() const throw();
};
const char* DocumentDoesNotExistException::what() const throw()
{
    return "The document does not exists!\n";
}

class InvalidNumberException : public std::exception
{
public:
	InvalidNumberException(string _input_name) {input_name = _input_name;};
    const char* what() const throw();
private:
	string input_name;
};
const char* InvalidNumberException::what() const throw()
{
	string message= "Invalid Number: "+input_name+".\n";
    return message.c_str();;
}

class Person
{
public:
	Person(string _name)
	{	name=_name;
		max_book_borrow = 0;
		borrowed_book = 0;
		extended = 0;
	};
	virtual string get_role() = 0;
	string get_name(){return name;}
	int get_borrowed_book(){return borrowed_book;}
	bool can_borrow()
	{
		if(borrowed_book >= max_book_borrow) return false;
		return true;
	}
	void decrease_borrow()
	{
		if(borrowed_book > 0) borrowed_book--;
	}
	void increase_borrow(){borrowed_book++;}
	void reset()
	{
		decrease_borrow();
		extended = 0;
	}
	void extend()
	{
		if(extended < MAX_EXTEND_TIME) extended++;
	}
	bool is_extend_allowed()
  {
    if(extended < MAX_EXTEND_TIME) return true;
    return false;
  }
protected:
	string name;
	int max_book_borrow;
	int borrowed_book;
	int extended;
};

class Student : public Person
{
public:
	Student(string _name,string _student_id) : Person(_name)
	{
		student_id = stoi(_student_id);
		max_book_borrow = STUDENT_MAX__BOOK_BORROW;
	}
	int get_student_id(){return student_id;}
	string get_role(){return "Student";}
private:
	int student_id;
};

class Professor : public Person
{
public:
	Professor(string _name) : Person(_name)
	{
		max_book_borrow = PROFESSOR_MAX__BOOK_BORROW;
	};
	string get_role(){return "Professor";}
private:

};

class Document
{
public:
	Document(string _name,int _copies)
	{
		name=_name;
		copies = _copies;
		max_borrow_time = 1;
		borrowed = 0;
	}
	string get_name(){return name;}
	int get_max_borrow_time(){return max_borrow_time;}
	bool is_borrowable()
	{
		if(borrowed >= copies) return false;
		return true;
	}
	void decrease_borrow()
	{
		if(borrowed > 0) borrowed--;
	}
	void increase_borrow(){borrowed++;}
	void reset()
	{
		decrease_borrow();
	}
	virtual int calculate_punishment(int date,int deadline,int delay_before_extension)
	{
		int diff = calculate_diff_time(date,deadline,delay_before_extension);
		int punishment = 0;
		punishment = punish(diff);
		return punishment;
	}
	virtual int punish(int diff) = 0;
	int calculate_diff_time(int date,int deadline,int delay_before_extension);
protected:
	string name;
	int copies;
	int max_borrow_time;
	int borrowed;
};
int Document::calculate_diff_time(int date,int deadline,int delay_before_extension)
{
	int diff = (date - deadline);
	if(diff < 0) diff = delay_before_extension;
	else if(diff >= 0) diff += delay_before_extension;
	return diff;
}
class Book : public Document
{
public:
	Book(string _name,int _copies) : Document(_name,_copies)
	{
		max_borrow_time = BOOK_MAX_BORROW_TIME;
	}
	virtual int punish(int diff);
private:
};

int Book::punish(int diff)
{
	const int MAX_DAY = 7;
	const int MAX_MIDDLE_DAY = 21;
	const int MIN_MIDDLE_DAY = 8;
	const int PUNISHMENT_FOR_LOWER_DAY = 2000;
	const int PUNISHMENT_FOR_MIDDLE_DAY = 3000;
	const int PUNISHMENT_FOR_HIGHER_DAY = 5000;
	int punishment = 0;
	for(int day = 1; day <= diff;day++)
	{
		if(day <= MAX_DAY) punishment += PUNISHMENT_FOR_LOWER_DAY;
		else if(day >= MIN_MIDDLE_DAY && day <= MAX_MIDDLE_DAY) punishment += PUNISHMENT_FOR_MIDDLE_DAY;
		else punishment += PUNISHMENT_FOR_HIGHER_DAY;
	}
	return punishment;
}

class ReferenceBook : public Book
{
public:
	ReferenceBook(string _name,int _copies) : Book(_name,_copies)
	{
		max_borrow_time = REFERENCE_MAX_BORROW_TIME;
	}
	virtual int punish(int diff);
private:
};

int ReferenceBook::punish(int diff)
{
	const int MAX_DAY = 7;
	const int PUNISHMENT_FOR_LOWER_DAY = 5000;
	const int PUNISHMENT_FOR_HIGHER_DAY = 7000;
	int punishment = 0;
	for(int day = 1; day <= diff;day++)
	{
		if(day <= MAX_DAY) punishment += PUNISHMENT_FOR_LOWER_DAY;
		else punishment += PUNISHMENT_FOR_HIGHER_DAY;
	}
	return punishment;
}

class Magazine : public Document
{
public:
	Magazine(string _name, int _year, int _number, int _copies) : Document(_name,_copies)
	{
		year = _year;
		copies = _number;
		max_borrow_time = MAGAZINE_MAX_BORROW_TIME;
	}
	virtual int punish(int diff);
private:
	int year;
	int number;
};

int Magazine::punish(int diff)
{
	const int MAX_YEAR = 1390;
	const int PUNISHMENT_FOR_LOWER_YEAR = 2000;
	const int PUNISHMENT_FOR_HIGHER_YEAR = 3000;
	int punishment = 0;
	for(int day = 1; day <= diff;day++)
	{
		if(year <= MAX_YEAR) punishment += PUNISHMENT_FOR_LOWER_YEAR;
		else punishment += PUNISHMENT_FOR_HIGHER_YEAR;
	}
	return punishment;
}

class Borrow
{
public:
	Borrow(Document *_doc,Person *_borrower,int _deadline)
	{
		deadline = _deadline;
		borrower = _borrower;
		doc = _doc;
		_borrower->increase_borrow();
		_doc->increase_borrow();
		retured_status = false;
		total_days_delay_before_extension = 0;
		return_time = 0;
	};
	bool is_equal(Person *person,Document *document)
	{
		if(person == borrower && doc == document) return true;
		return false;
	}
	bool is_returned(){return retured_status;}
	void return_doc(int t)
	{
		retured_status = true;
		return_time = t;
	}
	void extend(int time)
	{
		deadline += time;
	}
	int calculate_punishment(Person *person,int date);
	int get_delay_before_extension(){return total_days_delay_before_extension;}
	void set_delay_before_extension(int t){total_days_delay_before_extension += t;}
	int get_deadline(){return deadline;}
	int get_return_time(){return return_time;}
private:
	Document *doc;
	Person *borrower;
	int deadline;
	int total_days_delay_before_extension;
	int return_time;
	bool retured_status;
};

int Borrow::calculate_punishment(Person *person,int date)
{
	if(person != borrower) return 0;
	return doc->calculate_punishment(date,deadline,total_days_delay_before_extension);
}

class BorrowSystem
{
public:
	int get_time(){return time;}
	void new_request(Person *person,Document *document);
	void advance_time(int t){time += t;}
	void return_document(Person *person,Document *document);
	void extend(Person *person,Document *document);
	int get_total_penalty(Person *person);
private:
	vector<Borrow*> borrows;
	int time = 0;
	int borrow_id(Person *person,Document *document);
	void punish(Borrow *borrow);
};

void BorrowSystem::extend(Person *person,Document *document)
{
	if(person->is_extend_allowed())
	{
		int borrow_id;
		Borrow *borrowed = borrows[borrow_id];
    if(borrowed != nullptr)
    {
      int diff = time - borrowed->get_deadline();
  		if(diff > 0) borrowed->set_delay_before_extension(diff);
  		int extend_time = document->get_max_borrow_time();
  		borrowed->extend(extend_time);
    }
	}
	else throw AlreadyExtendedException();
}

void BorrowSystem::new_request(Person *person,Document *document)
{
	if(person->can_borrow() && document->is_borrowable())
	{
		int deadline = document->get_max_borrow_time() + time;
		Borrow *borrow = new Borrow(document,person,deadline);
		borrows.push_back(borrow);
	}
	else throw CannotBorrowException();
}

void BorrowSystem::return_document(Person *person,Document *document)
{
	int borrow_id;
	Borrow *borrowed = borrows[borrow_id];
	borrowed->return_doc(time);
	person->reset();
	document->reset();
}

int BorrowSystem::borrow_id(Person *person,Document *document)
{
	for(int i = 0;i < borrows.size();i++)
	{
		if(borrows[i]->is_equal(person,document)) return i;
	}
	throw CannotBorrowException();
}

int BorrowSystem::get_total_penalty(Person *person)
{
	int total_penalty = 0;
	for(int i = 0;i < borrows.size();i++)
	{
		if(borrows[i]->is_returned()) total_penalty += borrows[i]->calculate_punishment(person,borrows[i]->get_return_time());
		else total_penalty += borrows[i]->calculate_punishment(person,time);
	}
	return total_penalty;
}

class Library
{
public:
	Library();
	void add_student_member(string student_id, string student_name);
	void add_prof_member(string prof_name);
	void add_book(string book_title, int copies);
	void add_reference(string book_title, int copies);
	void add_magazine(string magazine_title, int year, int number, int copies);
	void borrow(string member_name, string document_title);
	void extend(string member_name, string document_title);
	void return_document(string member_name, string document_title);
	int get_total_penalty(string member_name);
	vector<string> available_titles();
	int time_pass(int days);
private:
	vector<Person*> members;
	vector<Document*> documents;
	BorrowSystem *borrow_sys;
	bool user_exists(string student_name);
	bool is_valid(int n);
	void add_member(Person *new_member);
	bool document_exists(string name);
	void add_document(Document *new_doc);
	Person* find_member(string member_name);
	Document* find_document(string document_title);
};

Library::Library()
{
	borrow_sys = new BorrowSystem;
}

void Library::add_student_member(string student_id, string student_name)
{
	if(!user_exists(student_name))
	{
		Student *new_student = new Student(student_name,student_id);
		add_member(new_student);
	}
	else throw RepetitiveNameException();
}

void Library::add_prof_member(string prof_name)
{
	if(!user_exists(prof_name))
	{
		Professor *new_prof = new Professor(prof_name);
		add_member(new_prof);
	}
	else throw RepetitiveNameException();
}

void Library::add_member(Person *new_member)
{
	members.push_back(new_member);
}

bool Library::user_exists(string name)
{
	for(int i = 0;i < members.size();i++)
	{
		if(members[i]->get_name() == name) throw RepetitiveNameException();
	}
	return false;
}

void Library::add_book(string book_title, int copies)
{
	if(!is_valid(copies)) throw InvalidNumberException("Copies");
	else if(!document_exists(book_title))
	{
		Book *new_book = new Book(book_title,copies);
		add_document(new_book);
	}
	else throw RepetitiveNameException();
}

void Library::add_reference(string book_title, int copies)
{
	if(!is_valid(copies)) throw InvalidNumberException("Copies");
	else if(!document_exists(book_title))
	{
		ReferenceBook *new_book = new ReferenceBook(book_title,copies);
		add_document(new_book);
	}
	else throw RepetitiveNameException();
}

void Library::add_magazine(string magazine_title, int year, int number, int copies)
{
	if(!is_valid(year)) throw InvalidNumberException("Year");
	else if(!is_valid(number)) throw InvalidNumberException("Number");
	else if(!is_valid(copies)) throw InvalidNumberException("Copies");
	else if(!document_exists(magazine_title))
	{
		Magazine *new_mag = new Magazine(magazine_title,year,number,copies);
		add_document(new_mag);
	}
	else throw RepetitiveNameException();
}

void Library::add_document(Document *new_doc)
{
	documents.push_back(new_doc);
}

bool Library::document_exists(string name)
{
	if(name == "") throw EmptyArgumentException();
	for(int i = 0;i < documents.size();i++)
	{
		if(documents[i]->get_name() == name) throw RepetitiveNameException();
	}
	return false;
}

bool Library::is_valid(int n)
{
	if(n <= 0) return false;
	return true;
}

Person* Library::find_member(string member_name)
{
	for(int i = 0;i < members.size();i++)
	{
		if(members[i]->get_name() == member_name) return members[i];
	}
	return nullptr;
}

Document* Library::find_document(string document_title)
{
	for(int i = 0;i < documents.size();i++)
	{
		if(documents[i]->get_name() == document_title) return documents[i];
	}
	return nullptr;
}

void Library::borrow(string member_name, string document_title)
{
	Person *member = find_member(member_name);
	Document *doc = find_document(document_title);
	if(member == nullptr) throw MemeberDoesNotExistException();
	else if(doc == nullptr) throw DocumentDoesNotExistException();
	else borrow_sys->new_request(member,doc);
}

int Library::time_pass(int days)
{
	if(days < 0) throw InvalidNumberException("Days");
	borrow_sys->advance_time(days);
	return borrow_sys->get_time();
}

void Library::return_document(string member_name, string document_title)
{
	Person *member = find_member(member_name);
	Document *doc = find_document(document_title);
	if(member == nullptr) throw MemeberDoesNotExistException();
	else if(doc == nullptr) throw DocumentDoesNotExistException();
	else borrow_sys->return_document(member,doc);
}

vector<string> Library::available_titles()
{
	vector<string> titles;
	for(int i = 0;i < documents.size();i++)
	{
		if(documents[i]->is_borrowable())
			titles.push_back(documents[i]->get_name());
	}
	return titles;
}

void Library::extend(string member_name, string document_title)
{
	Person *member = find_member(member_name);
	Document *doc = find_document(document_title);
	if(member == nullptr) throw MemeberDoesNotExistException();
	if(doc == nullptr) throw DocumentDoesNotExistException();
	borrow_sys->extend(member,doc);
}

int Library::get_total_penalty(string member_name)
{
	Person *member = find_member(member_name);
	if(member == nullptr) throw MemeberDoesNotExistException();
	return borrow_sys->get_total_penalty(member);
}

int main()
{
	try
	{
		Library ut_lib =  Library();
		ut_lib.add_student_member("810199999", "Negar");
		ut_lib.add_student_member("810198888", "Naser");
		ut_lib.add_prof_member("Dr. Nagargar");
		ut_lib.add_prof_member("Dr. Naseri");
		ut_lib.add_book("Lean Startup", 1);
		ut_lib.add_magazine("Today News, vol.38, no.3", 1395, 3, 1);
		ut_lib.add_reference("Cambridge Dictionary", 3);
		ut_lib.borrow("Naser", "Lean Startup");
		vector<string> available_docs = ut_lib.available_titles();
		ut_lib.time_pass(10);
		ut_lib.extend("Naser", "Lean Startup");
		ut_lib.time_pass(12);
		ut_lib.return_document("Naser", "Lean Startup");
		ut_lib.borrow("Naser", "Cambridge Dictionary");
		ut_lib.time_pass(8);
		int penalty = ut_lib.get_total_penalty("Naser");
		cout << penalty << endl;
	}
	catch(exception &error)
	{
		cerr << error.what();
		exit(1);
	}
	return 0;
}
