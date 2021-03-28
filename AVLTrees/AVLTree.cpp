#include "AVLTree.h"

AVLTREE::AVLTREE()
{
	pRoot = NULL;
}

void AVLTREE::Insert(int nKey)
{
	Add(pRoot, nKey);
}

//Aux. to Insert()
void AVLTREE::CreateNode(struct Node*& pNewNode, int nKey)
{
	pNewNode = new Node;
	pNewNode->nData = nKey;
	pNewNode->nHeight = 0;
	pNewNode->pLeft = pNewNode->pRight = NULL;
}

//Aux. to Insert()
void AVLTREE::Add(struct Node*& pCurrentNode, int nKey)
{
	if (pCurrentNode == NULL)
		CreateNode(pCurrentNode, nKey);
	else if (nKey < pCurrentNode->nData)
		Add(pCurrentNode->pLeft, nKey);
	else
		Add(pCurrentNode->pRight, nKey);
}

void AVLTREE::Delete(int nKey)
{
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
	PostOrder(pRoot);
}

//Aux. to ReverseSortedOrder()
void AVLTREE::PostOrder(struct Node*& pCurrentNode)
{
	if (pCurrentNode != NULL)
	{
		PostOrder(pCurrentNode->pLeft);
		PostOrder(pCurrentNode->pRight);
		std::cout << pCurrentNode->nData << std::endl;
	}
}

void AVLTREE::PrintTree()
{
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

AVLTREE::~AVLTREE()
{
	Destroy(pRoot);
}

//Aux. to ~AVLTREE()
void AVLTREE::Destroy(struct Node*& pCurrentNode)
{
	if (pRoot != NULL)
	{
		Destroy(pCurrentNode->pLeft);
		Destroy(pCurrentNode->pRight);
		delete pCurrentNode;
	}
}