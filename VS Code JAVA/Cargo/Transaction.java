package Cargo;

public class Transaction implements Comparable<Object> {
    String type;
    String Item;
    int num;
    String customer;

    Transaction(String _type, String _Item, int _num, String _customer) {
        type = _type;
        Item = _Item;
        num = _num;
        customer = _customer;
    }

    @Override
    public int compareTo(Object o) {
        Transaction t = (Transaction) o;
        return num - t.num;
    }
}
