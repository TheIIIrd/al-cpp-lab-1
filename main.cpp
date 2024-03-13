/*
Лабораторная работа 1. Изучение классов языка Си++

Вариант 19
Класс - студент. Параметры (поля): ФИО, массив экзаменационных оценок (m=4).
Статус доступа всех полей private. Класс включает: конструктор и функцию
определения среднего балла, при необходимости функции доступа к полям,
функцию печати параметров. Напечатать параметры всех студентов и 3-х
самых сильных студентов группы.
*/

#include <cstddef>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;

class Student {
  friend ostream &operator<<(ostream &os, const Student &student);

private:
  string _USERNAME;
  pmr::vector<size_t> _MARKS;

public:
  Student();
  void set_name(string &_NAME);
  string get_name();
  void add_mark(size_t &_MARK);
  double get_aver_mark() const;
};

Student::Student() {
  this->_USERNAME = "";
  this->_MARKS.clear();
}

void Student::set_name(string &_NAME) {
  if (_NAME.empty()) {
    cerr << "[-] _NAME is empty" << endl;
    return;
  }

  this->_USERNAME = _NAME;

  return;
}

string Student::get_name() { return this->_USERNAME; }

void Student::add_mark(size_t &_MARK) {
  if (_MARK < 0 || _MARK > 5) {
    cerr << "[-] _MARK is incorrect" << endl;
    return;
  }

  this->_MARKS.push_back(_MARK);

  return;
}

double Student::get_aver_mark() const {
  if (this->_MARKS.empty())
    return 0.0;
  else {
    size_t _SIZE = this->_MARKS.size();
    double _MARKS_SUM = 0;

    for (size_t i = 0; i < _SIZE; ++i) {
      _MARKS_SUM += this->_MARKS[i];
    }

    return (_MARKS_SUM / _SIZE);
  }
}

ostream &operator<<(ostream &os, const Student &student) {
  if (student._USERNAME.empty())
    os << endl << "Unidentified student ";
  else
    os << endl << student._USERNAME << ' ';

  if (student._MARKS.empty())
    os << "There are no grades " << endl;
  else {
    size_t _SIZE = student._MARKS.size();
    for (size_t i = 0; i < _SIZE; ++i) {
      os << student._MARKS[i] << ' ';
    }
    os << endl << "Average : " << student.get_aver_mark() << endl;
  }

  return os;
}

class Stgroup {
  friend ostream &operator<<(ostream &os, const Stgroup &stgroup);
  friend istream &operator>>(istream &is, Stgroup &stgroup);

private:
  pmr::vector<Student> _STUDENTS;
  pmr::vector<double> _AVER;
  size_t _NUMBER;

public:
  Stgroup();
  void add_student(string &_NAME, vector<size_t> _MARKS);
  void print_top();
};

Stgroup::Stgroup() {
  this->_STUDENTS.clear();
  this->_AVER.clear();
  this->_NUMBER = 0;
}

void Stgroup::add_student(string &_NAME, vector<size_t> _MARKS) {
  if (_NAME.empty()) {
    cerr << "[-] _NAME is empty" << endl;
    return;
  }

  if (_MARKS.empty()) {
    cerr << "[-] _MARKS are empty" << endl;
    return;
  }

  Student _NEWCOMER;
  size_t _SIZE = _MARKS.size();
  _NEWCOMER.set_name(_NAME);

  for (size_t i = 0; i < _SIZE; ++i) {
    _NEWCOMER.add_mark(_MARKS[i]);
  }

  this->_STUDENTS.push_back(_NEWCOMER);
  this->_AVER.push_back(_NEWCOMER.get_aver_mark());
  this->_NUMBER += 1;

  return;
}

void Stgroup::print_top() {
  if (this->_STUDENTS.empty()) {
    cerr << "[-] _STUDENTS are empty" << endl;
    return;
  }

  map<double, Student> _MAP;
  for (size_t i = 0; i < this->_STUDENTS.size(); ++i) {
    _MAP[this->_AVER[i]] = this->_STUDENTS[i];
  }

  size_t counter = 0;

  for (auto it = _MAP.rbegin(); it != _MAP.rend(); ++it) {
    Student *temp = &it->second;
    cout << it->first << ' ' << temp->get_name() << endl;

    counter += 1;
    if (counter == 3) {
      return;
    }
  }
  return;
}

ostream &operator<<(ostream &os, const Stgroup &stgroup) {
  if (stgroup._STUDENTS.empty()) {
    os << "There are no students" << endl;
    return os;
  }

  for (size_t i = 0; i < stgroup._NUMBER; ++i) {
    os << stgroup._STUDENTS[i];
  }

  os << "Total " << stgroup._NUMBER << endl;

  return os;
}

istream &operator>>(istream &is, Stgroup &stgroup) {
  string _NAME = "";
  size_t _SIZE = 0;
  size_t _MARK = 0;
  size_t _AMOUNT = 0;

  is >> _AMOUNT;

  for (size_t i = 0; i < _AMOUNT; ++i) {
    vector<size_t> _MARKS;
    is >> _NAME;
    is >> _SIZE;

    for (size_t j = 0; j < _SIZE; ++j) {
      is >> _MARK;
      _MARKS.push_back(_MARK);
    }

    stgroup.add_student(_NAME, _MARKS);
  }
  return is;
}

void customOutput(const Stgroup &stgroup) {
  ofstream file("output.txt", ios_base::app);

  cout << stgroup;
  file << stgroup;

  file.close();
}

void customInput(Stgroup &stgroup) {
  ifstream file("input.txt");

  file >> stgroup;

  file.close();
}

int main() {
  Stgroup studg;

  customInput(studg);
  customOutput(studg);
  studg.print_top();

  return 0;
}
