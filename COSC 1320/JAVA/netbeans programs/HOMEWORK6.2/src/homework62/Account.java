
package homework62;

public class Account
{
    private double balance;

    public Account()
    {
        balance = 0;
    }

    public Account(double initialDeposit)
    {
        balance = initialDeposit;
    }

    public double getBalance()
    {
        return balance;
    } //returns new balance or -1 if error

    public double deposit(double amount) throws InvalidAmtException
    {
        if(amount>0)
            balance = balance+amount;
        else
            throw new InvalidAmtException("Invalid deposit amount!!");
        return balance;
    } //throws an exception if error occurs

    public double withdraw(double amount) throws InvalidAmtException
    {
        if((amount>balance) || (amount<0))
            throw new InvalidAmtException("Invalid withdrawal amount!!");
        else balance = balance - amount;
        return balance;
    }
}
