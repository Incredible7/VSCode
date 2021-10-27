package Cargo;

import java.io.*;
import java.util.Collections;
import java.util.Vector;

public class Test {
    private static BufferedReader reader;
    private static BufferedReader reader2;

    public static void main(String[] args) throws Exception {
        Vector<Inventory> invVector = readInventory("D:/Inventory.txt"); // ����Inventory������Vector�У�ÿ��Ԫ��Ϊһ����
        Vector<Transaction> tVector = readTransaction("D:/Transaction.txt");// ����transaction������Vector�У�ÿ��Ԫ��Ϊһ���¼�
        Vector<Transaction> oVector = new Vector<Transaction>();
        for (int i = 0; i < tVector.size(); i++) {
            if (tVector.get(i).type.equals("R")) { // �ȴ���R�¼�����������
                for (int j = 0; j < invVector.size(); j++) {
                    if (invVector.get(j).Item.equals(tVector.get(i).Item)) {
                        invVector.get(j).Quantity += tVector.get(i).num;
                        break;
                    }
                }
            } else if (tVector.get(i).type.equals("A")) { // A��R�����ȼ���ͬ��ͬΪ���������������ȴ���
                invVector.add(new Inventory(tVector.get(i).Item, 0, Integer.toString(tVector.get(i).num),
                        tVector.get(i).customer));
            } else if (tVector.get(i).type.equals("O")) { // OΪ���������Ӧ��A��R������ɺ��ڴ���
                oVector.add(tVector.get(i)); // Ϊ�˷���ΪO�¼����򣬼��ȴ���������ٵģ���������ѯ��Oʱ��������Vector���ȴ��ͺ���
            }
        }
        Collections.sort(oVector); // ΪO�¼����򣬼��������ٵĶ������ȼ�����
        for (int i = 0; i < oVector.size(); i++) { // ��ʼ��������O�¼�
            for (int j = 0; j < invVector.size(); j++) {
                if (invVector.get(j).Item.equals(oVector.get(i).Item)) { // �������>=����������ִ��O����
                    if (invVector.get(j).Quantity >= oVector.get(i).num) {
                        invVector.get(j).Quantity -= oVector.get(i).num;
                    } else {
                        FileOutputStream fos = new FileOutputStream("D:/Errors.txt"); // �������<����������˵����O����Υ�棬���뵽d:/Errors.txt��
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
        for (int i = 0; i < tVector.size(); i++) { // �����D��������ɾ��ĳ����
            if (tVector.get(i).type.equals("D")) {
                for (int j = 0; j < invVector.size(); j++) {
                    if (invVector.get(j).Item.equals(tVector.get(i).Item)) {
                        invVector.remove(j);
                    }
                }
            }
        }
        File file = new File("D:/Inventory.txt");
        try { // ��ԭd:/Inventory.txt���
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
        FileOutputStream fos = new FileOutputStream("D:/Inventory.txt");// ���µĿ����Ϣ���뵽d:/Inventory.txt��
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

    private static Vector<Inventory> readInventory(String filename) throws Exception { // �� Inventory
        Vector<Inventory> invVector = new Vector<Inventory>();
        reader2 = new BufferedReader(new InputStreamReader(new FileInputStream(filename)));
        String line = "";
        while ((line = reader2.readLine()) != null) {
            String[] temp = line.split("\t"); // ͨ��String.split()������ÿ������ÿ������ͨ��"\t"�ֿ���Ϊ��������׼��
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
            String[] temp = line.split("\t"); // ͨ��String.split()�������¼�����������ͨ��"\t"�ֿ���Ϊ��������׼��
            if (temp.length == 3) { // ��temp.length==3��˵�����¼�ΪR
                tVector.add(new Transaction(temp[0], temp[1], Integer.parseInt(temp[2]), ""));
            } else if (temp.length == 4) { // ��temp.length==4��˵�����¼�ΪO��A
                tVector.add(new Transaction(temp[0], temp[1], Integer.parseInt(temp[2]), temp[3]));
            } else if (temp.length == 2) { // ��temp.length==2��˵�����¼�ΪD
                tVector.add(new Transaction(temp[0], temp[1], 0, ""));
            }
        }
        return tVector;
    }
}
