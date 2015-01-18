//Topping Class Programming Assignment 2
//holds name of a topping
//Stefan Theard
//6/17/2013
package ProgrammingAssignment2;

public class Topping
{
    private String name;
    public Topping(String name)
    {
        this.name = name;
    }
    
    public String toString()
    {
        return name;
    }

    public boolean equals(Object other)
    {
        return name.equals(other.toString());
    }
}