// Program to create an array of 100 elements
#include <stdio.h>
#include <stdlib.h>

int main() {
  int *data = 0;
  int *randomPointer = 0;
  int n = 100;
  data = (int*) malloc(n * sizeof(int));
  randomPointer = &data[50];
  // if memory cannot be allocated
  if(data == NULL) {
    printf("Error! memory not allocated.");
    exit(0);
  }	
  free(data);
  free(randomPointer);
  printf("Random Pointer Value %d\n",randomPointer[0]);
  
  return 0;
}




  // deallocating the memory
  //free(ptr);
