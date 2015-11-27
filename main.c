#include<stdio.h>
#include<stdlib.h>
#include"assemble.h"
#include"read.h"

int main()
{
    int ch,e;
    while(1)
    {
        system("cls");
        printf("\n\n\t\tASSEMBLER");
        printf("\n\t\t1.Get Object Program Of a Program File");
        printf("\n\t\t2.Text Files");
        printf("\n\t\t3.Exit");
        fflush(stdin);
        printf("\n\t\tEnter Your Choice [1..3]:");
        scanf("%d",&ch);
        switch(ch)
        {
            case 1:e=mainp();
                   if(e==1)
                   {
                       printf("\n Additional files can have Wrong data");
                   }
                   else
                       printf("\nObject Program is stored in Oprogram.txt");
                   getch();
                   break;
            case 2:readmain();
                   break;
            case 3:exit(1);

            default:printf("\n Invalid Input!!");

        }
    }
    return 0;
}
