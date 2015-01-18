//Course Class Programming Assignment 1
//Holds values for the course and processes the data that each course holds
//Stefan Theard
//6/10/2013
package programmingassignment1;

public class Course
{
    private String number, name, grade;
    private int creditHours;

    public Course(String newName, String newNumber,  int newCreditHours, String newGrade)
    {
        number = newNumber;
        name = newName;
        creditHours = newCreditHours;
        grade = newGrade;
    }
    public String getGrade()
    {
        return grade;
    }
    public int getHours()
    {
        return creditHours;
    }
    public String getName()
    {
        return name;
    }
    public String getNumber()
    {
        return number;
    }

    public String toString()
    {
        return (number + "     " + name + "    " + creditHours + "    " + grade);
    }
}