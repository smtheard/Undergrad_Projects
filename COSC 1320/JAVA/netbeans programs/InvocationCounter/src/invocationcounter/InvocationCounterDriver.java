
package invocationcounter;

/**
 *
 * @author Administrator
 */

public class InvocationCounterDriver
{

    public static void main(String[] args)
    {
        int i;
        InvocationCounter object1 = new InvocationCounter();
        for (i = 1; i <= 5; i++)
        {
            object1.demoMethod();
        }
        object1.outPutCount();

        InvocationCounter object2 = new InvocationCounter();
        for (i = 1; i <= 5; i++)
        {
            object2.demoMethod();
            object2.outPutCount();
        }

        System.out.println("Total number of invocations = " +
                InvocationCounter.numberSoFar());
    }
}