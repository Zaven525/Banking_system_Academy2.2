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

void SavingsAccount::withdraw(double amount)
{
    if (amount < 0) throw Negative_Amount("Ur savings account cant withdraw negative amount"); 
    else if (_balance > amount) { _balance -= amount; return; }
    else if (_balance < amount && amount-_balance < _overdraft) { _balance -= amount; _overdraft -= amount; }
    else throw InsufficientFunds("U dont have enough funds in ur savings account my bro");
}

void SavingsAccount::deposit(double amount)
{
    if (amount < 0) throw Negative_Amount("U cant withdraw negative amount from your savings account"); 
    _balance += amount;
}


// Checking account

void CheckingAccount::display() const noexcept 
{
    std::cout << "Card number: " << _card_number << std::endl
              << "Name: "        << _name        << std::endl
              << "Balance: "     << _balance     << std::endl
              << "Rate: "   << _rate  << std::endl;
}

void CheckingAccount::withdraw(double amount)
{
    if (amount < 0) throw Negative_Amount("Ur checking account cant withdraw negative amount"); 
    else if (_balance > amount) { _balance -= amount; return; }
    else throw InsufficientFunds("U dont have enough funds in ur checking account my bro");
}

void CheckingAccount::deposit(double amount)
{
    if (amount < 0) throw Negative_Amount("U cant withdraw negative amount from your checkings account"); 
    _balance += amount;
}


// Bank


BankAccount& Bank::operator[](std::string card_number)
{
    for (const auto& elem : _bank_accounts)
    {
        if (elem->getCardNumer() == card_number) return *elem;
    }
    throw AccountNotFound("There is no account with card number " + card_number + "in our system");
}

void Bank::transfer(const BankAccount& lhs, const BankAccount& rhs, double amount)
{
    if (lhs.getCardNumer() == rhs.getCardNumer()) return;
    if (amount < 0) throw Negative_Amount("U cant transfer negative amount");
    
    try {
        BankAccount& from = (*this)[lhs.getCardNumer()];
        BankAccount& to = (*this)[rhs.getCardNumer()];

        from.withdraw(amount);
        to.deposit(amount);
    }
    catch(AccountNotFound& e)
    {
        std::cout << e.what();
    }
    catch(Negative_Amount& e)
    {
        std::cout << e.what();
    }
    
}