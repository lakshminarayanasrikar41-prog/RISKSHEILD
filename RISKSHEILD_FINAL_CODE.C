#include <stdio.h>
#include <string.h>
struct Transaction
{
int id;
char customer[50];
float amount;
char type[20];
int riskScore;
char riskLevel[20];
};
struct Transaction transactions[100];
int count = 0;
int calculateRisk(float amount)
{
int score = 0;
if(amount >= 100000)
score = 50;
else if(amount >=50000)
score = 30;
else if(amount >=20000)
score = 15;
else
score = 5;

return score;
}
void setRiskLevel(struct Transaction *t)
{
if(t->riskScore >= 50)
strcpy(t->riskLevel, "HIGH");
else if(t->riskScore >= 30)
strcpy(t->riskLevel, "MEDIUM");
else
strcpy(t->riskLevel, "LOW");
}
void searchTransaction()
{
int id;
printf("\nEnter Transaction ID to search: ");
scanf("%d", &id);
int found = 0;
int i;
for(i = 0; i < count; i++)
{
if(transactions[i].id == id)
{	
printf("\nTransaction Found!\n");
printf("Customer   : %s\n", transactions[i].customer);
printf("Amount   : %.2f\n", transactions[i].amount);
printf("Type   : %s\n", transactions[i].type);
printf("Risk Score : %d\n", transactions[i].riskScore);
printf("Risk Level : %s\n", transactions[i].riskLevel);
found = 1;
break;
}
}
if(found == 0)
{
printf("\nTransaction not found.\n");
}
}
void loadData()
{
FILE *fp;
fp = fopen("transactions.txt", "r");
if(fp == NULL)
{
return;
}
count = 0;
while(count < 100 &&
fscanf(fp, "%d %49s %f %19s %d %19s",
&transactions[count].id,
&transactions[count].customer,
&transactions[count].amount,
&transactions[count].type,
&transactions[count].riskScore,
&transactions[count].riskLevel) == 6)
{
	count++;
}
fclose(fp);
}
int main()
{
int choice;
loadData();
do
{
printf("\n\n===============================");
printf("\n             RISKSHEILD");
printf("\n Transaction Risk Monitoring");
printf("\n-------------------------------------");
printf("\n     SPEND WISE | STAY SAFE");
printf("\n          BUILD TOMORROW");
printf("\n===============================");
printf("\n1. Add Transaction");
printf("\n2. View Transactions");
printf("\n3. Search Transaction");
printf("\n4. Save Data");
printf("\n5. Exit");
printf("\n\n Enter your choice:");
scanf("%d", &choice);
switch(choice)
{
case 1:
{
if(count >= 100)	
{
printf("\nTransaction limit reached!\n");
break;
}
printf("\nEnter Transaction ID:");
scanf("%d", &transactions[count].id);
int i;
int duplicate = 0;
for(i = 0; i < count; i++)
{
if(transactions[i].id == transactions[count].id)
{
duplicate = 1;
break;
}
}
if(duplicate == 1 )
{
printf("\nTransaction ID already exists!\n");
break;
}
printf("Enter Customer Name:");
scanf("%49s",transactions[count].customer);
printf("Enter Transaction Amount:");
scanf("%f", &transactions[count].amount);
if(transactions[count].amount <= 0)
{
printf("Invalid amount!\n");
break;
}   
printf("Enter Transaction Type:");
scanf("%19s", transactions[count].type);
transactions[count].riskScore = calculateRisk(transactions[count].amount);
setRiskLevel(&transactions[count]);
printf("\ntransaction added successfully!\n");
printf("Risk Score : %d\n", transactions[count].riskScore);
printf("Risk Level : %s\n", transactions[count].riskLevel);
count++;
break;
}
case 2:
if(count == 0)
{
printf("\nNo transactions availble.\n");
break;
}
printf("\n===== TRANSACTION REPORT =====\n");
int i;
for(i = 0; i < count; i++)
{
printf("\nTransaction ID : %d", transactions[i].id);
printf("\nCustomer      : %s", transactions[i].customer);
printf("\nAmount        : %.2f", transactions[i].amount);
printf("\nType          : %s\n", transactions[i].type);
printf("\nRisk Score    : %d", transactions[i].riskScore);
printf("\nRisk level    : %s\n", transactions[i].riskLevel);
}
break;


case 3:
searchTransaction();
break;
case 4:
FILE *fp;
fp = fopen("transactions.txt", "w");
if(fp == NULL)
{
printf("\nFile opening error!\n");
break;
}
int j;
for(j = 0; j < count; j++)
{
fprintf(fp, "%d %s %.2f %s %d %s\n",
transactions[j].id,
transactions[j].customer,
transactions[j].amount,
transactions[j].type,
transactions[j].riskScore,
transactions[j].riskLevel);
}
fclose(fp);
printf("\nData saved successfully!\n");
break;
case 5:	
printf("\nThank you for using RISKSHEILD!\n");
break;
default:
printf("\nInvalid choice!\n");
}
} while(choice != 5);
return 0;
}





