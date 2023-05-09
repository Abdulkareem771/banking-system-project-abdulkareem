#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <time.h>

void input(); //gets input from user and save it in the data structure
void output(); //views the content in the data structure
void search();
void add(); //writes the input to the data file
void view(); //views all the data saved in the file
void create(); //in case the file doesn't exist, create one
int check(char x[100],unsigned long long int); // checks if the input name and phone number are previously existing or no.
void deposit();
void withdraw();
void check_money();
void acc_statement();
void check_PhNum();

int c2; //declaring a global variable so that we can make the function add() runs freely.
int tl,sl,ts; //declaring global variables to use when navigating through the file in binary mode
float stock;
unsigned long long int cn;

struct account {

    int num;
    unsigned long long int ph_num;
    char name[100];
};
struct account customer;
struct account buffer;

struct acc_sta
{
    char date[50]; //Here we declare an array to store the date and time of the Depositing or Withdrawing process.
    unsigned long long int ph_num;
    float deposit, withdraw;

};
struct acc_sta statement;


int main()
{
    int c,z,m,sc;
    printf("\n___________________________\n");
    create();
    system("cls");
    printf("\nEnter 1 to create a new account.\nEnter 2 for withdrawing and depositing processes.\nEnter 3 to export an account statement.\nEnter 4 to search for an account.\nEnter 5 to show all saved accounts.\nEnter 6 to exit.\n");
    while (scanf(" %d",&c)<1)
    {
        printf("\nError, please enter an integer number\n");
        printf("\nEnter 1 to create a new account.\nEnter 2 for withdrawing and depositing processes.\nEnter 3 to export an account statement.\nEnter 4 to search for an account.\nEnter 5 to show all saved accounts.\nEnter 6 to exit.\n");
        fflush(stdin);
        continue;
    }

  switch(c)
  {
      case 1:
        do
        {
            printf("\nAdding a new account\n\n");
            input();
        lo:
            printf("\nEnter 1 to confirm your input\nEnter 2 to exit\nEnter 3 to return to the main page\n");
            fflush(stdin);
            while (scanf("%d",&c2)<1)
            {
              printf("\nError, please enter an integer number\n");
              printf("\nEnter 1 to confirm your input\nEnter 2 to exit\nEnter 3 to return to the main page\n");
              fflush(stdin);
              continue;
            }

            switch(c2)
            {
                case 1:
                    customer.num++;
                    add(); // this function asks the user to confirm his input or exist the program.
                lo7:
                    printf("\n\nEnter 1 to add a new account again\nEnter 2 to return to the main page\nEnter 3 to exit\n");
                    fflush(stdin);
                    while(scanf("%d",&z)<1)
                        {
                            printf("\nError, please select a correct number\n");
                            printf("\n\nEnter 1 to add a new account again\nEnter 2 to return to the main page\nEnter 3 to exit\n");
                            fflush(stdin);
                            continue;
                        }
                        switch(z)
                        {
                            case 1:
                                continue;
                                break;
                            case 2:
                                main();
                                break;
                            case 3:
                                exit(0);
                                break;
                            default:
                                printf("\nError, please select a correct number\n");
                                goto lo7;
                        }
                    break;
                case 2:
                    exit(0);
                    break;
                case 3:
                    main();
                    break;
                default:
                    printf("\nError, please select the correct number.\n");
                    goto lo;
                    break;
            }
        }
        while(c=1);
        break;
      case 2:

          printf("\nEnter 1 for Depositing process.\nEnter 2 for Withdrawing process.\nEnter 3 to return to the main page.\nEnter 4 to exit.\n");
    lo_sc:
          fflush(stdin);
          while(scanf("%d",&sc)<1)
          {
              printf("\nError, please select the correct number.\n");
              printf("\nEnter 1 for Depositing process.\nEnter 2 for Withdrawing process.\nEnter 3 to return to the main page.\nEnter 4 to exit.\n");
              fflush(stdin);
              continue;
          }
          switch(sc)
          {
            case 1:
                deposit();
                break;
            case 2:
                withdraw();

                break;
            case 3:
                main();
                break;
            case 4:
                exit(0);
                break;
            default:
                printf("\nError, invalid input. Please select a correct number.\n");
                goto lo_sc;
                break;
          }
          break;
      case 3:
          printf("\n\n\tACCOUNT STATEMENT\n\n");
          acc_statement();
            break;
      case 4:
        printf("\nSearch for an account.\n");
        search();
        break;
      case 5:

            printf("\nList of the saved accounts.\n");
            view();
        lo5:
            printf("\n\nEnter 1 to return to the main page.\nEnter 2 to exit.\n");
            fflush(stdin);
            while(scanf("%d",&m)<1)
            {
                printf("\n\nError, please select a correct number\n");
                printf("\n\nEnter 1 to return to the main page.\nEnter 2 to exit.\n");
                continue;
            }
            switch(m)
            {
                case 1:
                    main();
                    break;
                case 2:
                    exit(0);
                    break;
                default:
                    printf("\n\nError, please select a correct number\n");
                    goto lo5;
            }
        break;
      case 6:
        exit(0);
        break;
      default :
        printf("Invalid input,please try again.");
        main();
      }
    return 0;
}

//defintion of used functions
void add(){

            //writting the input to the file
    FILE *fp=fopen("Data.dat","ab");
    fwrite(&customer,sizeof(customer),1,fp);
    fclose(fp);
    printf("\nAdded\n");
  return;
}


void input() //allows the user to store input in the account data structure
{
    //get the last customer number in the file and add one to it to view the current customer number.
    int r,n;
    char name[100];
    unsigned long long int num1;
    FILE *fp= fopen("Data.dat","rb"); //initializing file pointer to handle the file and using fopen funciton and read in binary mode, using the file extension .dat
    fseek(fp,0,SEEK_END); //changing the position to the end of file with 0 offset, means exactly after the last charecter
    tl=ftell(fp); //assigning the value of the current position (the end of file positoin) to the global varuable tl
    sl=sizeof(customer); //assigning the value of size of the structure customer
    ts=tl/sl;
    fseek(fp,(ts-1)*sl,SEEK_SET); //getting to the positin ritght before the last block in the file so we can obtain the number of the last account
    fread(&customer,sizeof(customer),1,fp); //reading the information from the current postion (right before the last block), storing them in customer structre, readin one block
    printf("\ncustomer number: %d",(customer.num+1)); //we didn't use ++customer.num because we don't want to make any changes in the file until the input is confirmed
    fclose(fp); //closing the file.
    printf("\nCustomer name: ");
    fflush(stdin);
    scanf("%[^\n]%*c",&customer.name); // [^\n] tells scanf to continue taking input until new line is encountered
    printf("Phone number : ");
    while (scanf("%llu",&customer.ph_num)<1)
        {
            printf("\nError, please enter the phone number\n");
            printf("Phone number : ");
            fflush(stdin);
            continue;
        }
    strcpy(name,customer.name); //Here we copy the name that user inputs to a new array.
    num1=customer.ph_num; //Here we copy the phone number that user inputs to a new variable.
    r=check(name,num1);

    //printf("\n\nN.Name is : %s\n\n",name);
    //printf("\n\nPh.Number is :%llu\n\n",num1);

    fopen("Data.dat","rb");
    fseek(fp,(ts-1)*sl,SEEK_SET); //getting to the positin ritght before the last block in the file so we can obtain the number of the last account
    fread(&customer,sizeof(customer),1,fp); //reading the information from the current postion (right before the last block), storing them in customer structre, readin one block
    fclose(fp); //closing the file.
    strcpy(customer.name,name); //Here and the next line we return the information (the name and the phone number) that user inputs them to the data structure.
    customer.ph_num=num1;
    if(r==1)
    {
        input();
    }
    else
    {
        printf("\n_____________________________________________________________________");
        return;
    }
}

void search()
{
    int choice,n,i,v,s,y;
    unsigned long long int num1;
    char name[50];

    FILE *fp=fopen("Data.dat","rb");
    fseek(fp,0,SEEK_END);
    sl=sizeof(customer);
    tl=ftell(fp);
    ts=tl/sl;
    printf("Enter 1 to search by number\nEnter 2 to search by name\nEnter 3 to search by phone number\nEnter 4 to return to the main page\nEnter 5 to exit\n\n");
    fflush(stdin);
    while (scanf("%d",&choice)<1)
    {
        printf("\nError, please enter an integer number\n");
        printf("Enter 1 to search by number\nEnter 2 to search by name\nEnter 3 to search by phone number\nEnter 4 to return to the main page\nEnter 5 to exit\n\n");
        fflush(stdin);
        continue;
    }

  switch(choice)
  {
    case 1:
   lo:
        printf("\nSearch by number\n");
        printf("\nEnter the number : \n");
        while (scanf("%d",&n)<1)
        {
            printf("\nError, please enter a correct number\n");
            fflush(stdin);
            continue;
        }
        if (n>ts || n<=0)
        {
            printf("\nThere is not an account for this number.\n");
        lo3:
            printf("\nEnter 1 to try again\nEnter 2 to search by other method\nEnter 3 to return to the main page\nEnter 4 to exit\n");
            fflush(stdin);
            while(scanf("%d",&y)<1)
            {
                printf("\nError, please enter a correct number\n");
                printf("\nEnter 1 to try again\nEnter 2 to search by other method\nEnter 3 to return to the main page\nEnter 4 to exit\n");
                fflush(stdin);
                continue;
            }
            switch(y)
            {
                case 1:
                    goto lo;
                    break;
                case 2:
                    search();
                    break;
                case 3:
                    main();
                    break;
                case 4:
                    exit(0);
                    break;
                default:
                    printf("\nError, please select a correct number\n");
                    goto lo3;
                    break;
            }
        }
        else
        {
            fseek(fp,(n-1)*sl,SEEK_SET);
            fread(&customer,sizeof(customer),1,fp);
            output();
        }
    lo_v:
        printf("\n\nEnter 1 to search again.\nEnter 2 to return to the main page.\nEnter 3 to exit.\n");
        fflush(stdin);
        while(scanf("%d",&v)<1)
        {
            printf("\nError, please enter a correct number\n");
            printf("\n\nEnter 1 to search again.\nEnter 2 to return to the main page.\nEnter 3 to exit.\n");
            fflush(stdin);
            continue;
        }
        switch(v)
        {
            case 1:
                search();
                break;
            case 2:
                main();
                break;
            case 3:
                exit(0);
                break;
            default:
                printf("\n\nError, invalid input. Please select a correct number.\n");
                goto lo_v;
                break;
        }
    break;
    case 2: //searching by name
    lo_case2:
        printf("\nSearching by name: \n");
        fseek(fp,(ts-1)*sizeof(customer),SEEK_SET); //getting to right before the last block
        fread(&customer,sizeof(customer),1,fp); //storring the information of the last block in the data structure
        n=customer.num; // getting the number of the last customer to help us loop thruogh the file
        fseek(fp,0,SEEK_SET); // return to the beggining of the file to start looping
        printf("\nEnter name to look for: ");
        fflush(stdin);
        scanf("%[^\n]%*c",name); // to allow the user to enter name until encountring newline (ignoring white spaces)
        for(i=1;i<=n;i++) //startting from one because the first block is stored in the position zero
            {
                fread(&customer,sizeof(customer),1,fp);
                if (strcmp(customer.name,name) ==0) //strcmp is a function that compares strings and results 0 if the strings are identical. it is defined in the <string.h>
                {
                    output();
                    v=1; //store a vlaue of 1 for v if a match is found
                    break;
                }
            }
        if (v!=1)
        printf("\nName has not been found\n");
    lo2:
        printf("Enter 1 to try again\nEnter 2 to search by another method \nEnter 3 to return to the main page\nEnter 4 to exit\n\n");
        fflush(stdin);
        while (scanf("%d",&y)<1)
        {
            printf("\nError, please enter an integer number\n");
            printf("Enter 1 to try again\nEnter 2 to search by another method \nEnter 3 to return to the main page\nEnter 4 to exit\n\n");
            fflush(stdin);
            continue;
        }
        switch(y)
            {
                case 1:
                    goto lo_case2;
                    break;
                case 2:
                    search();
                    break;
                case 3:
                    main();
                    break;
                case 4:
                    exit(0);
                    break;
                default:
                    printf("\nError, please select a correct number\n");
                    goto lo2;
                    break;
            }
    break;
    case 3:      //searching by phone number
    lo5:
        printf("\nSearching by phone number: \n");
        fseek(fp,(ts-1)*sizeof(customer),SEEK_SET); //getting to right before the last block
        fread(&customer,sizeof(customer),1,fp); //storring the information of the last block in the data structure
        n=customer.num; // getting the number of the last customer to help us loop thruogh the file
        fseek(fp,0,SEEK_SET); // return to the beggining of the file to start looping
        printf("\nEnter phone number: ");
        scanf("%llu",&num1);
        for(i=1;i<=n;i++) //startting from one because the first block is stored in the position zero
        {
            fread(&customer,sizeof(customer),1,fp);
            if ((customer.ph_num) == num1)
            {
                output();
                s=1;
                break;
            }
            s=0;
        }
        if (s!=1)
        printf("\nThere isn't any account with this phone number.\n\n");
    lo4:
        printf("Enter 1 to try again\nEnter 2 to search by another method \nEnter 3 to return to the main page\nEnter 4 to exit\n");
        fflush(stdin);
        while (scanf(" %d",&y)<1)
        {
            printf("\nError, please select a correct number\n");
            printf("Enter 1 to try again\nEnter 2 to search by another method \nEnter 3 to return to the main page\nEnter 4 to exit\n");
            fflush(stdin);
            continue;
        }
        switch(y)
            {
                case 1:
                    goto lo5;
                    break;
                case 2:
                    search();
                    break;
                case 3:
                    main();
                    break;
                case 4:
                    exit(0);
                    break;
                default:
                    printf("\nError, please select a correct number\n");
                    goto lo4;
                    break;
            }
      break;
    case 4:
        main();
        break;
    case 5:
        exit(0);
        break;
    default:
        printf("\nError, invalid input. Please select a correct number.\n\n");
        search();
        break;
  }
    fclose(fp);
    return;
}

void view()
{
    int n,i,m;
    FILE *fp=fopen("Data.dat","rb");
    fseek(fp,0,SEEK_END);
    sl=sizeof(customer);
    tl=ftell(fp);
    ts=tl/sl;
    fseek(fp,(ts-1)*sl,SEEK_SET);
    fread(&customer,sizeof(customer),1,fp);
    n=customer.num;
    fseek(fp,0,SEEK_SET);
    for(i=1;i<=n;i++)
    {
        fread(&customer,sizeof(customer),1,fp);
        output();
    }
    fclose(fp);
    return;

}

void output() //views the information of the last customer stored in the dara structure
{
  printf("\n\n_____________________________________________________________________________\n");
  printf("Customer Number: %d\n",customer.num);
  printf("Name: %s\n",customer.name);
  printf("Phone number: %llu\n",customer.ph_num);
  printf("\n___________________________________________________________________________________\n");
  return;
}
void create() //this function checks if there is an existing file, otherwise it would create a new one
{
    FILE *fp, *T;

    fp=fopen("Data.dat","rb");
    if (fp == NULL)
    {
        fp=fopen("Data.dat","wb"); //if the file does not exist, create one using the write mode.
    }
    fclose(fp);

    T=fopen("Transactions.dat","rb");
    if (T == NULL)
    {
        T=fopen("Transactions.dat","wb");
    }
    fclose(T);
    return;
}


int check(char x[100], unsigned long long int y)
{
    int i,n,v=0,s;
    FILE *fp= fopen("Data.dat","rb");
    fseek(fp,0,SEEK_END);
    sl=sizeof(customer);
    tl=ftell(fp);
    ts=tl/sl;
    fseek(fp,(ts-1)*sizeof(customer),SEEK_SET);
    fread(&customer,sizeof(customer),1,fp);
    n=customer.num;
    fseek(fp,0,SEEK_SET);
    for(i=1;i<=n;i++)
    {
        fread(&customer,sizeof(customer),1,fp);
        if (strcmp(customer.name,x) ==0) //Here we check if the name that user inputs is previously existing or no,by comparing between that name and accounts' names that are saved in the file.
        {
            v=1;
            break;
        }
    }
    if (v==1)
    {
        printf("\nYou can not create a new account with this name, because this name is previously existing.\n");
    }
    else
    {
        v=0;
    }
    fseek(fp,0,SEEK_SET);
    for(i=1;i<=n;i++)
    {
       fread(&customer,sizeof(customer),1,fp);
       if(customer.ph_num==y)
       {
           s=1;
           break;
       }
    }
    fclose(fp);
    if(s==1)
    {
        printf("\nYou can not create a new account with this Phone number, because this number is previously existing.\n");
    }
    else
    {
        s=0;
    }
    if (s==1 || v==1)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void deposit()
{
    FILE *fp, *T;
    time_t t;
    int sc2,a;
    char date[20];

    check_PhNum();
    printf("\n\nEnter the amount of money that you want to deposit : ");
    fflush(stdin);
    while(scanf("%f",&statement.deposit)<1)
    {
        printf("\nError, invalid input. Please enter a correct number.\n");
        fflush(stdin);
        continue;
    }
    statement.withdraw=0;
    statement.ph_num=customer.ph_num;
    time(&t); // Here we get the amount of the time as seconds object.
    strcpy(date,ctime(&t));//Here we get the date and the time from the computer and store it to the date array.

lo_sc2:

    printf("\nEnter 1 to confirm your input.\nEnter 2 to return to the main page.\nEnter 3 to exit.\n\n");
    fflush(stdin);
    while(scanf("%d",&sc2)<1)
    {
        printf("\nError, please select a correct number.\n");
        printf("\nEnter 1 to confirm your input.\nEnter 2 to return to the main page.\nEnter 3 to exit.\n\n");
        fflush(stdin);
        continue;
    }
    switch(sc2)
    {
        case 1:
            T=fopen("Transactions.dat","a");
            fprintf(T,"%llu  \t%.3f\t%.3f\tDepositing \t%s", statement.ph_num, statement.deposit, statement.withdraw,date); //Here we write the information of the transaction to the file by using fprintf() function.
            fclose(T);

            printf("\nThe Depositing process is successfully finished.\n");
    lo_sc3:
            printf("\n\nEnter 1 to do Depositing process again.\nEnter 2 to return to the main page.\nEnter 3 to exit.\n");
            fflush(stdin);
            while(scanf("%d",&a)<1)
            {
                printf("\nError, please select a correct number.\n");
                printf("\nEnter 1 to do Depositing process again.\nEnter 2 to return to the main page.\nEnter 3 to exit.\n");
                fflush(stdin);
                continue;
            }
            switch(a)
            {
                case 1:
                    deposit();
                    break;
                case 2:
                    main();
                    break;
                case 3:
                    exit(0);
                    break;
                default:
                    printf("\nError, please select a correct number.\n");
                    goto lo_sc3;
                    break;
            }
            break;
        case 2:
            main();
            break;
        case 3:
            exit(0);
            break;
        default:
            printf("Invalid input,please try again.");
            goto lo_sc2;
            break;
    }
    return;
}

void withdraw()
{
   FILE *fp, *T;
    time_t t;
    int sc,a,m;
    float dep,sck;
    char date[20];

    check_money();
    printf("\n\nEnter the amount of money that you want to withdraw : ");
    fflush(stdin);
    while(scanf("%f",&statement.withdraw)<1)
    {
        printf("\nError, invalid input. Please enter a correct number.\n");
        fflush(stdin);
        continue;
    }

    if(statement.withdraw>stock)
    {
        printf("\n\nSorry, you can not withdraw this amount of money, because you don't have enough money.\n");
    }
    else
    {
        statement.deposit=0;
        statement.ph_num=customer.ph_num;
        time(&t); // Here we get the amount of the time as seconds object.
        strcpy(date,ctime(&t));//Here we get the date and the time from the computer and store it to the date array.

    lo_sc:

        printf("\nEnter 1 to confirm your input.\nEnter 2 to return to the main page.\nEnter 3 to exit.\n\n");
        fflush(stdin);
        while(scanf("%d",&sc)<1)
        {
            printf("\nError, please select a correct number.\n");
            printf("\nEnter 1 to confirm your input.\nEnter 2 to return to the main page.\nEnter 3 to exit.\n\n");
            fflush(stdin);
            continue;
        }
        switch(sc)
        {
            case 1:
                T=fopen("Transactions.dat","a");
                fprintf(T,"%llu  \t%.3f\t%.3f\tWithdrawing \t%s", statement.ph_num, statement.deposit, statement.withdraw,date); //Here we write the information of the transaction to the file by using fprintf() function.
                fclose(T);

                printf("\nThe Withdrawing process is successfully finished.\n");
        lo_sc3:
                printf("\n\nEnter 1 to do Withdrawing process again.\nEnter 2 to return to the main page.\nEnter 3 to exit.\n");
                fflush(stdin);
                while(scanf("%d",&a)<1)
                {
                    printf("\nError, please select a correct number.\n");
                    printf("\nEnter 1 to do Depositing process again.\nEnter 2 to return to the main page.\nEnter 3 to exit.\n");
                    fflush(stdin);
                    continue;
                }
                switch(a)
                {
                    case 1:
                        withdraw();
                        break;
                    case 2:
                        main();
                        break;
                    case 3:
                        exit(0);
                        break;
                    default:
                        printf("\nError, please select a correct number.\n");
                        goto lo_sc3;
                        break;
                }
                break;
            case 2:
                main();
                break;
            case 3:
                exit(0);
                break;
            default:
                printf("Invalid input,please try again.");
                goto lo_sc;
                break;
        }
    }
        lo_m:
                printf("\n\nEnter 1 to return to the main page.\nEnter 2 to exit.\n");
                fflush(stdin);
                while(scanf("%d",&m)<1)
                {
                    printf("\n\nError, please select a correct number\n");
                    printf("\n\nEnter 1 to return to the main page.\nEnter 2 to exit.\n");
                    continue;
                }
                switch(m)
                {
                    case 1:
                        main();
                        break;
                    case 2:
                        exit(0);
                        break;
                    default:
                        printf("\n\nError, please select a correct number\n");
                        goto lo_m;
                }

    return ;
}

void check_money()
{
    FILE *T;
    char Date[27], st[20];
    char Buf[70]; // Here we declare this array just to use it as a buffer to count the lines of the file (Transactions.dat).
    unsigned long long int pnum,num;
    float De, Wd,SumDe=0,SumWi=0;
    int i,n=0;
    check_PhNum();
    T=fopen("Transactions.dat","r");
    if (T==NULL)
    {
        printf("\n\nThe file can not be opened\n");
    }
    else
    {
        n=0;
        while(!feof(T))
        {
            fgets(Buf,70,T);
            n++; // Here we account the number of lines of the file (Transactions.dat).
        }
        rewind(T); // This function returns the file position to the beginning of the file (T).
        for (i=1;i<n;i++)
        {
            fscanf(T,"%llu %f %f %s", &num, &De, &Wd, st);
            fgets(Date,27,T);
            if (num==cn)
            {
                SumDe=SumDe+De;
                SumWi=SumWi+Wd;
                stock=SumDe-SumWi;
            }
        }
    }
    //printf("\n\nThe stock account = %f\n",stock);
    fclose(T);
    return;
}
void check_PhNum()
{
    FILE *fp;
    int i,s=0,n,b;
    printf("\nEnter the customer phone number : ");
    fflush(stdin);
    while (scanf("%llu",&cn)<1)
    {
        printf("\n\nError, please enter a correct number\n");
        fflush(stdin);
        continue;
    }
    fp=fopen("Data.dat","rb");
    fseek(fp,0,SEEK_END);
    sl=sizeof(customer);
    tl=ftell(fp);
    ts=tl/sl;
    fseek(fp,(ts-1)*sizeof(customer),SEEK_SET);
    fread(&customer,sizeof(customer),1,fp);
    n=customer.num;
    fseek(fp,0,SEEK_SET);
    for(i=1;i<=n;i++)
    {
       fread(&customer,sizeof(customer),1,fp);
       if(customer.ph_num==cn)
       {
           s=1;
           break;
       }
    }
    fclose(fp);
    if(s==1)
    {
        output();
        return;
    }
    else
    {
        printf("\nIt doesn't exist any account with this phone number.\nPlease first create an account and then you can easily complete.\n");
        lo_sc4:
            printf("\nEnter 1 to return to the main page.\nEnter 2 to exit.\n");
            fflush(stdin);
            while(scanf("%d",&b)<1)
            {
                printf("\nError, please select a correct number.\n");
                printf("\nEnter 1 to return to the main page.\nEnter 2 to exit.\n");
                fflush(stdin);
                continue;
            }
            switch(b)
            {
                case 1:
                    main();
                    break;
                case 2:
                    exit(0);
                    break;
                default:
                    printf("\nError, please select a correct number.\n");
                    goto lo_sc4;
                    break;
            }
    }

}

void acc_statement()
{
    FILE *S, *T;
    time_t t;
    char name[100], date[27], Date[27], st[20];
    char Buf[70]; // Here we declare this array just to use it as a buffer to count the lines of the file (Transactions.dat).
    unsigned long long int pnum,num;
    float De, Wd,SumDe=0,SumWi=0;
    int i,n=0,m;
    check_PhNum();
    time(&t);
    strcpy(date,ctime(&t));
    strcpy(name,customer.name);
    pnum=customer.ph_num;

    S=fopen("Statement.html","w");
    fputs("<!DOCTYPE html>\n <html lang='en'>\n  <head>\n   <body dir='ltr'>\n     <h1>ACCOUNT STATEMENT</h1>\n",S);
    fprintf(S,"     <h2>%s</h2>\n     <h2>%llu</h2>\n     <h3>%s</h3>\n", name, pnum, date);
    fputs("     <table width='800px'>\n        <tr height='40' bgcolor='#949797'>\n        <th align='center' valign='middle'>Date</th>\n        <th align='center' valign='middle'>Amount</th>\n        <th align='center' valign='middle'>Amount</th>\n        <th align='center' valign='middle'>Statement</th>\n     </tr>\n  \n",S);

    T=fopen("Transactions.dat","r");
    if (T==NULL)
    {
        printf("\n\nThe file can not be opened\n");
    }
    else
    {
        n=0;
        while(!feof(T))
        {
            fgets(Buf,70,T);
            n++;
            //printf("%s",Buf);
        }
        rewind(T); // This function returns the file position to the beginning of the file (T).
        for (i=1;i<n;i++)
        {
            fscanf(T,"%llu %f %f %s", &num, &De, &Wd, st);
            fgets(Date,27,T);
            if (num==pnum)
            {
                SumDe=SumDe+De;
                SumWi=SumWi+Wd;
                stock=SumDe-SumWi;
                fprintf(S,"       <tr height='40' bgcolor='#5FD6E2'>\n         <td align='center' valign='middle'>%s</td>\n         <td align='center' valign='middle'>%.3f $</td>\n         <td align='center' valign='middle'>%.3f $</td>\n         <td align='center' valign='middle'>%s</td>\n       </tr>\n  \n",Date , De, Wd, st);
            }
        }
    }
    //printf("\n\nThe stock account = %f\n",stock);
    fclose(T);
    fprintf(S,"       <tr height='20'>\n       <td></td>\n       </tr>\n  \n       <tr height='40' bgcolor='#949797'>\n         <td align='center' valign='middle'>Available balance</td>\n         <td align='center' valign='middle'>%.3f $</td>\n       </tr>\n  \n       </table>\n     </body>\n   </head>\n</html>\n",stock);
    fclose(S);
    system("explorer Statement.html");
    //exit(0);
    lo_m:
                printf("\n\nEnter 1 to return to the main page.\nEnter 2 to exit.\n");
                fflush(stdin);
                while(scanf("%d",&m)<1)
                {
                    printf("\n\nError, please select a correct number\n");
                    printf("\n\nEnter 1 to return to the main page.\nEnter 2 to exit.\n");
                    continue;
                }
                switch(m)
                {
                    case 1:
                        main();
                        break;
                    case 2:
                        exit(0);
                        break;
                    default:
                        printf("\n\nError, please select a correct number\n");
                        goto lo_m;
                }

    return;
}
