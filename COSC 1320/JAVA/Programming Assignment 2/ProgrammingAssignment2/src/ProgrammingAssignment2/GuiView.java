//GuiView Class Programming Assignment 2
//view class, contains JFrames checkboxes radiobuttons etc for the GUI
//Stefan Theard
//6/17/2013
package ProgrammingAssignment2;

import java.awt.Color;
import java.awt.GridLayout;
import java.awt.BorderLayout;
import java.awt.FlowLayout;
import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.JLabel;
import javax.swing.JCheckBox;
import javax.swing.BorderFactory;
import javax.swing.JRadioButton;
import javax.swing.JButton;
import javax.swing.JTextArea;
import javax.swing.ButtonGroup;


public class GuiView
{
    
    public static final int WIDTH = 400;
    public static final int HEIGHT = 350;
    private JFrame menu;
    ToppingListener toppings;
    SizeListener size;
    TypeListener type;
    ProcessListener process;
    JTextArea displayTextArea;

    public void initGui(ToppingListener toppings, SizeListener size,
                            TypeListener type, ProcessListener process)
    {
        //TODO: move to a constructor
        this.toppings = toppings;
        this.size = size;
        this.type = type;
        this.process = process;

        initFrame();
        initToppingsPanel();
        
        JLabel sizeLabel = new JLabel("  Pizza Size  ");
        JLabel typeLabel = new JLabel("  Pizza Type  ");
   
        //TODO: refactor radiobutton initalization into methods
        //Size radio buttons begin here
        JPanel sizePanel = new JPanel(new GridLayout(0, 1));
        sizePanel.add(sizeLabel);
        sizePanel.setBorder(BorderFactory.createLineBorder(Color.black));
        JRadioButton smButton = new JRadioButton("Small Pizza $6.50");
        JRadioButton mdButton = new JRadioButton("Medium Pizza $8.50");
        JRadioButton lgButton = new JRadioButton("Large Pizza $10.00");
        //set small selected as default and add buttons to a group
        smButton.setSelected(true);
        ButtonGroup sizeGroup = new ButtonGroup();
        sizeGroup.add(smButton);
        sizeGroup.add(mdButton);
        sizeGroup.add(lgButton);
        //add to panel
        sizePanel.add(smButton);
        sizePanel.add(mdButton);
        sizePanel.add(lgButton);
        //adding listeners
        smButton.addActionListener(size);
        mdButton.addActionListener(size);
        lgButton.addActionListener(size);
        menu.add(sizePanel);

        // Type radio buttons begin here
        JPanel typePanel = new JPanel(new GridLayout(0, 1));
        typePanel.add(typeLabel, BorderLayout.NORTH);
        typePanel.setBorder(BorderFactory.createLineBorder(Color.black));
        JRadioButton thinCrust = new JRadioButton("Thin Crust");
        JRadioButton medCrust = new JRadioButton("Medium Crust");
        JRadioButton panCrust = new JRadioButton("Pan");
        //set thin selected as default and add buttons to group
        thinCrust.setSelected(true);
        ButtonGroup typeGroup = new ButtonGroup();
        typeGroup.add(thinCrust);
        typeGroup.add(medCrust);
        typeGroup.add(panCrust);
        //adding listeners
        thinCrust.addActionListener(type);
        medCrust.addActionListener(type);
        panCrust.addActionListener(type);
        //add to panel
        typePanel.add(thinCrust);
        typePanel.add(medCrust);
        typePanel.add(panCrust);
        menu.add(typePanel);

        //Process Order button begins here
        JButton processOrder = new JButton("Process Order");
        //adding listener
        processOrder.addActionListener(process);
        menu.add(processOrder, BorderLayout.SOUTH);

        initTextPanel();

        menu.setVisible(true);
    }

    private void initFrame()
    {
        menu = new JFrame();
        menu.setSize(WIDTH, HEIGHT);
        menu.setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
        menu.setTitle("Pizza Menu");
        menu.setLayout(new FlowLayout());
    }

    public void updateDisplay(OrderModel order)
    {
        String orderSummary = "";
        orderSummary = orderSummary + "Pizza type: " + order.getType() + "\n";
        orderSummary = orderSummary + "Pizza size: " + order.getSize() + "\n";

        orderSummary = orderSummary + "Toppings: ";
        for(Topping topping : order.pizza.selectedToppings)
            orderSummary = orderSummary + topping + ", ";

        orderSummary = orderSummary + "\nAmount due: $" + order.getCost();
        displayTextArea.setText(orderSummary);
    }

    private void initToppingsPanel()
    {
        String[] toppingNames = {"Tomatoes", "Green Pepper", "Black Olives",
                           "Mushrooms", "Extra Cheese", "Sausage", "Pepperoni"};
        JLabel toppingLabel = new JLabel("  Toppings $1.50 each  ");
        JPanel toppingPanel = new JPanel(new GridLayout(0, 1));
        toppingPanel.add(toppingLabel, BorderLayout.NORTH);
        toppingPanel.setBorder(BorderFactory.createLineBorder(Color.black));

        for(String topping : toppingNames)
        {
            JCheckBox toppingCheckBox = new JCheckBox(topping);
            toppingCheckBox.addActionListener(toppings);
            toppingPanel.add(toppingCheckBox);
        }
            
        menu.add(toppingPanel);
    }

    private void initTextPanel()
    {
        JLabel textLabel = new JLabel("  Your Order:  ");
        JPanel textPanel = new JPanel();
        displayTextArea = new JTextArea(4, 25);
        displayTextArea.setEditable(false);
        textPanel.add(textLabel, BorderLayout.NORTH);
        textPanel.add(displayTextArea);
        textPanel.setBorder(BorderFactory.createLineBorder(Color.black));

        menu.add(textPanel);
    }
}
