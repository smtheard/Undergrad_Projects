
package homework52;

public class SnakeAlien extends Alien
{
    public static final int SNAKE_DAMAGE = 10;

    //constructors

    public SnakeAlien()
    {
        super();
    }

    public SnakeAlien(int health, String name)
    {
        super(health,name);
    }

    //returns amt of dmg this alien inflicts
    public int getDamage()
    {
        return SNAKE_DAMAGE;
    }
}
