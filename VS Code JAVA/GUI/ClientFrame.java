package GUI;

import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.*;
import java.net.Socket;

public class ClientFrame extends Frame implements ActionListener {
    Label[] labels = new Label[5];
    TextField[] textFields = new TextField[5];
    Button[] buttons = new Button[5];
    TextArea[] textAreas = new TextArea[5];
    Panel[] panels = new Panel[5]; 
    Socket Speaker = null;

    public ClientFrame(String title) {// 构造函数
        super(title);
    }

    public static void main(String[] args) {

        ClientFrame f = new ClientFrame("Client");
        f.DrawGUI();
    }

    void DrawGUI() {

        labels[0] = new Label("Server IP");
        labels[2] = new Label("Say:");
        labels[1] = new Label("Server Port:");

        textFields[0] = new TextField(35);
        textFields[1] = new TextField(35);
        textFields[2] = new TextField(90);

        buttons[0] = new Button(" Connect ");
        buttons[1] = new Button(" Say ");

        textAreas[0] = new TextArea(8, 8);
        panels[0] = new Panel();
        panels[1] = new Panel();
        for (int i = 0; i <= 0; ++i) {

            panels[i].add(labels[i]);
            panels[i].add(textFields[i]);
            panels[i].add(labels[1]);
            panels[i].add(textFields[1]);
            panels[i].add(buttons[i]);
        }
        for (int i = 1; i <= 1; ++i) {
            panels[i].add(labels[2]);
            panels[i].add(textFields[2]);
            panels[i].add(buttons[i]);
        }

        add(panels[0], "North");
        add(panels[1], "South");

        add(textAreas[0], "Center");
        pack();
        setVisible(true);

        buttons[0].addActionListener(this);// 捆绑事件
        buttons[1].addActionListener(this);
    }

    @Override // @Override下面的方法名是否是你父类中所有的，如果没有则报错
    public void actionPerformed(ActionEvent e) {
        Object source = e.getSource();// 事件开始
        String tem_IP;
        int tem_Port;
        if (source == buttons[0]) {
            textAreas[0].append("Connect to server…" + '\n');
            tem_IP = textFields[0].getText();
            tem_Port = Integer.parseInt(textFields[1].getText());
            // parseInt() 方法用于将字符串参数作为有符号的十进制整数进行解析。
            // 如果方法有两个参数， 使用第二个参数指定的基数，将字符串参数解析为有符号的整数。
            try {
                Speaker = new Socket(tem_IP.trim(), tem_Port);
            } catch (IOException ioException) {
                ioException.printStackTrace();// 在命令行打印异常信息在程序中出错的位置及原因
            }
            Thread ClientLister = new Thread(new Client_Lister(Speaker));
            ClientLister.start();// Client输入线程开始
        } else {
            Thread ClientSpeaker = new Thread(new Client_Speaker(Speaker));
            ClientSpeaker.start();// Client线程开始
        }
    }

    class Client_Speaker implements Runnable {// 实现Runnable接口
        Socket Speaker;

        public Client_Speaker(Socket Speaker) {
            this.Speaker = Speaker;
        }

        @Override
        public void run() {
            try {
                OutputStream os = Speaker.getOutputStream();
                OutputStreamWriter osw = new OutputStreamWriter(os);
                BufferedWriter writer = new BufferedWriter(osw);
                String message = textFields[2].getText();
                writer.write(message);
                writer.newLine();
                writer.flush();
            } catch (Exception e1) {
                e1.printStackTrace();
            }
        }
    }

    class Client_Lister implements Runnable {
        Socket Speaker;

        public Client_Lister(Socket Speaker) {
            this.Speaker = Speaker;
        }

        @Override
        public void run() {
            {
                try {
                    InputStream ios = this.Speaker.getInputStream();
                    BufferedReader reader = new BufferedReader(new InputStreamReader(ios));
                    String tem = reader.readLine();
                    while (tem != null) {
                        textAreas[0].append("Form Server:" + tem + '\n');
                        tem = reader.readLine();
                    }
                    reader.close();
                } catch (Exception e) {
                    e.printStackTrace();
                }
            }
        }
    }
}
