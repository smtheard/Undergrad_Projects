//Main Class Programming Assignment 1
//executes 2 use cases for the controller part of the program
//Stefan Theard
//6/10/2013
package programmingassignment1;

public class Main
{
    static final int MAX_STUDENTS = 600;
    public static void main(String[] args) //  GradeReportApplication
    {
        InputData inputData = new InputData();
        Student[] student = new Student[MAX_STUDENTS];
        inputData.analyzeData(student);
        inputData.searchId(student);
    }

}