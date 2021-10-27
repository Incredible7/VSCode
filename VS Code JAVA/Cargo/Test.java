package Cargo;

import java.io.*;
import java.util.Collections;
import java.util.Vector;

public class Test {
    private static BufferedReader reader;
    private static BufferedReader reader2;

    public static void main(String[] args) throws Exception {
        Vector<Inventory> invVector = readInventory("D:/Inventory.txt"); // 读入Inventory并存入Vector中，每个元素为一项库存
        Vector<Transaction> tVector = readTransaction("D:/Transaction.txt");// 读入transaction并存入Vector中，每个元素为一个事件
        Vector<Transaction> oVector = new Vector<Transaction>();
        for (int i = 0; i < tVector.size(); i++) {
            if (tVector.get(i).type.equals("R")) { // 先处理R事件，即入库操作
                for (int j = 0; j < invVector.size(); j++) {
                    if (invVector.get(j).Item.equals(tVector.get(i).Item)) {
                        invVector.get(j).Quantity += tVector.get(i).num;
                        break;
                    }
                }
            } else if (tVector.get(i).type.equals("A")) { // A和R的优先级相同，同为入库操作，都是首先处理
                invVector.add(new Inventory(tVector.get(i).Item, 0, Integer.toString(tVector.get(i).num),
                        tVector.get(i).customer));
            } else if (tVector.get(i).type.equals("O")) { // O为出库操作，应待A和R处理完成后在处理
                oVector.add(tVector.get(i)); // 为了方便为O事件排序，即先处理出货量少的，当遍历查询到O时，存入新Vector，等待滞后处理
            }
        }
        Collections.sort(oVector); // 为O事件排序，即出货量少的订单优先级更高
        for (int i = 0; i < oVector.size(); i++) { // 开始遍历处理O事件
            for (int j = 0; j < invVector.size(); j++) {
                if (invVector.get(j).Item.equals(oVector.get(i).Item)) { // 若库存量>=出货量，则执行O操作
                    if (invVector.get(j).Quantity >= oVector.get(i).num) {
                        invVector.get(j).Quantity -= oVector.get(i).num;
                    } else {
                        FileOutputStream fos = new FileOutputStream("D:/Errors.txt"); // 若库存量<出货量，则说明该O操作违规，读入到d:/Errors.txt中
                        OutputStreamWriter writer = new OutputStreamWriter(fos, "UTF-8");
                        BufferedWriter bwriter = new BufferedWriter(writer);
                        bwriter.write(oVector.get(i).type + "\t" + oVector.get(i).Item + "\t" + oVector.get(i).num
                                + "\t" + oVector.get(i).customer);
                        bwriter.newLine();
                        bwriter.flush();
                        bwriter.close();
                    }
                }
            }
        }
        for (int i = 0; i < tVector.size(); i++) { // 最后处理D操作，即删除某货物
            if (tVector.get(i).type.equals("D")) {
                for (int j = 0; j < invVector.size(); j++) {
                    if (invVector.get(j).Item.equals(tVector.get(i).Item)) {
                        invVector.remove(j);
                    }
                }
            }
        }
        File file = new File("D:/Inventory.txt");
        try { // 把原d:/Inventory.txt清空
            if (!file.exists()) {
                file.createNewFile();
            }
            FileWriter fileWriter = new FileWriter(file);
            fileWriter.write("");
            fileWriter.flush();
            fileWriter.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
        FileOutputStream fos = new FileOutputStream("D:/Inventory.txt");// 把新的库存信息存入到d:/Inventory.txt中
        OutputStreamWriter writer = new OutputStreamWriter(fos, "GBK");
        BufferedWriter bwriter = new BufferedWriter(writer);
        for (int i = 0; i < invVector.size(); i++) {
            bwriter.write(invVector.get(i).Item + "\t" + invVector.get(i).Quantity + "\t" + invVector.get(i).Supplier
                    + "\t" + invVector.get(i).Description);
            bwriter.newLine();
        }
        bwriter.flush();
        bwriter.close();
    }

    private static Vector<Inventory> readInventory(String filename) throws Exception { // 读 Inventory
        Vector<Inventory> invVector = new Vector<Inventory>();
        reader2 = new BufferedReader(new InputStreamReader(new FileInputStream(filename)));
        String line = "";
        while ((line = reader2.readLine()) != null) {
            String[] temp = line.split("\t"); // 通过String.split()函数把每条库存的每项数据通过"\t"分开，为读操作做准备
            if (temp.length == 4) {
                invVector.add(new Inventory(temp[0], Integer.parseInt(temp[1]), temp[2], temp[3]));
            }
        }
        return invVector;
    }

    private static Vector<Transaction> readTransaction(String filename) throws Exception {
        Vector<Transaction> tVector = new Vector<Transaction>();
        reader = new BufferedReader(new InputStreamReader(new FileInputStream(filename)));
        String line = "";
        while ((line = reader.readLine()) != null) {
            String[] temp = line.split("\t"); // 通过String.split()函数把事件包含的数据通过"\t"分开，为读操作做准备
            if (temp.length == 3) { // 当temp.length==3，说明该事件为R
                tVector.add(new Transaction(temp[0], temp[1], Integer.parseInt(temp[2]), ""));
            } else if (temp.length == 4) { // 当temp.length==4，说明该事件为O或A
                tVector.add(new Transaction(temp[0], temp[1], Integer.parseInt(temp[2]), temp[3]));
            } else if (temp.length == 2) { // 当temp.length==2，说明该事件为D
                tVector.add(new Transaction(temp[0], temp[1], 0, ""));
            }
        }
        return tVector;
    }
}
