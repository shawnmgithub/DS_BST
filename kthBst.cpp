#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
// creates a node struct that has a value, and if it is pointing left or right.it defines itself with a root, a left and a right
struct node{
	int val;
	node* left;
	node* right;
};//end
/* creates a functoion to create new node with a value, but no information on wheather it is placed on the left or right.*/
node* makeNewNode(int value){
	node* newNode = new node;
	newNode -> left = nullptr;
	newNode -> right = nullptr;
	newNode -> val = value;
	return newNode;
}//end of makeNewNode
/*create a function to insert a node into the bst. It will do this by checking the value of the root and determining if the new node is greater than or less than it. If it is greater than it the node will be placed on the right, and if it is less it will be placed on the left. if there is no root the node will become the root. I had problems getting my logic to work, then I realized I needed to call the node variable by reference so I am not just editing a copy of the variable.
*/
/* if there is no node make it the main node if it is larger than the node's value put it on the right if the value is less than the root put it on the left*/
void insertNode(node* &node,int x){
		// if node is empty make the first node there
	if(node == nullptr){
		node = makeNewNode(x);
		return;
	}
	// if x is larger than the node's value stick it on the right
	if(node->val<x){
		if(node->right==nullptr){
			node->right = makeNewNode(x);
			return;
		}
		else{
			insertNode(node->right,x);
		}
	}
	// if x is smaller than the node's value stick it on the left
	if(node->val>x){
		if(node->left==nullptr){
			node->left=makeNewNode(x);
			return;
		}
		else{
			insertNode(node->left,x);
		}
	}	

}// end of insert
// create a function to find the minimum
int findMin(node* node){
	while(node->left != nullptr){
		node = node->left;
	}
	return(node->val);
}//end of findMin
// delete a given int in a tree

// create a function to print the whole bst with a preorder traversal
void printBst(node* node){
	if(node != nullptr){
		cout << node->val << " ";
		printBst(node->left);
		printBst(node->right);
	}
}//end of printBst
node* balancedBst(vector<int> values){
	int midPoint;
	sort(values.begin(), values.end());
	node* node = nullptr;
	int end = values.size();

	// variable declaration
	int start = 0;
	int rightArrayIndex =0;
	int leftArrayIndex = 0;
	// find the inital median
	midPoint =(start+end)/2 ;
	// insert the median to the first node
	insertNode(node,values[midPoint]);
	// make 2 vectors to put the information to the left/right of the median into
	vector<int> rightVect;
	vector<int> leftVect;

	/* loop the whole vector. put everything to the left of the median into 1 vector and everything to the right of the midpoint in another.*/

	for(int i=0;i<values.size();i++){
		if(i == midPoint){
			// do nothing
		}
		// make leftvector
		if(midPoint>i){
			int x =values[i];
			leftVect.push_back(x);
			leftArrayIndex++;
		}
		// make right vector
		if(midPoint<i){
			int y =values[i];
			rightVect.push_back(y);
			leftArrayIndex++;
		}
	}
	
	if(values.size()!=1){
		/* recusirvly call the function to find the median and insert it into the bst for the right and left vector.*/
		node->right=balancedBst(rightVect);
		node->left=balancedBst(leftVect);
	}

return node;
//end balancedbst
}


// removing a min from a tree.
void removeMin(node* &node){
	if(node->left == nullptr){
		node=node->right;
	}
	/* if it is not on the minimum, then recusirvly go back into the tree and continue on the left. */
	else{
		removeMin(node->left);
	}
}

int main() {
	int min;
	int temp;
	bool rightInt = false;
	node* root = nullptr;
	int k=0;
	// create the array that was given to us.
	int arr[] = {57,52,17,87,76,92,6,65,95,71,45,20,41,99,79};
	vector<int> values;

	// copy the array to a vector so it is able to pass to the function
	for (int i = 0; i < sizeof(arr)/sizeof(arr[0]); ++i) {
    int x  = arr[i];
		values.push_back(x);	
  }

	/* get a user defined k that is no larger than the length of the array and no less than 1 */
	cout << "pick a number(k) between 1 and 15 "; 
	while(k==0) {
		cin >> k; // Get user input from the keyboard
		if(k<1||k>=16){
			cout << "Please type a number in the range ";
			k=0;
		}
	}
	/* find the median of the array
		 place the median in the first root and then. take the median of the left and right side. place those, continue until all elements of the array are on the bst */
	root=balancedBst(values);
	node* duplicateBst = root;
	
	// loop k times and remove the minimum, on the last loop return that minimum:
	cout<< "preorder traversal of the whole tree:  ";
	printBst(duplicateBst);
	cout<<endl;
	for(int i=0;i<k-1;i++){
		temp = findMin(root);
		removeMin(root);
	}
	cout<< "the "<< k << "th min is : "<< findMin(root) <<endl;
}//end of main
