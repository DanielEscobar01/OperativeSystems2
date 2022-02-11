#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<sys/utsname.h>
#include<string.h>
#include<ctype.h>
#include <sys/stat.h>
#ifndef MAX
#define MAX 10000
#endif
	
	void changeName(char string[]);	// Change the name of the file with the process id
	void getProcessInformation(char process[], int print);	// Sent the process id and if you want to print, and then see the magic
	void writeFile(char string[]);	// Send the string we want to write and the method will create the file and write onto it
	int isNumeric(char string[]); 	// Send string to check if its a number or not


	int main(int argc, char *argv[]){
		if(argc<2) {								// If the argc value is less 2, that means theres nothing sent as parameter
			printf("You must send a value as parameter\n");			// We let the user know that he is stu***
			return EXIT_FAILURE;						// We return because there is not enough information
		}
		char *operationType = argv[1];						// Getting the first parameter
		if(argc ==2){								// If the argc value equals 2, that means there is only one parameter to evaluate
			if(isNumeric(operationType)!=1){				// If the isNumeric method return something different than 1, that means is not numeric
				printf("You must send a numeric value instead of: %s\n", operationType); 	//Let the user know about the error
				return EXIT_FAILURE;					// We return because we need numeric values for ID
			} else {
				getProcessInformation(operationType,0);			// Get the process information without writing on a file (Thats why we sent 0 as parameter)
			}
		} else {
		if(strcmp(operationType, "-r")==0){					// If operationType is -r we must write the values on the file
			char states[MAX] = "";						// This variable is used to store the process id values
			for(int i=2;i<argc;i++){					// For for the next items sent as parameters
				char *processId = argv[i];				// Getting the process id sent as parameter
				if(isNumeric(processId)==0){				// If isNumeric equals 0, that means the input is not numeric
					printf("Please write numbers instead of this shit \n");	// Let the user know the error
				}else{
					strcat(states, "-");				// Concatenate the - to show different processes
					strcat(states, processId);			// Concatenate the previous process with the next one
					getProcessInformation(processId,1);		// The second parameter is 1 because we want to write on the file
				}
				

			}
			changeName(states);					// Change the name of the file with the process id
		} else if (strcmp(operationType, "-l")==0){			// If operationType is -l we must print the results 
			for(int i=2;i<argc;i++){				// For for the next items sent as parameters
				char *processId = argv[i];			// Getting the process id sent as parameter
				if(isNumeric(processId)==0){			// If isNumeric equals 0, that means the input is not numeric
					printf("Please write numbers instead of this shit \n"); // Let the user know the error
				}else{
					getProcessInformation(processId,0);	// The second parameter is because we dont want to write on the file

				}
				
			}	
			} else {
				printf("If you want to check two or more processes you must put the -l first\n"); // Message to let the user know the error
				return EXIT_FAILURE;				// We return because for two or more ids, we need the -l or -f first.
			}			
		}
		
		
	return 0; 								// Return
	}
		   	
	   
	   
	void changeName(char string[]){
    		char buffer1[MAX];
    		char buffer2[MAX];
    		strcat(strcpy(buffer1, "psinfo-report"),string);
    		strcat(strcpy(buffer2, buffer1),".info");
    		rename("psinfo-report.txt",buffer2);
	}   
	   
	   
	int isNumeric(char string[]){						// This function will let us know if a parameter is numeric or not
		int length,i ;							// Declaring the variables 
		length=strlen(string);						// The length value of the string sent as parameter
		for(i=0;i<length;i++){						// For to check each value of the string sent as parameter
			if(!isdigit(string[i])){				// If some of the char inside the array is not digit
				return 0;					// We return 0 that means is not numeric
			}
		}
		return 1;							// We return 1 that means is numeric
	}
	
		void writeFile(char string[]) {              			//This function will write each process into the requested file
    		char buffer[MAX];						// This is where we are going to store each line of the string	
    		strcat(strcpy(buffer, string),"\n\n");  			// Apply a line break
    		FILE *fp = fopen("psinfo-report.txt", "a+");        		// Open the file 
    		for(int i=0; i<strlen(buffer); i++){    			// Read each line of the string
      			fputc(buffer[i], fp);               			// Write on the file
    		}                                      
    		fclose(fp);                             			// Close the file
	}


	void getProcessInformation(char process[], int print){			// This function get the details from certain process and write the information in a file.
		char lastPart[] = "/status";					// The last part of the code
		char destination[256] = "/proc/";				// The first part of the code
		strcat(destination,process);					// Concatenate the first part with the previous concatenated part
		strcat(destination,lastPart);					// Concatenate the Id with the last part
		char *filename = destination;					// Setting file name as the file of the process 
	    	FILE *fp = fopen(filename, "r"); 				// Open the requested file in lecture mode
	    	if (fp == NULL) {						// Check if the file exists 
			printf("\nThe process you are trying to access does not exist -> %s\n", process);	// If it doesnt exist, then we throw a message
			char statusdata[]= "The requested process does not exist";				// This is where we are going to save the information
			if(print==1){						// If the parameter is 1, that mean we have to write the information on the file
		    		writeFile(statusdata);				// Call writeFile method
		    	}
	    	}else{
			char statusdata[MAX]= "";				// This is were we are going to save the information
			char temp[264]="";					// Define temporary variable
			char temp2[264]="";					// Define temporary variable
			char temp3[264]="";					// Define temporary variable
			char temp4[264]="";					// Define temporary variable for the name
    			char delimitador[] = ":";				// Define temporary variable
		    	const unsigned MAX_LENGTH = 10000; 			// The maximum length of the text
		    	char buffer[MAX_LENGTH]; 				// This is where we are going to store each line of the document
			fgets(buffer, MAX_LENGTH, fp); 				// Reads the first line of the file 
			char *token = strtok(buffer, delimitador); 		// We use this to divide the string using the delimiter ":"
			token = strtok(NULL, delimitador);			// We take the value after the first appearance of ":"
			strcat(temp4, token);   				// Stores the name state in temp4
			token = strtok(NULL, delimitador);			// We take the value after the first appearance of ":"
	
			while( token != NULL ) {
				strcat(temp4, ":");   				// Stores the name state in temp4
				strcat(temp4, token);   			// Stores the name state in temp4
				token = strtok(NULL, delimitador);		// We take the value after the first appearance of ":"

			}

			strcat(statusdata, "\n\nNombre del proceso: ");		// Stores the process name in statusData
			strcat(statusdata, temp4);				// Stores the process name in statusData
			fgets(buffer, MAX_LENGTH, fp);				// Reads the second line of the file
			fgets(buffer, MAX_LENGTH, fp);				// Reads the third line of the file
			token = strtok(buffer, delimitador);     		// We use this to divide the string using the delimiter ":"			
			token = strtok(NULL, delimitador);			// We take the value after the first appearance of ":"	
			strcat(statusdata, "Estado: ");				// Stores the process Estado in statusData
			strcat(statusdata, token);   				// Stores the process state in statusData
			int VmExe = 0;						// This variable is a flag to check if VmExe exists
		   	for (int i = 0; i < 51; i++ ){ 				// Read the i-next lines of the file
				fgets(buffer, MAX_LENGTH, fp);	 		// Get the i-line of the file
				token = strtok(buffer, delimitador); 		// Takes the value before the ":" 
				if(strcmp( token, "VmExe" ) == 0){		
					VmExe = VmExe + 1;			// Change the status of the flag
					if(strcmp( temp3, "" ) == 0){
						strcat(statusdata, "Tamaño total de la imagen de memoria:\n");			// Stores the process Estado in statusData
					}else{
						strcat(statusdata, "Tamaño total de la imagen de memoria: ");			// Stores the process Estado in statusData
						strcat(statusdata, temp3);
					}					
					
					token = strtok(NULL, delimitador);
					strcat(statusdata, "\tTamaño de la sección de memoria TEXT: ");				// Stores the process Estado in statusData
					strcat(statusdata, token);
					if(strcmp( temp, "" ) == 0){
						strcat(statusdata, "\tEste proceso no tiene la variable VmData\n");		// Stores the process Estado in statusData
					}else{
						strcat(statusdata, "\tTamaño de la sección de memoria DATA: ");			// Stores the process Estado in statusData
						strcat(statusdata, temp);
					}
					
					if(strcmp( temp2, "" ) == 0){
						strcat(statusdata, "\tEste proceso no tiene la variable VmStk\n");		// Stores the process Estado in statusData
					}else{
						strcat(statusdata, "\tTamaño de la sección de memoria STACK: ");		// Stores the process Estado in statusData
						strcat(statusdata, temp2);
					}
				}

				if(strcmp( token, "voluntary_ctxt_switches" ) == 0){
					if(VmExe == 0){
						if(strcmp( temp3, "" ) == 0){
							strcat(statusdata, "Tamaño total de la imagen de memoria:\n");				// Stores the process Estado in statusData
						}else{
							strcat(statusdata, "Tamaño total de la imagen de memoria: ");				// Stores the process Estado in statusData
							strcat(statusdata, temp3);
						}
						strcat(statusdata, "\tEste proceso no tiene la variable VmExe\n");				// Stores the process Estado in statusData
						if(strcmp( temp, "" ) == 0){
						strcat(statusdata, "\tEste proceso no tiene la variable VmData\n");				// Stores the process Estado in statusData
						}else{
							strcat(statusdata, "\tTamaño de la sección de memoria DATA: ");				// Stores the process Estado in statusData
							strcat(statusdata, temp);
						}
						
						if(strcmp( temp2, "" ) == 0){
						strcat(statusdata, "\tEste proceso no tiene la variable VmStk\n");				// Stores the process Estado in statusData
						}else{
							strcat(statusdata, "\tTamaño de la sección de memoria STACK: ");				// Stores the process Estado in statusData
							strcat(statusdata, temp2);
						}
					}
					token = strtok(NULL, delimitador);
					token[strcspn(token, "\n")] = 0;  									//Deletes the line break
					strcat(statusdata, "Número de cambios de contexto realizados (Voluntarios - no voluntarios): ");	// Stores the process Estado in statusData
					strcat(statusdata, token);
				}
				
				if(strcmp( token, "nonvoluntary_ctxt_switches" ) == 0){
					token = strtok(NULL, delimitador);
					if(token != NULL){
						strcat(statusdata, " - ");				// Stores the process Estado in statusData	
						strcat(statusdata, token);
					}else{
						break;
					}					
				}

				if(strcmp( token, "VmData" ) == 0){  
					token = strtok(NULL, delimitador);
					strcat(temp, token); 		// Stores the memory image size in temp
				}

				if(strcmp( token, "VmStk" ) == 0){
					token = strtok(NULL, delimitador);
					strcat(temp2, token); 		// Stores the memory image size in temp
				}

				if(strcmp( token, "VmPeak" ) == 0){
					token = strtok(NULL, delimitador);
					strcat(temp3, token); 		// Stores the memory image size in temp
				}
					
			}
			
			

			printf("%s", statusdata);		// Print the All data in statusdata
		    	fclose(fp);  
		    	if(print==1){
		    		writeFile(statusdata);
		    	}							// Close the file
	    	}
	    	
	}













