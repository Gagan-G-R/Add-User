#include"server.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
void print_Use(){
	//this function is called if there is any error in the users entry
	//this displays the crrect syntax of the addgroup command
	printf("The correct syntax is :\n./addgroup -i <group ID> -n <group name> -p <group pwd> -m <group members>\n\n");
}
char* encript(char message[])
{
	//this function is called to encript the passwoed enterd by the user
	//i have user a simple ROT13 cypher to encripy data
	char ch;
	for(int i = 0; message[i] != '\0'; ++i){
		ch = message[i];	
		if(ch >= 'a' && ch <= 'm')
			ch = ch + 13;		
		else if(ch >= 'n' && ch <= 'z')
			ch = ch-13;
		else if(ch >= 'A' && ch <= 'M')
			ch = ch + 13;		
		else if(ch >= 'N' && ch <= 'Z')
			ch = ch-13;
		else if (ch>='0' && ch<='9')
			ch = '9'-ch+'0';
		else
			ch = '@';
		message[i] = ch;
	}
	//returning the encripted data to the main 
	return message;
}

int check(char I[],int cF){
	//this function is used to check if ther already existed group with same ID
	//as there cant be two groups with the same ID
	int i=0;
	char LF [50],MF [50];
	FILE *p =fopen("group.txt","r");		
	void simp(char a[]){
		//saparating the ID part from the entire line of data
		i=0;
		char * token = strtok(a,":");
		while (token !=NULL){
			if(i==2){
				//check is anything matches with the user entered ID
				if (strcmp(I,token) == 0){
					cF++;
					printf("\nID already taken try again \n");
				}
			}
			token = strtok(NULL,":");
			i++;
		}
	}	
	while(p != EOF){
		//getting info from the group file , line by line
		fgets(LF,100,p);
		if(strcmp(MF,LF) == 0)
			break; 
		simp(LF);
		strcpy(MF,LF);
	
	}
	fclose(p);
	return cF;
}
char* replace(char M[]){
	//this function is used to format the members string
	//replace all the "," with ":" as that is the syntax os storing the data
	for(int i=0;i<strlen(M);i++)
	{
		if(M[i]==',')
			M[i]=':';
	}
	return M;
}



char* format_1(char N[],char I[],char M[]){
	//add the data without pwd entered will be put together in one format to be stored in the Group file
	strcat(N,":x:");
	strcat(N,I);
	strcat(N,":");
	strcat(N,M);
	strcat(N,"\n");
	return N;
}

char* format_2(char FN[],char E[],char I[],char M[]){
	//add the data with encripted pwd entered will be put together in one format to be stored in the gShadow file
	strcat(FN,":");
	strcat(FN,E);
	strcat(FN,":");
	strcat(FN,I);
	strcat(FN,":");
	strcat(FN,M);
	strcat(FN,"\n");
	return FN;
}
