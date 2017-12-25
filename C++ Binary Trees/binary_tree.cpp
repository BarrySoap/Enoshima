#include "binary_tree.h"
#include <iostream>

void createEmpty(node **tree)
{
	// Make sure a tree hasn't been initialised
	if (*tree == nullptr)
	{
		*tree = new node;
		(*tree)->left = nullptr;
		(*tree)->right = nullptr;
	}
	// Initialise the root node with a left/right branch without values
}

// Creates an empty binary tree
binary_tree::binary_tree()
{
	node *tree;
	createEmpty(&tree);	// Initialise and create the tree using a reference
}

void insertEmpty(node **tree, int value)
{
	// Make sure a tree hasn't been initialised
	if (*tree == nullptr)
	{
		*tree = new node;
		(*tree)->data = value;
		(*tree)->left = nullptr;
		(*tree)->right = nullptr;
	}
	// Initialise the root node WITH a value, as well as branches with no values
}

void additionTest(node **tree, int value)
{
	if (*tree == nullptr)
	{
		*tree = new node;
		(*tree)->data = value;
		(*tree)->left = nullptr;
		(*tree)->right = nullptr;
	}
	else {
		if (value < (*tree)->data)
		{
			additionTest(&(*tree)->left, value);	// If the given value is less than the root node, recursively check again with a reference to the left branch

		}
		else if (value >(*tree)->data)
		{
			additionTest(&(*tree)->right, value);	// If the given value is greater than the root node, recursively check again with a reference to the right branch
		}
	}
}

// Creates a binary tree with an initial value to store
binary_tree::binary_tree(int value)
{
	insertEmpty(&tree, value);						 // Do the same as createEmpty, except with a value
}

// Creates a binary tree from a collection of existing values
binary_tree::binary_tree(const std::vector<int> &values)
{
	for (int i = 0; i < values.size(); ++i)			// For the amount of values given,
	{
		additionTest(&tree, values[i]);				// Cycle through each value and add them to the tree the same way values are given normally
	}
}

void copyHelper(node *tree, node *&tree2)
{
	if (tree != nullptr) {							// If a tree has been initialised
		tree2 = new node;							// Create a new tree,
		(tree2)->data = (tree)->data;				// Copy the value of tree1's root node
		(tree2)->left = nullptr;
		(tree2)->right = nullptr;
		copyHelper((tree)->left, (tree2)->left);	// Recursively copy the left side until there aren't any other left branches
		copyHelper((tree)->right, (tree2)->right);	// Recursively copy the right side until there aren't any other right branches
	}
}

// Creates a binary tree by copying an existing tree
binary_tree::binary_tree(const binary_tree &rhs)
{
	copyHelper(rhs.tree, this->tree);	// Call on the helper, using the given tree and our tree in the binary_tree class (hence 'this->')
}

void delete_tree(node *tree)
{
	if (tree == nullptr) {
		return;						// If a tree isn't initialised, there is nothing to delete
	}
	delete_tree((*tree).left);		// Recursively delete the left side
	delete_tree((*tree).right);		// Recursively delete the right side
	delete tree;					// Delete the root node,
	tree = nullptr;					// and set it to nullptr as good practice
}


// Destroys (cleans up) the tree
binary_tree::~binary_tree()
{
	delete_tree(tree);
}

// Adds a value to the tree
void binary_tree::insert(int value)
{
	additionTest(&tree, value);
}

void removeHelper2(node *tree, node *rightTree)
{
	if (tree != nullptr) {								// If a tree exists,
		if (tree->right != nullptr) {					// and if a right branch exists,
			removeHelper2(tree->right, rightTree);		// recursively check the right side
		}
		else {
			tree->right = rightTree; 
		}
	}
}

void removeHelper(node *&tree, int value)
{
	if (tree != nullptr) {							// If a tree has been initialised
		if (value == (tree)->data) {				// and if the current node matches the given value to be removed
			(tree)->data = NULL;					// replace it with NULL
			node *righttemp;						
			node *lefttemp;							// Create two temporary left/right branches
			lefttemp = (tree)->left;
			righttemp = (tree)->right;				// Add the values of the current node's left/right branches respectively to lefttemp/righttemp
			delete tree;							// Delete the current node
			tree = lefttemp;
			removeHelper2(tree, righttemp);			// After moving the tree upwards, call the second helper to move righttemp to the right side of the deleted node
		}
		else if (value > (tree)->data) {
			removeHelper(tree->right, value);		// If the value is greater than the current node, recursively check the right side until it is found
		}
		else if (value < (tree)->data) {
			removeHelper(tree->left, value);		// If the value is less than the current node, recursively check the left side until it is found
		}
	}
}

// Removes a value from the tree
void binary_tree::remove(int value)
{
	removeHelper(tree, value);
}

bool existCheck(node *tree, int value)
{
	if (tree != nullptr) {
		if (value == (tree)->data) {					// Simply check that if the current node matches the given value, the value must exist
			return true;
		}
		else if (value > (tree)->data) {				// If the value is greater than the current node,
			if (existCheck((tree)->right, value)) {		// recursively check the right side until the value matches the current node
				return true;
			}
		}
		else if (value < (tree)->data) {				// If the value is less than the current node,
			if (existCheck((tree)->left, value)) {		// recursively check the left side until the value matches the current node
				return true;
			}
		}
	}
	else {
		return false;									// If the value doesn't exist in the tree, return false
	}
}

// Checks if a value is in the tree
bool binary_tree::exists(int value) const
{
	return existCheck(tree, value);
}

void inorderTest(node *tree, std::string &temp)
{
	if (tree != nullptr)
	{
		inorderTest((*tree).left, temp);				// Recursively sort the left side in order
		temp += std::to_string((*tree).data) + " ";		// Add a space to the end of each given value (after sorting)
		inorderTest((*tree).right, temp);				// Recursively sort the right side in order
	}
}

void preorderTest(node *tree, std::string &temp)
{
	if (tree != nullptr)
	{
		temp += std::to_string((*tree).data) + " ";
		preorderTest((*tree).left, temp);				// Do the same as inorder, but sort the tree before finalising the values
		preorderTest((*tree).right, temp);
	}
}

void postorderTest(node *tree, std::string &temp)
{
	if (tree != nullptr)
	{
		postorderTest((*tree).left, temp);
		postorderTest((*tree).right, temp);				// Do the same as inorder, but sort the tree after finalising the values
		temp += std::to_string((*tree).data) + " ";
	}
}

// Prints the tree to standard out in numerical order
std::string binary_tree::inorder() const
{
	std::string temp = std::string("");
	inorderTest(tree, temp);
	return temp.substr(0, temp.length() - 1);			// Return the values from the first element to the length of the string - 1 (to account for the white space at the end)
}

// Prints the tree in pre-order
std::string binary_tree::preorder() const
{
	std::string temp = std::string("");
	preorderTest(tree, temp);
	return temp.substr(0, temp.length() - 1);			// Return the values from the first element to the length of the string - 1 (to account for the white space at the end)
}

// Prints the tree in post-order
std::string binary_tree::postorder() const
{
	std::string temp = std::string("");
	postorderTest(tree, temp);
	return temp.substr(0, temp.length() - 1);			// Return the values from the first element to the length of the string - 1 (to account for the white space at the end)
}

// Copy assignment operator
binary_tree& binary_tree::operator=(const binary_tree &other)
{
    return binary_tree();
}

// Checks if two trees are equal
bool binary_tree::operator==(const binary_tree &other) const
{
	return true;
}

// Checks if two trees are not equal
bool binary_tree::operator!=(const binary_tree &other) const
{
    return true;
}

// Inserts a new value into the binary tree
binary_tree& binary_tree::operator+(int value)
{
	this->insert(value);								// Call on the insert function within the binary_tree class
    return binary_tree();
}

// Removes a value from the binary tree
binary_tree& binary_tree::operator-(int value)
{
	this->remove(value);								// Call on the remove function within the binary_tree class
    return binary_tree();
}

// Reads in values from an input stream into the tree
std::istream& operator>>(std::istream &in, binary_tree &value)
{
	int temp;
	while (in >> temp) {								// While values are being read in (until there are none left),
		value.insert(temp);								// insert them into the tree as normal
	}
    return in;
}

// Writes the values, in-order, to an output stream
std::ostream& operator<<(std::ostream &out, const binary_tree &value)
{
	out << value.inorder();
    return out;
}