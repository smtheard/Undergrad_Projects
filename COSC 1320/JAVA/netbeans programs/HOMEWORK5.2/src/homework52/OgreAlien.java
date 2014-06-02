
package homework52;

public class OgreAlien extends Alien
{
    public static final int OGRE_DAMAGE = 6;

    //constructors
    public OgreAlien()
    {
        super();
    }

    public OgreAlien(int health, String name)
    {
        super(health, name);
    }

    public int getDamage()
    {
        return OGRE_DAMAGE;
    }
}
