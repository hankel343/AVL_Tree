#include "AVLTree.h"

AVLTREE::AVLTREE()
{
	pRoot = NULL;
}

void AVLTREE::Insert(int nKey)
{
	if (!IsFull())
	{
		Add(pRoot, nKey);
		pRoot = Balance(pRoot);
	}
		
}

//Aux. to Insert()
void AVLTREE::Add(struct Node*& pCurrentNode, int nKey)
{
	if (pCurrentNode == NULL)
		CreateNode(pCurrentNode, nKey);
	else if (nKey < pCurrentNode->nData) {
		Add(pCurrentNode->pLeft, nKey);
		pCurrentNode->pLeft = Balance(pCurrentNode->pLeft);
	}
	else {
		Add(pCurrentNode->pRight, nKey);
		pCurrentNode->pRight = Balance(pCurrentNode->pRight);
	}
}

//Aux. to Insert()
void AVLTREE::CreateNode(struct Node*& pNewNode, int nKey)
{
	pNewNode = new Node;
	pNewNode->nData = nKey;
	pNewNode->nHeight = 0;
	pNewNode->pLeft = pNewNode->pRight = NULL;
}

void AVLTREE::Delete(int nKey)
{
	if (!IsEmpty())
		FindDeletedNode(pRoot, nKey);
}

//Aux. to Delete()
void AVLTREE::FindDeletedNode(struct Node*& pCurrentNode, int nKey)
{
	if (nKey == pCurrentNode->nData)
		DeleteNode(pCurrentNode, nKey);
	else if (nKey < pCurrentNode->nData)
		FindDeletedNode(pCurrentNode->pLeft, nKey);
	else
		FindDeletedNode(pCurrentNode->pRight, nKey);
}

//Aux. to Delete()
void AVLTREE::DeleteNode(struct Node*& pCurrentNode, int nKey)
{
	struct Node* pTemp = pCurrentNode;

	if (pCurrentNode->pLeft == NULL) {
		pCurrentNode = pCurrentNode->pRight;
		delete pTemp;
	} else if (pCurrentNode->pRight == NULL) {
		pCurrentNode = pCurrentNode->pLeft;
		delete pTemp;
	} else {
		GetInorderPredecessor(pCurrentNode, nKey);
		pCurrentNode->nData = nKey;
		FindDeletedNode(pCurrentNode->pLeft, nKey);
	}
}

//Aux. to Delete()
void AVLTREE::GetInorderPredecessor(struct Node*& pNode, int& nDeletedValue)
{
	while (pNode->pRight != NULL)
		pNode = pNode->pRight;

	nDeletedValue = pNode->nData;
}

void AVLTREE::SortedOrder()
{
	InOrder(pRoot);
}

//Aux. to SortedOrder()
void AVLTREE::InOrder(struct Node*& pRoot)
{
	if (pRoot != NULL)
	{
		InOrder(pRoot->pLeft);
		std::cout << pRoot->nData << std::endl;
		InOrder(pRoot->pRight);
	}
}

void AVLTREE::ReverseSortedOrder()
{
	ReverseInOrder(pRoot);
}

//Aux. to ReverseSortedOrder()
void AVLTREE::ReverseInOrder(struct Node*& pCurrentNode)
{
	if (pCurrentNode != NULL)
	{
		ReverseInOrder(pCurrentNode->pRight);
		std::cout << pCurrentNode->nData << std::endl;
		ReverseInOrder(pCurrentNode->pLeft);
	}
}

void AVLTREE::PrintTree()
{
	if (!IsEmpty())
		PrintGraph(pRoot, 0, 1);
}

//Aux. to PrintTree()
void AVLTREE::PrintGraph(Node* pCurrentNode, int nSpacingValue, int nLevelValue)
{
	//Base case and end of recursive calls to PrintGraph()
	if (pCurrentNode == NULL)
		return;

	//Every level lower in the tree adds 1 to nSpacingValue which determines the number of tab characters to print
	//The number of tab characters is the same for items at the same level, and this achieved through the recursive -
	//structure of this function.
	nSpacingValue += nLevelValue;

	//Recursive call to travel to the bottom of the right subtree and work back up.
	PrintGraph(pCurrentNode->pRight, nSpacingValue, nLevelValue);

	std::cout << std::endl;
	for (int i = nLevelValue; i < nSpacingValue; i++) //For loop prints out tab characters one less than nSpacingValue
		std::cout << '\t';
	std::cout << pCurrentNode->nData << "\n";

	//Recursive call to travel to the bottom of the left subtree and work back up.
	PrintGraph(pCurrentNode->pLeft, nSpacingValue, nLevelValue);
}

bool AVLTREE::IsFull()
{
	try
	{
		Node* pTest = new Node;
		delete pTest;
		return false;
	} catch (std::bad_alloc exception){
		return true;
	}
}

bool AVLTREE::IsEmpty()
{
	return (pRoot == NULL);
}

void AVLTREE::DestroyTree()
{
	Destroy(pRoot);
	pRoot = NULL;
}

AVLTREE::~AVLTREE()
{
	Destroy(pRoot);
}

//Aux. to ~AVLTREE() and DestroyTree()
void AVLTREE::Destroy(struct Node*& pCurrentNode)
{
	if (pCurrentNode != NULL)
	{
		Destroy(pCurrentNode->pLeft);
		Destroy(pCurrentNode->pRight);
		delete pCurrentNode;
	}
}

/*AVL Rotation Methods*/
struct Node* AVLTREE::RotateRight(Node* T)
{
	//T is the root before rotation.
	Node* S = T->pLeft;
	Node* B = S->pRight; //Right child of the root's left child.

	S->pRight = T;
	T->pLeft = B;

	return S;
}

struct Node* AVLTREE::RotateLeft(Node* T)
{
	//T is the root node before rotation.
	Node* S = T->pRight;
	Node* B = S->pLeft;

	S->pLeft = T;
	T->pRight = B;

	return S;
}

struct Node* AVLTREE::RotateRightLeft(Node* T)
{
	Node* S = T->pRight;
	T->pRight = RotateRight(S);
	return RotateLeft(T);
}

struct Node* AVLTREE::RotateLeftRight(Node* T)
{
	Node* S = T->pLeft;
	T->pLeft = RotateLeft(S);
	return RotateRight(T);
}

/*AVL Height and Balancing Methods*/
int AVLTREE::Difference(struct Node* T)
{
	return GetHeight(T->pLeft) - GetHeight(T->pRight);
}

int AVLTREE::GetHeight(struct Node* T)
{
	if (T == NULL)
		return 0;
	else
	{
		int nHeightLeft = GetHeight(T->pLeft);
		int nHeightRight = GetHeight(T->pRight);
		
		if (nHeightLeft > nHeightRight)
			return nHeightLeft + 1;
		else
			return nHeightRight + 1;
	}
}

struct Node* AVLTREE::Balance(Node* T)
{
	int nBalanceFactor = Difference(T);
	if (nBalanceFactor > 1) {
		
		if (Difference(T->pLeft) > 1)
			return RotateRight(T);
		else
			return RotateLeftRight(T);

	} else if (nBalanceFactor < -1) {
		
		if (Difference(T->pRight) < 0)
			return RotateLeft(T);
		else
			return RotateRightLeft(T);

	} else {
		return T;
	}
}