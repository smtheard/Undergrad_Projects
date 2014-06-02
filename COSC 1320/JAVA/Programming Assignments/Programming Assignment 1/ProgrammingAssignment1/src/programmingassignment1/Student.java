//Student Class Programming Assignment 1
//Holds values for the student and processes the students data
//Stefan Theard
//6/10/2013
package programmingassignment1;

import java.text.DecimalFormat;

public class Student
{
    private double gpa, amtDue;
    private String name, isTuitionPaid;
    private int id;
    private int numCourses = 20;//initialized to some value above anything that is possible for array memory allocation
    private int totalHours = 0;
    public Course[] courses = new Course[numCourses];
    private InputData inputData = new InputData();

    public void printReport()
    {
        DecimalFormat d = new DecimalFormat("0.00");
        String  courseString;
        calcGPA();
        if(isTuitionPaid.equals("N") || isTuitionPaid.equals("n"))
        {
            System.out.println("\nStudents grades are being held for non-payment of tuition.");
            amtDue = totalHours*inputData.getRate();
            System.out.println("The current amount due is $" + d.format(amtDue));
            return;
        }
        System.out.println("\nStudent Name: " + name +"\n"
                + "Student ID: " + id + "\n"
                + "Number of courses enrolled: " + numCourses + "\n"
                + "Course No. Course Name Credits Grade");
        sortCourses();
        sortCourses();
        for(int i = 0; i<numCourses; i++)
            System.out.printf("%23s%n", courses[i]);
        System.out.println("\nTotal number of credit hours: " + totalHours);
        System.out.println("Midsemester GPA: " + d.format(gpa));

    }
    private void sortCourses()
    {
        Course temp;
        String word1, word2;
        for(int i = 0; i<numCourses-1; i++)
        {
            word1 = courses[i].getName();
            word2 = courses[i+1].getName();
            if(word1.compareToIgnoreCase(word2)>0)
            {
            temp = new Course(courses[i].getName(), courses[i].getNumber(),
                                courses[i].getHours(), courses[i].getGrade());
            courses[i] = new Course(courses[i+1].getName(), courses[i+1].getNumber(),
                                courses[i+1].getHours(), courses[i+1].getGrade());
            courses[i+1] = new Course(temp.getName(), temp.getNumber(),
                                temp.getHours(), temp.getGrade());
            }
        }
    }

    private void calcGPA()  //multiply creditHours*grade divide grade points by credit hours
    {
        double a = 4.00, b = 3.00, c = 2.00, d = 1.00, f = 0.00, gradeSum = 0;
        if(gpa>0)
            return;
        for(int i = 0; i<numCourses; i++)
        {
            if(courses[i].getGrade().equals("A") || courses[i].getGrade().equals("a"))
            {
                totalHours = courses[i].getHours() + totalHours;
                gradeSum = courses[i].getHours()*a + gradeSum;
            }
            else if(courses[i].getGrade().equals("B") || courses[i].getGrade().equals("b"))
            {
                totalHours = courses[i].getHours() + totalHours;
                gradeSum = courses[i].getHours()*b + gradeSum;
            }
            else if(courses[i].getGrade().equals("C") || courses[i].getGrade().equals("c"))
            {
                totalHours = courses[i].getHours() + totalHours;
                gradeSum = courses[i].getHours()*c + gradeSum;
            }
            else if(courses[i].getGrade().equals("D") || courses[i].getGrade().equals("d"))
            {
                totalHours = courses[i].getHours() + totalHours;
                gradeSum = courses[i].getHours()*d + gradeSum;
            }
            else
            {
                totalHours = courses[i].getHours() + totalHours;
                gradeSum = courses[i].getHours()*f + gradeSum;
            }
        }
        gpa = gradeSum/totalHours;
    }

    //constructors
    public Student()
    {
        gpa = 0.00;
        name = "";
        isTuitionPaid = "N";
        id = 00000;
        numCourses = 0;
    }
    public Student(String newName, int newId, String newTuition, int newCourses)
    {
        name = newName;
        isTuitionPaid = newTuition;
        id = newId;
        numCourses = newCourses;
    }

    // accessors
    public int getNumCourses()
    {
        return numCourses;
    }
    public int getId()
    {
        return id;
    }
}