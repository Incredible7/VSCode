#include"tag_bintree.h"
using namespace std;


int main()
{
	
	string s= "ABD##E##CF##G##";
    Thread_BiTree<char> tree(s);
    tree.travIn();
	// BinNodePosi(char) p=tree._pRoot;
	// tree.insert_as_lchild(p->lchild->lchild,'S');
 
	tree.PreOrderThreading();            //先序线索化
	tree.PreOrder();                   //遍历先序线索二叉树
	cout << endl << "------------------------" << endl;
 
	string s1 = "ABD##E##CF##G##";
	Thread_BiTree<char> tree1(s1);
	tree1.InOrderThreading();          //中序线索化
	tree1.InOrder();                //遍历中序线索二叉树
	cout << endl << "------------------------" << endl;
 
	string s2 = "ABD##E##CF##G##";
	Thread_BiTree<char> tree2(s2);
	tree2.PostOrderThreading();
	tree2.PostOrder();
	cout << endl << "------------------------" << endl;
	system("pause");
    return 0;
}