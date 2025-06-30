#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct Account{ 
    int accountNumber ;  char name[50];
    float balance; 

};

void createAccount();
void depositMoney();
void withdrawMoney();
void viewAccount();
void displayMenu();

int main(){
    int choice;
    while(1){ displayMenu();
        printf("Enter your choice:");
       if (scanf("%d",&choice) !=1){
        printf("Invalid input! Please enter a number.\n");
        while(getchar() !='\n');
        continue;
       }

        switch(choice){

            case 1:
            createAccount();
            break;
            case 2:
            depositMoney();
            break;
            case 3:
            withdrawMoney();
            break;
            case 4:
            viewAccount();
            break;
            case 5:
            printf("Exiting the program.\n");
            exit(0);
            break;
            default:
            printf("Invalid choice.Please try again.\n");
        }
}

    
return 0;
}
void displayMenu()
{
    printf("\n---Bank Management System---\n");
   printf("1. Creat Account\n");
   printf("2. Deposit Money\n");
   printf("3. Withdraw Money\n");
   printf("4. Veiw Account\n");
   printf("5. Exit\n");
}

void createAccount(){
    FILE *file = fopen("accounts.dat","ab");
    struct Account newAccount;
    if(file == NULL){
        printf("Error opening file.\n");
        return;
}
printf("Enter account number:");
scanf("%d",&newAccount.accountNumber);
printf("Enter name:");
scanf("%s",newAccount.name);
printf("Enter initial deposit:");
scanf("%f",&newAccount.balance);

fwrite(&newAccount,sizeof(struct Account),1,file);
fclose(file);
printf("Account created successfully!\n");
}
void depositMoney()
{
    FILE *file = fopen("accounts.dat","rb+");
    struct Account account;
    int accountNumber;
    float depositAmount;
    int found =0;

    if(file == NULL){
        printf("Error opening file.\n");
        return;
    }
    printf("Enter account number:");
    scanf("%d",&accountNumber);

    while 
    (fread(&account,sizeof(struct Account),1,file))
    {
        if(account.accountNumber ==  accountNumber) {
            found =1;
            printf("Enter amount to deposit:");
            scanf("%f",&depositAmount);
            account.balance +=depositAmount;
            fseek(file,-sizeof(struct Account),SEEK_CUR);
            fwrite(&account,sizeof(struct Account),1,file);
            printf("Deposit succesfully! New balance:%.2f\n",account.balance);
            break;
        }
    }
     
    if(!found){
        printf("Account not found.\n");
    }

    fclose(file);
}

void withdrawMoney(){
    FILE *file = fopen("accounts.dat","rb+");
    struct Account account;
    int accountNumber;
    float withdrawAmount;
    int found=0;

    if(file == NULL){
        printf("Enter opening file.\n");
        return;
    }

    printf("Enter account number:");
    scanf("%d",&accountNumber);
    while (fread(&account,sizeof( struct Account),1,file)){
        if(account.accountNumber == accountNumber)
{
    found=1;
    printf("Enter amount to withdraw:");
    scanf("%f",&withdrawAmount);
    if(withdrawAmount> account.balance){
        printf("Insufficient balance.\n");
    }
    else{
        account.balance-=withdrawAmount;
        fseek(file,-sizeof(struct Account),SEEK_CUR);
        fwrite(&account,sizeof(struct Account),1,file);
        printf("Withdrawal successfully ! New balance:%2f\n",account.balance);
    }
    break;
}
    }
    if(!found){
        printf("Account not found.\n");
    }
    fclose(file);
}
void viewAccount(){
    FILE *file = fopen("accounts.dat","rb");
    struct Account account;
    int accountNumber;
    int found=0;
    if(file == NULL){
        printf("Error opening file.\n");
        return ;
    }
    printf("Enter account number:");
    scanf("%d",&accountNumber);
    while(fread(&account,sizeof(struct Account),1,file))
    {
        if(account.accountNumber == accountNumber)
        {
            found =1;
            printf("\n---Account Details---\n");
            printf("Account Number:%d\n",account.accountNumber);
            printf("Name:%s\n",account.name);
            printf("Balance:%2f\n",account.balance);
            break;
        }
    }
    if(!found){
        printf("Account not found.\n");
    }
    fclose(file);
 }

 