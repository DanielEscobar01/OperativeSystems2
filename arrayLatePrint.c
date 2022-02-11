// Program to create an array of 100 elements
#include <stdio.h>
#include <stdlib.h>

int main() {
  int *data = 0;
  int n = 100;
  data = (int*) malloc(n * sizeof(int));
  // if memory cannot be allocated
  if(data == NULL) {
    printf("Error! memory not allocated.");
    exit(0);
  }	
  free(data);
  printf("%d\n",data[0]);
  return 0;
}




  // deallocating the memory
  //free(ptr);
