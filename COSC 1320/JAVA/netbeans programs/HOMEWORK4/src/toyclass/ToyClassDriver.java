
package toyclass;


public class ToyClassDriver
{

public static void main(String[] args)
    {
        ToyClass sampleVariable  = new ToyClass("Josephine Student", 42);
        ToyClass variable1 = new ToyClass("Joe", 42);
        System.out.println(variable1);
        ToyClass variable2;
        variable2 = variable1;
        System.out.println(variable2);
        variable2.set("Josephine", 1);
        System.out.println(variable1);
        System.out.println(variable2);
        ToyClass.changer(variable2);
        System.out.println(variable2);
    }
}
