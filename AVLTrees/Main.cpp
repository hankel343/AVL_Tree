#include <iostream>
#include "AVLTree.h"

using namespace std;

void ProcessSelection(AVLTREE& Tree, char chInput);
void InsertCase(AVLTREE& Tree);
void DeleteCase(AVLTREE& Tree);

int main()
{
	AVLTREE Tree;
	char chInput = '-1';
	do
	{
		cout << "This program is a simple test for an AVL tree class.\n";
		cout << "Enter selections from the menu below to perform basic operations on the AVL tree.\n";
		cout << "\n\nEnter your selection: \n";
		cout << "1 - Insert an element into the tree.\n";
		cout << "2 - Delete an element from the tree.\n";
		cout << "3 - Print the elements of the tree in sorted order.\n";
		cout << "4 - Print the elements of the tree in reverse sorted order.\n";
		cout << "5 - Print a 2-D graphical representation of the tree.\n";
		cout << "Q - Exit the program.\n";
		cout << "Selection: ";
		cin >> chInput;

		system("cls");

		ProcessSelection(Tree, chInput);

	} while (toupper(chInput) != 'Q');

	cout << "Goodbye...\n";

	return 0;
}

void ProcessSelection(AVLTREE& Tree, char chInput)
{
	switch (toupper(chInput))
	{
	case '1':	InsertCase(Tree);
				break;

	case '2':	DeleteCase(Tree);
				break;

	case '3':	Tree.SortedOrder();
				break;

	case '4':	Tree.ReverseSortedOrder();
				break;

	case '5':	Tree.PrintTree();
				break;

	case 'Q':	break;

	default:	cout << "Unrecognized input - try again.\n";
				break;
	}
}

void InsertCase(AVLTREE& Tree)
{
	int nNewKey = 0;
	cout << "Enter the key you would like to insert into the tree: ";
	cin >> nNewKey;

	Tree.Insert(nNewKey);
}

void DeleteCase(AVLTREE& Tree)
{
	int nDeletedKey = 0;
	cout << "Enter the key you would like to delete from the tree: ";
	cin >> nDeletedKey;

	Tree.Delete(nDeletedKey);
}