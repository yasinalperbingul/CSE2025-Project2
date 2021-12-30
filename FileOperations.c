//-------------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------------
// 										CSE2025 - Data Structures Project #2
//
//										   Yasin Alper Bingül - 170517033
//
//-------------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------------
#include <stdio.h>

int inputValidation(int* numbers){
	int count = 0;
	int valid = 1;
	
	// Getting input values
	FILE *filePtr;
	filePtr = fopen("input.txt", "r") ;
	
	fscanf (filePtr, "%d", &(*(numbers+count)));
	
	while (!feof (filePtr)){  
    	//printf ("%d ", numbers[count]);
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
		for(i=0; i<16; i++){
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
    	//printf ("%d ", numbers[count]);
    	count++;
    	fscanf (filePtr, "%d", &(*(numbers+count)));      
    }
    
	fclose (filePtr);
	
	return count;
}


int main(){
	int* numbers;
	int i=0,valid,numOfInputs; 
	
	// Check the file content is valid or not.
	valid = inputValidation(&numbers);
	numOfInputs = numberOfInput(&numbers);
	
	if(valid){
		// Print input content
		for(i=0; i<numOfInputs; i++){
			printf("%d. : %d\n",i+1,((numbers+i)));
		}	
		
		//Create a BTS
	}
	
	
	
}
