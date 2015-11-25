#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#include<string.h>
typedef struct line
{
    int add;
    char lbl[10],comm[20],operand[20],object[20];
    struct line *next;
}line;


int insertq(char program[],line **r,line **f,int *start)
{

    FILE *f1,*info,*f2,*O;
    line *np;
    int flag=0,add;
    char Pname[7],symbol[25],opc[25];
    int LOCCTR=0000,error=0,num,l;
    f2=fopen("Symbol.txt","w");
    fclose(f2);
    f1=fopen(program,"r");
    info=fopen("Name.txt","w");
    if(f1!=NULL)
    {
        np=(line*)malloc(sizeof(line));
        fscanf(f1,"%s ",&np->lbl);
        strcpy(Pname,np->lbl);
        fscanf(f1,"%s ",&np->comm);
        if(strcmp(np->comm,"START")!=0)
        {
            printf("ERROR:invalid format!!");
            error=1;
            return error;
        }
        if(*f==NULL)
        {
            np->next=NULL;
            *f=np;
            *r=np;
        }
        else
        {
            np->next=NULL;
            (*r)->next=np;
            *r=np;
        }
        np->add=0000;
        strcpy(np->operand,"");
        fscanf(f1,"%X\n",&LOCCTR);
        *start=LOCCTR;
        while(!feof(f1))
        {
            np=(line*)malloc(sizeof(line));
            fscanf(f1,"%s ",&np->lbl);
            fscanf(f1,"%s ",&np->comm);
            if(strcmp(np->comm,"RSUB")!=0)
                fscanf(f1,"%s ",&np->operand);
            else
                strcpy(np->operand,"");
            if(strcmp(np->comm,"START")!=0)
                np->add=LOCCTR;
            else
                np->add=0;
            O=fopen("opcode.txt","r");
            while(!feof(O))
            {
                fscanf(O,"%s ",opc);
                if(strcmp(np->comm,opc)==0 || strcmp(np->comm,"WORD")==0 || strcmp(np->comm,"BYTE")==0 ||strcmp(np->comm,"RESW")==0||strcmp(np->comm,"RESB")==0 || strcmp(np->comm,"RSUB")==0 )
                {
                    flag=0;
                    printf("%s-%s\n",np->comm,opc);
                    break;

                }
                else
                {
                    flag=1;

                }
            }
            fclose(O);
            if(flag==1)
            {
                printf("\nInvalid mnemonic used... %s",np->comm);
                error=1;
                getch();
                return error;
            }
            flag=0;
            if(*f==NULL)
            {
                np->next=NULL;
                *f=np;
                *r=np;
            }
            else
            {
                np->next=NULL;
                (*r)->next=np;
                *r=np;
            }
            f2=fopen("Symbol.txt","r");
            while(!feof(f2))
            {
                fscanf(f2,"%s ",symbol);
                fscanf(f2,"%X ",&add);
                if(strcmp(np->lbl,symbol)==0)
                {
                    printf("\nDuplicate Labels!!");
                    flag=1;
                    return 1;
                }
            }
            fclose(f2);
            if(flag==0 && strcmp(np->comm,"START")!=0 && strcmp(np->comm,"END")!=0 && strcmp(np->lbl,"##")!=0)
            {
                f2=fopen("Symbol.txt","a");
                fprintf(f2,"%s %04X\n",np->lbl,np->add);
                fclose(f2);
            }
            flag=0;
            if(strcmp(np->comm,"END")==0)
            {
                info=fopen("info.txt","w");
                fprintf(info,"%s\n%d",Pname,LOCCTR-*start+1);
                fclose(info);
                return 0;
            }
            else if(strcmp(np->comm,"RESB")==0)
            {
                num=atoi(np->operand);
                LOCCTR+=num;
            }
            else if(strcmp(np->comm,"RESW")==0)
            {
                num=atoi(np->operand);
                LOCCTR+=num*3;
            }
            else if(strcmp(np->comm,"WORD")==0)
                LOCCTR+=3;
            else if(strcmp(np->comm,"BYTE")==0)
            {
                l=strlen(np->operand);
                LOCCTR+=l;
            }
            else
                LOCCTR+=3;
        }
    }
    return 1;
}

