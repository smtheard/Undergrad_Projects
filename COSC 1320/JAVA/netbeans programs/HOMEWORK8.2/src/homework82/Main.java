package homework82;

import java.util.Scanner;

public class Main
{

    public static void main(String[] args)
    {
        NamesProcess nameProcessor = new NamesProcess();
        Scanner userin = new Scanner(System.in);
        System.out.println("Input boy file name(default is boynames.txt)");
        nameProcessor.loadBoyFile(userin.next());
        System.out.println("Input girl file name(default is girlnames.txt)");
        nameProcessor.loadGirlFile(userin.next());

        String userinput = "";
        while(!userinput.equals("exit"))
        {
            System.out.print("Enter a name to search for(enter 'exit' to exit program): ");
            userinput = userin.next();
            nameProcessor.searchFiles(userinput);
        }
        
    }

}
