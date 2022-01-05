//=======================================================================================================
//
//					CSE2025 - DATA STRUCTURES Term Project #2
//						
//						  Yasin Alper Bingül - 170517033
//
//=======================================================================================================
#include<stdio.h>
#include<stdlib.h>
#include <math.h>

//Binary Tree Node struct
struct BTNodeType{
	struct BTNodeType *left;
	struct BTNodeType *right;
	int key;
	int height;
};

//This function creates new Binary Search Tree node (new root)
struct BTNodeType* newNode(int key)
{
	struct BTNodeType* root = (struct BTNodeType*)malloc(sizeof(struct BTNodeType));
	
	root->key = key;
	root->left = NULL;
	root->right = NULL;
	root->height = 1;
	
	return(root);
}

//This function rotate right the Binary Search Tree to balance tree (for better access time)
struct BTNodeType *rightRotate(struct BTNodeType *p)
{
	//printf("Right rotate\n");
	struct BTNodeType *pLeft = p->left;
	struct BTNodeType *pLRight = pLeft->right;
	
	//pLeft > p
	//pLRight > pLeft
	//If pLeft would be new top node, then pLeft's left would be p and pLeft's right would be pLRight (rotation)
	pLeft->right = p;
	p->left = pLRight;
	
	//Update the height values
	p->height = findBigger(findHeight(p->left), findHeight(p->right))+1;
	pLeft->height = findBigger(findHeight(pLeft->left), findHeight(pLeft->right))+1;
	
	//Return the new local top node / root
	return pLeft;
}

//This function rotate left the Binary Search Tree to balance tree (for better access time)
struct BTNodeType *leftRotate(struct BTNodeType *p)
{
	//printf("Left rotate\n");
	struct BTNodeType *pRight = p->right;
	struct BTNodeType *pRLeft = pRight->left;

	//pLeft > p
	//pLRight > pLeft
	//If pLeft would be new top node, then pLeft's left would be p and pLeft's right would be pLRight (rotation)
	pRight->left = p;
	p->right = pRLeft;

	//Update the height values
	p->height = findBigger(findHeight(p->left), findHeight(p->right))+1;
	pRight->height = findBigger(findHeight(pRight->left), findHeight(pRight->right))+1;

	//Return the new local top node / root
	return pRight;
}

//This function compares left and right heights of entered node as parameter
int compareHeights(struct BTNodeType *p)
{
	if (p == NULL)
		return 0;
	
	//printf("Height Difference (left hegiht: %d)- (right height: %d): %d\n",findHeight(N->left),findHeight(N->right),findHeight(N->left) - findHeight(N->right));
	return findHeight(p->left) - findHeight(p->right);
}

//This function compares two values and returns the bigger one
int findBigger(int num1, int num2)
{
	if(num1 > num2)
		return num1;
	else
		return num2;
}

//This function returns the height value of entered node as parameter
int findHeight(struct BTNodeType *p)
{
	if (p == NULL){
		return 0;
	}
		
	return p->height;
}

//This function inserts a new node according to rules
struct BTNodeType* insert(struct BTNodeType* p, int key)
{
	//printf("Inserting %d\n",key);
	//Insert new node to given root. If there is no root, then create a new one
	if (p == NULL)
		return(newNode(key));

	if (key < p->key){
		//printf("Going to left\n");
		p->left = insert(p->left, key);
		
	}
	else if (key > p->key){
		//printf("Going to right\n");
		p->right = insert(p->right, key);
	}

	//printf("node (%d)'s depth level is %d\n",p->key, p->depthLevel);
	
	//printf("Insertion complated.\n");
	//printf("Height of inserted node before update : %d\n",p->height);
	
	//Update the height value 
	p->height = 1 + findBigger(findHeight(p->left), findHeight(p->right));
	//printf("Height of inserted node after update %d: %d\n",p->key,p->height);
	
	//Compare the left and right height
	int comparisonHeights = compareHeights(p);

	if (comparisonHeights > 1 && key < p->left->key){
		//printf("comparisonHeights>1 and key(%d) < (p->left->key)(%d)",key,p->left->key);
		return rightRotate(p);
	}
		
	if (comparisonHeights < -1 && key > p->right->key){
		//printf("comparisonHeights<-1 and key(%d) > (p->right->key)(%d)",key,p->right->key);
		return leftRotate(p);
	}
		
	if (comparisonHeights > 1 && key > p->left->key)
	{
		//printf("comparisonHeights>1 and key(%d) > (p->left->key)(%d)",key,p->left->key);
		p->left = leftRotate(p->left);
		return rightRotate(p);
	}

	if (comparisonHeights < -1 && key < p->right->key)
	{
		//printf("comparisonHeights<-1 and key(%d) < (p->right->key)(%d)",key,p->right->key);
		p->right = rightRotate(p->right);
		return leftRotate(p);
	}
	
	//printf("Returned node : %d\n",p->key);

	return p;
}

//Delete this function
void preOrder(struct BTNodeType *root)
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

//This function calculates the depth level of Binary Search Tree
int depthLevel(int numOfInputs){
	//log4 (x) = logy (x) / logy (4)
	return 3*((log(numOfInputs)/log(4)));
}

int getLevelUtil(struct BTNodeType *p, int key, int level)
{
    if (p == NULL)
        return 0;
 
    if (p->key == key)
        return level;
 
    int downlevel = getLevelUtil(p->left,
                                 key, level+1);
    if (downlevel != 0)
        return downlevel;
 
    downlevel = getLevelUtil(p->right,
                             key, level+1);
    return downlevel;
}

int getLevel(struct BTNodeType *p, int key)
{
    return getLevelUtil(p,key,1);
}


int getElement(struct BTNodeType *p, int key, int depth){
	int element;
	
	if(getLevel(&p,key) == depth){
		if(p->key == key){
			return element;
		}
		else{
			element++;
		}
	}
	
}


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
	
	if(valid){
		// Print input content3
			printf("Input Numbers:\n");
	    for(i=0; i<=numOfInputs; i++){
	    	printf("%d ",numArray[i]);
	    	if(i==30){
	    		printf("\n");
			}
	   	}
		printf("\n");
		
		//Create an AVL BTS
		struct BTNodeType *root = NULL;

	    root = insert(root, numArray[0]);
	    
  		for(i=1; i<=numOfInputs; i++){
  	 			root = insert(root, numArray[i]);
	    }


        printf("\nPreorder traversal of the constructed AVL tree is \n");
        preOrder(root);
        
        //Fix the AVL tree according to second requirement
        
        
        
        
        
        //Print the values
        int depthL = depthLevel(numOfInputs);
        printf("\n\nDepth level of BST is : %d\n\n",depthL);
        
        //Find the depth level histogram
        int levels[depthL];
        for(i=0; i<=depthL; i++){
        	levels[i]=0;
		}
		
        for(i=0; i<=numOfInputs; i++){
			int inLevel = getLevel(root,numArray[i]);
			//printf("%d level is : %d\n",numArray[i],inLevel);
        	levels[inLevel-1]++;
		}
        
        for(i=0; i<depthL; i++){
        	printf("Depth Level %d -> %d\n",i,levels[i]);
		}
		
		/*
		int a;
		printf("Key value to be searched (Enter 0 to exit) :");
		scanf("%d\n",&a);
		*/
		
		int searchKey;
		a:
		printf("Key value to be searched (Enter 0 to exit) : ");
		scanf("%d",&searchKey);
		int depth = getLevel(root,searchKey);
		//int element = getElement(root, searchKey, depth);
		if(depth){
			printf("At Depth level %d, %dth element\n",depth,0);
			goto a;
		}
		else{
			if(searchKey){
				printf("%d is not found in BST\n",searchKey);
				goto a;
			}
			else{
				printf("Exit\n");
			}	
		}	
	}
	else{
		printf("\nProgram ended..");
	}

return 0;
}

