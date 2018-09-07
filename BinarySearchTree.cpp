#include <iostream>
#include <cstdlib>

using namespace std;

class BinarySearchTree
{
	private:
		
	BinarySearchTree(const BinarySearchTree& other) {}
	BinarySearchTree& operator=(const BinarySearchTree& other) {}
	
	Node* root_;
	unsigned int size_;
		
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
		
	BinarySearchTree()
	{
		root_ = NULL;
		size_ = 0;
	}
	
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
	
	bool insert(DataType val)
	{
		if(exists(val))
			return false;
	
		Node* newNode = new Node(val);
	
		if(size_ == 0)
		{
			root_ = newNode;
			size_++;
			return true;
		}
	
		size_++;
	
		Node* temp = root_;
	
		while(temp->left != NULL || temp->right != NULL)
		{
			if(temp->val > val && temp->left != NULL)
				temp = temp->left;
			else if(temp->val < val && temp->right != NULL)
				temp = temp->right;
			else
				break;
		}
	
		if(temp->val > val)
			temp->left = newNode;
		else
			temp->right = newNode;
	
		return true;
	}
	
	bool remove(DataType val)
	{
		if(!exists(val) || size_ == 0)
			return false;
	
		Node* deleteNode = root_;
	
		if(deleteNode->val == val)
		{
			if(size_ == 1)
			{
				delete root_;
				root_ = NULL;
			}
			else if(deleteNode->left == NULL || deleteNode->right == NULL)
			{
				if(deleteNode->left == NULL)
					root_ = deleteNode->right;
				else
					root_ = deleteNode->left;
	
				delete deleteNode;
			}
			else
			{
				Node* temp = deleteNode->right;
	
				if(temp->left == NULL)
				{
					deleteNode->val = temp->val;
					deleteNode->right = temp->right;
	
					delete temp;
				}
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
		else
		{
			Node* parent = deleteNode;
	
			bool left;
	
			if(val > parent->val)
				left = false;
			else
				left = true;
	
			while((parent->left != NULL && parent->left->val != val) || (parent->right != NULL && parent->right->val != val))
			{
				if(val > parent->val && parent->right != NULL && val != parent->right->val)
					parent = parent->right;
				else if(val < parent->val && parent->left != NULL && val != parent->left->val)
					parent = parent->left;
				else
					break;
			}
	
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
	
		if(deleteNode->left == NULL && deleteNode->right == NULL)
		{
			delete deleteNode;
	
			if(left)
				parent->left = NULL;
			else
				parent->right = NULL;
		}
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
		else
		{
			Node* temp = deleteNode->right;
	
			if(temp->left == NULL)
			{
				deleteNode->val = temp->val;
				deleteNode->right = temp->right;
	
				delete temp;
			}
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
	
	DataType min() const
	{
		Node* temp = root_;
	
		while(temp->left != NULL)
			temp = temp->left;
	
		return temp->val;
	}
	
	DataType max() const
	{
		Node* temp = root_;
	
		while(temp->right != NULL)
			temp = temp->right;
	
		return temp->val;
	}
	
	unsigned int size() const
	{
		return size_;
	}
	
	unsigned int depth() const
	{
		return getNodeDepth(root_);
	}
	
	void print() const
	{
	}
};
