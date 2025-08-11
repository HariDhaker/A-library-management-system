### **System Architecture Design**

**Database Design**[1][2]
```
Core Tables:
- Users (user_id, name, email, phone, user_type, password)
- Books (book_id, title, author, isbn, genre, publication_date, total_copies)
- Transactions (transaction_id, user_id, book_id, issue_date, due_date, return_date, status)
- Fines (fine_id, user_id, transaction_id, amount, payment_status)
```

**Class Structure Design**[3][4]
```cpp
Main Classes:
- Book: Manages book information and operations
- User: Handles user data and authentication
- Transaction: Manages borrowing/returning operations
- Library: Central management class
- DatabaseManager: Handles data persistence
```


### **Technology Stack**

**Core Technologies**
- **Programming Language**: C++ (C++11 or higher)
- **Database**:file-based storage
- **Development Environment**: Visual Studio
- **Libraries**: Standard Template Library (STL)

### **Book Search Algorithm**

```
Algorithm: Linear Search with Multiple Criteria
Input: search_term, search_type (title/author/isbn)
Output: list of matching books

1. Initialize empty result list
2. For each book in book_collection:
   a. If search_type is "title":
      - Compare search_term with book.title (case-insensitive)
   b. If search_type is "author":
      - Compare search_term with book.author (case-insensitive)
   c. If search_type is "isbn":
      - Compare search_term with book.isbn (exact match)
   d. If match found, add book to result list
3. Return result list

Time Complexity: O(n)
Space Complexity: O(k) where k is number of matches
```

### **Book Issue Algorithm**

```
Algorithm: Book Issue Process
Input: user_id, book_id
Output: success/failure status

1. Validate user_id exists and is active
2. Check if user has reached borrowing limit
3. Validate book_id exists in system
4. Check if book is available (not issued)
5. If all validations pass:
   a. Create new transaction record
   b. Set issue_date to current date
   c. Calculate due_date (issue_date + loan_period)
   d. Update book status to "issued"
   e. Link transaction to user and book
   f. Return success
6. Else return failure with error message

Time Complexity: O(1)
Space Complexity: O(1)
```

### **Fine Calculation Algorithm**

```
Algorithm: Automatic Fine Calculation
Input: transaction_id
Output: fine_amount

1. Get transaction details by transaction_id
2. Get current_date
3. If return_date is null (book not returned):
   a. overdue_days = current_date - due_date
4. Else:
   a. overdue_days = return_date - due_date
5. If overdue_days > 0:
   a. fine_amount = overdue_days * daily_fine_rate
   b. Apply maximum fine limit if applicable
6. Else:
   a. fine_amount = 0
7. Return fine_amount

Time Complexity: O(1)
Space Complexity: O(1)
```

### **User Authentication Algorithm**

```
Algorithm: Secure Login Process
Input: username, password
Output: authentication_status, user_session

1. Retrieve user record by username
2. If user not found:
   a. Return "Invalid username"
3. Hash input password using same algorithm as stored
4. Compare hashed_password with stored_password_hash
5. If passwords match:
   a. Create user session
   b. Set session_timeout
   c. Return "Login successful" with session
6. Else:
   a. Log failed attempt
   b. Return "Invalid password"

Time Complexity: O(1) for hash table lookup
Space Complexity: O(1)
```
