#include<iostream>
#include<string>
#include<fstream>
using namespace std;

void change(string a, string b) {
    fstream outfile, infile;
    char i[100], j[100];
    infile.open("1.txt", ios::in);
    outfile.open("2.txt", ios::out);
    char ch2;
    while (infile.get(ch2))                 //get函数逐个读取字符吧，注意空行如何继续读取
    {
        if (ch2 == '/')
        {
            infile.get(ch2);
            if (ch2 == '/')
            {

                while (infile.get(ch2))
                {
                    if (ch2 == '\n')
                    {
                        outfile << endl; break;
                    }
                }
            }
            else if (ch2 == '*')
            {
                while (infile.get(ch2))
                {
                    if (ch2 == '*')
                    {
                        infile.get(ch2);
                        if (ch2 == '/')
                            break;
                        outfile << ch2;
                    }
                    else if (ch2 == '\n')
                        outfile << '\n';
                }
            }
        }
        else
        {
            outfile << ch2;
        }
    };
    cout << "\n\n文件操作完毕！" << b << endl;
    cout << "现在我们将其加上行号后转存入 3.txt" << endl;
    system("pause");

}


int main() {
    ifstream file;
    file.open("1.txt");
    if (!file.is_open()) {
        cout << "文件不存在" << endl;
        return 0;
    }
    char c;
    while ((c = file.get()) != EOF) {          //EOF end of file
        cout << c;
    }
    file.close();
    file.clear();
    cout << "\n\n以上是源文件的内容，我们将其去掉注释后存入2.txt中" << endl;
    system("pause");
    system("cls");

    string a = "1.txt";
    string b = "2.txt";
    change(a, b);

    fstream outfile1, infile1;
    infile1.open("2.txt", ios::in);
    if (!infile1)
    {
        cout << "2.txt can't open" << endl;
        abort();
    }
    outfile1.open("3.txt", ios::out);
    if (!outfile1)
    {
        cout << "3.txt can't be created" << endl;
        abort();
    }
    char buf[80];
    int i = 0;
    while (!infile1.eof())
    {
        infile1.getline(buf, sizeof(buf));
        outfile1 << "[" << i++ << "]   " << buf << endl;
    }
    cout << "2.txt=>3.txt成功！" << endl;
    infile1.close();
    outfile1.close();
}