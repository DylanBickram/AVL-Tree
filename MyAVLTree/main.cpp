#include <iostream>
#include <sstream>
#include <string>
#include "MyAVLTree.h"
using namespace std;


/* Note: 
	1. You will have to comment main() when unit testing your code because catch uses its own main().
	2. You will submit this main.cpp file and any header files you have on Gradescope. 
*/

int main(){

	MyAVLTree tree;   // Create a Tree object 
	string name;
	string id;
	string function;
	int commandNum = 0;

	cin >> commandNum;

	// The maximum ammount of commands is 10000
	if (commandNum > 10000)
		commandNum = 10000;

	for (int i = 0; i < commandNum; i++)
	{
		//Parse the function inputed by the user
		cin >> function;

		/*=============== Parsing insertion function ================*/

		if (function.compare("insert") == 0)
		{
			string next;

			// Parsing the input for the name of the student
			getline(cin, next, '"');
			getline(cin, name, '"');

			// Parsing the input for the ufid.
			cin >> id;

			//Insert user parameters into the function.
			tree.insert(name, id);
		}

		/*================ Parsing search ID and search NAME functions ==================*/

		else if (function.compare("search") == 0)
		{
			string next;
			string searchedItem;

			getline(cin, next, ' ');
			getline(cin, searchedItem);


			// Continue if the character at searchedItem[1] is a letter
			if (isalpha(searchedItem[1]))
			{
				// Let name be equal to name inside quotation marks
				name = searchedItem.substr(1, searchedItem.size() - 2);
				tree.searchName(name);
			}

			// If the character at 1 in searchedItem is a digit continue
			else 
			{
				// Set id equal to the search item 
				id = searchedItem;

				//If the id is not 8 digits long print unsuccessful
				if (id.length() != 8)
					cout << "unsuccessful" << endl;

				// Otherwise pass in the id string
				else
					tree.searchId(id);
			}

			

		}

		/*========== Parsing removal function ==============*/

		else if (function.compare("remove") == 0)
		{
			// Parse id string
			cin >> id;
			tree.remove(id);
		}

		/*============= Parsing removeInorder function ==============*/

		else if (function.compare("removeInorder") == 0)
		{
			string N;
			// Parse in the Nth term in the inorder traversal
			cin >> N;

			//Convert N to an integer and pass it through the removeInorder function
			tree.removeInorder(stoi(N));
		}

		/*============ Parsing printInorder function ==============*/

		else if (function.compare("printInorder") == 0)
			tree.printInorder(); // Call printInorder function

		/*=========== Parsing printPreorder function =============*/

		else if (function.compare("printPreorder") == 0)
			tree.printPreorder(); // Call preOrder function;

		/*=========== Parsing printPostorder function ============*/

		else if (function.compare("printPostorder") == 0)
			tree.printPostorder(); // Call postOrder functoin

		/*=========== Parsing printLevelCount function =============*/

		else if (function.compare("printLevelCount") == 0)
			tree.printLevelCount(); //Call printLevelCount
	}
	return 0;
}

