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

	void Add(struct Node*& pCurrentNode, int nKey);
	void CreateNode(struct Node*& pNewNode, int nKey);
	void InOrder(struct Node*& pRoot);
	void FindDeletedNode(struct Node*& pCurrentNode, int nKey);
	void DeleteNode(struct Node*& pCurrentNode, int nKey);
	void Destroy(struct Node*& pCurrentNode);
	void GetInorderPredecessor(struct Node*& pNode, int& nDeletedValue);
	void PostOrder(struct Node*& pCurrentNode);
	void PrintGraph(struct Node* pCurrentNode, int nSpacingValue, int nLevelValue);
	bool IsFull();
	bool IsEmpty();

public:
	AVLTREE();
	~AVLTREE();

	void Insert(int nKey);
	void Delete(int nKey);
	void SortedOrder();
	void ReverseSortedOrder();
	void PrintTree();
	
};

#endif AVL_TREE_H