#include <stdio.h>
#include <stdlib.h>
  
struct BTNodeType{
	int key;
	struct BTNodeType *left;
	struct BTNodeType *right;
};

struct BTNodeType* newNode(int key){
	struct BTNodeType* p = (struct BTNodeType*)malloc(sizeof(struct BTNodeType));
	
	p->key = key;
	p->left = NULL;
	p->right = NULL;
	
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
	}
	else if(key> p->key){
		p->right = insertNode(key,p->right);
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

int findHeight(struct BTNodeType *p){

	if(p == NULL){
		return 1;
	}
	else{
		
	}
}

int main()  
{  
   int numbers[19] = {49,1,2,5,3,8,3,10,21,32,25,12,78,69,65,70,115,97,152};
   int i=0;
   struct BTNodeType* root = NULL;
   
   root = insertNode(numbers[0],root);
   for(i=1; i<19; i++){
   		insertNode(numbers[i],root);
   }
   
   inorder(root);
}  
