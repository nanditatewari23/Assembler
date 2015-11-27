#include<stdio.h>
#include<stdlib.h>

int Sym()
{
    FILE *s;
    int c;
    s=fopen("Symbol.txt","r");
    if(s)
    {
        while ((c = getc(s)) != EOF)
            putchar(c);
        fclose(s);
    }
    else
    {
        printf("\n\t\t File doesn't exist!!");
    }
    return 0;
    fclose(s);
}
int op()
{
    FILE *o;
    int num;
    o=fopen("opcode.txt","r");
    if(o)
    {
        while(!feof(o))
        {
            while((num=getc(o))!=EOF)
                putchar(num);
            return 0;
            fclose(o);
        }

    }
    else
        printf("\n\t\t File doesn't exist!!");


}
int mid()
{
    FILE *mi;
    int n;
    mi=fopen("mid.txt","r");
    if(mi)
    {
        while(!feof(mi))
        {
            while((n=getc(mi))!=EOF)
                putchar(n);
            return 0;
            fclose(mi);
        }
    }
    else
        printf("\n\t\t File doesn't exist!!");
    return 0;

}
int ob()
{
    FILE *ob;
    int o;
    ob=fopen("oprogram.txt","r");
    if(ob)
    {
        while(!feof(ob))
        {
            while((o=getc(ob))!=EOF)
                putchar(o);
            return 0;
            fclose(ob);
        }

    }
    else
        printf("\n\t\t File doesn't exist!!");
    fflush(stdin);
    return 0;
}
int readmain()
{
    int ch;
    while(1)
    {
        system("cls");
        printf("\n\t\t TEXT FILE");
        printf("\n\n\t\t1.SYMTAB");
        printf("\n\t\t2.OPTAB");
        printf("\n\t\t3.INTERMEDIATE FILE");
        printf("\n\t\t4.OBJECT PROGRAM");
        printf("\n\t\t5.MAIN MENU");
        printf("\n\t\t Enter Your Choice[1..3]:");
        scanf("%d",&ch);
        switch(ch)
        {
            case 1:Sym();
                    break;
            case 2:op();
                    break;
            case 3:mid();
                    break;
            case 4:ob();
                    break;
            case 5:return 0;
            default:printf("\nINVALID INPUT!");
        }
        getch();
    }
}
