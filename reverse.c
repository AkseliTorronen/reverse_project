/**************************************************************/
/*CT30A3370 Käyttöjärjestelmät ja systeemiohjelmointi      	*/
/*Tekijä: Akseli Törrönen					*/
/*Opiskelijanumero: 0542794					*/
/*Harjoitustyö: reverse.c					*/
/**************************************************************/
/*Lähteet: https://www.tutorialride.com/c-stack-programs/push-pop-items-from-string-stack-c-program.htm*/ 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 5000

void read_file(char fname[256], char stack[MAX][256], int *top){
	FILE *in_file;
	char *line = NULL;
	size_t line_buffer = 0;
	ssize_t line_size = 0;
	//Error handler
	if((in_file = fopen(fname, "r"))==NULL){
		fprintf(stdout,"Cannot open file %s\n", fname);
		exit(1);
	}
	//reading the file line by line
	fprintf(stdout,"The input file:\n");
	while ((line_size = getline(&line, &line_buffer, in_file)) >= 0){
		fprintf(stdout,"%s", line);
		*top = *top + 1;		//the first entry in the stack has the index 0
		strcpy(stack[*top],line);	//saving the lines into a stack
	}

	fclose(in_file);
}

void write_file(char out_name[256], char stack[MAX][256], int *top){
	FILE *out_file;
	//Error handler
	if((out_file = fopen(out_name, "w"))==NULL){
		fprintf(stderr,"Cannot open file %s\n", out_name);
		exit(1);
	}
	//writing the file from the top of the stack towards the bottom
	while(*top>=0){
		fprintf(out_file,"%s", stack[*top]);
		*top= *top - 1;
	}
	fclose(out_file);
		
}

int main(int argc, char* argv[]){
	char stack[MAX][256];
	char buffer[256];
	int temp = 0;
	int top = -1;//top initialized as -1
	if(argc > 3){fprintf(stdout,"usage: reverse <input> <output>\n");exit(1);}
	char in_name[256];
	char out_name[256];
	if(argc == 3){
		if(strcmp(argv[1], argv[2]) == 0){fprintf(stdout,"Input and output file must differ\n");exit(1);}
		strcpy(in_name, argv[1]);
		read_file(in_name, stack, &top);
		strcpy(out_name, argv[2]);
		write_file(out_name, stack, &top);
		return 0;
	}
	if(argc == 2){//if no output file the program will read the file and later print it to the console in reverse
		strcpy(in_name, argv[1]);
		read_file(in_name, stack, &top);
	}
	if(argc == 1){ //if there si no file specified the program will read stdin
		fprintf(stdout, "exit with an integer\n");
		while(1){
			printf("Enter a string: ");
			if(fscanf(stdin, "%d", &temp)){break;}
			else{fgets(buffer, 256, stdin);}
			
			top = top + 1;
			strcpy(stack[top], buffer);
			
		}
	}
	
	fprintf(stdout,"\nThe file in reverse:\n");
	while(top>=0){
		fprintf(stdout,"%s", stack[top]);
		top= top - 1;
	}
	
	

return 0;
}
