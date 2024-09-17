#include <iostream>
#include <fstream>
#include <string>
#include <limits>
#include <iomanip>

using namespace std;

void showHeading() {
    cout << "_________________________________________________________________________________\n";
    cout << " \n\t\t\t\t BOOK SHOP MANAGEMENT SYSTEM\n";
    cout << "_________________________________________________________________________________\n";
}

class Authentication {
public:
    static bool authenticate() {
        const int maxAttempts = 3;  // Maximum number of login attempts
        string username, password;

        for (int attempts = 1; attempts <= maxAttempts; ++attempts) {
            cout << "\nEnter username: ";
            cin >> username;
            cout << "Enter password: ";
            cin >> password;

            if (username == "abc" && password == "123") {
                return true;  // Authentication successful
            } else {
                cout << "Authentication failed\n" << " Please enter the correct username and password.\n";
                cout << "Attempts left: " << maxAttempts - attempts << endl;
            }
        }

        cout << "Maximum login attempts reached. Exiting...\n";
        return false;
    }
};

class Book {
public:
    string title;
    string author;
    int totalCopies;
    int availableCopies;

    Book(string t, string a, int copies = 10)
        : title(t), author(a), totalCopies(copies), availableCopies(copies) {}

    bool isAvailable() const {
        return availableCopies > 0;
    }

    void sellCopy(int numCopies) {
        if (isAvailable() && numCopies > 0 && numCopies <= availableCopies) {
            availableCopies -= numCopies;
            cout << numCopies << " copy/copies of book '" << title << "' by "
                 << author << " purchased successfully. Remaining copies: "
                 << availableCopies << "\n";
        } else {
            cout << "Invalid number of copies or the book '" << title
                 << "' is not available in the requested quantity.\n\n";
        }
    }

    void addStock(int additionalCopies) {
        totalCopies += additionalCopies;
        availableCopies += additionalCopies;
        cout << "Additional " << additionalCopies << " copies of book '"
             << title << "' by " << author
             << " added to the stock. Total copies: " << totalCopies << "\n\n";
    }

    void displayBookInfo() const {
        cout << setw(25) << left << title << setw(25) << left << author
             << setw(20) << left << "Total Copies: " << " " << totalCopies  
             << setw(20) << left << "Available Copies: " << availableCopies << "\n";
    }
};

class Bookshop {
private:
    Book books[5];

public:
    Bookshop() : books
	{
                    {"C++", "Bjarne Stroustrup"},
                    {"Web", "John Duckett"},
                    {"C", "Dennis Ritchie"},
                    {"Python", "Guido van Rossum"},
                    {"Communication Skills", "Dale Carnegie"}} {}

    ~Bookshop() {
        saveBooksToFile("books.txt");
    }

    void loadBooksFromFile(const string &filename) {
        ifstream inFile(filename.c_str());
        if (inFile.is_open()) {
            for (int i = 0; i < 5; ++i) {
                inFile >> books[i].title >> books[i].author >>
                    books[i].totalCopies >> books[i].availableCopies;
            }
            inFile.close();
        } else {
            cout << "Error: Could not open file for reading.\n";
        }
    }

    void saveBooksToFile(const string &filename) const {
        ofstream outFile(filename.c_str());
        if (outFile.is_open()) {
            for (int i = 0; i < 5; ++i) {
                outFile << books[i].title << " " << books[i].author << " "
                        << books[i].totalCopies << " "
                        << books[i].availableCopies << "\n";
            }
            outFile.close();
        } else {
            cout << "Error: Could not open file for writing.\n";
        }
    }

    void displayBooks() const {
        cout << "Available Books:\n";
        for (int i = 0; i < 5; ++i) {
            books[i].displayBookInfo();
        }
        cout << "--------------------------\n";
    }

    void inquireBookAvailability(int bookIndex) const {
        if (bookIndex >= 1 && bookIndex <= 5) {
            books[bookIndex - 1].displayBookInfo();
        } else {
            cout << "Invalid book index.\n";
        }
    }

    void sellBookCopy(int bookIndex) {
        if (bookIndex >= 1 && bookIndex <= 5) {
            int numCopies;
            cout << "Enter the number of copies you want to purchase: ";
            while (true) {
                if (cin >> numCopies && numCopies > 0) {
                    break;
                } else {
                    cout << "Invalid input. Please enter a positive integer for the number of copies: ";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
            }
            books[bookIndex - 1].sellCopy(numCopies);
        } else {
            cout << "Invalid book index.\n";
        }
    }

    void addNewStock(int bookIndex) {
        if (bookIndex >= 1 && bookIndex <= 5) {
            int additionalCopies;
            cout << "Enter the number of additional copies you want to add to the stock: ";
            while (true) {
                if (cin >> additionalCopies && additionalCopies > 0) {
                    break;
                } else {
                    cout << "Invalid input. Please enter a positive integer for the number of additional copies: ";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
            }
            books[bookIndex - 1].addStock(additionalCopies);
        } else {
            cout << "Invalid book index.\n";
        }
    }

    void generateReport(const string &filename) const {
        ofstream reportFile(filename.c_str());
        if (reportFile.is_open()) {
            reportFile << "BOOKSHOP MANAGEMENT SYSTEM REPORT\n";
            reportFile << "_________________\n\n";
            reportFile << setw(25) << left << "Title" << setw(25) << left << "Author"
                       << setw(20) << left << "Total Copies" << setw(20) << left << "Available Copies\n";
            reportFile << "-------------------------------------------------\n";
            for (int i = 0; i < 5; ++i) {
                reportFile << setw(25) << left << books[i].title << setw(25) << left << books[i].author
                           << setw(20) << left << books[i].totalCopies << setw(20) << left << books[i].availableCopies << "\n";
            }
            reportFile << "_________________\n";
            cout << "Report generated successfully. Check '" << filename << "' for details.\n";
            reportFile.close();
        } else {
            cout << "Error: Could not open file for writing the report.\n";
        }
    }
};

int main() {
    showHeading();
    if (!Authentication::authenticate()) {
        cout << "Authentication failed. Exiting...\n";
        return 0;
    }

    Bookshop bookshop;

    cout << "_________________________________________________________________\n";
    cout << "        \n\t\t\t\t LOGIN SUCCESSFULLY\n";
    cout << "_________________________________________________________________\n";

    while (true) {
        cout << "_____________________________\n";
        cout << "1. Display Available Books\n";
        cout << "2. Inquire about a Book\n";
        cout << "3. Purchase a Book\n";
        cout << "4. Add New Stock\n";
        cout << "5. Generate Report\n";
        cout << "6. Exit\n";
        cout << "_____________________________\n";
        cout << "Enter your choice: ";

        int choice;
        while (true) {
            if (cin >> choice && choice >= 1 && choice <= 6) {
                break;
            } else {
                cout << "Invalid input. Please enter a number between 1 and 6: ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        }

        switch (choice) {
            case 1:
                bookshop.displayBooks();
                break;
            case 2: {
                int bookIndex;
                cout << "Enter the index of the book you want to inquire about: ";
                while (true) {
                    if (cin >> bookIndex && bookIndex >= 1 && bookIndex <= 5) {
                        break;
                    } else {
                        cout << "Invalid input. Please enter a number between 1 and 5: ";
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    }
                }
                bookshop.inquireBookAvailability(bookIndex);
                break;
            }
            case 3: {
                int bookIndex;
                cout << "Enter the index of the book you want to purchase: ";
                while (true) {
                    if (cin >> bookIndex && bookIndex >= 1 && bookIndex <= 5) {
                        break;
                    } else {
                        cout << "Invalid input. Please enter a number between 1 and 5: ";
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    }
                }
                bookshop.sellBookCopy(bookIndex);
                break;
            }
            case 4: {
                int bookIndex;
                cout << "Enter the index of the book you want to add new stock: ";
                while (true) {
                    if (cin >> bookIndex && bookIndex >= 1 && bookIndex <= 5) {
                        break;
                    } else {
                        cout << "Invalid input. Please enter a number between 1 and 5: ";
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    }
                }
                bookshop.addNewStock(bookIndex);
                break;
            }
            case 5: {
                string reportFilename = "bookshop_report.txt";
                bookshop.generateReport(reportFilename);
                break;
            }
            case 6:
                cout << "Thank you for using the Bookshop Management System. Goodbye!\n";
                return 0;
            default:
                cout << "Invalid choice. Please enter a valid option.\n";
        }
    }

    return 0;
}

