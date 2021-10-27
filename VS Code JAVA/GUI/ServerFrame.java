package GUI;


import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.*;
import java.net.ServerSocket;
import java.net.Socket;


public class ServerFrame extends  Frame implements ActionListener{
    Label [] labels = new Label[5];
    TextField [] textFields = new TextField[5];
    Button [] buttons = new Button[5];
    TextArea [] textAreas= new TextArea[5];
    Panel [] panels = new Panel[5];
    ServerSocket listen1=null;
    Socket Client=null;

    public ServerFrame(String title){//构造函数
        super(title);
    }
    public static void main(String[] args) {
        ServerFrame f= new ServerFrame("Server");
        f.DrawGUI();
    }
    void DrawGUI() {//基本绘图
        labels[0] = new Label("Port:");
        labels[1] = new Label("Say:");

        textFields[0] = new TextField(80);
        textFields[1] = new TextField(80);

        buttons[0] = new Button(" start ");
        buttons[1] = new Button(" Say ");

        textAreas[0] =new TextArea(8,80);

        panels[0] = new Panel();
        panels[1] = new Panel();

        for(int i =0;i<=1;++i){
            panels[i].add(labels[i]);panels[i].add(textFields[i]);panels[i].add(buttons[i]);
        }
        add(panels[0],"North");
        add(panels[1],"South");

        add(textAreas[0],"Center");
        pack();
        setVisible(true);

        buttons[0].addActionListener(this);//绑定按钮和事件
        buttons[1].addActionListener(this);
    }
    @Override
    public void actionPerformed(ActionEvent e) {
        Object source =e.getSource();
        if(source == buttons[0]) {
            try {
                int port = Integer.parseInt(textFields[0].getText().trim());
                textAreas[0].append("Server starting…"+'\n');
                listen1 = new ServerSocket(port);
                Client = listen1.accept();
                textAreas[0].append("Client connected…"+'\n');
                Thread ServerListen = new Thread(new Server_ListenThread(Client));
                ServerListen.start();//开始Server的读入线程
            } catch (Exception e1) {
            e1.printStackTrace();
        }
        }else{
            Thread ServerSpeaker = new Thread(new Server_Speaker(Client));
            ServerSpeaker.start();//开始Server的讲话线程
        }
    }
    class Server_ListenThread implements Runnable{//实现Runnable接口实现run函数
        Socket Client;
        public  Server_ListenThread(Socket Client){
            this.Client=Client;
        }
        @Override
        public void run() {
            try {
                InputStream ios = this.Client.getInputStream();
                BufferedReader reader = new BufferedReader(new InputStreamReader(ios));
                String tem =reader.readLine();
            while(tem!=null){
                textAreas[0].append("Form Client:"+tem+'\n');
                tem=reader.readLine();
            }
            reader.close();
        } catch (Exception e1) {
            e1.printStackTrace();
        }
        }
    }
    class Server_Speaker implements Runnable{
        Socket Client;
        public  Server_Speaker(Socket Client){
            this.Client=Client;
        }
        @Override
        public void run() {
            try {
                OutputStream os = Client.getOutputStream();
                BufferedWriter writer = new BufferedWriter(new OutputStreamWriter(os));
                String message = textFields[1].getText();
                writer.write(message);
                writer.newLine();
                writer.flush();
            }catch (Exception e){
                e.printStackTrace();
            }
        }
    }
}