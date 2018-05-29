#include "Header.h"
string convertToLower(string A)
{
	int len = A.length();
	for (int i = 0; i < len; i++)			//Converts the word into lowercase so it compares the word without any case sensitive error
		A[i] = tolower(A[i]);
	return A;
}
int AVLTree::height(AVL *temp)
{
	if (temp != NULL)
	{
		int left = height(temp->left);
		int right = height(temp->right);
		int maxHeight = max(left, right);
		return maxHeight + 1;
	}
	return 0;
}
int AVLTree::max(int x, int y)
{

	if (x >= y)
		return x;
	else
		return y;
}
int AVLTree::diff(AVL *temp)
{
	return height(temp->left) - height(temp->right);
}
void AVLTree::RR(AVL *&root)
{
	AVL *temp;
	temp = root->right;
	root->right = temp->left;
	temp->left = root;
	root->height = max(height(root->left), height(root->right)) + 1;
	temp->height = max(height(temp->left), root->height) + 1;
	root = temp;
}
void AVLTree::LL(AVL *&root)
{
	AVL *temp;
	temp = root->left;
	root->left = temp->right;
	temp->right = root;
	root->height = max(height(root->left), height(root->right)) + 1;
	temp->height = max(height(temp->left), root->height) + 1;
	root = temp;
}
void AVLTree::LR(AVL *&root)
{
	AVL *temp;
	temp = root->left;
	RR(temp);
	root->left = temp;
	LL(root);
}
void AVLTree::RL(AVL *&root)
{
	AVL *temp;
	temp = root->right;
	LL(temp);
	root->right = temp;
	RR(root);
}
void AVLTree::balance(AVL *&root)
{
	if (root)
	{
		int bal_factor = diff(root);
		if (bal_factor > 1)
		{
			if (diff(root->left) > 0)
				LL(root);
			else
				LR(root);
		}
		else if (bal_factor < -1)
		{
			if (diff(root->right) > 0)
				RL(root);
			else
				RR(root);
		}
	}
}
void AVLTree::insertByMain(string word, int &count, ofstream &out, int &result)
{
	insert(root, word, count, out, result);
}
void AVLTree::insert(AVL *&root, string value, int &count, ofstream &out, int &result)
{
	if (!root)

	{
		root = new AVL;
		root->word = value;
		root->left = NULL;
		root->right = NULL;
		root->height = 1;
		count++;
	}
	else if (value < root->word)
	{
		insert(root->left, value, count, out, result);
		balance(root);
	}
	else if (value > root->word)
	{
		insert(root->right, value, count, out, result);
		balance(root);

	}
	else if (value == root->word)
	{
		out << "\n" << value << " isn't added to the dictionary.\n";
		result = 1;
		return;
	}
	root->height = max(height(root->left), height(root->right)) + 1;
	//return root;

}
bool AVLTree::find(AVL *&root, string A, ofstream &out)
{
	if (!root)
	{
		return false;
	}
	else if (A < root->word)
	{
		out << "Find:\tgoing left from " << root->word << endl;
		return find(root->left, A, out);
	}
	else if (A > root->word)
	{
		out << "Find:\tgoing right from " << root->word << endl;
		return find(root->right, A, out);
	}
	else if (A == root->word)
	{
		out << "Found: " << A << endl << "Word is spelled correctly" << endl;;
		return true;
	}
}
AVL *AVLTree::findMin(AVL *&temp)
{
	if (!temp->left)
		return temp;
	return findMin(temp->left);
}
void AVLTree::remove(string x, AVL *&root)
{
	if (root == NULL)
		return;
	if (x < root->word)
		remove(x, root->left);
	else if (root->word < x)
		remove(x, root->right);
	else if (root->left != NULL && root->right != NULL)
	{
		root->word = findMin(root->right)->word;
		remove(root->word, root->right);
	}
	else
	{
		AVL *oldNode = root;
		root = (root->left != NULL) ? root->left : root->right;
		delete oldNode;
		if (oldNode)
			oldNode = NULL;
	}
	balance(root);
}
void spellChecker::inputFromFile(ifstream &in, ofstream &out)
{
	string str;
	int count = 0;
	int result = 0;
	if (in.is_open())
	{
		while (!in.eof())
		{
			in >> str;
			str = convertToLower(str);
			obj->insertByMain(str, count, out, result);
		}
		in.close();
	}
	out << "Dictionary contains " << count << " words.\n";
}
AVL* AVLTree::getRoot()								//iterator
{
	return root;
}
void spellChecker::commandFile(ofstream &out, ifstream &in)
{
	int i = 0, result = 0;
	root = obj->getRoot();
	string command, word;
	bool match = false;
	while (!in.eof())
	{
		out << "--------------------------------" << i++ << endl;
		in >> command;
		command = convertToLower(command);
		if (command == "check")
		{
			in >> word;
			word = convertToLower(word);
			out << "\nCommand: " << command << "\t" << word << endl;
			match = obj->find(root, word, out);
			if (!match)
			{
				check(root, word);
				if (listObj->head)
				{
					out << "word is spelled incorrectly:\n\tSuggested Spelling:\n";
					listObj->display(listObj->head, out);
				}
				else
				{
					out << "word is spelled incorrectly:\n\tSuggested Spelling:\n";
					out << "No suggestions found\n";
				}
				listObj->deleteList(listObj->head);
			}
			match = false;
		}
		else if (command == "add")
		{
			in >> word;
			word = convertToLower(word);
			out << "\nCommand: " << command << "\t" << word << endl;
			insert(word, out, result);
			if (result != 1)
				out << word << " has been added to the dictionary\n";
			result = 0;
		}
		else if (command == "remove")
		{
			in >> word;
			word = convertToLower(word);
			out << "\nCommand: " << command << "\t" << word << endl;
			out << word << " has been removed to the dictionary\n";
			obj->remove(word, root);
		}
		else if (command == "display")
		{
			inOrderByMain(command, out);
		}
		else if (command == "exit")
		{
			out << "\nCommand: " << command << endl << "Exiting Now...\n--------------------------------";
			exit(1);
		}

	}

}
void linkList::display(node *&tempH, ofstream &out)
{
	node *ptr = tempH;
	while (ptr)
	{
		out << "\t" << ptr->word << endl;
		ptr = ptr->next;
	}
}
void spellChecker::insert(string A, ofstream &out, int &result)
{
	int count = 0;
	A = convertToLower(A);
	obj->insertByMain(A, count, out, result);
}
void spellChecker::check(AVL *&root, string A)
{
	if (root == NULL)
		return;
	else
	{
		int count = 0;
		int len1 = A.length(); //8
		int len2 = root->word.length(); //6

		if (len2 - len1 <= 2 && len2 - len1 >= -2)                   //Rule 1:If the lengths of W and C differ by more than two, do not suggest C.
		{
			int i, len;
			if (len2 - len1 >= 0)
			{
				len = len1;
			}
			else
			{
				len = len2;
			}
			for (i = 0; i < len; i++)
			{
				if (A[i] != root->word[i])         //Compare the characters of W to those of C, one by one, until reaching the end of one or both strings.If there are no more than two mismatches, and the number of mismatches is less than the lengths of both W and C, suggest C.
				{
					count++;
				}

			}
			if (len2 - i > 0)
			{
				count += len2 - i;
			}
			else if (len1 - i > 0)
			{
				count += len1 - i;
			}
			if (count <= 2)
			{
				listObj->insert(listObj->head, root->word);
			}
		}
		check(root->left, A);
		check(root->right, A);
	}
}
void linkList::deleteList(node *&tempH)
{
	node *ptr;
	while (tempH)
	{
		ptr = tempH->next;
		delete tempH;
		if (tempH)
			tempH = NULL;
		tempH = ptr;
	}
}
void linkList::insert(node *& tempH, string A)
{
	node * ptr;
	ptr = new node;
	ptr->word = A;
	ptr->next = tempH;
	tempH = ptr;
}
void spellChecker::inOrderByMain(string A, ofstream &out)
{
	out << "\nCommand: " << A << endl;
	out << "Spelling Dictionary Contents: \n\n";
	root = obj->getRoot();
	inOrder(root, out, root->height);
}
void spellChecker::inOrder(AVL *&root, ofstream &out, int &height)
{
	if (root == NULL)
		return;

	inOrder(root->left, out, height);
	for (int i = 0; i < (height - root->height); i++)
	{
		out << "-";
	}
	out << "(" << obj->diff(root) << ")   " << root->word << "\n";

	inOrder(root->right, out, height);

}