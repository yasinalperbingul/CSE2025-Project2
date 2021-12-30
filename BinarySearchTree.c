#include <stdio.h>
#include <stdlib.h>

struct BTNodeType{
	struct BTNodeType *left;
	struct BTNodeType *right;
	int key;
	int numRight;
	int numLeft;
	
};

struct BTNodeType* newNode(int key){
	struct BTNodeType* p = (struct BTNodeType*)malloc(sizeof(struct BTNodeType));
	
	p->key = key;
	p->left = NULL;
	p->right = NULL;
	p->numLeft=0;
	p->numRight=0;
	
	return p;
}

struct BTNodeType* insertNode(int key, struct BTNodeType *p){
	//If the tree is empty, then create a new one
	//If not, then insert the node according to BST rules
	if(p==NULL){
		return newNode(key);
	}
	else if(key< p->key){
		p->left = insertNode(key,p->left);
		p->numLeft++;
	}
	else if(key> p->key){
		p->right = insertNode(key,p->right);
		p->numRight++;
	}
	
	return p;
}

void inorder(struct BTNodeType *p){
	if(p != NULL){
		inorder(p->left);
		printf("%d\n", p->key);
		inorder(p->right);
	}
}

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
	
	//If the input file is valid, then build the binary search tree
	if(valid){
		for(i=0; i<=numOfInputs; i++){
		printf("\ni:%d: %d",i,numArray[i]);
		}
		
		printf("\n");
		//Create a root node
		struct BTNodeType* root = NULL;
   
  		root = insertNode(numArray[0],root);
  		for(i=1; i<=numOfInputs; i++){
  	 		insertNode(numArray[i],root);
	    }
   
 	    inorder(root);
  	    printf("Left: %d ",root->numLeft);
  	    printf("Right: %d",root->numRight);
	}
	else{
		exit(0);
	}
	
   
}  
