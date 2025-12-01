Bank Account Management System
A C++ banking system that implements savings and checking accounts with exception handling, transfers, and overdraft protection.
Features

Two Account Types:

Savings Account: Supports overdraft protection
Checking Account: Includes interest rate functionality


Core Operations:

Deposit funds
Withdraw funds
Transfer between accounts
Account lookup by card number


Exception Handling:

Negative amount protection
Insufficient funds detection
Account not found errors
Custom exception hierarchy



Files

bank_system.hpp - Header file with class declarations
banking_system.cpp - Implementation of banking system
main.cpp - Comprehensive testing suite
Makefile - Build automation

Requirements

C++17 compatible compiler (g++, clang++)
Make utility

Building
Compile the project:
bashmake
Run the executable:
bashmake run
Clean build files:
bashmake clean
Rebuild from scratch:
bashmake rebuild
Usage Example
cppBank bank;

// Create accounts
SavingsAccount alice(1000.0, "Alice Johnson", 500.0);
CheckingAccount bob(2500.0, "Bob Smith", 5.0);

bank.CreateSaving(alice);
bank.CreateChecking(bob);

// Perform operations
alice.deposit(500.0);
alice.withdraw(300.0);
bank.transfer(alice, bob, 200.0);

// Display account info
alice.display();
Exception Types

Negative_Amount - Thrown when negative values are used
InsufficientFunds - Thrown when account lacks funds
AccountNotFound - Thrown when card number doesn't exist

Testing
The main.cpp file includes 16 comprehensive tests covering:

Account creation and display
Deposits and withdrawals
Overdraft usage
Transfers between accounts
All exception scenarios
Edge cases

Run with make run to see full test output.
Class Hierarchy
BankException (extends std::runtime_error)
├── Negative_Amount
├── InsufficientFunds
└── AccountNotFound

BankAccount (abstract base class)
├── SavingsAccount
└── CheckingAccount

Bank (manages multiple accounts)
