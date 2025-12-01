#include "bank_system.hpp"

void printSeparator() {
    std::cout << "\n============================================================\n\n";
}

int main() {
    
    try {
        Bank bank;
        
        // Test 1: Create accounts and store references
        std::cout << "TEST 1: Creating Accounts\n";
        printSeparator();
        
        SavingsAccount alice(1000.0, "Alice Johnson", 500.0);
        CheckingAccount bob(2500.0, "Bob Smith", 5.0);
        SavingsAccount charlie(500.0, "Charlie Brown", 200.0);
        CheckingAccount diana(1500.0, "Diana Prince", 3.5);
        
        bank.CreateSaving(alice);
        bank.CreateChecking(bob);
        bank.CreateSaving(charlie);
        bank.CreateChecking(diana);
        
        std::cout << "Created 4 accounts successfully\n";
        std::cout << "Alice's card: " << alice.getCardNumer() << "\n";
        std::cout << "Bob's card: " << bob.getCardNumer() << "\n";
        std::cout << "Charlie's card: " << charlie.getCardNumer() << "\n";
        std::cout << "Diana's card: " << diana.getCardNumer() << "\n";
        
        // Test 2: Display all accounts
        std::cout << "\nTEST 2: Display Account Information\n";
        printSeparator();
        
        std::cout << "Alice's Account:\n";
        alice.display();
        std::cout << "\nBob's Account:\n";
        bob.display();
        std::cout << "\nCharlie's Account:\n";
        charlie.display();
        std::cout << "\nDiana's Account:\n";
        diana.display();
        
        // Test 3: Basic deposits
        std::cout << "\nTEST 3: Deposit Operations\n";
        printSeparator();
        
        alice.deposit(500.0);
        std::cout << "Alice deposited $500. New balance: $" << alice.getBalance() << "\n";
        
        bob.deposit(1000.0);
        std::cout << "Bob deposited $1000. New balance: $" << bob.getBalance() << "\n";
        
        // Test 4: Basic withdrawals
        std::cout << "\nTEST 4: Withdrawal Operations\n";
        printSeparator();
        
        alice.withdraw(300.0);
        std::cout << "Alice withdrew $300. New balance: $" << alice.getBalance() << "\n";
        
        bob.withdraw(500.0);
        std::cout << "Bob withdrew $500. New balance: $" << bob.getBalance() << "\n";
        
        // Test 5: Overdraft usage (Savings Account)
        std::cout << "\nTEST 5: Overdraft Usage (Savings)\n";
        printSeparator();
        
        charlie.withdraw(600.0);  // Balance: 500, needs 100 from overdraft
        std::cout << "Charlie withdrew $600 (used overdraft). Balance: $" << charlie.getBalance() << "\n";
        
        // Test 6: Transfer between accounts
        std::cout << "\nTEST 6: Transfer Operations\n";
        printSeparator();
        
        std::cout << "Before transfer - Alice: $" << alice.getBalance() 
                  << ", Bob: $" << bob.getBalance() << "\n";
        
        bank.transfer(alice, bob, 200.0);
        std::cout << "Transferred $200 from Alice to Bob\n";
        std::cout << "After transfer - Alice: $" << alice.getBalance() 
                  << ", Bob: $" << bob.getBalance() << "\n";
        
        // Test 7: Access accounts through Bank operator[]
        std::cout << "\nTEST 7: Access Accounts via Bank Operator[]\n";
        printSeparator();
        
        BankAccount& alice_ref = bank[alice.getCardNumer()];
        std::cout << "Retrieved Alice's account. Balance: $" << alice_ref.getBalance() << "\n";
        
        // Test 8: Exception handling - Negative amount deposit
        std::cout << "\nTEST 8: Exception Handling - Negative Deposit\n";
        printSeparator();
        
        try {
            alice.deposit(-100.0);
        } catch (Negative_Amount& e) {
            std::cout << "Caught exception: " << e.what() << "\n";
        }
        
        // Test 9: Exception handling - Negative amount withdrawal
        std::cout << "\nTEST 9: Exception Handling - Negative Withdrawal\n";
        printSeparator();
        
        try {
            bob.withdraw(-50.0);
        } catch (Negative_Amount& e) {
            std::cout << "Caught exception: " << e.what() << "\n";
        }
        
        // Test 10: Exception handling - Insufficient funds (Checking)
        std::cout << "\nTEST 10: Exception Handling - Insufficient Funds (Checking)\n";
        printSeparator();
        
        try {
            diana.withdraw(10000.0);
        } catch (InsufficientFunds& e) {
            std::cout << "Caught exception: " << e.what() << "\n";
        }
        
        // Test 11: Exception handling - Insufficient funds (Savings with overdraft exceeded)
        std::cout << "\nTEST 11: Exception Handling - Overdraft Exceeded\n";
        printSeparator();
        
        try {
            charlie.withdraw(1000.0);  // Already used some overdraft
        } catch (InsufficientFunds& e) {
            std::cout << "Caught exception: " << e.what() << "\n";
        }
        
        // Test 12: Exception handling - Account not found
        std::cout << "\nTEST 12: Exception Handling - Account Not Found\n";
        printSeparator();
        
        try {
            BankAccount& nonexistent = bank["9999999999999999"];
        } catch (AccountNotFound& e) {
            std::cout << "Caught exception: " << e.what() << "\n";
        }
        
        // Test 13: Transfer with negative amount
        std::cout << "\nTEST 13: Exception Handling - Negative Transfer\n";
        printSeparator();
        
        bank.transfer(alice, bob, -100.0);  // Exception caught internally
        std::cout << "Attempted negative transfer (handled internally)\n";
        
        // Test 14: Transfer to same account
        std::cout << "\nTEST 14: Transfer to Same Account (Should Do Nothing)\n";
        printSeparator();
        
        double balance_before = alice.getBalance();
        bank.transfer(alice, alice, 100.0);
        std::cout << "Transfer to same account - Balance unchanged: $" << alice.getBalance() << "\n";
        
        // Test 15: Multiple operations sequence
        std::cout << "\nTEST 15: Complex Operation Sequence\n";
        printSeparator();
        
        std::cout << "Starting balances:\n";
        std::cout << "  Alice: $" << alice.getBalance() << "\n";
        std::cout << "  Bob: $" << bob.getBalance() << "\n";
        
        alice.deposit(1000.0);
        alice.withdraw(200.0);
        bank.transfer(alice, bob, 500.0);
        bob.withdraw(100.0);
        
        std::cout << "\nAfter deposit->withdraw->transfer->withdraw sequence:\n";
        std::cout << "  Alice: $" << alice.getBalance() << "\n";
        std::cout << "  Bob: $" << bob.getBalance() << "\n";
        
        // Test 16: Final account states
        std::cout << "\nTEST 16: Final Account States\n";
        printSeparator();
        
        std::cout << "Alice (" << alice.getCardNumer() << ") - Balance: $" << alice.getBalance() << "\n";
        std::cout << "Bob (" << bob.getCardNumer() << ") - Balance: $" << bob.getBalance() << "\n";
        std::cout << "Charlie (" << charlie.getCardNumer() << ") - Balance: $" << charlie.getBalance() << "\n";
        std::cout << "Diana (" << diana.getCardNumer() << ") - Balance: $" << diana.getBalance() << "\n";
        
        std::cout << "\nALL TESTS COMPLETED SUCCESSFULLY!\n";
        printSeparator();
        
    } catch (std::exception& e) {
        std::cerr << "Unexpected error: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}