🏦 C++ Bank System

A complete banking system implemented in modern C++ featuring polymorphism, custom exceptions, two account types, money transfers, and an overloaded operator[] for card-based account lookup.
Includes a full test suite inside main.cpp.

🚀 Features

Abstract base class BankAccount

Two concrete account types:

SavingsAccount — supports overdraft

CheckingAccount — supports interest rate

Automatic, unique card number generation

Account lookup via Bank::operator[]

Money transfer between accounts

Full exception system:

Negative_Amount

InsufficientFunds

AccountNotFound

16 comprehensive tests covering all features

📁 Project Structure
📁 project/
 ├── Makefile
 ├── bank_system.hpp
 ├── banking_system.cpp
 ├── main.cpp

🛠 Build & Run
Build:
make

Run:
make run

Rebuild from scratch:
make rebuild

Clean object files:
make clean

📘 Class Overview
🔹 BankAccount (Abstract)

Base class for all account types.
Fields:

_card_number

_balance

_name

Pure virtual methods:

display()

withdraw()

deposit()

🔹 SavingsAccount

Special features:

Supports overdraft (_overdraft)

Can withdraw beyond balance if overdraft allows

🔹 CheckingAccount

Special features:

Has interest rate (_rate)

update() recalculates balance based on the rate

🔹 Bank

Stores account pointers and provides:

Creating savings/checking accounts

Access accounts by card number via operator[]

Money transfers with exception safety

🧪 Testing

main.cpp includes 16 detailed test cases, verifying:

✔ Account creation
✔ Displaying account info
✔ Deposits and withdrawals
✔ Overdraft behavior
✔ Transfers
✔ Access via operator[]
✔ All exception types
✔ Complex operation sequences

Example output snippet:

TEST 1: Creating Accounts
============================================================

Created 4 accounts successfully
Alice's card: 1178584561034111
Bob's card:   ...

💡 Usage Example
Bank bank;

SavingsAccount alice(1000.0, "Alice Johnson", 500.0);
CheckingAccount bob(2500.0, "Bob Smith", 5.0);

bank.CreateSaving(alice);
bank.CreateChecking(bob);

alice.deposit(500);
bank.transfer(alice, bob, 200);
bob.withdraw(300);

⚠ Exception Handling

Custom exceptions guarantee safety and clarity:

Negative_Amount — deposit/withdraw/transfer below zero

InsufficientFunds — not enough balance

AccountNotFound — invalid card number

Example:

try {
    alice.withdraw(-50);
} catch (Negative_Amount& e) {
    std::cout << e.what();
}

📄 License

MIT License — feel free to use, modify, and distribute.
