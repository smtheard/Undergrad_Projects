//InputData Class Programming Assignment 1
//uses scanner to evaluate incoming .txt file copypasted into program
//Stefan Theard
//6/10/2013
package programmingassignment1;

import java.util.Scanner;

public class InputData
{
    private int noOfStudents;
    private static int tuitionRate;
    private String studentName,  fname, lname;
    Scanner input = new Scanner(System.in);

    public void analyzeData(Student[] student)
    {

        System.out.println("Enter raw input file by copy-pasting to create database:");
        noOfStudents = input.nextInt();
        tuitionRate = input.nextInt();
        for(int i = 0; i<noOfStudents; i++)
        {
            fname = input.next();
            lname = input.next();
            studentName = fname + " " + lname;
            student[i] = new Student(studentName, input.nextInt(), input.next(), input.nextInt());
            for(int j = 0; j<student[i].getNumCourses(); j++)
            {
                student[i].courses[j] = new Course(input.next(), input.next(), input.nextInt(), input.next());
            }
        }
    }
    public void searchId(Student[] student)
    {
        Integer userin, studentId;
        System.out.print("Enter ID of student you want to parse database for (enter -1 to exit program): ");
        userin = input.nextInt();
        if(userin.equals(-1))
                    return;
        do{
        for(int i = 0; i<noOfStudents; i++)
        {
            studentId = student[i].getId();
            if(userin.equals(studentId))
            {
                student[i].printReport();
                System.out.print("\nEnter ID of student you want to parse database for (enter -1 to exit program): ");
                userin = input.nextInt();
                if(userin.equals(-1))
                    return;
                i = -1;
            }
        }
        System.out.print("ID not found, please try again(or enter -1 to exit): ");
        userin = input.nextInt();
        }while(userin != -1);
    }
    public double getRate()
    {
        return tuitionRate;
    }
}