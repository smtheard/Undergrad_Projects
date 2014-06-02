package homework26;

public class Animal
{
    private String species;
    private int population;
    private double growthRate;

    // default constructor
    public Animal()
    {
        species = "";
        population = 0;
        growthRate = 0;
    }
    public Animal(String newSpecies, int newPop, double newRate)
    {
        species = newSpecies;
        population = newPop;
        growthRate = newRate;
    }

    // accessors
    public String getSpecies()
    {
        return species;
    }
    public int getPop()
    {
        return population;
    }
    public double getRate()
    {
        return growthRate;
    }

    // mutators
    public void setSpecies(String newSpecies)
    {
        species = newSpecies;
    }
    public void setPop(int newPop)
    {
        population = newPop;
    }
    public void setRate(double newRate)
    {
        growthRate = newRate;
    }
    public String toString()
    {
        return "Species: " + species + ", Population: " + population + ", Growth Rate: "
                + growthRate;
    }
    public boolean equals(Animal other)
    {
        return (species.equals(other.species));
    }
    public boolean endangered()
    {
        if(growthRate < 0)
            return true;
        else
            return false;
    }
}
