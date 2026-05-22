#include "ACCOUNT.h"

int accountcount=0;;
struct account a[MAX];

void createaccount()
{       
	int num;
	printf("Enter the date : ");
	scanf("%s",a[accountcount].account_issue_date);
	printf("Enter the name : ");
	scanf(" %[^\n]",a[accountcount].name);
	printf("Enter the age : ");
	scanf(" %d",&(a[accountcount].age));
	while(1)
	{
		printf("Select the gender  \nPress 1 : Female\nPress 2 : Male\nPress 3 : Transgender\n");
        	scanf("%d",&num);
	        if(num==1)
          		{strcpy(a[accountcount].gender,"Female");break;}
		else if(num==2)
            		{strcpy(a[accountcount].gender,"Male");break;}
		else if(num==3)
                        {strcpy(a[accountcount].gender,"Transgender");break;}
		else
			printf("You Enter invalid choise.....\n");
	}
	printf("Enter the phone number : ");
        scanf("%ld",&(a[accountcount].phonenumber));
	printf("Enter the email id : ");
        scanf(" %s",a[accountcount].emailid);
        printf("Enter the address : ");
        scanf(" %[^\n]",a[accountcount].address);
	char str[10];
        sprintf(str, "%d", accountcount+1000);
        strcpy(a[accountcount].accountnumber,"0XSBI");
	strncat(a[accountcount].accountnumber,a[accountcount].name,2);
	strncat(a[accountcount].accountnumber,a[accountcount].address,2);
	strcat(a[accountcount].accountnumber,str);
	printf("Your account number is : %s\n",a[accountcount].accountnumber);
	while(1)
	{
		printf("Enter your password (contain 4 digit number) : ");
        	scanf("%d",&(a[accountcount].password));
	        if(a[accountcount].password<1000)
		    printf("Password does not contain 4 digits....\n");
	        else if(a[accountcount].password>9999)
		    printf("Password is greater that 4 digits....\n");
	        else
	           {printf("Password is created successfully....\n");break;}
	}
	a[accountcount].debitcount=0;
        a[accountcount].creditcount=0;
        a[accountcount].totalamount=0;
        a[accountcount].active=1;
	a[accountcount].passwordchecker=0;
	a[accountcount].blocked=0;
	accountcount++;
}

int passwordchecker(int password,int accountcount)
{
	//if(a[accountcount].passwordchecker>=3)
	  //      {a[accountcount].blocked=1;}
	//if(a[accountcount].blocked==1)
	    //    {printf("This account is blocked....\n");return 2;}
	if(a[accountcount].active==0)
                {printf("This account is inactive....\n");return 2;}
        else if(a[accountcount].password==password)
	        {a[accountcount].passwordchecker=0;return 1;}
	else if(a[accountcount].passwordchecker<2) 
	        {a[accountcount].passwordchecker++;printf("Password is wrong....\nOnly %d attempts remaining....\nYou have enter worng password for %d times....\nIf you enter 3 times wrong password then your account will automatically blocked....\n",3-a[accountcount].passwordchecker,a[accountcount].passwordchecker);return 0;}
        if(a[accountcount].passwordchecker>=2)
                {a[accountcount].blocked=1;}	
        if(a[accountcount].blocked==1)
                {printf("This account is blocked....\n");return 2;}
	return 0;
}

void deactivate_account()
{ 
	int password;char accountnumber[N];
	printf("Enter the account number : ");
	scanf("%s",accountnumber);
	for(int i=0;i<accountcount;i++)
	     if(!(strcmp(a[i].accountnumber,accountnumber)))
	        {  
		 if((a[i].blocked==0)&&(a[i].active==1))
                  {
		   printf("Enter the password :\t");
                   scanf("%d",&password);
		   int checker=passwordchecker(password,i); 
		   if(checker==2)
			   return;
		   else if(checker==1)
		           {
				   a[i].active=0;
		                   printf("Account is deactivated successfully....\n");
		                   return;
			   }
		   else
			   i--;
		  }
		  else
                      {a[i].blocked?printf("This account is not active...\n"):printf("This account is blocked...\n");return;}
		}
}

void debit_amount()
{       int amount,password;char accountnumber[N];int checker=0;;
	printf("Enter the account number : ");
	scanf("%s",accountnumber);
	for(int i=0;i<accountcount;i++)
	{
		if(!(strcmp(a[i].accountnumber,accountnumber)))
		{ 
		    if((a[i].blocked==0)&&(a[i].active==1))
                      {
			printf("Enter the password :\t");
			scanf("%d",&password);
			checker=passwordchecker(password,i);
			if(checker==2)
                           return;
                        else if(checker==1)
                           {
                                   printf("Enter the amount to withdraw : ");
				   scanf("%d",&amount);
				   if(amount<=a[i].totalamount)
				   {
					   printf("Enter today's date : ");
                                           scanf("%s",a[i].debit_date[(a[i].debitcount)]);
                                           a[i].debit[(a[i].debitcount)++]=amount;
					   a[i].totalamount-=amount;
					   strcpy(a[i].debit_member_id[(a[i].debitcount)-1],a[i].accountnumber);
					   printf("Withdraw process completed successfully....\nAmount withdraw : %d\nTotal Balance : %d\n",amount,a[i].totalamount);
				           return;
				   }
                                   printf("Insufficient balance....\nProcess cancelled....\n");
                                   return;
                           }
                        else
                           i--;
                }
		     else
                      {a[i].blocked?printf("This account is not active...\n"):printf("This account is blocked...\n");return;}
		}
	}
	printf("No such account number found....\n");
	return;
}


void credit_amount()
{       int amount,password;char accountnumber[N];int checker=0;;
        printf("Enter the account number : ");
        scanf("%s",accountnumber);
        for(int i=0;i<accountcount;i++)
        {
                if(!(strcmp(a[i].accountnumber,accountnumber)))
                {
                     if((a[i].blocked==0)&&(a[i].active==1))
		      {
			printf("Enter the password :\t");
                        scanf("%d",&password);
			checker=passwordchecker(password,i);
                        if(checker==2)
                           return;
                        else if(checker==1)
                           {
                                   printf("Enter the amount to credit : ");
                                   scanf("%d",&amount);
                                   if(amount>=0)
                                   {
					   printf("Enter today's date : ");
					   scanf("%s",a[i].credit_date[(a[i].creditcount)]);
					   a[i].credit[(a[i].creditcount)++]=amount;
                                           a[i].totalamount+=amount;
					   strcpy(a[i].credit_member_id[(a[i].creditcount)-1],a[i].accountnumber);
                                           printf("crediting process completed successfully....\nAmount credited : %d\nTotal Balance : %d\n",amount,a[i].totalamount);
                                           return;
                                   }
                                   printf("Invalid amount....\nProcess cancelled....\n");
                                   return;
                           }
                        else
                           i--;
		      }
		     else
		      {a[i].blocked?printf("This account is not active...\n"):printf("This account is blocked...\n");return;}
                }
        }
        printf("No such account number found....\n");
        return;
}

void display_account_holder_detail()
{
	char accountnumber[N];
	printf("Enter the account number : ");
	scanf("%s",accountnumber);
	for(int i=0;i<accountcount;i++)
	{
		if(!(strcmp(a[i].accountnumber,accountnumber)))
                { 
			  printf("Account holder name : %s\n",a[i].name);
                          printf("Account holder age : %d\n",a[i].age);
                          printf("Account holder gender : %s\n",a[i].gender);
			  printf("Account holder phonenumber: %ld\n",a[i].phonenumber);
			  printf("Account holder emailid : %s\n",a[i].emailid);
		}
	}
}

void transfermoney()
{
        int amount,password;char accountnumber1[N],accountnumber2[N];int checker=0;;
        printf("Enter your account number : ");
        scanf("%s",accountnumber1);
        for(int i=0;i<accountcount;i++)
        {
                if(!(strcmp(a[i].accountnumber,accountnumber1)))
			{
                    if((a[i].blocked==0)&&(a[i].active==1))
                      {
                        printf("Enter the password :\t");
                        scanf("%d",&password);
                        checker=passwordchecker(password,i);
                        if(checker==2)
				return;
                        else if(checker==1)
                           {     
			       printf("Enter receiver account number : ");
			       scanf("%s",accountnumber2);
			       for(int j=0;j<accountcount;j++)
			       {
				 if(!(strcmp(a[j].accountnumber,accountnumber2)))
				 {
                                   printf("Account holder name : %s\nEnter the amount transfer : ",a[j].name);
                                   scanf("%d",&amount);
                                   if(amount<=a[i].totalamount)
                                   {
					   printf("Enter today's date : ");
                                           scanf("%s",a[i].debit_date[(a[i].debitcount)]);
					   strcpy(a[j].credit_date[(a[j].creditcount)],a[i].debit_date[(a[i].debitcount)]);
					   a[j].credit[(a[j].creditcount)++]=amount;
					   a[j].totalamount+=amount;
                                           a[i].debit[(a[i].debitcount)++]=amount;
                                           a[i].totalamount-=amount;
					   strcpy(a[i].debit_member_id[(a[j].debitcount)-1],a[j].accountnumber);
					   strcpy(a[j].credit_member_id[(a[j].creditcount)-1],a[i].accountnumber);
                                           printf("transaction process completed successfully....\nAmount Transfered : %d\nTotal Balance : %d\n",amount,a[i].totalamount);
                                           return;
                                   }
				    printf("Insufficient balance....\nProcess cancelled....\n");
                                   return;
                                 } 
			       }
			   }
                        else
                           i--;
                }
                     else
                      {a[i].blocked?printf("This account is not active...\n"):printf("This account is blocked...\n");return;}
                }
        }
        printf("No such account number found....\n");
        return;
}



void display_ministatemtnt()
{
         char accountnumber[N];
         printf("Enter the account number : ");
         scanf("%s",accountnumber);
         for(int i=0;i<accountcount;i++)
         {
	  	 if(!(strcmp(a[i].accountnumber,accountnumber)))
                 {
		     if((a[i].blocked==0)&&(a[i].active==1))
                       { int password,checker;
                         printf("Enter the password :\t");
                         scanf("%d",&password);
                         checker=passwordchecker(password,i);
                         if(checker==2)
                                 return;
                         else if(checker==1)
                           {
                            printf("Account holder name : %s\n",a[i].name);
                            printf("Account holder age : %d\n",a[i].age);
                            printf("Account holder gender : %s\n",a[i].gender);
                            printf("Account holder phonenumber: %ld\n",a[i].phonenumber);
                            printf("Account holder emailid : %s\n",a[i].emailid);
			    int f=0,s=0;
		            for(int j=0;j<(a[i].debitcount+a[i].creditcount);j++)
                                {if( dategreater(a[i].debit_date[f],a[i].credit_date[s]))
					{printf("Date : %s   Debit : %d   From : %s\n", a[i].debit_date[f],a[i].debit[f],a[i].debit_member_id[(a[f].debitcount)-1]);
					 f++;}
				 else
					{printf("Date : %s   credit: %d   From : %s\n", a[i].credit_date[s],a[i].credit[s],a[i].credit_member_id[(a[s].creditcount)-1]);
						  s++;}
                                 
                                }
			    return;
			   }
                         else
                            i--;
                       }
                      else
                       {a[i].blocked?printf("This account is not active...\n"):printf("This account is blocked...\n");return;}
                 }
         }
         printf("No such account number found....\n");
         return;
 }

int dategreater(char *f,char *s)
{int d1,d2,m1,m2,y1,y2;
	d1=atoi(f);d2=atoi(s);
	m1=atoi(&f[3]);m2=atoi(&s[3]);
	y1=atoi(&f[6]);y2=atoi(&s[6]);
	if(y1>y2)
		return 1;
	if(y2>y1)
		return 0;
	if(m1>m2)
                return 1;
        if(m2>m1)
	        return 0;
	if(d1>d2)
                return 1;
        if(d2>d1)
                return 0;
        else
		return 0;
}


int main()
{  
	int num;
	while(1)
	{
	printf("Press 1 : create an new account\nPress 2 : Deactive account\nPress 3 : Debit amount\nPress 4 : Credit amount\nPress 5 : Transfer amount\nPress 6 : Ministatement\nPress 7 : Display account holder details\nPress 8 : Exit\n");
	scanf("%d",&num);
	if(num==1)
		createaccount();
	if(num==2)
		deactivate_account();
        if(num==3)
		debit_amount();
        if(num==4)
		credit_amount();
	if(num==5)
		 transfermoney();
	if(num==6)
		display_ministatemtnt();
	if(num==7)
		display_account_holder_detail();
	printf("Press 1 : Continue....\nPress 2 : Quit....\n");
	scanf("%d",&num);
	if(num==2)
		break;
	if(num==1)
		continue;
	else
	       {printf("enter invalid choise so process completed...\n");break;}
	
	}
}






  

