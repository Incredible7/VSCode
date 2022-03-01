
#include <fstream>
#include <iostream>
#include<string>
#include <queue> //队列容器
using namespace std;
const int leaf = 256; //最多可能出现的不同字符数

//huffman树的结点结构体
class HTnode {
public:
    long weight; //记录结点的权值
    int parent; //记录结点的双亲结点位置
    int lchild; //结点的左孩子
    int rchild; //结点的右孩子
    int* code; //记录该结点的huffman编码
    int codelen; //记录该结点huffman编码的长度

    //初始化结点，令其权值为无穷大，无双亲及左右孩子
    HTnode() :weight(INT_MAX), parent(-1), lchild(-1), rchild(-1), codelen(0),code(nullptr) {}
};
//huffman树类
class huffmanTree {
public:
    huffmanTree() :root(0), leafnum(0), byte(0), bitsnum(0), lacknum(0) {}
    virtual ~huffmanTree();
    bool count(string input); //压缩时统计各字符出现的次数，将其写入对应结点的权值
    void create(); //压缩时根据各结点的权值构造huffman树
    void code(); //压缩时，利用建好的huffman树计算每个字符的huffman编码
    void printcode(); //列出每个字符的huffman编码
    void addbit(int bit); //压缩时对一个未满8个bit的byte中加入一个bit
    void resetbyte(); //将byte清空
    bool compress(string input, string output); //压缩函数 成功执行返回 true 失败 false
    bool decompress(string input, string output); //恢复函数 成功执行返回 true 失败 false
    void compare(string input, string output); //将原文件与压缩后的文件比较
    void compare2(string input, string output); //将原文件与恢复后的文件比较

private:
    int root; //记录根结点的位置
    int leafnum; //记录不同字符的个数
    HTnode HT[leaf * 2 - 1]; //HTnode结构的数组，用来表示huffman树，树的最大结点个数不会超过leaf*2-1
    char byte; //压缩文件时用来缓冲bit的变量
    int bitsnum; //byte中bit的个数
    int lacknum; //压缩到最后byte中的bit不满8个时填充的0的个数
};

huffmanTree::~huffmanTree()
{
    for (int i = 0; i < leaf; i++) {
        if (HT[i].codelen != 0)
            delete HT[i].code;
    }
}

//统计各字符出现的次数
bool huffmanTree::count(string input)
{
    ifstream ifs;
    char c;
    ifs.open(input, ios::binary);
    if (!ifs) {
        cout << "无法打开文件 " << input << '!' << endl;
        return false;
    }
    while (ifs.get(c)) {
        if (HT[c + 128].weight == INT_MAX) { //若该字符是第一次出现，先初始化权值
            HT[c + 128].weight = 0;
            leafnum++;
        }
        HT[c + 128].weight++; //权值+1
    }
    ifs.close();
    return true;
}

//选权值最小的两棵树组成新的数
void huffmanTree::create()
{
    for (int i = leaf; i < 2 * leaf - 1; i++) {
        int loc1 = -1, loc2 = -1;
        for (int j = 0; j < i; j++) {
            if (HT[j].parent != -1)
                continue;
            if (loc1 == -1 || HT[j].weight < HT[loc1].weight) {
                loc2 = loc1;
                loc1 = j;
            }
            else if (loc2 == -1 || HT[j].weight < HT[loc2].weight)
                loc2 = j;
        }
        if (HT[loc1].weight == INT_MAX || HT[loc2].weight == INT_MAX || loc2 == -1) //只剩一棵树，结束
            break;
        HT[i].weight = HT[loc1].weight + HT[loc2].weight;
        //为了减少压缩文件中需要写入的huffman树的信息，约定小标小的结点做为双亲结点的左孩子
        HT[i].lchild = (loc1 > loc2) ? loc2 : loc1;
        HT[i].rchild = (loc1 > loc2) ? loc1 : loc2;
        HT[loc1].parent = i;
        HT[loc2].parent = i;
        root = i;
    }
}

//压缩时，利用建好的huffman树计算每个字符的huffman编码
void huffmanTree::code()
{
    for (int i = 0; i < leaf; i++) {
        int len = 0;
        int loc = i;
        while (HT[loc].parent != -1) { //计算huffman编码长度
            len++;
            loc = HT[loc].parent;
        }
        HT[i].codelen = len;
        HT[i].code = new int[len];
        loc = i;
        for (int j = len - 1; j >= 0; j--) { //从后往前找，记录结点的huffman编码
            if (loc == HT[HT[loc].parent].lchild)
                HT[i].code[j] = 0;
            else
                HT[i].code[j] = 1;
            loc = HT[loc].parent;
        }
    }
}

//压缩时对一个未满8个bit的byte中加入一个bit
void huffmanTree::addbit(int bit)
{
    if (bit == 0)
        byte = byte << 1; //若新增的bit为0，则直接将byte按位左移
    else
        byte = ((byte << 1) | 1); //若新增的bit为1，先将byte按位左移，再与1按位或运算
    bitsnum++;
}

//将byte清空
void huffmanTree::resetbyte()
{
    byte = 0;
    bitsnum = 0;
}

//列出每个字符的huffman编码
void huffmanTree::printcode()
{
    for (int i = 0; i < leaf; i++) {
        if (HT[i].codelen != 0) {
            cout << "值为" << i - 128 << "的字符的huffman编码：";
            for (int j = 0; j < HT[i].codelen; j++) {
                cout << HT[i].code[j];
            }
            cout << endl;
        }
    }
}

//压缩函数 成功执行返回 true 失败 false
bool huffmanTree::compress(string input, string output)
{
    if (!count(input))
        return false;

    create();
    code();
    ifstream ifs;
    ofstream ofs;
    ifs.open(input, ios::binary);
    ofs.open(output, ios::binary);
    char c;
    if (!ifs) {
        cout << "无法打开文件 " << input << '!' << endl;
        return false;
    }
    if (!ofs) {
        cout << "无法打开文件 " << output << '!' << endl;
        return false;
    }

    ofs.put(0); //预留一个字符，等压缩完后在该位置写入不足一个byte的bit个数
    ofs.put(root - 384); //将根节点的位置-384写入（为使该值不超过char的最大表示范围）
    for (int i = 0; i < leaf * 2 - 1; i++) { //写入每个结点的双亲结点位置
        if (HT[i].parent == -1) //若该节点没有双亲结点，则写入127(一个字节所能表示的最大值)
            ofs.put(127);
        else //否则将双亲结点的位置-384再写入（为使该值不超过char的最大表示范围）
            ofs.put(HT[i].parent - 384);
    }

    while (ifs.get(c)) { //将字符的huffman编码并加入byte中
        int tmp = c + 128;
        for (int i = 0; i < HT[tmp].codelen; i++) {
            addbit(HT[tmp].code[i]);
            if (bitsnum == 8) { //若byte已满8位，则输出该byte并将byte清空
                ofs.put(byte);
                resetbyte();
            }
        }
    }
    if (bitsnum != 0) { //处理最后未满8个字符的byte，用0填充并记录填充的个数
        for (int i = bitsnum; i < 8; i++) {
            addbit(0);
            lacknum++;
        }
        ofs.put(byte);
        resetbyte();
    }
    ofs.seekp(0, ios::beg); //将写指针移动到文件开头
    ofs.put(lacknum); //写入最后一个字节缺失的bit个数
    ifs.close();
    ofs.close();
    return true;
}

//恢复函数 成功执行返回 true 失败 false
bool huffmanTree::decompress(string input, string output)
{
    queue<char> q;
    char c;
    ifstream ifs;
    ofstream ofs;
    ifs.open(input, ios::binary);
    ofs.open(output, ios::binary);
    if (!ifs) {
        cout << "无法打开文件 " << input << '!' << endl;
        return true;
    }
    if (!ofs) {
        cout << "无法打开文件 " << output << '!' << endl;
        return false;
    }

    ifs.get(c);
    lacknum = c; //读出最后一个字节缺失的bit个数
    ifs.get(c);
    root = c + 384; //读出根结点的位置
    for (int i = 0; i < leaf * 2 - 1; i++) { //建立各结点之间的双亲孩子关系
        ifs.get(c);
        if (c == 127)
            continue;
        else {
            HT[i].parent = c + 384;
            if (HT[c + 384].lchild == -1)
                HT[c + 384].lchild = i;
            else
                HT[c + 384].rchild = i;
        }
    }

    int point = root;
    //为了方便处理最后一个可能有缺失bit的字节，先将读出的数据放入队列
    while (ifs.get(c))
        q.push(c);

    //还原文件过程
    while (q.size() > 1) { //还未到最后一个字节
        c = q.front();
        for (int i = 0; i < 8; i++) {
            if (int(c & 128) == 0) {
                point = HT[point].lchild;
                if (HT[point].lchild == -1 && HT[point].rchild == -1) {
                    ofs.put(char(point - 128));
                    point = root;
                }
                c = c << 1;
            }
            else {
                point = HT[point].rchild;
                if (HT[point].lchild == -1 && HT[point].rchild == -1) {
                    ofs.put(char(point - 128));
                    point = root;
                }
                c = c << 1;
            }
        }
        q.pop();
    }
    c = q.front(); //最后一个字节
    for (int i = 0; i < 8 - lacknum; i++) {
        if (int(c & 128) == 0) {
            point = HT[point].lchild;
            if (HT[point].lchild == -1 && HT[point].rchild == -1) {
                ofs.put(char(point - 128));
                point = root;
            }
            c = c << 1;
        }
        else {
            point = HT[point].rchild;
            if (HT[point].lchild == -1 && HT[point].rchild == -1) {
                ofs.put(char(point - 128));
                point = root;
            }
            c = c << 1;
        }
    }
    q.pop();
    ifs.close();
    ofs.close();
    return true;
}

//将原文件与压缩后的文件比较
void huffmanTree::compare(string input, string output)
{
    ifstream origin, compress;
    origin.open(input, ios::binary);
    compress.open(output, ios::binary);

    if (!origin) {
        cout << "无法打开文件 " << input << '!' << endl;
        return;
    }
    if (!compress) {
        cout << "无法打开文件 " << output << '!' << endl;
        return;
    }
    double total1 = 0, total2 = 0;
    char c;
    while (origin.get(c))
        total1++;
    while (compress.get(c))
        total2++;
    cout << "原文件大小：" << total1 << " Byte" << endl;
    cout << "压缩后大小：" << total2 << " Byte" << endl;
    cout << "压缩率：" << total2 / total1 * 100 << '%' << endl;
    origin.close();
    compress.close();
}

//将原文件与恢复后的文件比较
void huffmanTree::compare2(string input, string output)
{
    ifstream origin, decompress;
    origin.open(input, ios::binary);
    decompress.open(output, ios::binary);
    double total1 = 0, total2 = 0;
    char c1, c2;
    bool dif = false;
    while (origin.get(c1) && decompress.get(c2)) {
        if (c1 != c2) //依次比较每个字节，不同则将dif标志设为true
            dif = true;
        total1++;
        total2++;
    }
    while (origin.get(c1)) { //若原文件还有剩余的数据，将dif设为true
        dif = true;
        total1++;
    }
    while (decompress.get(c2)) { //若恢复文件还有剩余的数据，将dif设为true
        dif = true;
        total2++;
    }
    cout << "原文件大小：" << total1 << " Byte" << endl;
    cout << "恢复文件大小：" << total2 << " Byte" << endl;
    if (dif == true)
        cout << "原文件与恢复文件不同!" << endl;
    else
        cout << "原文件与恢复文件相同!" << endl;
    origin.close();
    decompress.close();
}

int main()
{
    int choice;
    char input[255], output[255];
    huffmanTree h;
    while (true) {
        cout << "   ***************************************************" << endl;
        cout << "   *               哈夫曼编码压缩恢复算法             *" << endl;
        cout << "   *                                                  *" << endl;
        cout << "   *                    1)压缩                        *" << endl;
        cout << "   *                                                  *" << endl;
        cout << "   *                    2) 恢复                       *" << endl;
        cout << "   *                                                  *" << endl;
        cout << "   *                    3) 恢复文件与原文件的对比     *" << endl;
        cout << "   *                                                  *" << endl;
        cout << "   *                    4) 清屏                       *" << endl;
        cout << "   *                                                  *" << endl;
        cout << "   *                    5) 退出                       *" << endl;
        cout << "   *                                                  *" << endl;
        cout << "   *        说明：请您输入相应的操作序号进行操作      *" << endl;
        cout << "   ****************************************************" << endl;
        cout << ">";
        cin >> choice;
        switch (choice) {
        case 1: {
            cout << "请输入待压缩的文件名：";
            cin >> input;
            cout << "请输入压缩后的文件名：";
            cin >> output;
            if (h.compress(input, output)) {
                h.printcode();
                h.compare(input, output);
                cout << endl
                    << "文件压缩成功!" << endl;
            }
            else {
                cout << endl
                    << "文件压缩失败!" << endl;
            }
        } break;
        case 2: {
            cout << "请输入待恢复的文件名：";
            cin >> input;
            cout << "请输入恢复后的文件名：";
            cin >> output;
            if (h.decompress(input, output))
                cout << endl
                << "文件恢复成功!" << endl;
            else
                cout << endl
                << "文件恢复失败!" << endl;
        } break;
        case 3: {
            cout << "请输入原文件的文件名：";
            cin >> input;
            cout << "请输入恢复文件的文件名：";
            cin >> output;
            h.compare2(input, output);
        } break;
        case 4: {
            //执行清屏命令
            system("cls");
        } break;
        case 5:
            exit(0);
        }
        cout << endl;
    }
    return 0;
}