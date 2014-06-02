  package temperature;

import java.util.Scanner;


  
public class TemperatureDriver 
{

    public static void main(String[] args)
    {
        double degreesF, degreesC;

        Scanner keyboard = new Scanner(System.in);
        System.out.println("Enter degrees Fahrenheit:");
        degreesF = keyboard.nextDouble();

        degreesC = Temperature.toCelsius(degreesF);

        Temperature temperatureObject = new Temperature(degreesC);
        System.out.println("Equivalent Celsius temperature is " + temperatureObject.toString());
    }
}