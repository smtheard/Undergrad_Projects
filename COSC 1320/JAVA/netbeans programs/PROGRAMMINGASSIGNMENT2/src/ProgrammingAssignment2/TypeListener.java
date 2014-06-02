//TypeListener Class Programming Assignment 2
//generic listener
//Stefan Theard
//6/17/2013
package ProgrammingAssignment2;

import java.awt.event.ActionListener;
import java.awt.event.ActionEvent;

public class TypeListener implements ActionListener
{
    private PizzaShopController controller;

    public TypeListener(PizzaShopController controller)
    {
        this.controller = controller;
    }
    public void actionPerformed(ActionEvent e)
    {
        controller.UCchooseCrust(e.getActionCommand());
    }
}