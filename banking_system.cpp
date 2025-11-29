#include "bank_system.hpp"

BankAccount::BankAccount(double balance, std::string name) : _balance{balance}, _name{name}
{
    unsigned long long rem = initial_card_number++;
    for (short i = 0; i < 4; i++) 
    {
        _card_number += std::to_string(rem % 10000);
        rem /= 10000;
    }
}

// Saving account
void SavingsAccount::display() const noexcept 
{
    std::cout << "Card number: " << _card_number << std::endl
              << "Name: "        << _name        << std::endl
              << "Balance: "     << _balance     << std::endl
              << "Overdraft: "   << _overdraft   << std::endl;
}

void SavingsAccount::withdraw(int amount)
{
    if (amount < 0) throw Negative_Amount("U cant withdraw negative amount"); 
    else if (_balance > amount) { _balance -= amount; return; }
    else if (_balance < amount && amount-_balance < _overdraft) { _balance -= amount; _overdraft -= amount; }
    else throw InsufficientFunds("U dont have enough funds my bro");
}

void SavingsAccount::deposit(int amount)
{
    if (amount < 0) throw Negative_Amount("U cant withdraw negative amount"); 
    _balance += amount;
}

