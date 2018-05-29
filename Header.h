#include <iostream>
#include <string>
#include <fstream>
#include <conio.h>
using namespace std;
string convertToLower(string);
struct AVL
{
	string word;
	AVL *left;
	AVL *right;
	int height;
	AVL() :word(""), left(NULL), right(NULL), height(0){}
};
class AVLTree{ 
	AVL *root;
public:
	AVLTree() :root(NULL){}
	int max(int, int);
	int height(AVL *);
	int diff(AVL *);
	void RR(AVL *&);
	void LL(AVL *&);
	void LR(AVL *&);
	void RL(AVL *&);
	void balance(AVL *&);
	void insert(AVL*&,string,int &,ofstream &,int &);
	void insertByMain(string,int &,ofstream &,int &);
	bool find(AVL *&,string,ofstream &);
	void remove(string, AVL *&);
	AVL* findMin(AVL *&);
	AVL* getRoot();
};
struct node
{
	string word;
	node *next;
};
class linkList
{
public:
	node *head;
	linkList() : head(NULL){}
	void insert(node *&,string);
	void displayFromSC();
	void display(node *&,ofstream &);
	void deleteList(node *&);
};
class spellChecker{
	AVL *root;
	AVLTree *obj;
	linkList *listObj;
public:
	spellChecker()
	{
		obj = new AVLTree;
		listObj = new linkList;
		root = obj->getRoot();
	}
	void remove();
	void insert(string,ofstream &,int &);
	void check(AVL *&, string);
	void inputFromFile(ifstream &,ofstream &);
	void commandFile(ofstream &,ifstream &);
	void inOrder(AVL*&,ofstream &,int &);
	void inOrderByMain(string,ofstream &);
	~spellChecker()
	{
		delete obj;
		delete listObj;
	}
};