
package homework26;

public class TestAnimal
{

    public static void main(String[] args)
    {
        Animal bear1 = new Animal("Bear", 400000, 2.1);
        Animal bear2 = new Animal("Bear", 400000, 2.1);
        Animal sealion = new Animal();
        sealion.setSpecies("Steller Sea Lion");
        sealion.setPop(50000);
        sealion.setRate(-1);

        System.out.println("For bear 1:");
        System.out.println("Species: " + bear1.getSpecies());
        System.out.println("Population: " + bear1.getPop());
        System.out.println("Growth Rate: " + bear1.getRate());

        System.out.println("For sea lion:");
        System.out.println(sealion.toString());
        System.out.println("sealion = bear1? " + sealion.equals(bear1));
        System.out.println("bear 1 = bear 2? " + bear1.equals(bear2));
        System.out.println("Sealion endangered? " + sealion.endangered());
        System.out.println("Bear endangered? " + bear1.endangered());
    }

}
