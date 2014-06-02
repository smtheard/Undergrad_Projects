package latebinding;


/**
Demonstrates late binding.
 */
public class Main
{

    public static void main(String[] args)
    {
        Sale s = new Sale();
        DiscountSale discount = new DiscountSale();
        s.announcement();
        discount.announcement();
        System.out.println("no surprises so far but wait");

        Sale discount2 = discount;
        System.out.println(" discount2 is a DiscountSale object in a Sale variable.");
        System.out.println(" which definition of announcement() will it use?");
        discount2.announcement();
        System.out.println(" which??");
    }
}
    /*Sale simple = new Sale("floor mat", 10.00);//One item at $10.00.
        DiscountSale discount = new DiscountSale("floor mat", 11.00, 10);
        //One item at $11.00 with a 10% discount.
        System.out.println(simple);
        System.out.println(discount);
        if (discount.lessThan(simple))
            System.out.println("Discounted item is cheaper.");
         else
            System.out.println("Discounted item is not cheaper.");
        Sale regularPrice = new Sale("cup holder", 9.90);//One item at $9.90.
        DiscountSale specialPrice = new DiscountSale("cup holder", 11.00, 10);
        //One item at $11.00 with a 10% discount.
        System.out.println(regularPrice);
        System.out.println(specialPrice);
        if (specialPrice.equalDeals(regularPrice))
            System.out.println("Deals are equal.");
         else
            System.out.println("Deals are not equal.");*/