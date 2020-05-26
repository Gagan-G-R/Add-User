#include<stdio.h>
#include<stdlib.h>
#include<getopt.h>
#include<string.h>
#include"server.h"
int main(int argc,char **argv){
	//Using P to store the Password entered
	//using N to store the Group Name entered
	//using M to store the Group Members saparated with ","
	//using FN to copy the Group Name into it
	//using E to store the encripted password
	char P[50],N[50],M[50],I[50],FN[50],E[50];
	//using PF,nF,mF,iF as a Flag to check if all the fields have been entered 
	//using dF to check if any field in not entered or entered worng
	int pF=0,nF=0,mF=0,iF=0,dF=0,cF=0;
	//opning the two files where the group info have to be stored
	FILE *fPtr1 = fopen("group.txt", "a");
	FILE *fP1 = fopen("gshadow.txt", "a");	
	//storing the data entered by the user in the commamd line
	int option;
	while((option = getopt(argc , argv , "n:p:i:m:"))!=-1){
		switch(option){
			case 'p':
				//performed is -p tag is user to enter the Group Password 
				pF++;
				if(pF==1){
					strcpy(P,optarg);
				}
				break;
			case 'n':
				//performed is -n tag is user to enter the Group Name
				nF++;
				if(nF==1){
					strcpy(N,optarg);
				}
				break;
			case 'i':
				//performed is -i tag is user to enter the Group ID 
				iF++;
				if(iF==1){
					strcpy(I,optarg);
				}
				break;
			case 'm':
				//performed is -m tag is user to enter the Group Members
				mF++;
				if(mF==1){
					strcpy(M,optarg);
				}								
				break;
			default:
				dF++;
		}
	}
	//this is done to check if the entered Group ID already exits in the system
	cF = check(I,cF);
	//thus function used for replacing the "," to ":" in the Members string
	strcpy(M,replace(M));
	// thus function used for encripting the entered password 
	strcpy(E,encript(P));
	//to check if all the critria for creating a group is saticfied
	if (iF==1 && mF==1 && nF==1 && pF==1 && dF==0 && cF==0){
		printf("\n\nThe group has been SUCCESSFULLY added !!!\n\n");
		strcpy(FN,N);
		//to format all the info other than pwd given by the user in a way to store it in group file
		strcpy(N,format_1(N,I,M));
		fputs(N, fPtr1);
		//to format all the info with the encripted pwd so as to store the data in the gshadow file
		strcpy(FN,format_2(FN,E,I,M));
		fputs(FN, fP1);
		
	}
	else
		//this is to display the syntax of the adduser command if user has done some mistake in entering the data
		print_Use();
	fclose(fPtr1);
	fclose(fP1);
}
