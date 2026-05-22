#ifndef ACCOUNT
#define ACCOUNT
#include <unistd.h> 
#include<stdio.h>
#include<stdlib.h>
#include<string.h>  
#define N 20
#define ADDRESS 50
#define DATE 11
#define MAX 100
struct account{
	char name[N];
	int age;  
	char gender[N]; 
	long int phonenumber;
	char emailid[MAX];   
	char address[ADDRESS];
	char accountnumber[N];   
	int password;
	char account_issue_date[DATE];
	int debit[MAX];
	int credit[MAX];
	char credit_member_id[MAX][N]; 
	char debit_member_id[MAX][N];  
	char debit_date[MAX][DATE]; 
	char credit_date[MAX][DATE];
	int debitcount,creditcount; 
	int totalamount;
	int active; 
	int passwordchecker;  
	int blocked;  
};  

void createaccount();
int passwordchecker(int password,int accountcount);
void deactivate_account();
void debit_amount();
void credit_amount();
void display_account_holder_detail();
void transfermoney();
int dategreater(char *f,char *s);
void display_ministatemtnt();


#endif

