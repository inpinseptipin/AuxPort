#include "AuxAVL.h"

AvlTree::AvlTree(int value)
{
	allNodes.push_back(new AvlNode);
	parent = allNodes[allNodes.size() - 1];
	parent->height = 0;
	parent->left = nullptr;
	parent->right = nullptr;
	parent->val = value;
}


void AvlTree::add(int value)
{
	insert(parent, value);
	masterComputeHeight(parent, parent->height);
}

AvlNode* AvlTree::insert(AvlNode* current,int value)
{
	AuxAssert(current->val != value,"Duplicate Nodes not supported");
	if (value < current->val)
	{
		if (current->left != nullptr)
		{
			current->left = insert(current->left, value);
			masterComputeHeight(current->left, current->height);
			isBalanced(current) ? AuxPort::Logger::Log("Balanced") : AuxPort::Logger::Log("Unbalanced");
			if (!isBalanced(current))
				current = rotateRight(current);
		}	
		else
		{
			AvlNode avlNode;
			allNodes.push_back(new AvlNode);
			auto newNode = allNodes[allNodes.size() - 1];
			newNode->left = nullptr;
			newNode->right = nullptr;
			newNode->val = value;
			newNode->height = 0;
			current->left = newNode;
		}
		
	
	}
	if (value > current->val)
	{
		if (current->right != nullptr)
		{
			current->right = insert(current->right, value);
			masterComputeHeight(current->right, current->height);
			isBalanced(current) ? AuxPort::Logger::Log("Balanced") : AuxPort::Logger::Log("Unbalanced");
			if (!isBalanced(current))
				current = rotateLeft(current);
		}
		else
		{
			AvlNode avlNode;
			allNodes.push_back(new AvlNode);
			auto newNode = allNodes[allNodes.size() - 1];
			newNode->left = nullptr;
			newNode->right = nullptr;
			newNode->val = value;
			newNode->height = 0;
			current->right = newNode;
		}
	}
	return current;


}

int AvlTree::leftHeight(AvlNode* curr, int height)
{
	if (curr->left != nullptr)
	{
		height = leftHeight(curr->left, height+1);
	}
	return height;

}

int AvlTree::rightHeight(AvlNode* curr,int height)
{
	if (curr->right != nullptr)
	{
		height = rightHeight(curr->right,height+1);
	}
	return height;
}

int AvlTree::masterComputeHeight(AvlNode* parent, int height)
{
	auto leftHeightVal = leftHeight(parent, 0);
	auto rightHeightVal = rightHeight(parent, 0);
	if (leftHeightVal > rightHeightVal)
		parent->height = leftHeightVal;
	else
		parent->height = rightHeightVal;
	return parent->height;
}

int AvlTree::isBalanced(AvlNode* parent)
{
	auto leftHeightVal = leftHeight(parent, 0);
	auto rightHeightVal = rightHeight(parent, 0);
	if (abs(leftHeightVal - rightHeightVal) > 1)
		return false;
	return true;
}

//AvlNode* AvlTree::rotateLeft(AvlNode* node)
//{
//	auto currentParent = node;
//	auto currentParentLeftChild = node->left;
//	auto currentParentRightChild = node->right;
//	auto currentRightChildLeftChild = node->right->left;
//	auto currentRightChildRightChild = node->right->right;
//
//
//// Create new nodes
//	std::unique_ptr<AvlNode> newNodeParent;
//	std::unique_ptr<AvlNode> newNodeParentRightChild;
//
//// Instantiate new nodes
//	newNodeParent.reset(currentParent);
//	newNodeParentRightChild.reset(currentParentRightChild);
//
//	newNodeParent->left = currentParentLeftChild;
//	newNodeParent->right = currentParentRightChild;
//	newNodeParentRightChild->left = node->right->left;
//	newNodeParentRightChild->right = node->right->right;
//
//// Swap Children
//	newNodeParent->right = currentRightChildLeftChild;
//	newNodeParentRightChild->left = newNodeParent.get();
//
//
//
//// Swap Values
//	currentParent->left = newNodeParentRightChild->left;
//	currentParent->right = newNodeParentRightChild->right;
//	currentParent->val = newNodeParentRightChild->val;
//	currentParent->height = newNodeParentRightChild->height;
//
//	currentParentRightChild->left = newNodeParent->left;
//	currentParentRightChild->right = newNodeParent->right;
//	currentParentRightChild->height = newNodeParent->height;
//	currentParentRightChild->val = newNodeParent->val;
//	
//// Auto Deletes temporary nodes
//	return currentParent;
//	
//}

AvlNode* AvlTree::rotateRight(AvlNode* node)
{
	AvlNode *A = node->left->left;
	AvlNode *B = node->left;
	AvlNode *C = node->left->right;
	AvlNode *D = node;
	AvlNode *E = node->right;

	B->right = D;
	D->left = C;
	return B;
}

AvlNode* AvlTree::rotateLeft(AvlNode* node)
{
	AvlNode* A = node->left;
	AvlNode* B = node;
	AvlNode* C = node->right->left;
	AvlNode* D = node->right;
	AvlNode* E = node->right->right;

	B->right = C;
	D->left = B;
	return D;
}

/*
AvlNode* AvlTree::rotateRight(AvlNode* node)
{

	auto currentParent = node;
	auto currentParentLeftChild = node->left;
	auto currentParentRightChild = node->right;
	auto currentLeftChildLeftChild = node->left->left;
	auto currentLeftChildRightChild = node->left->right;



	// Create new nodes
	std::unique_ptr<AvlNode> newNodeParent;
	std::unique_ptr<AvlNode> newNodeParentLeftChild;

	// Instantiate new nodes
	newNodeParent.reset(currentParent);
	newNodeParentLeftChild.reset(currentParentLeftChild);
	
	newNodeParent->left = currentParentLeftChild;
	newNodeParent->right = currentParentRightChild;
	newNodeParentLeftChild->left = node->left->left;
	newNodeParentLeftChild->right = node->left->right;

	// Swap Children

	newNodeParent->left = currentLeftChildRightChild;
	newNodeParentLeftChild->right = newNodeParent.get();


	// Swap Values
	currentParent->left = newNodeParentLeftChild->left;
	currentParent->right = newNodeParentLeftChild->right;
	currentParent->val = newNodeParentLeftChild->val;
	currentParent->height = newNodeParentLeftChild->height;

	currentParentLeftChild->left = newNodeParent->left;
	currentParentLeftChild->right = newNodeParent->right;
	currentParentLeftChild->height = newNodeParent->height;
	currentParentLeftChild->val = newNodeParent->val;


	// Auto Deletes temporary nodes

	return currentParent;

}
*/


