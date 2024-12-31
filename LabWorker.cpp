#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Section;
class LabWorker;

class Section {
private:  
    class Time {
    private:
        string day;
        int hour;

    public:
        Time(const string& day, const int hour) 
            : day(day), hour(hour) {}

        friend ostream& operator<<(ostream& os, const Time& time) {
            os << "Time slot: [Day: " << time.day << ", Start time: ";
            if (time.hour < 12) {
                os << time.hour << "AM]";
            } 
            else {
                os << time.hour - 12 << "PM]";
            }
            return os;
        }
    };

    class Student {
    public:
        string name;
        // week of grade is the index of the vector
        vector<int> grades;

        Student(const string& name) : name(name), grades(14, -1) {}

        bool setGrade(int week, int grade) {
            if (week < 1 || week > 14) {
                return false;
            }
            grades[week - 1] = grade;
            return true;
        }
        
        friend ostream& operator<<(ostream& os, const Student& student) {
            os << "Name: " << student.name << " " << endl;
            os << "Grades:\t";
            for (size_t i = 0; i < student.grades.size(); i++) {
                os << student.grades[i] << ", ";
            }
            os << endl;
            return os;
        }
    };

    string name;
    Time time;
    vector<Student*> records;

public:
    Section(const string& name, const string& day, const int hour) 
        : name(name), time(day, hour) {}

    ~Section() {
        for (Student* student : records) {
            delete student;
        }
        records.clear();
    }

    Section(const Section& section) 
        : name(section.name), time(section.time) {
        for (Student* student : section.records) {
            records.push_back(new Student(*student));
        }
    }

    void addStudent(const string& name) {
        records.push_back(new Student(name));
    }

    void setStudentGrade(const string& name, int grade, int week) {
        for (Student* student : records) {
            if (student->name == name) {
                student->setGrade(week, grade);
            }
        }
    }

    friend ostream& operator<<(ostream& os, const Section& section) {
        os << section.name << endl;
        os << section.time << endl;
        os << "Records: " << endl;
        if (section.records.empty()) {
            os << "None";
        }
        for (const Student* student : section.records) {
            os << *student << endl;
        }
        return os;
    }
};

class LabWorker {
private:
    string name;
    Section* labSection;

public:
    LabWorker(const string& name) 
        : name(name), labSection(nullptr) {}

    void addSection(Section& section) {
        labSection = &section;
    }

    void addGrade(const string& name, int grade, int week) {
        labSection->setStudentGrade(name, grade, week);
    }

    friend ostream& operator<<(ostream& os, const LabWorker& worker) {
        os << worker.name;
        if (worker.labSection) {
            os << " has section " << *worker.labSection;
        }
        else {
            os << " does not have a section" << endl;
        }
        return os;
    }
};

void doNothing(Section sec) {
    cout << sec << endl;
}

int main()
{
    cout << "Test 1: Defining a section\n";
    Section secA2("A2", "Tuesday", 16);
    cout << secA2 << endl;

    cout << "\nTest 2: Adding students to a section\n";
    secA2.addStudent("John");
    secA2.addStudent("George");
    secA2.addStudent("Paul");
    secA2.addStudent("Ringo");
    cout << secA2 << endl;

    cout << "\nTest 3: Defining a lab worker.\n";
    LabWorker moe( "Moe" );
    cout << moe << endl;

    cout << "\nTest 4: Adding a section to a lab worker.\n";
    moe.addSection( secA2 );
    cout << moe << endl;

    cout << "\nTest 5: Adding a second section and lab worker.\n";
    LabWorker jane( "Jane" );
    Section secB3( "B3", "Thursday", 11 );
    secB3.addStudent("Thorin");
    secB3.addStudent("Dwalin");
    secB3.addStudent("Balin");
    secB3.addStudent("Kili");
    secB3.addStudent("Fili");
    secB3.addStudent("Dori");
    secB3.addStudent("Nori");
    secB3.addStudent("Ori");
    secB3.addStudent("Oin");
    secB3.addStudent("Gloin");
    secB3.addStudent("Bifur");
    secB3.addStudent("Bofur");
    secB3.addStudent("Bombur");
    jane.addSection( secB3 );
    cout << jane << endl;

    cout << "\nTest 6: Adding some grades for week one\n";
    moe.addGrade("John", 17, 1);  
    moe.addGrade("Paul", 19, 1);  
    moe.addGrade("George", 16, 1);  
    moe.addGrade("Ringo", 7, 1);  
    cout << moe << endl;

    cout << "\nTest 7: Adding some grades for week three (skipping week 2)\n";
    moe.addGrade("John", 15, 3);  
    moe.addGrade("Paul", 20, 3);  
    moe.addGrade("Ringo", 0, 3);  
    moe.addGrade("George", 16, 3);  
    cout << moe << endl;

    cout << "\nTest 8: We're done (almost)! \nWhat should happen to all "
         << "those students (or rather their records?)\n";

    cout << "\nTest 9: Copy Constructor: make sure the following calls work:\n";
    doNothing(secA2);
    cout << "Back from doNothing\n\n" << secA2 << endl;

} // main
