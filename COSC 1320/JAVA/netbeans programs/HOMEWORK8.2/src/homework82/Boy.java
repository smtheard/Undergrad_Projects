
package homework82;

public class Boy
{
    private String name;
    private int count;
    private int position;

    public Boy()
    {
        name = "";
        count = 0;
        position = -1;
    }

    public void setName(String name)
    {
        this.name = name;
    }

    public void setCount(int count)
    {
        this.count = count;
    }

    public void setPosition(int position)
    {
        this.position = position;
    }

    public String getName()
    {
        return name;
    }

    public String toString()
    {
        position = position+1;
        return(name + " is ranked " + position + " in popularity among boys with " + count + " namings");
    }
}
