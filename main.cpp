#include "bank_system.hpp"

int main()
{
    try
    {
        Bank bank;
        
        bank.CreateSaving(5000, "Alice", 1000);
        bank.CreateChecking(2000, "Bob", 5);

        // сохраним ссылки
        BankAccount& acc1 = bank["1110345618584847"]; // Alice
        // BankAccount& acc2 = bank["1110345618584848"]; // Bob

        // std::cout << "Initial accounts:\n";
        // acc1.display();
        // acc2.display();

        // std::cout << "--- Testing deposit ---\n";
        // acc1.deposit(500);
        // acc1.display();

        // std::cout << "--- Testing withdraw ---\n";
        // acc2.withdraw(300);
        // acc2.display();

        // std::cout << "--- Testing transfer Alice -> Bob (1000) ---\n";
        // bank.transfer(acc1, acc2, 1000);
        // acc1.display();
        // acc2.display();

        // std::cout << "--- Testing insufficient funds ---\n";
        // acc2.withdraw(100000);  // error

    }
    catch (const BankException& ex)
    {
        std::cout << "Bank exception: " << ex.what() << "\n";
    }
    catch (const std::exception& ex)
    {
        std::cout << "STD EX: " << ex.what() << "\n";
    }

    return 0;
}
