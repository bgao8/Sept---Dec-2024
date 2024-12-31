#ifndef STUDENT_H
#define STUDENT_H

#include <iostream>
#include <vector>
#include <string>

#include "course.h"

using namespace std;

class Course;

class Student {
    friend ostream& operator<<(ostream& os, const Student& rhs);
public:
    // Student methods needed by Registrar
    Student(const string& name);
    const string& getName() const;
    bool addCourse(Course* course);

    // Student method needed by Course::removeStudentsFromCourse
    void removedFromCourse(Course* course);

private:
    string name;
    vector<Course*> courses;
}; // Student


#endif