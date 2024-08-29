#include<iostream>
#include<fstream>
#include<string>
#include<sstream>
#include<windows.h>


using namespace std;

class Account {
    string Name, AccountNumber, Password;
    int Balance;

public: 
    Account() :Name(""), AccountNumber(""), Password(""), Balance(0){}

    // setter functions
    void setName(string name) {
        Name = name;
    }
    void setAccountNumber(string accountNumber) {
        AccountNumber = accountNumber;
    }
    void setPassword(string password) {
        Password = password;
    }
    void setBalance(int balance) {
        Balance = balance;
    }

    // Getter Function
    string getName() {
        return Name;
    }
    string getAccountNumber() {
        return AccountNumber;
    }
    string getPassword() {
        return Password;
    }
    
    int getBalance() {
        return Balance;
    }
};


void createNewAccount(Account user) {
    system("cls");
    string name, acNo, pw;
    cout << "\tEnter the Name : ";
    cin >> name;
    user.setName(name);

    cout << "\tEnter the Account Number : ";
    cin >> acNo;
    user.setAccountNumber(acNo);

    cout << "\tEnter the Password : ";
    cin >> pw;
    user.setPassword(pw);

    user.setBalance(0);


    ofstream outFile("Account.txt", ios::app);
    if (!outFile) {
        cout << "\tError:File can't Open."<<endl;
    }
    else {
        outFile << user.getName() << " : " << user.getAccountNumber() << " : " << user.getPassword() << " : " << user.getBalance() << endl << endl;
        cout << "\tAccount Created Successfully!" << endl;
    }
    outFile.close();

    Sleep(5000);
}


void depositCash() {
    system("cls");
    string id;
    cout << "\tEnter the Account Number: ";
    cin >> id;

    ifstream inFile("Account.txt");
    ofstream outFile("AccountTemp.txt");

    if (!inFile || !outFile) {
        cout << "\tError: File Can't Open!" << endl;
    }

    string line;
    bool found = false;

    while (getline(inFile, line)) {
        stringstream ss;
        ss << line;
        string userName, userId, userPW;
        int userBal;
        char delimiter;

        ss >> userName >> delimiter >> userId >> delimiter >> userPW >> delimiter >> userBal;
        if (id == userId) {
            found = true;
            int cash;
            cout << "\tEnter Cash: ";
            cin >> cash;

            int newBal = userBal + cash;
            userBal = newBal;

            outFile << userName << " : " << userId << " : " << userPW << " : " << userBal << endl;
            cout << "\tNew balance  is: " << newBal << endl;

        }
        else {
            outFile << line << endl;
        }
    }

    if (!found) {
        cout << "\tEnter Valid Account Number" << endl;
    }
    outFile.close();
    inFile.close();

    remove("Account.txt");
    rename("AccountTemp.txt","Account.txt");
    Sleep(5000);
}

void withdrawCash() {
    system("cls");
    string id, pw;
    cout << "\tEnter the Account Number: ";
    cin >> id;
    cout << "\tEnter the Password: ";
    cin >> pw;

    ifstream inFile("Account.txt");
    ofstream outFile("AccountTemp.txt");

    if (!inFile || !outFile) {
        cout << "\tError: File Can't Open!" << endl;
    }

    bool found = false;
    string line;
    while (getline(inFile, line)) {
        stringstream ss;
        ss << line;
        string userName, userId, userPw;
        int userBal;
        char delimiter;

        ss >> userName >> delimiter >> userId >> delimiter >> userPw >> delimiter >> userBal;

        if (userId == id && userPw == pw) {
            found = true;
            int cash;
            cout << "\tEnter Cash: ";
            cin >> cash;

            if (cash <= userBal) {
                int newBal = userBal - cash;
                userBal = newBal;
                outFile << userName << " : " << userId << " : " << userPw << " : " << userBal;
                cout << "\tTransaction Was Sucessful!" << endl;
                cout << "\tRemaining Balance is: " << newBal << endl;
            }
            else {
                cout << "\tInsufficient Balance" << endl;
                outFile << userName << " : " << userId << " : " << userPw << " : " << userBal;
            }
        }
        else {
            outFile << line<<endl;
        }
    }

    if (!found) {
        cout << "\tInvalid Credencials!" << endl;
    }
    outFile.close();
    inFile.close();

    remove("Account.txt");
    rename("AccountTemp.txt","Account.txt");
   
    Sleep(5000);
}

void displayAccountBalance() {
    
    system("cls");
    string id;
    cout << "Enter the Account Number: ";
    cin >> id;
    bool found = false;

    ifstream inFile("Account.txt");
    if (!inFile) {
        cout << "Error: File Can't Open" << endl;
    }
    else {
        string line;
        while (getline(inFile, line)) {
            stringstream ss;
            ss << line;
            string userName, userId, userPw;
            int userBal;
            char delimiter;

            ss >> userName >> delimiter >> userId >> delimiter >> userPw >> delimiter >> userBal;
            if (userId == id) {
                found = true;
                cout << "For Account Number: " << userId << " Balance is: " << userBal<<endl;
            }
            
        }
    }
    if (!found) {
        cout << "Account Number is Wrong" << endl;
    }
    inFile.close();
    Sleep(5000);
}




int main() {
    
    Account user;
    
    int choice;
    do {
        system("cls");
        cout << "\n\tBank Account Management System"<<endl;
        cout << "\t**********************************************" << endl << endl;
        cout << "\n\t1. Create New Account";
        cout << "\n\t2. Deposit";
        cout << "\n\t3. Withdraw";
        cout << "\n\t4. Balance Inquiry";
        cout << "\n\t5. Exit"<<endl;
        cout << "\n\tSelect Your Option (1-5): ";
        cin >> choice;

        switch (choice) {
        case 1:
            Sleep(3000);
            createNewAccount(user);
            break;
        case 2:
            //cout << "Enter Account Number: ";
            //cin >> accountNumber;
            //depositWithdraw(accountNumber, 1);
            Sleep(3000);
            depositCash();
            break;
        case 3:
            //cout << "Enter Account Number: ";
            //cin >> accountNumber;
            //depositWithdraw(accountNumber, 2);
            Sleep(3000);
            withdrawCash();
            break;
        case 4:
            Sleep(2000);
            displayAccountBalance();
            //cout << "Enter Account Number: ";
            //cin >> accountNumber;
            //displayAccount(accountNumber);
            break;
        
        case 5:
            cout << "\tExiting..." << endl;
            break;
        default:
            cout << "\tInvalid Option! Please Try Again." << endl;
        }
    } while (choice != 5);


    return 0;
}



  







