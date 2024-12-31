#include <iostream>
#include <string>
#include <vector>

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

    bool hire(Warrior& warrior) {
        if (!alive || warrior.isHired()) {
            cout << name << " failed to hire " << warrior.getName() << endl;
            return false;
        }  
        else {
            warriors.emplace_back(&warrior);
            warrior.setHired(true);
            return true;
        }
    }

    bool fire(Warrior& warrior) {
        if (!alive || !warrior.isHired()) {
            cout << "Failed to fire " << warrior.getName() << endl;
            return false;
        }
        for (size_t i = 0; i < warriors.size(); i++) {
            if (warriors[i] == &warrior) {
                cout << warrior.getName() << ", you don't work for me any more! -- " 
                    << name << endl;
                warrior.setHired(false);
                warriors.erase(warriors.begin() + i);
                return true;
            }
        }
        return false;
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
            warriors[i]->setStrength(getStrength() * (1 - ratio));
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


int main()
{
    Noble art("King Arthur");
    Noble lance("Lancelot du Lac");
    Noble jim("Jim");
    Noble linus("Linus Torvalds");
    Noble billie("Bill Gates");
	
    Warrior cheetah("Tarzan", 10);
    Warrior wizard("Merlin", 15);
    Warrior theGovernator("Conan", 12);
    Warrior nimoy("Spock", 15);
    Warrior lawless("Xena", 20);
    Warrior mrGreen("Hulk", 8);
    Warrior dylan("Hercules", 3);
	
    jim.hire(nimoy);
    lance.hire(theGovernator);
    art.hire(wizard);
    lance.hire(dylan);
    linus.hire(lawless);
    billie.hire(mrGreen);
    art.hire(cheetah);
    art.hire(nimoy);
	
    cout << "==========\n\n"
         << "Status before all battles, etc.\n";
    cout << jim << endl;
    cout << lance << endl;
    cout << art << endl;
    cout << linus << endl;
    cout << billie << endl;
    cout << "==========\n\n";
	
    art.fire(cheetah);
    cout << art << endl;

    lance.fire(nimoy);
    cout << lance << endl;
    cout << "==========\n\n";

    art.battle(lance);
    jim.battle(lance);
    linus.battle(billie);
    billie.battle(lance);

    cout << "==========\n\n"
         << "Status after all battles, etc.\n";
    cout << jim << endl;
    cout << lance << endl;
    cout << art << endl;
    cout << linus << endl;
    cout << billie << endl;
    cout << "==========\n";
	
} // main
