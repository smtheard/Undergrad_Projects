//PizzaShopController Class Programming Assignment 2
//generic controller class, redirects to model
//Stefan Theard
//6/17/2013
package ProgrammingAssignment2;

public class PizzaShopController
{

    public OrderModel order = new OrderModel();

    public void UCchooseTopping(String topping)
    {
        order.setTopping(topping);
    }

    public void UCchooseSize(String size)
    {
        order.selectSize(size);
    }

    public void UCchooseCrust(String crust)
    {
        order.selectCrust(crust);
    }

    public void UCprocessOrder()
    {
        order.processOrder();
    }
}