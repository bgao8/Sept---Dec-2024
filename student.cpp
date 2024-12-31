#include <string>
#include <vector>
#include <iostream>
#include "student.h"
#include "course.h"

using namespace std;

Student::Student(const string& name) : name(name) {}

const string& Student::getName() const {
    return name;
}

// Student method needed by Course::removeStudentsFromCourse
void Student::removedFromCourse(Course* course) {
    for (size_t i = 0; i < courses.size(); ++i) {
        if (courses[i] == course) {
            courses[i] = courses[courses.size() - 1];
            courses.pop_back();
            return; 
        }
    }
}

bool Student::addCourse(Course* course) {
    for (Course* c : courses) {
        if (course == c) {
            cout << "Course already in course list" << endl;
            return false;
        }
    }
    courses.emplace_back(course);
    return true;
}

ostream& operator<<(ostream& os, const Student& student) {
    os << student.name << ": ";
    if (!student.courses.empty()) {
        for (Course* course : student.courses) {
            os << course->getName() << " ";
        }
    } 
    else {
        os << "No Courses";
    }
    return os;
}