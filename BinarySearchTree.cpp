//Boris Kim's Pointer Based Binary Search Tree.
#include <iostream>
#include <cstdlib>

using namespace std;

//Class Declaration for Binary Search Tree.
class BinarySearchTree
{
	private:
	
	//Copy constructor and assignment operators declared in private.	
	BinarySearchTree(const BinarySearchTree& other) {}
	BinarySearchTree& operator=(const BinarySearchTree& other) {}
	
	//Variable declarations of the root node and size.
	Node* root_;
	unsigned int size_;
	
	
	//private function to get depth of tree. Implemented recursively.
	int getNodeDepth(Node* n) const
	{
		if(n->left == NULL && n->right == NULL)
			return 0;
		else if(n->right == NULL)
			return getNodeDepth(n->left) + 1;
		else if(n->left == NULL)
			return getNodeDepth(n->right) + 1;
		else if(getNodeDepth(n->right) >= getNodeDepth(n->left))
			return getNodeDepth(n->right) + 1;
		else if(getNodeDepth(n->left) > getNodeDepth(n->right))
			return getNodeDepth(n->left) + 1;
	}
	
	public:
	
	typedef int DataType;
	
	//Node object declaration.
	struct Node
	{
		DataType val;  // value of the node
   	 	Node* left;    // left child
    	Node* right;   // right child
    	
		Node(DataType val)
		{
			val = data;
			left = NULL;
			right = NULL;
		}
	};
	
	
	//Default constructor. Initializes tree to size 0 and root pointing to NULL.
	BinarySearchTree()
	{
		root_ = NULL;
		size_ = 0;
	}
	
	//Destructor to prevent memory leaks.
	~BinarySearchTree()
	{
		if(root_ == NULL)
			return;
		while(root_->left != NULL)
			remove(root_->left->val);
		while(root_->right != NULL)
			remove(root_->right->val);
		delete root_;
	}
	
	//Insert mutator.
	bool insert(DataType val)
	{
		//Returns false if value inserted already exists.
		if(exists(val))
			return false;
	
		Node* newNode = new Node(val);
		
		//If tree is empty, assigns new value to root.
		if(size_ == 0)
		{
			root_ = newNode;
			size_++;
			return true;
		}
	
		size_++;
	
		Node* temp = root_;
		
		//Traverses through tree to find the appropriate spot for insertion.
		while(temp->left != NULL || temp->right != NULL)
		{
			if(temp->val > val && temp->left != NULL)
				temp = temp->left;
			else if(temp->val < val && temp->right != NULL)
				temp = temp->right;
			else
				break;
		}
		
		//Compares itself with parent node to see if it goes to the right or left.
		if(temp->val > val)
			temp->left = newNode;
		else
			temp->right = newNode;
	
		return true;
	}
	
	//Remove mutator.
	bool remove(DataType val)
	{
		//Returns false if empty, or the value removed does not exist.
		if(!exists(val) || size_ == 0)
			return false;
	
		Node* deleteNode = root_;
		
		//Remove case where the value removed is the root node.
		if(deleteNode->val == val)
		{
			//Removes root if it is the only node in tree.
			if(size_ == 1)
			{
				delete root_;
				root_ = NULL;
			}
			//If root only has one child, re-assigns new root to the existing child.
			else if(deleteNode->left == NULL || deleteNode->right == NULL)
			{
				if(deleteNode->left == NULL)
					root_ = deleteNode->right;
				else
					root_ = deleteNode->left;
	
				delete deleteNode;
			}
			//If both children exist.
			else
			{
				//Assigns temporary value to the root's right child.
				Node* temp = deleteNode->right;
				
				//If temp's left child does not exist, shifts right child up as the new root.
				if(temp->left == NULL)
				{
					deleteNode->val = temp->val;
					deleteNode->right = temp->right;
	
					delete temp;
				}
				//If temp has a left child, pushes left most leaf up as new root.
				else
				{
					while(temp->left->left != NULL)
						temp = temp->left;
	
					root_->val = temp->left->val;
					delete temp->left;
					temp->left = NULL;
				}
			}
			size_--;
			return true;
		}
		//If the value to be deleted is not the root.
		else
		{
			Node* parent = deleteNode;
	
			bool left;
			
			if(val > parent->val)
				left = false;
			else
				left = true;
			//Searches for the parent node of the node to be deleted.
			while((parent->left != NULL && parent->left->val != val) || (parent->right != NULL && parent->right->val != val))
			{
				if(val > parent->val && parent->right != NULL && val != parent->right->val)
					parent = parent->right;
				else if(val < parent->val && parent->left != NULL && val != parent->left->val)
					parent = parent->left;
				else
					break;
			}
		
		//Determines if the node to be deleted is greater than or less than parent node.
		if(val < parent->val)
		{
			deleteNode = parent->left;
			left = true;
		}
		else
		{
			deleteNode = parent->right;
			left = false;
		}
		
		//If node being deleted is a leaf node, it is just deleted.
		if(deleteNode->left == NULL && deleteNode->right == NULL)
		{
			delete deleteNode;
	
			if(left)
				parent->left = NULL;
			else
				parent->right = NULL;
		}
		//If deleted node has one child, its parent is connected with the child, then deleted.
		else if(deleteNode->left == NULL || deleteNode->right == NULL)
		{
			if(left)
			{
				if(deleteNode->left == NULL)
					parent->left = deleteNode->right;
				else
					parent->left = deleteNode->left;
			}
			else
			{
				if(deleteNode->left == NULL)
					parent->right = deleteNode->right;
				else
					parent->right = deleteNode->left;
			}
			delete deleteNode;
		}
		//If both children exist.
		else
		{
			Node* temp = deleteNode->right;
			
			//If the right child of the deleted node has no subtree, the deleted node is replaced by it's right child.
			if(temp->left == NULL)
			{
				deleteNode->val = temp->val;
				deleteNode->right = temp->right;
	
				delete temp;
			}
			//If the right child has a subtree, the left most leaf of the subtree replaces the deleted node.
			else
			{
				while(temp->left->left != NULL)
					temp = temp->left;
	
				deleteNode->val = temp->left->val;
				delete temp->left;
				temp->left = NULL;
			}
		}
		size_--;
		return true;
		}
	}
	
	//Accessor for finding if a node exists within the tree.
	bool exists(DataType val) const
	{
		if(size_ == 0)
			return false;
	
		Node* temp = root_;
	
		while(temp->left != NULL || temp->right != NULL)
		{
			if(val > temp->val && temp->right != NULL)
				temp = temp->right;
			else if(val < temp->val && temp->left != NULL)
				temp = temp->left;
			else
				break;
		}
	
		if(temp->val == val)
			return true;
		else
			return false;
	}
	
	//Accessor that returns the smallest value in the tree i.e. the left most leaf.
	DataType min() const
	{
		Node* temp = root_;
	
		while(temp->left != NULL)
			temp = temp->left;
	
		return temp->val;
	}
	
	//Accessor that returns the largest value in the tree i.e. the right most leaf.
	DataType max() const
	{
		Node* temp = root_;
	
		while(temp->right != NULL)
			temp = temp->right;
	
		return temp->val;
	}
	
	//Accessor that returns the size of the tree.
	unsigned int size() const
	{
		return size_;
	}
	
	//Accessor that returns the depth of the tree. Calls the private accessor getNodeDepth.
	unsigned int depth() const
	{
		return getNodeDepth(root_);
	}
};
