#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <ctime>
#include <algorithm>
#include <fstream>

using namespace std;

// Book class definition
class Book
{
private:
    int bookId;
    string title;
    string author;
    string isbn;
    string genre;
    int totalCopies;
    int availableCopies;
    double price;
    string publicationDate;

public:
    // Constructor
    Book(int id, string t, string a, string i, string g,
         int copies, double p, string pubDate)
        : bookId(id), title(t), author(a), isbn(i), genre(g),
          totalCopies(copies), availableCopies(copies),
          price(p), publicationDate(pubDate) {}

    // Getter methods
    int getBookId() const { return bookId; }
    string getTitle() const { return title; }
    string getAuthor() const { return author; }
    string getIsbn() const { return isbn; }
    string getGenre() const { return genre; }
    int getAvailableCopies() const { return availableCopies; }
    int getTotalCopies() const { return totalCopies; }
    double getPrice() const { return price; }
    string getPublicationDate() const { return publicationDate; }

    // Setter methods
    void setTitle(const string &t) { title = t; }
    void setAuthor(const string &a) { author = a; }
    void setGenre(const string &g) { genre = g; }
    void setPrice(double p) { price = p; }

    // Book availability methods
    bool isAvailable() const { return availableCopies > 0; }

    bool issueBook()
    {
        if (availableCopies > 0)
        {
            availableCopies--;
            return true;
        }
        return false;
    }

    void returnBook()
    {
        if (availableCopies < totalCopies)
        {
            availableCopies++;
        }
    }

    // Display book information
    void displayInfo() const
    {
        cout << "Book ID: " << bookId << endl;
        cout << "Title: " << title << endl;
        cout << "Author: " << author << endl;
        cout << "ISBN: " << isbn << endl;
        cout << "Genre: " << genre << endl;
        cout << "Available/Total: " << availableCopies
             << "/" << totalCopies << endl;
        cout << "Price: $" << price << endl;
        cout << "Publication Date: " << publicationDate << endl;
        cout << "Status: " << (isAvailable() ? "Available" : "Not Available")
             << endl;
    }
};

// User class definition
class User
{
private:
    int userId;
    string name;
    string email;
    string phone;
    string userType; // "student", "faculty", "librarian", "admin"
    string password;
    double accountBalance;
    int borrowedBooks;
    int maxBooksAllowed;
    vector<int> borrowingHistory;

public:
    // Constructor
    User(int id, string n, string e, string p, string type,
         string pass, int maxBooks = 5)
        : userId(id), name(n), email(e), phone(p), userType(type),
          password(pass), accountBalance(0.0), borrowedBooks(0),
          maxBooksAllowed(maxBooks) {}

    // Getter methods
    int getUserId() const { return userId; }
    string getName() const { return name; }
    string getEmail() const { return email; }
    string getPhone() const { return phone; }
    string getUserType() const { return userType; }
    double getAccountBalance() const { return accountBalance; }
    int getBorrowedBooks() const { return borrowedBooks; }
    int getMaxBooksAllowed() const { return maxBooksAllowed; }

    // Account management
    bool canBorrowMore() const
    {
        return borrowedBooks < maxBooksAllowed;
    }

    void incrementBorrowedBooks() { borrowedBooks++; }
    void decrementBorrowedBooks()
    {
        if (borrowedBooks > 0)
            borrowedBooks--;
    }

    void addToBalance(double amount) { accountBalance += amount; }
    bool deductFromBalance(double amount)
    {
        if (accountBalance >= amount)
        {
            accountBalance -= amount;
            return true;
        }
        return false;
    }

    // Password verification
    bool verifyPassword(const string &pass) const
    {
        return password == pass; // In real implementation, use hashing
    }

    void changePassword(const string &newPass)
    {
        password = newPass; // In real implementation, hash the password
    }

    // Display user information
    void displayInfo() const
    {
        cout << "User ID: " << userId << endl;
        cout << "Name: " << name << endl;
        cout << "Email: " << email << endl;
        cout << "Phone: " << phone << endl;
        cout << "User Type: " << userType << endl;
        cout << "Account Balance: $" << accountBalance << endl;
        cout << "Books Borrowed: " << borrowedBooks
             << "/" << maxBooksAllowed << endl;
    }
};

// Transaction class definition
class Transaction
{
private:
    int transactionId;
    int userId;
    int bookId;
    time_t issueDate;
    time_t dueDate;
    time_t returnDate;
    string status; // "issued", "returned", "overdue"
    double fineAmount;

public:
    // Constructor
    Transaction(int tId, int uId, int bId, int loanDays = 14)
        : transactionId(tId), userId(uId), bookId(bId),
          fineAmount(0.0), status("issued")
    {
        time(&issueDate);
        dueDate = issueDate + (loanDays * 24 * 60 * 60); // Convert days to seconds
        returnDate = 0;
    }

    // Getter methods
    int getTransactionId() const { return transactionId; }
    int getUserId() const { return userId; }
    int getBookId() const { return bookId; }
    time_t getIssueDate() const { return issueDate; }
    time_t getDueDate() const { return dueDate; }
    time_t getReturnDate() const { return returnDate; }
    string getStatus() const { return status; }
    double getFineAmount() const { return fineAmount; }

    // Transaction operations
    void returnBook()
    {
        time(&returnDate);
        status = "returned";
        calculateFine();
    }

    void calculateFine(double dailyFineRate = 1.0)
    {
        time_t currentTime;
        time(&currentTime);

        time_t compareDate = (status == "returned") ? returnDate : currentTime;

        if (compareDate > dueDate)
        {
            int overdueDays = (compareDate - dueDate) / (24 * 60 * 60);
            fineAmount = overdueDays * dailyFineRate;
            if (status == "issued")
            {
                status = "overdue";
            }
        }
    }

    bool isOverdue() const
    {
        time_t currentTime;
        time(&currentTime);
        return currentTime > dueDate && status == "issued";
    }

    // Display transaction information
    void displayInfo() const
    {
        cout << "Transaction ID: " << transactionId << endl;
        cout << "User ID: " << userId << endl;
        cout << "Book ID: " << bookId << endl;
        cout << "Issue Date: " << ctime(&issueDate);
        cout << "Due Date: " << ctime(&dueDate);
        if (returnDate != 0)
        {
            cout << "Return Date: " << ctime(&returnDate);
        }
        cout << "Status: " << status << endl;
        cout << "Fine Amount: $" << fineAmount << endl;
    }
};

// Main Library Management System class
class LibraryManagementSystem
{
private:
    vector<Book> books;
    vector<User> users;
    vector<Transaction> transactions;
    map<string, int> userCredentials; // username -> userId mapping
    int nextBookId;
    int nextUserId;
    int nextTransactionId;
    User *currentUser;

public:
    // Constructor
    LibraryManagementSystem() : nextBookId(1001), nextUserId(2001),
                                nextTransactionId(3001), currentUser(nullptr)
    {
        initializeSystem();
    }

    // Initialize system with sample data
    void initializeSystem()
    {
        // Add sample books
        addBook("The Great Gatsby", "F. Scott Fitzgerald", "978-0-7432-7356-5",
                "Fiction", 3, 12.99, "1925-04-10");
        addBook("To Kill a Mockingbird", "Harper Lee", "978-0-06-112008-4",
                "Fiction", 2, 14.99, "1960-07-11");
        addBook("1984", "George Orwell", "978-0-452-28423-4",
                "Dystopian", 4, 13.99, "1949-06-08");
        addBook("Data Structures and Algorithms", "Thomas Cormen",
                "978-0-262-03384-8", "Computer Science", 5, 89.99, "2009-07-31");

        // Add sample users
        addUser("admin", "System Administrator", "admin@library.com",
                "555-0001", "admin", "admin123", 10);
        addUser("librarian1", "John Smith", "john@library.com",
                "555-0002", "librarian", "lib123", 10);
        addUser("student1", "Alice Johnson", "alice@student.edu",
                "555-0003", "student", "stu123", 5);
        addUser("faculty1", "Dr. Robert Brown", "robert@university.edu",
                "555-0004", "faculty", "fac123", 10);
    }

    // Book management methods
    void addBook(const string &title, const string &author, const string &isbn,
                 const string &genre, int copies, double price,
                 const string &pubDate)
    {
        Book newBook(nextBookId++, title, author, isbn, genre, copies, price, pubDate);
        books.push_back(newBook);
        cout << "Book added successfully with ID: " << (nextBookId - 1) << endl;
    }

    void displayAllBooks() const
    {
        if (books.empty())
        {
            cout << "No books available in the library." << endl;
            return;
        }

        cout << "\n=== LIBRARY CATALOG ===" << endl;
        for (const auto &book : books)
        {
            cout << "\n------------------------" << endl;
            book.displayInfo();
        }
    }

    vector<Book *> searchBooks(const string &searchTerm, const string &searchType)
    {
        vector<Book *> results;
        string lowerSearchTerm = searchTerm;
        transform(lowerSearchTerm.begin(), lowerSearchTerm.end(),
                  lowerSearchTerm.begin(), ::tolower);

        for (auto &book : books)
        {
            bool match = false;

            if (searchType == "title")
            {
                string lowerTitle = book.getTitle();
                transform(lowerTitle.begin(), lowerTitle.end(),
                          lowerTitle.begin(), ::tolower);
                match = lowerTitle.find(lowerSearchTerm) != string::npos;
            }
            else if (searchType == "author")
            {
                string lowerAuthor = book.getAuthor();
                transform(lowerAuthor.begin(), lowerAuthor.end(),
                          lowerAuthor.begin(), ::tolower);
                match = lowerAuthor.find(lowerSearchTerm) != string::npos;
            }
            else if (searchType == "isbn")
            {
                match = book.getIsbn() == searchTerm;
            }
            else if (searchType == "genre")
            {
                string lowerGenre = book.getGenre();
                transform(lowerGenre.begin(), lowerGenre.end(),
                          lowerGenre.begin(), ::tolower);
                match = lowerGenre.find(lowerSearchTerm) != string::npos;
            }

            if (match)
            {
                results.push_back(&book);
            }
        }

        return results;
    }

    // User management methods
    void addUser(const string &username, const string &name, const string &email,
                 const string &phone, const string &userType,
                 const string &password, int maxBooks = 5)
    {
        User newUser(nextUserId++, name, email, phone, userType, password, maxBooks);
        users.push_back(newUser);
        userCredentials[username] = nextUserId - 1;
        cout << "User registered successfully with ID: " << (nextUserId - 1) << endl;
    }

    bool login(const string &username, const string &password)
    {
        auto it = userCredentials.find(username);
        if (it != userCredentials.end())
        {
            int userId = it->second;
            for (auto &user : users)
            {
                if (user.getUserId() == userId && user.verifyPassword(password))
                {
                    currentUser = &user;
                    cout << "Login successful! Welcome, " << user.getName() << endl;
                    return true;
                }
            }
        }
        cout << "Invalid username or password." << endl;
        return false;
    }

    void logout()
    {
        if (currentUser)
        {
            cout << "Goodbye, " << currentUser->getName() << "!" << endl;
            currentUser = nullptr;
        }
    }

    bool isLoggedIn() const
    {
        return currentUser != nullptr;
    }

    // Transaction methods
    bool issueBook(int bookId)
    {
        if (!currentUser)
        {
            cout << "Please login first." << endl;
            return false;
        }

        if (!currentUser->canBorrowMore())
        {
            cout << "You have reached your borrowing limit." << endl;
            return false;
        }

        // Find the book
        Book *bookToIssue = nullptr;
        for (auto &book : books)
        {
            if (book.getBookId() == bookId)
            {
                bookToIssue = &book;
                break;
            }
        }

        if (!bookToIssue)
        {
            cout << "Book not found." << endl;
            return false;
        }

        if (!bookToIssue->isAvailable())
        {
            cout << "Book is not available for checkout." << endl;
            return false;
        }

        // Issue the book
        if (bookToIssue->issueBook())
        {
            Transaction newTransaction(nextTransactionId++, currentUser->getUserId(), bookId);
            transactions.push_back(newTransaction);
            currentUser->incrementBorrowedBooks();

            cout << "Book issued successfully!" << endl;
            cout << "Transaction ID: " << (nextTransactionId - 1) << endl;
            time_t due = newTransaction.getDueDate();
            cout << "Due Date: " << ctime(&due);

            return true;
        }

        return false;
    }

    bool returnBook(int bookId)
    {
        if (!currentUser)
        {
            cout << "Please login first." << endl;
            return false;
        }

        // Find the transaction
        Transaction *transactionToReturn = nullptr;
        for (auto &transaction : transactions)
        {
            if (transaction.getUserId() == currentUser->getUserId() &&
                transaction.getBookId() == bookId &&
                transaction.getStatus() != "returned")
            {
                transactionToReturn = &transaction;
                break;
            }
        }

        if (!transactionToReturn)
        {
            cout << "No active transaction found for this book." << endl;
            return false;
        }

        // Find the book and return it
        for (auto &book : books)
        {
            if (book.getBookId() == bookId)
            {
                book.returnBook();
                transactionToReturn->returnBook();
                currentUser->decrementBorrowedBooks();

                cout << "Book returned successfully!" << endl;

                // Check for fines
                if (transactionToReturn->getFineAmount() > 0)
                {
                    cout << "Fine Amount: $" << transactionToReturn->getFineAmount() << endl;
                    cout << "Please pay the fine at the library counter." << endl;
                }

                return true;
            }
        }

        return false;
    }

    // Reporting methods
    void displayUserTransactions() const
    {
        if (!currentUser)
        {
            cout << "Please login first." << endl;
            return;
        }

        cout << "\n=== YOUR TRANSACTIONS ===" << endl;
        bool hasTransactions = false;

        for (const auto &transaction : transactions)
        {
            if (transaction.getUserId() == currentUser->getUserId())
            {
                cout << "\n------------------------" << endl;
                transaction.displayInfo();

                // Display book details
                for (const auto &book : books)
                {
                    if (book.getBookId() == transaction.getBookId())
                    {
                        cout << "Book: " << book.getTitle()
                             << " by " << book.getAuthor() << endl;
                        break;
                    }
                }
                hasTransactions = true;
            }
        }

        if (!hasTransactions)
        {
            cout << "No transactions found." << endl;
        }
    }

    void displayOverdueBooks() const
    {
        if (!currentUser || (currentUser->getUserType() != "admin" &&
                             currentUser->getUserType() != "librarian"))
        {
            cout << "Access denied. Admin/Librarian privileges required." << endl;
            return;
        }

        cout << "\n=== OVERDUE BOOKS ===" << endl;
        bool hasOverdue = false;

        for (const auto &transaction : transactions)
        {
            if (transaction.isOverdue())
            {
                cout << "\n------------------------" << endl;
                transaction.displayInfo();

                // Display user and book details
                for (const auto &user : users)
                {
                    if (user.getUserId() == transaction.getUserId())
                    {
                        cout << "User: " << user.getName()
                             << " (" << user.getEmail() << ")" << endl;
                        break;
                    }
                }

                for (const auto &book : books)
                {
                    if (book.getBookId() == transaction.getBookId())
                    {
                        cout << "Book: " << book.getTitle()
                             << " by " << book.getAuthor() << endl;
                        break;
                    }
                }
                hasOverdue = true;
            }
        }

        if (!hasOverdue)
        {
            cout << "No overdue books found." << endl;
        }
    }

    // Main menu system
    void showMainMenu()
    {
        cout << "\n=== LIBRARY MANAGEMENT SYSTEM ===" << endl;
        cout << "1. Login" << endl;
        cout << "2. Register New User" << endl;
        cout << "3. View All Books" << endl;
        cout << "4. Search Books" << endl;
        cout << "0. Exit" << endl;
        cout << "Choose an option: ";
    }

    void showUserMenu()
    {
        cout << "\n=== USER MENU ===" << endl;
        cout << "Current User: " << currentUser->getName()
             << " (" << currentUser->getUserType() << ")" << endl;
        cout << "1. View All Books" << endl;
        cout << "2. Search Books" << endl;
        cout << "3. Issue Book" << endl;
        cout << "4. Return Book" << endl;
        cout << "5. View My Transactions" << endl;
        cout << "6. View My Account" << endl;

        if (currentUser->getUserType() == "admin" ||
            currentUser->getUserType() == "librarian")
        {
            cout << "7. Add New Book" << endl;
            cout << "8. View Overdue Books" << endl;
            cout << "9. View All Users" << endl;
        }

        cout << "0. Logout" << endl;
        cout << "Choose an option: ";
    }

    void handleUserRegistration()
    {
        string username, name, email, phone, userType, password;

        cout << "Enter username: ";
        cin >> username;

        // Check if username already exists
        if (userCredentials.find(username) != userCredentials.end())
        {
            cout << "Username already exists. Please choose a different username." << endl;
            return;
        }

        cin.ignore(); // Clear input buffer
        cout << "Enter full name: ";
        getline(cin, name);

        cout << "Enter email: ";
        cin >> email;

        cout << "Enter phone: ";
        cin >> phone;

        cout << "Enter user type (student/faculty): ";
        cin >> userType;

        cout << "Enter password: ";
        cin >> password;

        int maxBooks = (userType == "faculty") ? 10 : 5;
        addUser(username, name, email, phone, userType, password, maxBooks);
    }

    void handleBookSearch()
    {
        string searchTerm, searchType;

        cout << "Search by (title/author/isbn/genre): ";
        cin >> searchType;

        cin.ignore(); // Clear input buffer
        cout << "Enter search term: ";
        getline(cin, searchTerm);

        vector<Book *> results = searchBooks(searchTerm, searchType);

        if (results.empty())
        {
            cout << "No books found matching your search." << endl;
        }
        else
        {
            cout << "\n=== SEARCH RESULTS ===" << endl;
            for (const auto &book : results)
            {
                cout << "\n------------------------" << endl;
                book->displayInfo();
            }
        }
    }

    void handleBookIssue()
    {
        int bookId;
        cout << "Enter Book ID to issue: ";
        cin >> bookId;
        issueBook(bookId);
    }

    void handleBookReturn()
    {
        int bookId;
        cout << "Enter Book ID to return: ";
        cin >> bookId;
        returnBook(bookId);
    }

    void handleDynamicAddBook()
    {
        if (!currentUser || (currentUser->getUserType() != "admin" &&
                             currentUser->getUserType() != "librarian"))
        {
            cout << "Access denied. Admin/Librarian privileges required." << endl;
            return;
        }

        string title, author, isbn, genre, pubDate;
        int copies;
        double price;

        cin.ignore(); // Clear input buffer
        cout << "Enter book title: ";
        getline(cin, title);

        cout << "Enter author name: ";
        getline(cin, author);

        cout << "Enter ISBN: ";
        cin >> isbn;

        cout << "Enter genre: ";
        cin >> genre;

        cout << "Enter number of copies: ";
        cin >> copies;

        cout << "Enter price: $";
        cin >> price;

        cout << "Enter publication date (YYYY-MM-DD): ";
        cin >> pubDate;

        addBook(title, author, isbn, genre, copies, price, pubDate);
    }

    void displayAllUsers() const
    {
        if (!currentUser || (currentUser->getUserType() != "admin" &&
                             currentUser->getUserType() != "librarian"))
        {
            cout << "Access denied. Admin/Librarian privileges required." << endl;
            return;
        }

        cout << "\n=== ALL USERS ===" << endl;
        for (const auto &user : users)
        {
            cout << "\n------------------------" << endl;
            user.displayInfo();
        }
    }

    // Main application loop
    void run()
    {
        int choice;

        cout << "Welcome to the Library Management System!" << endl;

        while (true)
        {
            if (!isLoggedIn())
            {
                showMainMenu();
                cin >> choice;

                switch (choice)
                {
                case 1:
                {
                    string username, password;
                    cout << "Enter username: ";
                    cin >> username;
                    cout << "Enter password: ";
                    cin >> password;
                    login(username, password);
                    break;
                }
                case 2:
                    handleUserRegistration();
                    break;
                case 3:
                    displayAllBooks();
                    break;
                case 4:
                    handleBookSearch();
                    break;
                case 0:
                    cout << "Thank you for using Library Management System!" << endl;
                    return;
                default:
                    cout << "Invalid option. Please try again." << endl;
                }
            }
            else
            {
                showUserMenu();
                cin >> choice;

                switch (choice)
                {
                case 1:
                    displayAllBooks();
                    break;
                case 2:
                    handleBookSearch();
                    break;
                case 3:
                    handleBookIssue();
                    break;
                case 4:
                    handleBookReturn();
                    break;
                case 5:
                    displayUserTransactions();
                    break;
                case 6:
                    currentUser->displayInfo();
                    break;
                case 7:
                    if (currentUser->getUserType() == "admin" ||
                        currentUser->getUserType() == "librarian")
                    {
                        handleDynamicAddBook();
                    }
                    else
                    {
                        cout << "Invalid option." << endl;
                    }
                    break;
                case 8:
                    if (currentUser->getUserType() == "admin" ||
                        currentUser->getUserType() == "librarian")
                    {
                        displayOverdueBooks();
                    }
                    else
                    {
                        cout << "Invalid option." << endl;
                    }
                    break;
                case 9:
                    if (currentUser->getUserType() == "admin" ||
                        currentUser->getUserType() == "librarian")
                    {
                        displayAllUsers();
                    }
                    else
                    {
                        cout << "Invalid option." << endl;
                    }
                    break;
                case 0:
                    logout();
                    break;
                default:
                    cout << "Invalid option. Please try again." << endl;
                }
            }
        }
    }
};

// Main function
int main()
{
    LibraryManagementSystem library;
    library.run();
    return 0;
}
