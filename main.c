/* Aim: To create a Employee Management record system
   Author: Danish Khan */
#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<string.h>
#include<windows.h>

/* List of Global Variables */
COORD coord={0,0}; // top-left corner of window

/**
    function: gotoxy
      input: x and y coordinates
     output: moves the cursor in specified position of console
*/
void gotoxy(int x,int y)
{
    coord.X=x;
    coord.Y=y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}

void loginID()
{
    char username[40];

    printf("\n  ::::::::::::::::::::::::::  LOGIN FORM  ::::::::::::::::::::::::::  \n\n");

  do{
        printf(" \n                       ENTER USERNAME:- ");
        scanf("%s",username);

    if(strcmp(username,"danishkhanbx") == 0 || strcmp(username,"rameshkapoorcc") == 0 || strcmp(username,"alexwoodhj") == 0 || strcmp(username,"dmitriantonovyg") == 0 || strcmp(username,"lizhangio") == 0)
    {
        printf("\n        Now Enter the Password\n");
    }else{
            printf("\n        SORRY !!!!  INCORRECT USERNAME");
            printf("\n        ENTER TO TRY AGAIN\n");
        }
        }while(strcmp(username,"danishkhanbx") != 0 && strcmp(username,"rameshkapoorcc") != 0 && strcmp(username,"alexwoodhj") != 0 && strcmp(username,"dmitriantonovyg") != 0 && strcmp(username,"lizhangio") != 0);
}
void loginPASSWORD()
{
    char password[40];

  do{
        printf(" \n                       ENTER PASSWORD:- ");
        scanf("%s",password);

        if(strcmp(password,"124421") == 0 || strcmp(password,"indxy91") == 0 || strcmp(password,"usrec420") == 0 || strcmp(password,"ussr675") == 0 || strcmp(password,"commu48") == 0)
        {
        }else
        {
            printf("\n        SORRY !!!!  INCORRECT PASSWORD");
            printf("\n        ENTER TO TRY AGAIN\n");
        }
    }while(strcmp(password,"124421") != 0 && strcmp(password,"indxy91") != 0 && strcmp(password,"usrec420") != 0 && strcmp(password,"ussr675") != 0 && strcmp(password,"commu48") != 0);
}

/** Main function started */

int main()
{
    loginID(); /// after password is right and id is wrong & id is wrong password is right, we have to exit the program and try again, if both is wrong can continue to to try as multiple time as possible
    loginPASSWORD();
    FILE *fp,*ft; /// file pointers
    char another,choice;

/** structure that represents employees */
    struct emp
    {
        char name[40]; // name of employee
        int age;    //  age of employee
        float bs; // basic salary of employee
    };
    struct emp e; /// structure variable creation

    char empname[40]; /// string t store name of employee
    long int recsize; /// size of each record of employee

/** open the file in binary read and write mode
* if the file EMP.DAT already exists then it will that file in read & write mode
* if the file doesn't exists it will simply create a new copy
*/
    fp = fopen("EMP.DAT","rb+");
    if(fp == NULL)
        {
        fp = fopen("EMP.DAT","wb+");
        if(fp == NULL)
        {
            printf("Sorry cannot open the file");
            exit(1);
        }
    }

    /// size of each record i.e. size of the structure variable e
    recsize = sizeof(e);

    /// infinite loop continue until the break statement encounter i.e. ENTER: 5
    while(1)
        {
            system("cls"); /// clear the console window

            gotoxy(25,8);
            printf("<**** EMPLOYEE RECORDS ****>");
            gotoxy(98,26);
            printf("- by DANISH KHAN");

            gotoxy(30,10); /// move the cursor to 30,10 from top-left corner
            printf("1. Add Record"); // option for adding new records

            gotoxy(30,12);
            printf("2. List of Records"); // option for showing existing records

            gotoxy(30,14);
            printf("3. Modify Records"); // option for editing records

            gotoxy(30,16);
            printf("4. Delete Records"); // option for deleting existing records

            gotoxy(30,18);
            printf("5. Exit"); // option for existing the ongoing program while saving the existing records

            gotoxy(30,20);
            printf("Your Choice: "); // ENTER the input according to the need
            fflush(stdin);  /// flush the input bufffer
            choice = getche(); /// get the input from keyboard

            switch(choice)
            {
              case '1':               /// if press 1 = Add Record
                system("cls");
                fseek(fp,0,SEEK_END);  /// search the file and move cursor to the end of the file
/// here 0 indicates moving 0 distance from the end of the file i.e. (0,0) co-ordinates

                another = 'y';
                while(another == 'y') /// if user wants to add another record
                    {
                     printf("<--- ADD RECORDS --->\n");
                    printf("\nEnter name: ");
                    scanf("%s",e.name);
                    printf("\nEnter age: ");
                    scanf("%d",&e.age);
                    printf("\nEnter basic salary: ");
                    scanf("%f",&e.bs);

                    fwrite(&e,recsize,1,fp);  /// write the record in the file, recsize adds size of the new structure e

                    printf("\nAdd another record(y/n)");
                    fflush(stdin);
                    another = getche();
                }
                break;

              case '2':               ///  List of Records
                system("cls");
                rewind(fp);      /// this moves file cursor to start of the file
                printf("<--- LIST OF EMPLOYEES --->\n");
                while(fread(&e,recsize,1,fp) == 1) /// read the file and fetch the record, one record per fetch
                {
                    printf("\n%s %d %.2f",e.name,e.age,e.bs); // prints the name, age, basic salary
                }
                getch();
                break;

              case '3':              ///  Modify Records
                  system("cls");
                  another = 'y';
                  printf("<--- MODIFY RECORDS --->\n");
                  while(another =='y')
                    {
                    printf("\n\nEnter the employee name to modify: ");
                    scanf("%s",empname);
                    rewind(fp);
                    while(fread(&e,recsize,1,fp) == 1) /// fetch all records from file
                    {
                        if(strcmp(e.name,empname) == 0)  /// if entered name matches with that in file
                        {
                            printf("\nEnter new name, age and salary: ");
                            scanf("%s %d %f",e.name,&e.age,&e.bs);
                            fseek(fp,-recsize,SEEK_CUR);  /// move the cursor 1 step back from current position
                            fwrite(&e,recsize,1,fp);  /// override the record
                            break;
                        }
                    }
                    printf("\n\nModify another record(y/n): ");
                    fflush(stdin);
                    another = getche();
                  }
                  break;

                case '4':           /// Delete Records
                    system("cls");
                    another = 'y';
                    printf("<--- DELETE RECORDS --->\n");
                    while(another == 'y')
                        {
                       printf("\nEnter name of employee to DELETE: ");
                       scanf("%s",empname);
                       ft = fopen("TEMP.dat","wb"); /// creates a intermediate file for temporary storage
                       rewind(fp);  /// moves record to starting of file
                       while(fread(&e,recsize,1,fp) == 1) /// read all records from file
                       {
                        if(strcmp(e.name,empname) != 0) /// if the entered record match
                        {
                            fwrite(&e,recsize,1,ft); /// move all records except the one that is to be deleted to temp file
                        }
                       }
                       fclose(fp);
                       fclose(ft);
                       remove("EMP.DAT"); /// remove the original file
                       rename("Temp.dat","EMP.DAT"); /// rename the temp file to original file name
                       fp = fopen("EMP.DAT","rb+");
                        printf("\nDelete another record(y/n): ");
                        fflush(stdin);
                        another = getche();
                    }
                    break;

                 case '5':            /// EXIT
                     fclose(fp); // close the file
                     exit(0);  /// exit from the program
            }
    }
    return 0;
}
