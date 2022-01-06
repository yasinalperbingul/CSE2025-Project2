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

//This function is to find depthLevel of entered key value as parameter
int levelUnit(struct BTNodeType *p, int key, int level)
{
    if (p == NULL)
        return 0;
 
    if (p->key == key)
        return level;
 
    int levelOfKey = levelUnit(p->left, key, level+1);
    if (levelOfKey != 0)
        return levelOfKey;
 
    levelOfKey = levelUnit(p->right, key, level+1);
    return levelOfKey;
}

int getDepthLevel(struct BTNodeType *p, int key)
{
    return levelUnit(p,key,1);
}

//This function returns the element number of entered key value as parameter
int getElement(struct BTNodeType *p, int key)
{
	int ind = 0;
	int element = 0;
	
	if(p == NULL){
		return 0;
	}
	
	if(p->key < key){
		if(ind){
			element = element*2;
		}
		else{
			element = 2;
		}
		if(!ind){
			ind = 1;
		}

		p->right = getElement(p->right,key);
	}
	else if(p->key > key){
		if(ind){
			element = element + 1;
		}
		else{
			element = 1;
		}
		p->left = getElement(p->left,key);
	}
	else{
		return element;
	}
	
	return element;
}

//This function finds a leaf
struct BTNodeType* findLeaf(struct BTNodeType* p){
	if(p==NULL){
		return NULL;
	}
	
	if(p->left == NULL && p->right == NULL){
		return p;
	}
	else{
		//Check this!
		if(p->right){
			findLeaf(p->right);
		}
		else if(p->left){
			findLeaf(p->left);
		}	
	}
}

struct BTNodeType* findAnotherLeaf(struct BTNodeType* p){
	if(p==NULL){
		return NULL;
	}
	
	if(p->left == NULL && p->right == NULL){
		return p;
	}
	else{
		//Check this!
		if(p->right){
			findLeaf(p->right);
		}
		if(p->left){
			findLeaf(p->left);
		}	
	}
}

//This function removes a leaf
struct BTNodeType* removeLeaf(struct BTNodeType* p, int key){
	if(p==NULL){
		return NULL;
	}
	
	
	if(p->key < key){
		p->right = removeLeaf(p->right,key);
	}
	else if(p->key < key){
		p->left = removeLeaf(p->left,key);
	}
	else if(p->key == key){
		free(p);
		return NULL;
	}
	
	return p;
}

//This function inserts removed node leaf to the deepest depht
struct BTNodeType* insertDepthMost(struct BTNodeType* p,int key){
	struct BTNodeType* tempLeaf;
	
	if(p==NULL){
		return NULL;
	}
	
	tempLeaf = findLeaf(p);
	//printf("\nFounded new leaf %d\n",tempLeaf->key);
	//printf("New depth level : %d\n",getDepthLevel(p,tempLeaf->key));
	//printf("Insert new key %d to new leaf %d\n",key,tempLeaf->key);
	insert(tempLeaf,key);
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
        
        //Print the values
        int depthL = depthLevel(numOfInputs);
        printf("\nDepth level of BST is : %d\n",depthL);
        
        //Find the depth level histogram
        int levels[depthL];
        
        for(i=0; i<=depthL; i++){
        	levels[i]=0;
		}
		
        for(i=0; i<=numOfInputs; i++){
			int inLevel = getDepthLevel(root,numArray[i]);
			//printf("%d level is : %d\n",numArray[i],inLevel);
        	levels[inLevel-1]++;
		}
        
        for(i=0; i<depthL; i++){
        	printf("Depth Level %d -> %d\n",i,levels[i]);
		}
		
		
		//If it doesn't fit with the rules, fix the BST tree according to second requirement	
		//1. find a leaf to remove and add
		int indicator = 0;
		while(indicator <2){
			if(levels[depthL-1]==0){
			struct BTNodeType* leaf = findLeaf(root);
			struct BTNodeType* newLeaf;
			
			//int depthLeaf = getDepthLevel(root,leaf->key)-1;
			//printf("One of the leaf is : %d\n",leaf->key);
			if(indicator){

				//printf("Remove newLeaf %d\n",newLeaf->key);
				int inLevel = getDepthLevel(root,newLeaf->key);
				//printf("depth level of %d : %d\n",newLeaf->key,inLevel);
				
				removeLeaf(root,newLeaf->key);
				levels[inLevel-1]--;
				
				//printf("Insert new leaf\n");
				insertDepthMost(root,newLeaf->key);
				
				inLevel = getDepthLevel(root,newLeaf->key);
				//printf("New depth level of %d : %d\n",newLeaf->key,inLevel);
				levels[inLevel+1]++;
		
			}
			else{
				//2. remove it
				//printf("Remove leaf");
				removeLeaf(root,leaf->key);
	
				//3. insert it into downside
				//printf("Insert it.");
				//printf("Leaf depth : %d",depthLeaf);
				insertDepthMost(root,leaf->key);
				
				//Check the histogram
				for(i=0; i<=depthL; i++){
       			levels[i]=0;
				}
				for(i=0; i<=numOfInputs; i++){
				int inLevel = getDepthLevel(root,numArray[i]);
				//printf("%d level is : %d\n",numArray[i],inLevel);
       			levels[inLevel-1]++;
				}
				/*
      			printf("\n");
      			for(i=0; i<depthL; i++){
      			printf("Depth Level %d -> %d\n",i,levels[i]);
				}
				*/
			}	
		indicator++;
		newLeaf = findAnotherLeaf(root);
		//printf("One of the other leaf is : %d\n",newLeaf->key);
		}
		else{
			indicator = 2;
		}
		}
		printf("\n");
       	for(i=0; i<depthL; i++){
        	printf("Depth Level %d -> %d\n",i,levels[i]);
		}
					
		int searchKey;
		a:
		printf("Key value to be searched (Enter 0 to exit) : ");
		scanf("%d",&searchKey);
		int depth = getDepthLevel(root,searchKey);
		//int element = getElement(root, searchKey);
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

