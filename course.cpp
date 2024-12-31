#include <string>
#include <vector>
#include <iostream>
#include "course.h"
#include "student.h"

using namespace std;

Course::Course(const string& name) : name(name) {}

const string& Course::getName() const {
    return name;
}

bool Course::addStudent(Student* student) {
    for (Student* s : students) {
        if (s == student) {
            cout << "Student already in the course" << endl;
            return false;
        }
    }
    students.emplace_back(student);
    return true;
}

void Course::removeStudentsFromCourse() {
    // for (Student* student : students) {
    //     delete student;
    // }
    students.clear();   // use debugger
}

ostream& operator<<(ostream& os, const Course& course) {
    os << course.name << ": ";
    if (!course.students.empty()) {
        for (Student* student : course.students) {
            os << student->getName() << " ";
        }
    } 
    else {
        os << "No Students";
    }
    return os;
}