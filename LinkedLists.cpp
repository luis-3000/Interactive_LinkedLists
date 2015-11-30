/* 
	LinkedLists
	Author: Jose Luis Castillo
	Date: 11/29/2015
	This program builds a list of Node structures as follows:
	There is a pointer to the first node in the list, a pointer to the last node in the list, and a current 
	pointer for the new element in the list.
	When there is one item in the list, all 3 pointers will be pointing to the same node. 

	The user will be provided with options:
	1). To add to the list (add to the bottom of the list). The lastNodePtr will point to the added last node.
	2). Delete from the list. Deletes the first node in the list and makes sure that the firstNodePtr will be made to
	   point to the 2nd member in the list after removal of the first.
	3). Search the list, which does a linear search to find the indicated element
	4). Print the contents of the list.
*/

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
using namespace std;

struct Node {
	int data;
	Node * next; // pointer to next node in the list
};

struct Node * firstNodePtr = NULL;
struct Node * lastNodePtr = NULL;

/* Simplifies creation of a new list. */
void createNewList() {

	// Create a new struct for a new element
	// Allocate enough memory for each new struct Node
	struct Node *pNewNode = (struct Node *) malloc(sizeof(struct Node));

	pNewNode->next = NULL;

	cout << "Enter the new number you want to add to the list: " << endl;
	cin >> pNewNode->data;

	// Make all pointers point to this new element
	firstNodePtr = lastNodePtr = pNewNode;

}

/* Adds an element to the bottom/end of the list. */
void add() {

	// Special case, trying to insert a node which turns out to be the first new element in the list
	if (firstNodePtr == NULL) {

		createNewList();

	} else { // This means we are inserting the second or third element in the list

		// Create a new struct for a new node element
		struct Node *pNewNode = (struct Node *) malloc(sizeof (struct Node));

		cout << "Enter the new number you want to add to the list: " << endl;
		cin >> pNewNode->data;

		// Check if this is going to be the second item in the list
		if (firstNodePtr == lastNodePtr) { // This means we only have one node in the list, inserting the second
			
			firstNodePtr->next = pNewNode;
			
			lastNodePtr = pNewNode;

			pNewNode->next = NULL;

		} else { // General case for the third and more subsequent new nodes

			lastNodePtr->next = pNewNode;

			pNewNode->next = NULL;

			lastNodePtr = pNewNode;
		}

	}

}

// Global variable
struct Node *pNodeBeforeNodeToDelete = NULL; //Pointer to Node before the node we want to delete

/* Searches for a specified Node and returns a pointer to the struct Node for suchf item. */
struct Node * searchForNode(int item) {

	struct Node *pNodeIterator = firstNodePtr; // the name sort of reflects the purpose

	while (pNodeIterator != NULL) {
		// Check if we found the item
		if(pNodeIterator->data == item) { // If found
			
			cout << item << " was found." << endl;
			
			return pNodeIterator; // return a reference to the item found (its node)
		} 

		pNodeBeforeNodeToDelete = pNodeIterator; // Best place to assign this value here

		// Otherwise, keep moving the reference to the next node to seek out the item in the list
		pNodeIterator = pNodeIterator->next;
	}

	// Reached the end of the list, we did not find a match for the item we are looking for
	cout << item << " wasn't found!" << endl;

	return NULL;
}

/* Deletes an item in the list given its int value. */
void deleteNode (int itemToRemove) {

	struct Node *pNodeToDelete = NULL;

	pNodeToDelete = searchForNode(itemToRemove);

	if (pNodeToDelete != NULL) { // item to delete was found

		cout << itemToRemove  << " was deleted!" << endl;

		if (pNodeToDelete == firstNodePtr) { // If deleting what turned out to be the first element

			firstNodePtr = pNodeToDelete->next; // remove it from the list by moving this reference

		} else { // By keeping a reference to the node before the one we're deleting we can delete the
				// reference to it.
				// This variable was designated a value inside searchForNode()
			pNodeBeforeNodeToDelete->next = pNodeToDelete->next;

		}

		//free(pNodeToDelete); // free up memory	

	} else {

		cout << itemToRemove << " was not found!" << endl;

	}

}



/* Prints the list */
void print() {

	struct Node *pNodes = firstNodePtr; // Create  a New node to step through the list
									// Make it point to the head of the linked list

	cout << "Items in the list: ";

	//Print the first node's data
	if (firstNodePtr != NULL) {
		cout << "|" << firstNodePtr->data << "|";
		pNodes = pNodes->next; 
	}

	while (pNodes != NULL) {
		
		cout << "-->" << "|" << pNodes->data << "|";
 		
 		pNodes = pNodes->next;
	}
	cout << endl;
}


int main() {
	int itemToSearch;
	int itemToDelete;
	int choice;

	cout << " \n\nChoose from the following menu: " << endl;
	cout << " 1). To add a number to the linked list." << endl;
	cout << " 2). To delete a number to the linked list." << endl;
	cout << " 3). To search a number in the linked list." << endl;
	cout << " 4). To print the contents of the linked list." << endl;
	cout << " 5). To quit." << endl;
	cin >> choice;

	do {


		switch (choice) {
			case 1: 
				cout << "Adding a number to the list. " << endl;
				add();
				cout << "Confirming item was added to the list: " << endl;
				print();
				break;
			case 2:
				cout << "Enter the item to delete from the list." << endl;
				cin >> itemToDelete;
				deleteNode(itemToDelete);
				cout << "Confirming item was deleted from the list: " << endl;
				print();
				break;
			case 3:
				cout << "Enter the int value of the item you want to find in the list: " << endl;
				cin >> itemToSearch;
				searchForNode(itemToSearch);
				break;
			case 4:
				cout << "Printing the contents of the list." << endl;
				print();
				break;
			case 5:
				cout << "Exiting program ... " << endl;
				exit(0);
			default:
				cout << "Choice not recognized, try again." << endl;
		}


		cout << " \n\nChoose from the following menu: " << endl;
		cout << " 1). To add a number to the linked list." << endl;
		cout << " 2). To delete a number to the linked list." << endl;
		cout << " 3). To search a number in the linked list." << endl;
		cout << " 4). To print the contents of the linked list." << endl;
		cout << " 5). To quit." << endl;
		cin >> choice;

	} while (choice != 1 || choice != 2 || choice != 3 || choice != 4 || choice != 5);


	return 0;
}