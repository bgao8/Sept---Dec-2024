#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

class Warrior {
private:
    string name;
    double strength;
    bool hired;

public:
    Warrior(const string& name, double strength) 
        : name(name), strength(strength), hired(false) {}

    bool isHired() {
        return hired;
    }

    void setHired(bool status) {
        hired = status;
    }
 
    const double getStrength() const {
        return strength;
    }

    void setStrength(double newStrength) {
        strength = newStrength;
    }

    const string& getName() const {
        return name;
    }

    friend ostream& operator<<(ostream& os, const Warrior& warrior) {
        os << warrior.getName() << ": " << warrior.getStrength();
        return os;
    }
};

class Noble {
private:
    string name;
    vector<Warrior*> warriors;
    bool alive;

public:
    Noble(const string& name) 
        : name(name), alive(true) {}

    bool hire(Warrior* warrior) {
        if (!alive || warrior->isHired()) {
            cout << name << " failed to hire " << warrior->getName() << endl;
            return false;
        }  
        else {
            warriors.push_back(warrior);
            warrior->setHired(true);
            return true;
        }
    }

    bool fire(Warrior* warrior) {
        if (!alive) {
            cout << "Dead noble can't fire " << warrior->getName() << endl;
            return false;
        }
        if (!warrior || warrior->isHired()) {
            cout << "Failed to fire" << endl;
            return false;
        }
        for (size_t i = 0; i < warriors.size(); i++) {
            if (warriors[i] == warrior) {
                cout << warrior->getName() << ", you don't work for me any more! -- " 
                    << name << endl;
                warrior->setHired(false);
                warriors.erase(warriors.begin() + i);
                return true;
            }
        }
        return false;
    } 

    const string getName() const {
        return name;
    }

    double getStrength() const {
        double totalStrength = 0;
        for (size_t i = 0; i < warriors.size(); i++) {
            totalStrength += warriors[i]->getStrength();
        }
        return totalStrength;
    }

    void setStrength(double newStrength) {
        for (size_t i = 0; i < warriors.size(); i++) {
            warriors[i]->setStrength(newStrength);
        }
    }

    void reduceStrength(double ratio) {
    for (size_t i = 0; i < warriors.size(); i++) {
        double reducedStrength = warriors[i]->getStrength() * (1 - ratio);
        warriors[i]->setStrength(reducedStrength);
    }
}

    void battle(Noble& opponent) {
        if (!alive && !opponent.alive) {
            cout << "Oh, NO!  They're both dead!  Yuck!" << endl;
            return;
        } 
        else if (!alive) {
            cout << "He's dead, " << opponent.name << endl;
            return;
        } 
        else if (!opponent.alive) {
            cout << "He's dead, " << name << endl;
            return;
        }
        
        else {
            double strength = getStrength();
            double oppStrength = opponent.getStrength();
            
            if (strength == oppStrength) {
                cout << "Mutual Annihilation. " << name << " and " << opponent.name 
                    << " die at each other's hands " << endl << endl;
                alive = false;
                opponent.alive = false;
                setStrength(0);
                opponent.setStrength(0);
            }
            else if (strength > oppStrength) {
                cout << name << " defeats " << opponent.name << endl << endl;
                opponent.alive = false;
                reduceStrength(oppStrength / strength);
                opponent.setStrength(0);
            }
            else if (strength < oppStrength) {
                cout << opponent.name << " defeats " << name << endl << endl;
                alive = false;
                setStrength(0);
                opponent.reduceStrength(strength / oppStrength);
            }
        }
    }

    friend ostream& operator<<(ostream& os, const Noble& noble) {
        os << noble.name << " has an army of " << noble.warriors.size() << endl;
        for (size_t i = 0; i < noble.warriors.size(); i++) {
            os << *noble.warriors[i] << endl;
        }
        return os;
    }
};

void clearAll(vector<Noble*>& nobles, vector<Warrior*>& warriors) {
    for (Noble* noble : nobles) {
        delete noble;
        noble = nullptr;
    }
    nobles.clear();

    for (Warrior*& warrior : warriors) {
        delete warrior;
        warrior = nullptr;
    }
    warriors.clear();
}

int main() {
    ifstream(file);
    file.open("nobleWarriors.txt");

    if (!file) {
        cerr << "Failed to open file." << endl;
    }

    vector<Noble*> nobles;
    vector<Warrior*> warriors;

    string command;

    while (file >> command) {
        if (command == "Noble") {
            string name;
            file >> name;
            bool nobleExists = false;

            for (size_t i = 0; i < nobles.size(); i++) {
                if (name == nobles[i]->getName()) {
                    cout << "Noble " << name << " already exists" << endl;
                    nobleExists = true;
                    break;
                }
            }
            if (!nobleExists) {
                nobles.push_back(new Noble(name));
            }
        }
        else if (command == "Warrior") {
            string name;
            double strength;
            file >> name >> strength;

            bool exists = false;
            for (size_t i = 0; i < warriors.size(); i++) {
                if (name == warriors[i]->getName()) {
                    cout << "Warrior " << name << " already exists" << endl;
                    exists = true;
                    break;
                }
            }
            if (!exists) {
                warriors.push_back(new Warrior(name, strength));
            }
        }

        else if (command == "Hire") {
            string nobleName;
            string warriorName;

            Noble* noble = nullptr;
            Warrior* warrior = nullptr;

            file >> nobleName >> warriorName;

            for (size_t i = 0; i < nobles.size(); i++) {
                if (nobleName == nobles[i]->getName()) {
                    noble = nobles[i];
                    break;
                }
            }
            
            for (size_t i = 0; i < warriors.size(); i++) {
                if (warriorName == warriors[i]->getName()) {
                    warrior = warriors[i];
                    break;
                }
            }

            if (!noble) {
                cout << "Noble " << nobleName << " not found!" << endl;
            }
            else if (!warrior) {
                cout << "Attempting to hire using unknown warrior: " << warriorName << endl;
            }
            else {
                noble->hire(warrior);
            }
        }

        else if (command == "Fire") {
            string nobleName;
            string warriorName;

            Noble* noble = nullptr;
            Warrior* warrior = nullptr;

            file >> nobleName >> warriorName;

            for (size_t i = 0; i < nobles.size(); i++) {
                if (nobles[i]->getName() == nobleName) {
                    noble = nobles[i];
                    break;
                }
            }
            
            for (size_t i = 0; i < warriors.size(); i++) {
                if (warriorName == warriors[i]->getName()) {
                    noble->fire(warrior);
                    break;
                }
            }

            if (!noble) {
                cout << "Noble " << nobleName << " not found!" << endl;
            }
            else if (!warrior) {
                cout << "Warrior " << warriorName << " not found!" << endl;
            }
            else {
                noble->fire(warrior);
            }
        }

        else if (command == "Battle") {
            string nobleName1;
            string nobleName2;

            Noble* noble1 = nullptr;
            Noble* noble2 = nullptr;

            file >> nobleName1 >> nobleName2;

            for (size_t i = 0; i < nobles.size(); i++) {
                if (nobles[i]->getName() == nobleName1) {
                    noble1 = nobles[i];
                    break;
                }
            }
            
            for (size_t i = 0; i < nobles.size(); i++) {
                if (nobleName2 == nobles[i]->getName()) {
                    noble2 = nobles[i];
                    break;
                }
            }

            if (!noble1) {
                cout << "Noble " << nobleName1 << " not found!" << endl;
            }
            else if (!noble2) {
                cout << "Noble " << nobleName2 << " not found!" << endl;
            }
            else {
                noble1->battle(*noble2);
            }
        }

        else if (command == "Status") {
            cout << "Status" << endl;
            cout << "======" << endl;
            if (nobles.size() == 0) {
                cout << "Nobles: NONE" << endl;
            }
            else {
                cout << "Nobles:" << endl;
                for (const Noble* noble : nobles) {
                    cout << *noble;
                }
            }

            cout << "Unemployed Warriors:" << endl;
            bool unemployedWarriors = false;
            for (Warrior* warrior : warriors) {
                if (!warrior->isHired()) {
                    unemployedWarriors = true;
                    cout << "\t" << *warrior << endl;
                }
            }
            if (!unemployedWarriors) {
                cout << "NONE" << endl;
            }
        }

        // clear command
        else if (command == "Clear") {
            clearAll(nobles, warriors);
        }
    }

    file.close();
}