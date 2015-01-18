//Pizza Class Programming Assignment 2
//another model, holds the state of toppings
//Stefan Theard
//6/17/2013
package ProgrammingAssignment2;
import java.util.ArrayList;
public class Pizza
{
    private final String[] availableToppingNames = {
                                                    "Tomatoes",
                                                    "Green Pepper",
                                                    "Black Olives",
                                                    "Mushrooms",
                                                    "Extra Cheese",
                                                    "Sausage",
                                                    "Pepperoni"
                                                   };
    private String size = "Small";
    private String type = "Thin Crust";
    public Topping[] availableToppings;
    public ArrayList<Topping> selectedToppings;
    
    public Pizza()
    {
        availableToppings = new Topping[availableToppingNames.length];
        for(int i = 0; i<availableToppingNames.length; i++)
        {
            availableToppings[i] = new Topping(availableToppingNames[i]);
        }
        selectedToppings = new ArrayList<Topping>();
    }

    public String getSize()
    {
        return size;
    }

    public String getType()
    {
        return type;
    }

    public void setSize(String newSize)
    {
        size = newSize;
    }

    public void setType(String newType)
    {
        type = newType;
    }

    public void addTopping(String toppingName)
    {
        selectedToppings.add(new Topping(toppingName));
    }

    public void removeTopping(String toppingName)
    {
        selectedToppings.remove(new Topping(toppingName));
    }

    public boolean hasTopping(String toppingName)
    {
       return selectedToppings.contains(new Topping(toppingName));
    }
}