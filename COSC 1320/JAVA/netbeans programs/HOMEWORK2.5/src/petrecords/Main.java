package petrecords;


public class Main
{
    public static void main(String[] args)
    {
        Pet pet = new Pet();
        pet.set("SPLAT", 13, 15);
        System.out.println(pet);
    }
}
