//PizzaProgram Class Programming Assignment 2
//contains main which initiates the gui via the view
//Stefan Theard
//6/17/2013
package ProgrammingAssignment2;

public class PizzaProgram
{
    public static void main(String[] args)
    {
        GuiView view = new GuiView();
        PizzaShopController controller = new PizzaShopController();
        ToppingListener toppingListener = new ToppingListener(controller);
        SizeListener sizeListener = new SizeListener(controller);
        TypeListener typeListener = new TypeListener(controller);
        ProcessListener processListener = new ProcessListener(controller, view);
        view.initGui(toppingListener, sizeListener, typeListener,
                                                               processListener);
    }
}
