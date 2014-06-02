//SizeListener Class Programming Assignment 2
//generic listener
//Stefan Theard
//6/17/2013
package ProgrammingAssignment2;

import java.awt.event.ActionListener;
import java.awt.event.ActionEvent;

public class SizeListener implements ActionListener
{
    private PizzaShopController controller;

    public SizeListener(PizzaShopController controller)
    {
        this.controller = controller;
    }
    public void actionPerformed(ActionEvent e)
    {
        controller.UCchooseSize(e.getActionCommand());
    }
}
