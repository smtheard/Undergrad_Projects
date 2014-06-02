package homework82;

import java.util.Scanner;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.FileNotFoundException;

public class NamesProcess
{
    public static final int numChildren = 1000;
    private Boy[] boys   = new Boy[numChildren];
    private Girl[] girls = new Girl[numChildren];

    public void loadBoyFile(String fileName)
    {
        for(int i = 0; i<numChildren; i++)
        {
            boys[i] = new Boy();
        }
        Scanner inputStream = null;
        try
        {
            inputStream = new Scanner(new FileInputStream(fileName));

            for(int i = 0; i<numChildren; i++)
            {
                boys[i].setName(inputStream.next());
                boys[i].setCount(inputStream.nextInt());
                boys[i].setPosition(i);
            }
            
            inputStream.close();
        }
        catch(FileNotFoundException e)
        {
            System.out.println("File not found");
            System.exit(0);
        }
        catch(IOException e)
        {
            System.out.print(e);
            System.exit(0);
        }
    }

    public void loadGirlFile(String fileName)
    {
        for(int i = 0; i<numChildren; i++)
        {
            girls[i] = new Girl();
        }
        Scanner inputStream = null;
        try
        {
            inputStream = new Scanner(new FileInputStream(fileName));
            for(int i = 0; i<numChildren; i++)
            {
                girls[i].setName(inputStream.next());
                girls[i].setCount(inputStream.nextInt());
                girls[i].setPosition(i);
            }
            inputStream.close();
        }
        catch(FileNotFoundException e)
        {
            System.out.println("File not found");
            System.exit(0);
        }
        catch(IOException e)
        {
            System.out.print(e);
            System.exit(0);
        }
    }

    public void searchFiles(String name)
    {
        String foundBoy = "";
        String foundGirl = "";
        if(name.equals("exit"))
            return;
        for(int i = 0; i<numChildren; i++)
        {
            if(boys[i].getName().equals(name)){
                System.out.println(boys[i]);
                foundBoy = boys[i].getName();
            }
            if(girls[i].getName().equals(name)){
                System.out.println(girls[i]);
                foundGirl = girls[i].getName();
            }
            
        }
        if(!foundBoy.equals(name))
            System.out.println(name + " is not ranked among the top 1000 boy names.");
        if(!foundGirl.equals(name))
            System.out.println(name + " is not ranked among the top 1000 girl names.");
    }
    

}
