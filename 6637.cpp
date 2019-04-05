class Account
{
  public:
    int id;
    double balance;
    double annualInterestRate;
    Account() : id(0), balance(0), annualInterestRate(0)
    {
    }
    int getId() { return id; }
    void setId(int value) { id = value; }
    double getBalance() { return balance; }
    void setBalance(double value) { balance = value; }
    double getAnnualInterestRate() { return annualInterestRate; }
    void setAnnualInterestRate(double value) { annualInterestRate = value; }
    double getMonthlyInterestRate()
    {
        return annualInterestRate / 12;
    }
    void withDraw(double amount)
    {
        annualInterestRate -= amount;
    }
    void deposit(double amount)
    {
        annualInterestRate += amount;
    }
};

#include <iostream>
#include <iomanip>
using namespace std;
void print(Account &account)
{
    cout << "Account ID " << account.getId()
         << fixed << setprecision(2)
         << ", Balance " << account.getBalance() << ", Monthly Interest Rate " << account.getMonthlyInterestRate() << endl;
}
int main()
{

    Account a, b;
    print(a);

    b.setId(1122);
    b.setBalance(20000.0);
    b.setAnnualInterestRate(4.5);
    print(b);

    return 0;
}
