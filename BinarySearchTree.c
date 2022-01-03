// C program to insert a node in AVL tree
#include<stdio.h>
#include<stdlib.h>

// An AVL tree node
struct Node
{
	int key;
	struct Node *left;
	struct Node *right;
	int height;
};

// A utility function to get maximum of two integers
int max(int a, int b);

// A utility function to get the height of the tree
int height(struct Node *N)
{
	if (N == NULL)
		return 0;
	return N->height;
}

// A utility function to get maximum of two integers
int max(int a, int b)
{
	return (a > b)? a : b;
}

/* Helper function that allocates a new node with the given key and
	NULL left and right pointers. */
struct Node* newNode(int key)
{
	struct Node* node = (struct Node*)
						malloc(sizeof(struct Node));
	node->key = key;
	node->left = NULL;
	node->right = NULL;
	node->height = 1; // new node is initially added at leaf
	return(node);
}

// A utility function to right rotate subtree rooted with y
// See the diagram given above.
struct Node *rightRotate(struct Node *y)
{
	printf("Right rotate\n");
	struct Node *x = y->left;
	struct Node *T2 = x->right;

	// Perform rotation
	x->right = y;
	y->left = T2;

	// Update heights
	y->height = max(height(y->left), height(y->right))+1;
	x->height = max(height(x->left), height(x->right))+1;

	// Return new root
	return x;
}

// A utility function to left rotate subtree rooted with x
// See the diagram given above.
struct Node *leftRotate(struct Node *x)
{
	printf("Left rotate\n");
	struct Node *y = x->right;
	struct Node *T2 = y->left;

	// Perform rotation
	y->left = x;
	x->right = T2;

	// Update heights
	x->height = max(height(x->left), height(x->right))+1;
	y->height = max(height(y->left), height(y->right))+1;

	// Return new root
	return y;
}

// Get Balance factor of node N
int getBalance(struct Node *N)
{
	if (N == NULL)
		return 0;
	
	printf("Get Balanced (left hegiht: %d)- (right height: %d): %d\n",height(N->left),height(N->right),height(N->left) - height(N->right));
	return height(N->left) - height(N->right);
}

// Recursive function to insert a key in the subtree rooted
// with node and returns the new root of the subtree.
struct Node* insert(struct Node* node, int key)
{
	printf("Inserting %d\n",key);
	/* 1. Perform the normal BST insertion */
	if (node == NULL)
		return(newNode(key));

	if (key < node->key){
		printf("Going to left\n");
		node->left = insert(node->left, key);
		
	}
	else if (key > node->key){
		printf("Going to right\n");
		node->right = insert(node->right, key);
		
	}
	else // Equal keys are not allowed in BST
		return node;
	
	printf("Insertion complated.\n");
	printf("Height of inserted node before update : %d\n",node->height);
	/* 2. Update height of this ancestor node */
	node->height = 1 + max(height(node->left),
						height(node->right));
	printf("Height of inserted node after update : %d\n",node->height);
	
	/* 3. Get the balance factor of this ancestor
		node to check whether this node became
		unbalanced */
	int balance = getBalance(node);

	// If this node becomes unbalanced, then
	// there are 4 cases

	// Left Left Case
	if (balance > 1 && key < node->left->key){
		printf("balance>1 and key(%d) < (node->left->key)(%d)",key,node->left->key);
		return rightRotate(node);
	}
		
	// Right Right Case
	if (balance < -1 && key > node->right->key){
		printf("balance<-1 and key(%d) > (node->right->key)(%d)",key,node->right->key);
		return leftRotate(node);
	}
		
	// Left Right Case
	if (balance > 1 && key > node->left->key)
	{
		printf("balance>1 and key(%d) > (node->left->key)(%d)",key,node->left->key);
		node->left = leftRotate(node->left);
		return rightRotate(node);
	}

	// Right Left Case
	if (balance < -1 && key < node->right->key)
	{
		printf("balance<-1 and key(%d) < (node->right->key)(%d)",key,node->right->key);
		node->right = rightRotate(node->right);
		return leftRotate(node);
	}
	
	printf("Returned node : %d\n",node->key);
	/* return the (unchanged) node pointer */
	return node;
}

// A utility function to print preorder traversal
// of the tree.
// The function also prints height of every node
void preOrder(struct Node *root)
{
	if(root != NULL)
	{
		
		preOrder(root->left);
		preOrder(root->right);
		printf("%d ", root->key);
	}
}

//Getting input informations from the file
int inputValidation(int* numbers){
	int count = 0;
	int valid = 1;
	int i=0;
	// Getting input values
	FILE *filePtr;
	filePtr = fopen("input.txt", "r") ;
	
	fscanf (filePtr, "%d", &(*(numbers+count)));
	
	while (!feof (filePtr)){  
    	//printf ("%d ", (*(numbers+count)));
    	count++;
    	fscanf (filePtr, "%d", &(*(numbers+count)));      
    }
    
	fclose (filePtr);
  
  
	//  The BST should have at least 16 nonnegative and non-replicated keys, you have to control the input file, 
	//  if input file contains less and/or negative keys then the program produces an error message. 
	if(count<16){
		printf("Error: The input size is less than 16.");
		valid = 0;
	}
	else{
		int i=0;
		for(i=0; i<count; i++){
			if((*(numbers+i)) < 0){
				printf("Error: The input file has negative number.");
				valid = 0;
				break;
			}
		}
	}
	
	return valid;
}

int numberOfInput(int* numbers){
	int count = 0;
	int valid = 1;
	
	// Getting input values
	FILE *filePtr;
	filePtr = fopen("input.txt", "r") ;
	
	fscanf (filePtr, "%d", &(*(numbers+count)));
	
	while (!feof (filePtr)){  
    	//printf ("%d ", (*(numbers+count)));
    	count++;
    	fscanf (filePtr, "%d", &(*(numbers+count)));      
    }
    
    int i=0;
	
	fclose (filePtr);
	
	return count;
}


/* Driver program to test above function*/
int main()
{
	int* numbers;
   	int valid,numOfInputs; 

	// Check the file content is valid or not.
	valid = inputValidation(&numbers);
	numOfInputs = numberOfInput(&numbers);
	int numArray[numOfInputs];
	
	// Getting input values
	int i=0;
	FILE *filePtr;
	filePtr = fopen("input.txt", "r") ;
	fscanf (filePtr, "%d", &numArray[i]);
	while (!feof (filePtr)){  
   		//printf ("\ni: %d :: %d ",i, numArray[i]);
   		i++;
   		fscanf (filePtr, "%d", &numArray[i]);      
   	}
   	//printf ("\ni: %d :: %d ",i, numArray[i]);
   	
	fclose (filePtr);
	
	printf("Numbers:\n");
	for(i=0; i<=numOfInputs; i++){
		printf("\ni:%d: %d",i,numArray[i]);
		}
	printf("\n");
	struct Node *root = NULL;

	/* Constructing tree given in the above figure */
	//int numbers[19] = {49,1,2,5,3,8,10,21,32,25,12,78,69,65,70,115,97,152};

	root = insert(root, numArray[0]);
  		for(i=1; i<=numOfInputs; i++){
  	 			root = insert(root, numArray[i]);
	    }


printf("\nPreorder traversal of the constructed AVL"
		" tree is \n");
preOrder(root);

return 0;
}

