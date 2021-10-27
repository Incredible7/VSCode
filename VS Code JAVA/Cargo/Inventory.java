package Cargo;

public class Inventory {
    String Item;
    int Quantity;
    String Supplier;
    String Description;

    Inventory(String _Item, int _Quantity, String _Supplier, String _Description) {
        Item = _Item;
        Quantity = _Quantity;
        Supplier = _Supplier;
        Description = _Description;
    }
}
