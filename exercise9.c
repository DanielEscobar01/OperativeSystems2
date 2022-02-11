#include<stdio.h>
#include<stdlib.h>

char* getString(){
char message[100] = "Hello World!";
return message;
}

int main(int argc, char* argv[]){
printf("String: %s\n", getString());
}




