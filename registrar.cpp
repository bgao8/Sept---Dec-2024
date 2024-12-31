#include "registrar.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

Registrar::Registrar() {}

bool Registrar::addCourse(const string& courseName) {
    for (Course* course : courses) {
        if (course->getName() == courseName) return false;
    }
    courses.push_back(new Course(courseName));
    return true;
}

bool Registrar::addStudent(const string& studentName) {
    for (Student* student : students) {
        if (student->getName() == studentName) return false;
    }
    students.push_back(new Student(studentName));
    return true;
}

bool Registrar::enrollStudentInCourse(const string& studentName, const string& courseName) {
    Student* foundStudent = nullptr;
    Course* foundCourse = nullptr;

    // Find student and course
    for (Student* student : students) {
        if (student->getName() == studentName) {
            foundStudent = student;
            break;
        }
    }

    for (Course* course : courses) {
        if (course->getName() == courseName) {
            foundCourse = course;
            break;
        }
    }

    if (foundStudent && foundCourse) {
        foundStudent->addCourse(foundCourse);
        foundCourse->addStudent(foundStudent);
        return true;
    }

    cout << "Enrollment failed: Either student or course not found.\n";
    return false;
}

bool Registrar::cancelCourse(const string& courseName) {
    for (Course* course : courses) {
        if (course->getName() == courseName) {
            course->removeStudentsFromCourse();
            return true;
        }
        cout << "Course not found." << endl;
    }
    return false;
}

void Registrar::purge() {
    for (Course* course : courses) {
        delete course;
    }
    courses.clear();

    for (Student* student : students) {
        delete student;
    }
    students.clear();
}

ostream& operator<<(ostream& os, const Registrar& registrar) {
    os << "Registrar's Report\nCourses:\n";
    if (!registrar.courses.empty()) {
        for (const Course* course : registrar.courses) {
            os << *course << endl;
        }
    }
    else {
        os << "No Courses\n";
    }

    os << "Students:\n";
    if (!registrar.students.empty()) {
        for (const Student* student : registrar.students) {
            os << *student << endl;
        }
    } 
    else {
        os << "No Students\n";
    }
    return os;
}