//SizeListener Class Programming Assignment 2
//generic listener
//Stefan Theard
//6/17/2013
package ProgrammingAssignment2;

import java.awt.event.ActionListener;
import java.awt.event.ActionEvent;

public class ProcessListener implements ActionListener
{
    private PizzaShopController controller;
    private GuiView view;

    public ProcessListener(PizzaShopController controller, GuiView view)
    {
        this.controller = controller;
        this.view = view;
    }
    public void actionPerformed(ActionEvent e)
    {
        controller.UCprocessOrder();
        view.updateDisplay(controller.order);
    }
}