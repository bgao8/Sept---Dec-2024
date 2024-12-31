#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

class Transaction {
private:
    string type;
    int amount;
public:
    Transaction(const string& type, const int amount) 
        : type(type), amount(amount) {}

    friend ostream& operator<<(ostream& os, Transaction transaction);
};

ostream& operator<<(ostream& os, Transaction transaction) {
    os << transaction.type << ": $" << transaction.amount;
    return os;
}

class AccountClass {
private:
    string name;
    int accountNumber;
    int balance;
    vector<Transaction> transactions;

public:
    AccountClass(const string& name, const int accountNumber) 
        : name(name), accountNumber(accountNumber) {}  

    void deposit(int amount) {
        balance += amount;
        Transaction transaction = Transaction("Deposit", amount);
        transactions.push_back(transaction);
        // cout << balance << endl;
    }

    bool withdraw(int amount) {
        if (balance >= amount) {
            balance -= amount;
            transactions.push_back(Transaction({"Withdrawal", amount}));
            // cout << balance << endl;
            return true;
        }
        else {
            return false;
        }
    }

    // void addTransaction(const Transaction& transaction) {
    //     transactions.push_back(transaction);
    // }

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
    friend ostream& operator<<(ostream& os, AccountClass account);
};

// void printAccountClass(const vector<AccountClass>& accountsClass) {
//     for (size_t i = 0; i < accountsClass.size(); i++) {
//         cout << accountsClass[i] << endl;
//     }
// }

ostream& operator<<(ostream& os, AccountClass account) {
    os << account.name << "\t" << account.accountNumber << endl;
    for (size_t i = 0; i < account.transactions.size(); i++) {
        os << "\t" << account.transactions[i] << endl;
    }
    return os;
}

int main() {
    cout << "==============\n"
        << "\nTask 3:\nAccounts and Transaction:\n";

    ifstream file;
    file.open("transactions.txt");

    string command;
    string name;
    int accountNumber;
    int amount;
    vector<AccountClass> accounts;
    
    while (file >> command) {
        if (command == "Account") {
            file >> name >> accountNumber;
            AccountClass acc(name, accountNumber);
            accounts.push_back(acc);
        }
        else if (command == "Deposit") {
            file >> accountNumber >> amount;
            for (AccountClass& acc : accounts) {
                if (acc.getAccountNum() == accountNumber) {
                    acc.deposit(amount);
                    cout << "deposit done" << endl;
                    break;
                }
            }
        }
        else if (command == "Withdraw") {
            file >> accountNumber >> amount;
            for (AccountClass& acc : accounts) {
                if (acc.getAccountNum() == accountNumber) {
                    if (!acc.withdraw(amount)) {
                        cerr << "Account #" << accountNumber << " has only " << acc.getBalance()
                            << ". Insufficient for withdrawal of " << amount << endl;
                    }
                    break;
                }
            }
        }
    }

    file.close();

    for (size_t i = 0; i < accounts.size(); i++) {
        cout << accounts[i] << endl;
    }

    cout << "==============\n"
         << "\nTask 4:\nTransaction nested in public section of Account:\n";

    
    cout << "==============\n"
         << "\nTask 5:\nTransaction nested in private section of Account:\n";
}