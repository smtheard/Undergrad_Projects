
package homework52;

public abstract class Alien
{
    public static final int DEFAULT_DAMAGE = 0;
    private int health; //0 = dead, 100 = full strength
    private String name;

    public Alien()
    {
        health = 100;
        name = "";
    }

    public Alien(int health, String name)
    {
        this.health = health;
        this.name = name;
    }

    // accessor and mutator methods

    public int getHealth()
    {
        return health;
    }

    public void setHealth(int health)
    {
        this.health = health;
    }

    public String getName()
    {
        return name;
    }

    public void setName(String name)
    {
        this.name = name;
    }

    //getdamage returns the amount of damage this alien inflicts
    public abstract int getDamage();
}
