#include <iostream>
#include <exception>
#include <string>
#include <vector>

class BankException : public std::runtime_error
{
private:
    std::string _msg;
public:

    explicit BankException(const std::string &msg) : std::runtime_error(msg), _msg{msg} {}
    virtual const char * what() const noexcept override { return _msg.c_str(); }
};
class Negative_Amount : public BankException { public: Negative_Amount(std::string msg) : BankException{msg} {} };
class InsufficientFunds : public BankException { public: InsufficientFunds(std::string msg) : BankException{msg} {} };
class AccountNotFound : public BankException { public: AccountNotFound(std::string msg) : BankException{msg} {} };


inline static unsigned long long initial_card_number = 1110345618584847;

class BankAccount // Abstract class
{
protected:
    std::string _card_number;
    double _balance;
    std::string _name;
public:
    BankAccount(double balance, std::string name);
    virtual ~BankAccount();
    virtual void display() const noexcept = 0;
    virtual void withdraw(int) = 0;
    virtual void deposit(int) = 0;
    double getBalance() const noexcept { return _balance; }
    std::string getName() const noexcept { return _name; }
};

class SavingsAccount : public BankAccount
{
private:
    double _overdraft;
public:
    SavingsAccount(double balance, std::string name, double overdraft) : BankAccount{balance, name}, _overdraft{overdraft} {}
    virtual void display() const noexcept override;
    virtual void withdraw(int amount) override;
    virtual void deposit(int amount) override;
};

class CheckingAccount : public BankAccount
{
private:
    double _rate;
public:
    CheckingAccount(double balance, std::string name, double rate) : BankAccount{balance, name}, _rate{rate} {} 
    void update();
    virtual void display() const noexcept override;
    virtual void withdraw(int amount) override;
    virtual void deposit(int amount) override;
};

class Bank
{
private:
    std::vector<BankAccount*> _bank_accounts;
    void CreateSaving();
    void CreateChecking();
public:
    void transfer(const BankAccount& lhs, const BankAccount& rhs);
    BankAccount& operator[](std::string card_number);
};