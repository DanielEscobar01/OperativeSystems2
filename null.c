#include<stdio.h>
#include<stdlib.h>

int main(int argc, char* argv[]){
	int* integerPointer = NULL; // Creates the integer pointer with null value
	*integerPointer=0;	// This is not valid because you are not the owner of the 					address you are trying to access with the pointer and this will 				lead into Segmentation Fault
}



