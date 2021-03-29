#ifndef AVL_TREE_H
#define AVL_TREE_H
#include <cstdlib>
#include <iostream>

struct Node
{
	int nData;
	int nHeight;
	Node* pLeft;
	Node* pRight;
};

class AVLTREE
{
private:
	struct Node* pRoot;

	/*Binary Tree Methods*/
	void Add(struct Node*& pCurrentNode, int nKey);
	void CreateNode(struct Node*& pNewNode, int nKey);
	void InOrder(struct Node*& pRoot);
	void FindDeletedNode(struct Node*& pCurrentNode, int nKey);
	void DeleteNode(struct Node*& pCurrentNode, int nKey);
	void Destroy(struct Node*& pCurrentNode);
	void GetInorderPredecessor(struct Node*& pNode, int& nDeletedValue);
	void ReverseInOrder(struct Node*& pCurrentNode);
	void PrintGraph(struct Node* pCurrentNode, int nSpacingValue, int nLevelValue);
	bool IsFull();
	bool IsEmpty();

	/*AVL Tree Rotation Methods*/
	struct Node* RotateRight(Node* T);
	struct Node* RotateLeft(Node* T);
	struct Node* RotateRightLeft(Node* T);
	struct Node* RotateLeftRight(Node* T);

	/*AVL Height and Balancing Methods*/
	int Difference(struct Node* T);
	int GetHeight(struct Node* T);
	struct Node* Balance(struct Node* T);

public:
	AVLTREE();
	~AVLTREE();

	void Insert(int nKey);
	void Delete(int nKey);
	void SortedOrder();
	void ReverseSortedOrder();
	void PrintTree();
	void DestroyTree();
	
};

#endif AVL_TREE_H