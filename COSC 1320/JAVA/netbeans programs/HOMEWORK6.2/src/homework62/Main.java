
package homework62;
import java.util.Scanner;
public class Main
{

    public static void main(String[] args) 
    {
        Scanner input = new Scanner(System.in);
        double userin = 0;
        Account account = new Account();
        String tryagain = "N";
        do{
        try
        {
            System.out.println("Make a deposit");
            userin = input.nextDouble();
            account.deposit(userin);
            System.out.println("Account balance is: " + account.getBalance());
        }
        catch(InvalidAmtException e)
        {
            System.out.println("Entered catch within main method");
            System.out.println("Error message is :" + e.getMessage());
        }
        try
        {
            System.out.println("Make a withdrawal");
            userin = input.nextDouble();
            account.withdraw(userin);
            System.out.println("Account balance is: " + account.getBalance());
        }
        catch(InvalidAmtException e)
        {
            System.out.println("Entered second catch within main method");
            System.out.println("Error message is :" + e.getMessage());
        }
        finally
        {
            System.out.println("Restart program? (Y/N)");
            tryagain = input.next();
        }
        }while(tryagain.equals("Y") || tryagain.equals("y"));
    }

}
