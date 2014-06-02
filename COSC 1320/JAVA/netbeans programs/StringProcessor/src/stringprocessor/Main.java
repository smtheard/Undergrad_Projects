
package stringprocessor;

import java.util.Scanner;

public class Main
{
    public static void main(String[] args)
    {
        System.out.println("Enter a one line sentence:");
        Scanner keyboard = new Scanner(System.in);
        String sentence = keyboard.nextLine( );

        sentence = sentence.toLowerCase( );
        char firstCharacter = sentence.charAt(0);
        sentence = Character.toUpperCase(firstCharacter)
                         + sentence.substring(1);

        System.out.println("The revised sentence is:");
        System.out.println(sentence);
    }
}