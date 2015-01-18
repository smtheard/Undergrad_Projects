//OrderModel Class Programming Assignment 2
//main processing model does all of the heavy lifting
//Stefan Theard
//6/17/2013
package ProgrammingAssignment2;

public class OrderModel
{
    private double totalCost    = 0.00;
    private double toppingPrice = 1.50;
    private double smPrice      = 6.50;
    private double medPrice     = 8.50;
    private double lgPrice      = 10.00;
    public Pizza pizza         = new Pizza();

    public void setTopping(String topping)
    {
        if(pizza.hasTopping(topping))
        {
            pizza.removeTopping(topping);
        }else{
            pizza.addTopping(topping);
        }
    }

    public void selectSize(String size)
    {
        if(size.equals("Small Pizza $6.50"))
            pizza.setSize("Small");
        else if(size.equals("Medium Pizza $8.50"))
            pizza.setSize("Medium");
        else if(size.equals("Large Pizza $10.00"))
            pizza.setSize("Large");
    }

    public void selectCrust(String crust)
    {
        pizza.setType(crust);
    }

    public void processOrder()
    {
        totalCost = pizza.selectedToppings.size() * toppingPrice;

        if(pizza.getSize().equals("Large"))
            totalCost = totalCost + lgPrice;
        else if(pizza.getSize().equals("Medium"))
            totalCost = totalCost + medPrice;
        else if(pizza.getSize().equals("Small"))
            totalCost = totalCost + smPrice;
    }

    public double getCost()
    {
        return totalCost;
    }

    public String getType()
    {
        return pizza.getType();
    }

    public String getSize()
    {
        return pizza.getSize();
    }
}
