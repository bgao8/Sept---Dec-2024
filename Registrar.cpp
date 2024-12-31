/*
  rec08_starter.cpp
  Starter Code for required functionality

  Yes, of course, you may add other methods.

  And no, this won't compile. You have to fix the cyclic association
  and implement the methods.
  
 */

#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Student;

class Course {
    friend ostream& operator<<(ostream& os, const Course& rhs);
public:
    // Course methods needed by Registrar
    Course(const string& courseName);
    const string& getName() const;
    bool addStudent(Student*);

    // Tell the students that they are no longer in the course
    void removeStudentsFromCourse(); 

private:
    string name;
    vector<Student*> students;
}; // Course

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

class Registrar {
    friend ostream& operator<<(ostream& os, const Registrar& rhs);
public:
    Registrar();

    // Creates a new course, if none with that name
    bool addCourse(const string&);
    // Creates a new student, if none with that name
    bool addStudent(const string&);

    // If the student and the course exist, then enroll the student.
    bool enrollStudentInCourse(const string& studentName,
                               const string& courseName);

    // Unenroll the students from the course and remove the course
    // from the Registrar.
    bool cancelCourse(const string& courseName);

    // Get rid of everything!!!
    void purge();

private:
    size_t findStudent(const string&) const;
    size_t findCourse(const string&) const;

    vector<Course*> courses;
    vector<Student*> students;
}; // Registrar

int main()
{
    Registrar registrar;

    cout << "No courses or students added yet\n";
    cout << registrar << endl;
     
    cout << "AddCourse CS101.001\n";
    registrar.addCourse("CS101.001");
    cout << registrar << endl;

    cout << "AddStudent FritzTheCat\n";
    registrar.addStudent("FritzTheCat");
    cout << registrar << endl;

    cout << "AddCourse CS102.001\n";
    registrar.addCourse("CS102.001");
    cout << registrar << endl;

    cout << "EnrollStudentInCourse FritzTheCat CS102.001\n";
    registrar.enrollStudentInCourse("FritzTheCat", "CS102.001");
    cout << "EnrollStudentInCourse FritzTheCat CS101.001\n";
    registrar.enrollStudentInCourse("FritzTheCat", "CS101.001");
    cout << registrar << endl;

    cout << "EnrollStudentInCourse Bullwinkle CS101.001\n";
    cout << "Should fail, i.e. do nothing, "
         << "since Bullwinkle is not a student.\n";
    registrar.enrollStudentInCourse("Bullwinkle", "CS101.001");
    cout << registrar << endl;

    cout << "CancelCourse CS102.001\n";
    registrar.cancelCourse("CS102.001");
    cout << registrar << endl;
   
    cout << "Purge for start of next semester\n";
    registrar.purge();
    cout << registrar << endl;
} // main

// Course methods
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

// Student 
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

// Registrar
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