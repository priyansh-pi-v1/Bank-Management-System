#include<iostream>
#include<vector>

using namespace std;

void pause() {
    cout << "\t\tPress Enter to continue...";
    cin.clear();
    cin.sync();
    cin.get();
}

// ============================================================
// Class: BankAccount
// Represents a single bank account with its details and operations.
// ============================================================
class BankAccount{
    private:
        string name;          // Full name of the account holder
        int accountNumber;    // Unique account identifier
        double balance;       // Current account balance
        char accountType;     // 'S' for Savings, 'C' for Current
    public:
        // Constructor: initializes all account fields
        BankAccount(string n, int ac, double bal, char type) {
            name = n;
            accountNumber = ac;
            balance = bal;
            accountType = type;
        }

        // --- Getters ---
        string getName() {
            return name;
        }
        int getAccountNumber() {
            return accountNumber;
        }
        double getBalance() {
            return balance;
        }
        char getAccountType() {
            return accountType;
        }
        // Returns "Savings" or "Current" as a readable string
        string getAccountTypeStr() {
            return (accountType == 'S') ? "Savings" : "Current";
        }

        // --- Setters ---
        void setName(const string& n) {
            name = n;
        }
        void setAccountType(char type) {
            accountType = type;
        }

        // Adds the given amount to balance. Rejects non-positive values.
        void deposit(double amount) {
            if(amount <= 0) {
                cout << "\t\tInvalid amount! Must be greater than 0." << endl;
                return;
            }
            balance += amount;
            cout << "\t\tDeposit Successful!" << endl;
        }

        // Deducts the given amount from balance if sufficient funds exist.
        // Rejects non-positive values and overdrafts.
        void withdraw(double amount) {
            if(amount <= 0) {
                cout << "\t\tInvalid amount! Must be greater than 0." << endl;
                return;
            }
            if(balance >= amount) {
                balance -= amount;
                cout << "\t\tWithdrawal Successful!" << endl;
            } else {
                cout << "\t\tInsufficient Balance!" << endl;
            }
        }
};

// ============================================================
// Class: BankManagement
// Manages a collection of BankAccount objects.
// Handles account creation, search, modification, and deletion.
// ============================================================
class BankManagement{
    private:
        vector<BankAccount> accounts;   // Stores all bank accounts in memory
    public:
        // Creates and adds a new account. Returns false if account number already exists or balance is invalid.
        bool addAccount(const string& name, int accountNumber, double balance, char accountType) {
            if(balance <= 0) {
                return false;
            }
            // Reject duplicate account numbers
            if(findAccount(accountNumber) != nullptr) {
                return false;
            }
            accounts.push_back(BankAccount(name, accountNumber, balance, accountType));
            return true;
        }

        // Prints details of all accounts. Shows a message if no accounts exist.
        void showAllAccounts() {
            if(accounts.size() == 0) {
                cout << "\t\tNo accounts found!" << endl;
                return;
            }
            cout << "\t\tAll Account Holders:" << endl;
            cout << "\t\t---------------------------" << endl;
            for(int i = 0; i < accounts.size(); i++) {
                cout << "\t\tName         : " << accounts[i].getName() << endl;
                cout << "\t\tAccount No.  : " << accounts[i].getAccountNumber() << endl;
                cout << "\t\tAccount Type : " << accounts[i].getAccountTypeStr() << endl;
                cout << "\t\tBalance      : " << accounts[i].getBalance() << endl;
                cout << "\t\t---------------------------" << endl;
            }
        }

        // Searches for an account by number and prints its details.
        // Prints "Account Not Found" if no match exists.
        void searchAccount(int accountNumber) {
            for(int i = 0; i < accounts.size(); i++) {
                if(accounts[i].getAccountNumber() == accountNumber) {
                    cout << "\t\t---------------------------" << endl;
                    cout << "\t\tName         : " << accounts[i].getName() << endl;
                    cout << "\t\tAccount No.  : " << accounts[i].getAccountNumber() << endl;
                    cout << "\t\tAccount Type : " << accounts[i].getAccountTypeStr() << endl;
                    cout << "\t\tBalance      : " << accounts[i].getBalance() << endl;
                    cout << "\t\t---------------------------" << endl;
                    return;
                }
            }
            cout << "\t\tAccount Not Found!" << endl;
        }

        // Returns a pointer to the account with the given number, or nullptr if not found.
        // Used internally by other methods to avoid code duplication.
        BankAccount* findAccount(int accountNumber) {
            for(int i = 0; i < accounts.size(); i++) {
                if(accounts[i].getAccountNumber() == accountNumber) {
                    return &accounts[i];
                }
            }
            return nullptr;
        }

        // Removes the account with the given number from the vector.
        // Returns true if deleted, false if account was not found.
        bool deleteAccount(int accountNumber) {
            for(int i = 0; i < accounts.size(); i++) {
                if(accounts[i].getAccountNumber() == accountNumber) {
                    accounts.erase(accounts.begin() + i);
                    return true;
                }
            }
            return false;
        }

        // Allows modifying the name and/or account type of an existing account.
        // Presents a sub-menu to choose what to update.
        void modifyAccount(int accountNumber) {
            BankAccount* account = findAccount(accountNumber);
            if(!account) {
                cout << "\t\tAccount Not Found!" << endl;
                return;
            }

            cout << "\t\tCurrent Details:" << endl;
            cout << "\t\tName         : " << account->getName() << endl;
            cout << "\t\tAccount Type : " << account->getAccountTypeStr() << endl;

            int modChoice;
            cout << "\t\tWhat do you want to modify?" << endl;
            cout << "\t\t1. Name" << endl;
            cout << "\t\t2. Account Type" << endl;
            cout << "\t\t3. Both" << endl;
            cout << "\t\tEnter choice: ";
            cin >> modChoice;
            cin.ignore();   // Clear leftover newline before getline

            if(modChoice == 1 || modChoice == 3) {
                string newName;
                cout << "\t\tEnter New Name: ";
                getline(cin, newName);
                account->setName(newName);
            }
            if(modChoice == 2 || modChoice == 3) {
                char newType;
                cout << "\t\tEnter New Account Type (S = Savings / C = Current): ";
                cin >> newType;
                newType = toupper(newType);
                if(newType == 'S' || newType == 'C') {
                    account->setAccountType(newType);
                } else {
                    cout << "\t\tInvalid type entered. No change made." << endl;
                }
            }

            cout << "\t\tAccount Modified Successfully!" << endl;
        }
};

// ============================================================
// Main: Entry point. Displays the menu in a loop and routes
// user input to the appropriate BankManagement operations.
// ============================================================
int main() {
    BankManagement bank;
    int choice;

    // Clear screen and show welcome message on startup
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
    cout << "\t\t============================================" << endl;
    cout << "\t\t      Welcome to National Bank of India     " << endl;
    cout << "\t\t      Your Trusted Financial Partner        " << endl;
    cout << "\t\t============================================" << endl;
    pause();

    while(true) {
        #ifdef _WIN32
            system("cls");
        #else
            system("clear");
        #endif

        cout << "\t\t============================================" << endl;
        cout << "\t\t        National Bank of India              " << endl;
        cout << "\t\t============================================" << endl;
        cout << "\t\t  1. Open New Account" << endl;
        cout << "\t\t  2. View All Accounts" << endl;
        cout << "\t\t  3. Search Account" << endl;
        cout << "\t\t  4. Deposit Funds" << endl;
        cout << "\t\t  5. Withdraw Funds" << endl;
        cout << "\t\t  6. Modify Account Details" << endl;
        cout << "\t\t  7. Close Account" << endl;
        cout << "\t\t  8. Exit" << endl;
        cout << "\t\t============================================" << endl;
        cout << "\t\tPlease select an option: ";
        cin >> choice;

        // If cin failed (e.g. user typed "abc"), clear the error and flush the buffer
        if(cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "\t\tInvalid input! Please enter a number." << endl;
            pause();
            continue;
        }

        cin.ignore();   // Clear leftover newline before any getline below

        switch(choice) {
            case 1:{
                // Collect details and open a new account
                string name;
                int accountNumber;
                double balance;
                char accountType;

                cout << "\t\t--- Open New Account ---" << endl;
                cout << "\t\tEnter Full Name        : ";
                getline(cin, name);   // getline used to support names with spaces e.g. "John Doe"

                cout << "\t\tEnter Account Number   : ";
                cin >> accountNumber;

                // Reject duplicate account numbers early before collecting further input
                if(bank.findAccount(accountNumber) != nullptr) {
                    cout << "\t\tAccount number already exists!" << endl;
                    break;
                }

                cout << "\t\tEnter Account Type (S = Savings / C = Current): ";
                cin >> accountType;
                accountType = toupper(accountType);
                if(accountType != 'S' && accountType != 'C') {
                    cout << "\t\tInvalid type! Defaulting to Savings." << endl;
                    accountType = 'S';
                }

                cout << "\t\tEnter Initial Deposit  : ";
                cin >> balance;

                if(balance <= 0) {
                    cout << "\t\tInitial deposit must be greater than 0." << endl;
                    break;
                }

                if(bank.addAccount(name, accountNumber, balance, accountType)) {
                    cout << "\t\tAccount opened successfully. Welcome aboard!" << endl;
                } else {
                    cout << "\t\tAccount could not be created. Please check the details." << endl;
                }
                break;
            }
            case 2:{
                cout << "\t\t--- All Registered Accounts ---" << endl;
                bank.showAllAccounts();
                break;
            }
            case 3:{
                int accountNumber;
                cout << "\t\t--- Account Enquiry ---" << endl;
                cout << "\t\tEnter Account Number: ";
                cin >> accountNumber;
                bank.searchAccount(accountNumber);
                break;
            }
            case 4:{
                int accountNumber;
                double amount;
                cout << "\t\t--- Deposit Funds ---" << endl;
                cout << "\t\tEnter Account Number: ";
                cin >> accountNumber;
                BankAccount* account = bank.findAccount(accountNumber);
                if(account) {
                    cout << "\t\tEnter Amount to Deposit: ";
                    cin >> amount;
                    account->deposit(amount);
                }
                else {
                    cout << "\t\tAccount Not Found!" << endl;
                }
                break;
            }
            case 5:{
                int accountNumber;
                double amount;
                cout << "\t\t--- Withdraw Funds ---" << endl;
                cout << "\t\tEnter Account Number: ";
                cin >> accountNumber;
                BankAccount* account = bank.findAccount(accountNumber);
                if(account) {
                    cout << "\t\tEnter Amount to Withdraw: ";
                    cin >> amount;
                    account->withdraw(amount);
                }
                else {
                    cout << "\t\tAccount Not Found!" << endl;
                }
                break;
            }
            case 6:{
                int accountNumber;
                cout << "\t\t--- Modify Account Details ---" << endl;
                cout << "\t\tEnter Account Number: ";
                cin >> accountNumber;
                bank.modifyAccount(accountNumber);
                break;
            }
            case 7:{
                // Show account details and ask for explicit confirmation before closing
                int accountNumber;
                cout << "\t\t--- Close Account ---" << endl;
                cout << "\t\tEnter Account Number to Close: ";
                cin >> accountNumber;

                BankAccount* account = bank.findAccount(accountNumber);
                if(!account) {
                    cout << "\t\tAccount Not Found!" << endl;
                    break;
                }

                // Display account details so the user knows exactly what they're closing
                cout << "\t\tAccount Holder : " << account->getName() << endl;
                cout << "\t\tAccount Type   : " << account->getAccountTypeStr() << endl;
                cout << "\t\tCurrent Balance: " << account->getBalance() << endl;

                // Only capital Y confirms — anything else cancels the operation
                cout << "\t\tPress Y to confirm account closure. Any other key cancels: ";
                char confirm;
                cin >> confirm;
                if(confirm == 'Y') {
                    bank.deleteAccount(accountNumber);
                    cout << "\t\tAccount closed successfully." << endl;
                } else {
                    cout << "\t\tOperation cancelled." << endl;
                }
                break;
            }
            case 8:{
                // Clear screen and show farewell message before exiting
                #ifdef _WIN32
                    system("cls");
                #else
                    system("clear");
                #endif
                cout << "\t\t============================================" << endl;
                cout << "\t\t  Thank you for choosing National Bank of   " << endl;
                cout << "\t\t  India. We look forward to serving you     " << endl;
                cout << "\t\t  again. Have a wonderful day!              " << endl;
                cout << "\t\t============================================" << endl;
                exit(0);
            }
            default:{
                cout << "\t\tInvalid choice! Please select an option between 1 and 8." << endl;
                break;
            }
        }

        pause();
    }
}
