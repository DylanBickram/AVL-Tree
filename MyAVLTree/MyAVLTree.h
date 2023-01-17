#include <iostream>
#include <vector>
#include <queue>
#include <string>
using namespace std;

/*--------- Insertion function structure is based on the code from the video: https://www.youtube.com/watch?v=BjH_Pdu_2W4,
at time 14:30 -------------------------------------------------------------------------------*/

class MyAVLTree
{
private:
	struct TreeNode
	{
		string name;
		string ufid;
		int balanceFactor;
		TreeNode* left;
		TreeNode* right;

		// Default constructor for node object
		TreeNode()
		{
			ufid = "";
			name = "";
			balanceFactor = 0;
			left = nullptr;
			right = nullptr;
		}

		// Constructor
		TreeNode(string& name, string& id)
		{
			this->ufid = id;
			this->name = name;
			this->balanceFactor = 0;
			this->left = nullptr;
			this->right = nullptr;
		}
	};

	// Recursively deletes every node in the AVL tree
	void recursiveDestroy(TreeNode* node)
	{
		if (node != nullptr)
		{
			recursiveDestroy(node->left);
			recursiveDestroy(node->right);
			delete node;
			node = nullptr;
		}
	}

	/*--------- Insertion function structure is based on the code from the video: https://www.youtube.com/watch?v=BjH_Pdu_2W4,
	at time 14:30 -------------------------------------------------------------------------------*/

	// Insert helper function that inserts student object based on the parameters in the Insert function
	TreeNode* InsertHelper(TreeNode* node, string& name, string& id)
	{
		// If node doesn't point to anything create a new tree node.
		if (node == nullptr)
			return new TreeNode(name, id);

		// If the id less than the ufid of the current node, move down the left subtree
		else if (stoi(id) < stoi(node->ufid))
		{
			// Recursively go down the next left node
			node->left = InsertHelper(node->left, name, id);
		}

		// If id is greater than the ufid of the current node, move down the right subtree
		else
		{
			// Recursively go down the next right node
			node->right = InsertHelper(node->right, name, id);
		}

		return node;
	}

	// Remove helper function that recursively finds the node passed in add removes it from the tree
	TreeNode* RemoveHelper(TreeNode* node, string& id)
	{
		if (node == nullptr)
			return nullptr;
		
		else if (stoi(id) < stoi(node->ufid))
		{
			node->left = RemoveHelper(node->left, id);
			return node; // Nodes will recursively shift upwards after a node is deleted
		}

		else if (stoi(id) > stoi(node->ufid))
		{
			node->right = RemoveHelper(node->right, id);
			return node;
		}

		else
		{
			TreeNode* temp = node;

			// If the node has no children
			if (temp->left == nullptr && temp->right == nullptr)
			{
				node = nullptr; // return nullptr
				return node;
			}
			
			// If the node has a right subtree
			else if (temp->left == nullptr && temp->right != nullptr)
			{
				temp = node->right;
				delete node; 
				node = temp; // Replace parent's child with the deleted node's right child
				return node;
			}

			// If the node has a left subtree
			else if (temp->right == nullptr && temp->left != nullptr)
			{
				temp = node->left;
				delete node;
				node = temp; // Replace the parent's child with the delted node's left child
				return node;
			}

			// If the node has 2 subtrees
			else
			{
				temp = node->right;

				// Assign temp to the left most node in the right subtree
				while (temp->left != nullptr)
				{
					temp = temp->left;

				}

				// Take info from temp and apply it to node
				node->name = temp->name;
				node->ufid = temp->ufid;

				// Go through the right subtree and delete the inorder successor.
				node->right = RemoveHelper(node->right, temp->ufid); 
				return node;
			}
		}

	}

	/*------------------- End of cited code ------------------------------------------*/

	// A helper function that determines whether the inputted string is a number or not
	bool isNumber(const string& str)
	{
		for (char item : str)
		{
			// If any character is not a digit, return false
			if (isdigit(item) == 0)
				return false;
		}

		// Otherwise return true
		return true;
	}
	
	// A helper function that determines whehter the inputeed string is an appropriate name
	bool isName(const string& str)
	{
		for (char item : str)
		{
			// If the item not between ASCII values of a-z, A-Z, or a whitespace, return false
			if ((97 > item || item > 122) && (65 > item || item > 90) && item != 32)
				return false;
		}

		// Otherwise return true
		return true;

	}
	/*---------- The height function's structure is from the module 5.1a stepik solution by Lisha Zhou ----------*/

	// A helper function that finds the height of a given node
	int height(TreeNode* node)
	{
		// If root is null, set height = 0
		if (node == nullptr)
			return 0;

		// If the node is a leaf, return 1
		else if (node->left == nullptr && node->right == nullptr)
			return 1;

		// Otherwise recurisvely find the largest height for the given node
		else 
			return 1 + max(height(node->left), height(node->right));

	}
	/*--------------------------- End of cited code ---------------------------------------------------*/

	// A helper function that returns integer value of the balance factor of a given node
	void balanceFactor(TreeNode* node)
	{
		if (node == nullptr)
			return;

		// Return the difference of the heights of the subtrees
		else
		{
			node->balanceFactor = height(node->left) - height(node->right);

			// Find the balanceFactors of the subtrees
			balanceFactor(node->left);
			balanceFactor(node->right);
		}
	}

	// A helper function that balances the tree
	TreeNode* balance(TreeNode* node)
	{

		// If the absolute value of the balance factor is greater than 1, it needs to be balanced
		if (abs(node->balanceFactor) > 1)
		{
			// If the node is right heavy continue
			if (node->balanceFactor == -2)
			{
				// If right subtree is left heavy rotate right left
				if (node->right->balanceFactor == 1)
				{
					node = rotateRightLeft(node);
					balanceFactor(node); ///After rotation update balanceFactor
				}

				// Otherwise rotate to the left
				else
				{
					node = rotateLeft(node);
					balanceFactor(node);
				}
			}

			// If the node is left heavy
			else if (node->balanceFactor == 2)
			{
				// If left subtree is right heavy rotate left right
				if (node->left->balanceFactor == -1)
				{
					node = rotateLeftRight(node);
					balanceFactor(node);
				}

				// Otherwise rotate the node to the right
				else
				{
					node = rotateRight(node);
					balanceFactor(node);
				}
			}
		}

		return node;
	}

	// Helper function that searches for a id in the AVL Tree
	TreeNode* search(TreeNode* node, string id)
	{
		if (node == nullptr)
			return nullptr;

		else if (stoi(id) < stoi(node->ufid))
			return search(node->left, id);

		else if (stoi(id) > stoi(node->ufid))
			return search(node->right, id);

		else
			return node;
	}



	/*========= Rotations ===========*/

/*------ Citing the left rotation function based on balanced trees slides (slide 12)
written by Amanpreet Kapoor: file:///C:/Users/dbick/Downloads/4%20-%20Balanced%20Trees.pdf ------*/

// Function rotates a given node to the left and returns the new parent node
	TreeNode* rotateLeft(TreeNode* node)
	{
		TreeNode* grandchild = node->right->left;
		TreeNode* newParent = node->right;

		//The new parent is rotated, the old node becomes the left node of new parent
		newParent->left = node;
		node->right = grandchild;
		return newParent;
	}

	/*------------------------------- End of cited code ---------------------------------------------*/

	// Function rotates a given node to the right and returns the new parent node
	TreeNode* rotateRight(TreeNode* node)
	{
		TreeNode* grandchild = node->left->right;
		TreeNode* newParent = node->left;

		//The new parent is rotate, the old node becomes becomes the right of new parent
		newParent->right = node;
		node->left = grandchild;
		return newParent;
	}

	// Function rotates a given node's left node left and the given node to the right
	TreeNode* rotateLeftRight(TreeNode* node)
	{
		node->left = rotateLeft(node->left);
		return rotateRight(node);
	}

	// Function rotates a given node's right node right and the given node to the left
	TreeNode* rotateRightLeft(TreeNode* node)
	{
		node->right = rotateRight(node->right);
		return rotateLeft(node);
	}

	/*======== Depth First Traversals ===============*/

	/*---- The following code is cited from 5.1c balanced trees stepik problem solution by Lisha Zhou ----*/

	vector<TreeNode*> inorder()
	{
		vector<TreeNode*> nodes;
		inorderTraversal(root, nodes);
		return nodes;
	}

	// Function creates a vector of nodes in inorder traversal
	void inorderTraversal(TreeNode* node, vector<TreeNode*>& nodes)
	{
		if (node == nullptr)
			return;

		inorderTraversal(node->left, nodes);
		nodes.push_back(node);
		inorderTraversal(node->right, nodes);
	}

	/*------------------------------------ End of cited code -------------------------------------------------*/

	// Function creates a vector of nodes in preorder traversal
	void preOrder(TreeNode* node, vector<TreeNode*>& nodes)
	{
		if (node == nullptr)
			return;

		nodes.push_back(node);
		preOrder(node->left, nodes);
		preOrder(node->right, nodes);
	}

	// Functions creates a vector nodes in postorder traversal
	void Postorder(TreeNode* node, vector<TreeNode*>& nodes)
	{

		if (node == nullptr)
			return;

		Postorder(node->left, nodes);
		Postorder(node->right, nodes);
		nodes.push_back(node);
	}

public:

	TreeNode* root;

	// Constructor
	MyAVLTree()
	{
		root = nullptr;
	}

	// Destructor
	~MyAVLTree()
	{
		recursiveDestroy(root);
	}

	/*--------- Insertion function structure is based on the code from the video: https://www.youtube.com/watch?v=BjH_Pdu_2W4,
	at time 14:30 -------------------------------------------------------------------------------*/

	// Function inserts nodes into the AVL Tree
	void insert(string name, string ufid)
	{
		// If ufid is not a real number, ufid is not 8 digits long, or the name is not valid, print unsucessful and end function
		if (!isNumber(ufid) || ufid.length() != 8 || !isName(name))
		{
			cout << "unsuccessful" << endl;
			return;
		}

		TreeNode* inputNode = search(root, ufid); // Assign node to the searched id

		// If the node points to an id print unsuccessful
		if (inputNode != nullptr)
			cout << "unsuccessful" << endl;

		// Otherwise continue insertion
		else
		{
			// Execute InsertHelper function to insert the node into the AVL tree
			root = InsertHelper(root, name, ufid);

			// Determine the balance factor of the given node as well as its immediate children
		    balanceFactor(root);

			// Determine if the tree is balanced at the inserted node, if not rotate nodes and update balance factors
		    root = balance(root);
			cout << "successful" << endl;
			
		}

	}

	void remove(string ufid)
	{
		// If ufid is not a real number, ufid is not 8 digits long, or the name is not valid, print unsucessful and end function
		if (!isNumber(ufid) || ufid.length() != 8)
		{
			cout << "unsuccessful" << endl;
			return;
		}

		TreeNode* inputNode = search(root, ufid); // Assign node to the searched id

		// If the node doesn't point to an id print unsuccessful
		if (inputNode == nullptr)
			cout << "unsuccessful" << endl;

		// Otherwise continue removal
		else
		{
			// Execute RemoveHelper function to removethe node the AVL tree
			root = RemoveHelper(root, ufid);
			cout << "successful" << endl;
			
		}
	}

	// Remove node at N in the inorder traversal
	void removeInorder(int N)
	{
		vector<TreeNode*> nodes;
		nodes = inorder(); // Assign nodes to inorder vector of the AVL tree nodes

		// If N is outside the size of nodes return unsuccessful
		if (N > nodes.size() || N < 0)
		{
			cout << "unsuccessful" << endl;
			return;
		}

		// Otherwise call remove function on the ufid at N.
		else
		{
			remove(nodes[N]->ufid);
		}

	}

	// Funcation that searches for the matching ID in the AVL tree
	void searchId(string id)
	{
		// If ufid is not a real number, ufid is not 8 digits long, or the name is not valid, print unsucessful and end function
		if (!isNumber(id) || id.length() != 8)
		{
			cout << "unsuccessful" << endl;
			return;
		}
		TreeNode* searchedNode = search(root, id);

		// If the id is found print the name
		if (searchedNode != nullptr)
			cout << searchedNode->name << endl;

		// Otherwise print unsuccessful
		else 
			cout << "unsuccessful" << endl;
	
	}

	// Function that searches for the matching names in the AVL tree
	void searchName(string name)
	{
		// If the name is not valid, print unsucessful and end function
		if (!isName(name))
		{
			cout << "unsuccessful" << endl;
			return;
		}

		int count = 0;
		vector<TreeNode*> matchingNames;
		preOrder(root, matchingNames); // Call private preOrder function

		for (unsigned int i = 0; i < matchingNames.size(); i++)
		{
			// If the name held by the node at index i is the same as the parameter print the ufid
			if (matchingNames[i]->name.compare(name) == 0)
			{
				cout << matchingNames[i]->ufid << endl;
				count++;
			}
		}

		// If the number of matching names is 0 print unsuccessful
		if (count == 0)
			cout << "unsuccessful" << endl;

	
	}
	/*------------------------------------- End of cited code  ---------------------------------------------*/

	//Prints names inorder
	void printInorder()
	{
		vector<TreeNode*> nodes = inorder(); // call function to return inorder vector

		for (unsigned int i = 0; i < (nodes.size() - 1); i++)
		{
				cout << nodes[i]->name << ", ";
		}
		int index = nodes.size() - 1;

		cout << nodes[index]->name << endl;
	}

	// Prints names in preorder
	void printPreorder()
	{
		vector<TreeNode*> nodes;
		preOrder(root, nodes); // call function to return preorder vector

		for (unsigned int i = 0; i < (nodes.size() - 1); i++)
		{
				cout << nodes[i]->name << ", ";
		}

		int index = nodes.size() - 1;
		cout << nodes[index]->name << endl;

		
		
	}

	// Prints names in postorder
	void printPostorder()
	{
		vector<TreeNode*> nodes;
		Postorder(root, nodes);  //call function to return postorder vector

		for (unsigned int i = 0; (i < nodes.size() - 1); i++)
		{
			cout << nodes[i]->name << ", ";
		}

		int index = nodes.size() - 1;
		cout << nodes[index]->name << endl;
	}


	/*------------ The following code is structured from the quiz 4 solution 
	from discussion 5 slides (slide 55) https://ufl.instructure.com/courses/460732/files/72014240?wrap=1 ----------------*/

	// Function prints the amount of levels in the AVL tree
	void printLevelCount()
	{
		queue<TreeNode*> q;
		int count = 0;

		if (root != nullptr)
		{
			// Push left child onto the queue
			if (root->left != nullptr)
				q.push(root->left);

			// Push right child onto the queue
			if (root->right != nullptr)
				q.push(root->right);

			count++;

		}

		// if root == nullptr return the count
		else
		{
			cout << count << endl;
			return;
		}

		while (!q.empty())
		{
			int levelSize = q.size();

			// Every completion of the for loop counts as one level
			for (int i = 0; i < levelSize; i++)
			{
				if (q.front()->left != nullptr)
					q.push(q.front()->left);

				if (q.front()->right != nullptr)
					q.push(q.front()->right);

				// Pop parents
				q.pop();
			}

			// Level count increases
			count++;

		}

		// Print level count
		cout << count << endl;

	}

	/*------------------------- End of cited code -----------------------------------------------*/

};

