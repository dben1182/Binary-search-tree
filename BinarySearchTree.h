#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H
#include "BSTInterface.h"
#include <sstream>
#include <ostream>

using std::string;

template<typename T>
class BinarySearchTree : BSTInterface<T>
{
private://private data members
	struct Node
	{
		T data = T();
		Node* left = nullptr;
		Node* right = nullptr;
	};
	Node* root;

public://public functions

	BinarySearchTree()
	{
		root = nullptr;
	}
	~BinarySearchTree()
	{
		removeWholeTree();
	}
	bool addNode(const T& data)
	{
		return addNodePrivate(root, data);//calls the add node private function, which begins at the root
	}
	bool removeNode(const T& data)
	{
		return removeNodePrivate(root, data);
	}
	bool clearTree()//returns whether the root points to an node object, and thus the tree is clear or not
	{
		if (root == nullptr)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	std::string toString() const
	{
		std::ostringstream out;
		if (root == nullptr)
		{
			out << " empty";//outputs empty if the tree is empty
		}
		else
		{
			int level = 0;
			do
			{
				out << std::endl << "  " << ++level << ":";
			} while (outLevel(root, level, out));//outputs each level to the output
		}
		return out.str();
	}
	bool find(const T& data) const//public find function
	{
		return findPrivate(root, data);//calls find private function starting with the root
	}
	void removeWholeTree()//helper function removes whole tree
	{
		removeSubtree(root);
		root = nullptr;
	}
	int size()
	{
		return getSizePrivate(root);
	}

private://private functions
	Node* createLeaf(const T& data)
	{
		Node* nodePtr = new Node;
		nodePtr->data = data;
		return nodePtr;
	}
	bool findPrivate(const Node* nodePtr, const T& data) const
	{
		if (nodePtr == nullptr)
		{
			return false;
		}
		else if (data == nodePtr->data)
		{
			return true;
		}
		else if (data < nodePtr->data)//case data less than node data
		{
			return findPrivate(nodePtr->left, data);//recursively calls find function for left subtree
		}
		else if (data > nodePtr->data)//case data greater than node data
		{
			return findPrivate(nodePtr->right, data);//recursively calls find function for the right subtree
		}
	}
	bool addNodePrivate(Node* nodePtr, const T& data)//adds node to tree.
	{
		if (root == nullptr)//case root is null
		{
			root = createLeaf(data);
		}
		else if (data == nodePtr->data)//case already added
		{
			return false;
		}
		else if (data < nodePtr->data)//case left
		{
			if (nodePtr->left != nullptr)
			{
				return addNodePrivate(nodePtr->left, data);
			}
			else
			{
				nodePtr->left = createLeaf(data);
				return true;
			}
		}
		else if (data > nodePtr->data)//case right
		{
			if (nodePtr->right != nullptr)
			{
				return addNodePrivate(nodePtr->right, data);
			}
			else
			{
				nodePtr->right = createLeaf(data);
				return true;
			}
		}
	}
	void removeSubtree(Node* nodePtr)// helper function for remove whole tree and deconstructor
	{
		if (nodePtr != nullptr)
		{
			if (nodePtr->left != nullptr)
			{
				removeSubtree(nodePtr->left);//recursively calls the function for left subtree
			}
			if (nodePtr->right != nullptr)
			{
				removeSubtree(nodePtr->right);//recursively calls the function for the right subtree
			}
			delete nodePtr;
		}
	}
	bool outLevel(Node* root, int level, std::ostringstream& out) const
	{
		if (root == nullptr)
		{
			return false;
		}
		if (level == 1)
		{
			out << " " << root->data;
			if ((root->left != nullptr) || (root->right != nullptr))
			{
				return true;
			}
			return false;
		}
		if ((level == 2) && (!root->left) && (root->right))
		{
			out << " _";
		}
		bool left = outLevel(root->left, level - 1, out);
		bool right = outLevel(root->right, level - 1, out);
		if ((level == 2) && (root->left) && (!root->right))
		{
			out << " _";
		}
		return left || right;
	}//traverses a level
	bool removeNodePrivate(Node* parent, const T& data)
	{
		if (!clearTree())//code executes only if the tree is filled with objects in the first place
		{
			if (data == root->data)//case root
			{
				return removeRootMatch();//calls helper function for the root only
			}
			else
			{
				if (data < parent->data && parent->left != nullptr)//case left
				{
					if (parent->left->data == data)
					{
						return removeMatch(parent, parent->left, true);//case the function finds the data
					}
					else 
					{
						return removeNodePrivate(parent->left, data);//recursive call of self
					}
				}
				else if (data > parent->data && parent->right != nullptr)//case right
				{
					if (parent->right->data == data)
					{
						return removeMatch(parent, parent->right, false);//case calls helper function
					}
					else
					{
						return removeNodePrivate(parent->right, data);//case recursive call of self
					}
				}
				else
				{
					return false;//case could not find data returns false
				}

			}
		}
		else
		{
			return false;//returns false if the tree is empty
		}
	}
	bool removeRootMatch()//helper function for removing root of whole tree
	{
		if (root != nullptr)
		{
			Node* nodeToDelete = root;
			T rootData = root->data;
			T predecessor;
			if (root->left == nullptr && root->right == nullptr)//case root has no children
			{
				root = nullptr;
				delete nodeToDelete;
				return true;
			}
			else if (root->left == nullptr && root->right != nullptr)//case root has right child, but no left child
			{
				root = root->right;
				nodeToDelete->right = nullptr;
				delete nodeToDelete;
				return true;
			}
			else if (root->left != nullptr && root->right == nullptr)//case root has left child but no right child
			{
				root = root->left;
				nodeToDelete->left = nullptr;
				delete nodeToDelete;
				return true;
			}
			else//case root has two children
			{
				predecessor = findLargestPrivate(root->left);
				bool wasRemoved = removeNodePrivate(root, predecessor);
				root->data = predecessor;
				return wasRemoved;
			}
		}
		else
		{
			return false;
		}
	}
	bool removeMatch(Node* parent, Node* match, bool left)
	{
		if (!clearTree())
		{
			Node* nodeToDelete;
			T matchData = match->data;
			T predecessor;

			if (match->left == nullptr && match->right == nullptr)//case no children
			{
				nodeToDelete = match;
				if (left)
				{
					parent->left = nullptr;//sets left node to nullptr
				}
				else
				{
					parent->right = nullptr;//sets right node to nullptr
				}
				delete nodeToDelete;
				return true;
			}
			else if (match->left == nullptr && match->right != nullptr)//case only one child which is to the right
			{
				if (left)
				{
					parent->left = match->right;
				}
				else
				{
					parent->right = match->right;
				}
				match->right = nullptr;
				nodeToDelete = match;
				delete nodeToDelete;
				return true;
			}
			else if (match->left != nullptr && match->right == nullptr)//case only one child, which is to the left
			{
				if (left)
				{
					parent->left = match->left;
				}
				else
				{
					parent->right = match->left;
				}
				match->left = nullptr;
				nodeToDelete = match;
				delete nodeToDelete;
				return true;
			}
			else//case matching node has two children
			{
				predecessor = findLargestPrivate(match->left);
				bool wasRemoved = removeNodePrivate(match, predecessor);
				match->data = predecessor;
				return wasRemoved;
			}
		}
		else
		{
			return false;
		}
	}

	

	T& findLargestPrivate(Node* nodePtr)//finds largest value for a given subtree. called to find predecessor
	{
		if (nodePtr->right != nullptr)
		{
			return findLargestPrivate(nodePtr->right);//recursive call
		}
		else
		{
			return nodePtr->data;
		}
	}
	int getSizePrivate(Node* nodePtr)//gets size by recursive calls and returning size of subtree
	{
		int subtreeSize = 0;
		if (root == nullptr)//case input pointer was nullptr, which was a null child of a parent node, and thus returns 0
		{
			return subtreeSize;//returns the value 0
		}
		else
		{
			subtreeSize++;//increments return value by 1
			if (nodePtr->left != nullptr)//if the node has a left child, recursive call of left child's subtree is called
			{
				subtreeSize += getSizePrivate(nodePtr->left);//num items in left subtree added to tree
			}
			if (nodePtr->right != nullptr)//case node has left child
			{
				subtreeSize += getSizePrivate(nodePtr->right);//num items in right subtree added to tree
			}
			return subtreeSize;//returns size of subtree
		}
	}

};
#endif