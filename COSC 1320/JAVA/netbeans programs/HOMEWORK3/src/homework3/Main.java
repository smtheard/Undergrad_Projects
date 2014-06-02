
package homework3;

public class Main
{

    public static void main(String[] args)
    {
        int totalSeconds = 50391;
        int hours, minutes, seconds;
        hours = totalSeconds/3600;
        minutes = (totalSeconds%3600) /60;
        seconds = (totalSeconds%3600) % 60;
        System.out.println(totalSeconds + " seconds is equivalent to:\n"
                + hours + " hours " + minutes + " minutes " + seconds + " seconds.");
    }

}
