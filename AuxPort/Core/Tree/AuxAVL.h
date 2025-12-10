#ifndef AUXPORT_AVL_H
#define AUXPORT_AVL_H

#include <memory>
#include <vector>
#include "../Env/AuxEnv.h"
#include "../Log/AuxLog.h"


struct AvlNode
{
	AvlNode* left;
	AvlNode* right;
	int height;
	int val;
};

class AvlTree
{
public:
	AvlTree(int value);
	~AvlTree() = default;
	AvlTree(const AvlTree& avlTree) = default;
	void add(int value);
protected:
	AvlNode* insert(AvlNode* curr,int value);
	int leftHeight(AvlNode* curr, int height);
	int rightHeight(AvlNode* curr, int height);
	int masterComputeHeight(AvlNode* parent, int height);
	int isBalanced(AvlNode* parent);
	AvlNode* rotateLeft(AvlNode* node);
	AvlNode* rotateRight(AvlNode* node);
	std::vector<AvlNode*> allNodes;
	AvlNode* parent;
};

#endif
