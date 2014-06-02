
package homework52;

public class MarshmallowAlien extends Alien
{
    public static final int MARSHMALLOW_DAMAGE = 1;

    //constructors
    public MarshmallowAlien()
    {
        super();
    }

    public MarshmallowAlien(int health, String name)
    {
        super(health, name);
    }

    // returns dmg this alien inflicts
    public int getDamage()
    {
        return MARSHMALLOW_DAMAGE;
    } 
}