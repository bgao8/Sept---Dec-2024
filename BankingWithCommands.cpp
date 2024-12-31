#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

// Task 1
// Define an Account struct

struct Account {
    string name;
    int accountNumber;
};

// Task 2
// Define an Account class (use a different name than in Task 1)

class AccountClass {
private:
    string holderName;
    int holderAccountNumber;

public:
    AccountClass(const string& name, const int accountNumber)
        : holderName(name), holderAccountNumber(accountNumber) {}

    // const string& getName() {
    //     return holderName;
    // }

    // const int getNumber() {
    //     return holderAccountNumber;
    // }

    AccountClass(const string& name)
        : holderName(name) {}

    friend ostream& operator<<(ostream& os, AccountClass rhs);
};

// overload function not friend, needs getters

// ostream& operator<<(ostream& os, AccountClass rhs) {
//     os << rhs.getName() << "\t" << rhs.getNumber();
//     return os;
// }

ostream& operator<<(ostream& os, AccountClass rhs) {
    os << rhs.holderName << "\t" << rhs.holderAccountNumber;
    return os;
}

void printAccountClass(const vector<AccountClass>& accountsClass) {
    for (size_t i = 0; i < accountsClass.size(); i++) {
        cout << accountsClass[i] << endl;
    }
}

class Transaction {
private:
    string type;
    double amount;
public:
    Transaction(const string& type, const double amount) 
        : type(type), amount(amount) {}

    friend ostream& operator<<(ostream& os, const Transaction transaction);
};

class AccountClass2 {
private:
    string name;
    int accountNumber;
    double balance;
    vector<Transaction> transactions;

public:
    AccountClass2(const string& name, const int accountNumber) 
        : name(name), accountNumber(accountNumber) {}  

    void deposit(int amount) {
        balance += amount;;
        transactions.push_back(Transaction("Deposit", amount));
    }

    bool withdraw(int amount) {
        if (balance >= amount) {
            balance -= amount;
            transactions.push_back(Transaction("Withdrawal", amount));
            return true;
        }
        else {
            return false;
        }
    }

    void addTransaction(const Transaction& transaction) {
        transactions.push_back(transaction);
    }

    // getters
    const int getBalance() {
        return balance;
    }

    const string getName() {
        return name;
    }

    const int getAccountNum() {
        return accountNumber;
    }

    // friend
    friend ostream& operator<<(ostream& os, const AccountClass2 account);
};

void printAccountClass2(const vector<AccountClass2>& accountsClass) {
    for (size_t i = 0; i < accountsClass.size(); i++) {
        cout << accountsClass[i] << endl;
    }
}

ostream& operator<<(ostream& os, AccountClass2 account) {
    os << "Account " << account.accountNumber;
    return os;
}

ostream& operator<<(ostream& os, Transaction transaction) {
    os << "Fuck";
    return os;
}



int main() {
    // Task 1: account as struct
    //      1a
    cout << "Task1a:\n"
         << "Filling vector of struct objects, define a local struct instance\n"
         << "and set fields explicitly:\n";

    ifstream file("accounts.txt");
    if (!file) {
        cerr << "File not found." << endl;
    }
    string name;
    int accountNumber;  // accessed by the constructor parameters
    vector<Account> accounts;

    while (file >> name >> accountNumber ) {
        Account account;
        account.name = name;
        account.accountNumber = accountNumber;
        accounts.push_back(account);
    }

    for (size_t i = 0; i < accounts.size(); i++) {
        cout << "Name: " << accounts[i].name;
        cout << ", Account Number: " << accounts[i].accountNumber << endl;
    }   

    accounts.clear();

    file.close();

    //      1b
    cout << "\nTask1b:\n"
         << "Filling vector of struct objects, using {} initialization:\n";

    ifstream file2;
    file2.open("accounts.txt");
    if (!file2) {
        cerr << "File not found. 2" << endl;
    }
    // string name;
    // int accountNumber;
    // vector<Account> accounts;

    // read through file, push back all names and account numbers
    // into an aggregate thing
    while (file2 >> name >> accountNumber) {
        Account acc = {name, accountNumber}; 
        accounts.push_back(acc); // aggregate initialization
    }

    file2.close();

    for (size_t i = 0; i < accounts.size(); i++) {
        cout << "Name: " << accounts[i].name;
        cout << ", Account Number: " << accounts[i].accountNumber;
        cout << endl;
    }

    accounts.clear();

    //==================================
    // Task 2: account as class

    //      2a
    cout << "==============\n";
    cout << "\nTask2a:"
         << "\nFilling vector of class objects, using local class object:\n";

    ifstream file3;
    file3.open("accounts.txt");

    string holderName;
    int holderAccountNumber;
    string random;

    vector<AccountClass> accountsClass;

    while (file3 >> holderName >> holderAccountNumber) {
        AccountClass acc(holderName, holderAccountNumber);
        // AccountClass acc = AccountClass(holderName, holderAccountNumber);
        accountsClass.push_back(acc);
    }

    file3.close();

    //==================================

    cout << "\nTask2b:\n";
    cout << "output using output operator with getters\n";

    printAccountClass(accountsClass);
    // for (size_t i = 0; i < accountsClass.size(); i++) {
    //     cout << accountsClass[i] << endl;
    // }

    //==================================

    cout << "\nTask2c:\n"
         << "output using output operator as friend without getters\n";

    printAccountClass(accountsClass);

    accountsClass.clear();

    //==================================

    cout << "\nTask2d:\n"
         << "Filling vector of class objects, using temporary class object:\n";

    file3.open("accounts.txt");

    // using anonymous object
    while (file3 >> holderName >> holderAccountNumber) {
        accountsClass.push_back(AccountClass(holderName, holderAccountNumber));
    }

    printAccountClass(accountsClass);

    file3.close();
    accountsClass.clear();

    //==================================
    
    cout << "\nTask2e:\n"
         << "Filling vector of class objects, using emplace_back:\n";

    file3.open("accounts.txt");

    while (file3 >> holderName >> holderAccountNumber) {
        accountsClass.emplace_back(holderName, holderAccountNumber);
    }

    for (AccountClass account : accountsClass) {
        cout << account << endl;
    }

    file3.close();
    
    cout << "==============\n"
         << "\nTask 3:\nAccounts and Transaction:\n";

    ifstream file4;
    file4.open("transactions.txt");

    string command;
    string name2;
    int accountNumber2;
    int amount;
    vector<AccountClass2> accounts2;
    
    while (file4 >> command) {
        if (command == "Account") {
            file4 >> name2 >> accountNumber2;
            AccountClass2 acc(name2, accountNumber2);
            accounts2.push_back(acc);
        }
        else if (command == "Deposit") {
            file4 >> accountNumber2 >> amount;
            for (AccountClass2 acc : accounts2) {
                if (acc.getAccountNum() == accountNumber2) {
                    acc.addTransaction(Transaction("Deposit", amount));
                }
            }
        }
        else if (command == "Withdraw") {
            file4 >> accountNumber2 >> amount;
            for (AccountClass2 acc : accounts2) {
                if (acc.getAccountNum() == accountNumber2) {
                    acc.addTransaction(Transaction("Withdrawal", amount));
                }
            }
        }
    }

    file4.close();

    printAccountClass2(accounts2);

    cout << "==============\n"
         << "\nTask 4:\nTransaction nested in public section of Account:\n";

    
    cout << "==============\n"
         << "\nTask 5:\nTransaction nested in private section of Account:\n";

}