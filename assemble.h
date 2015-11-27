#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#include<string.h>
typedef struct line                                      //the data read from the file is stored in this structure
{
    int l,add;
    char lbl[10],comm[20],opp[20];
    struct line *next;
}line;


int Pass1(char program[],line **r,line **f,int *start)       //perform addressing
{

    FILE *f1,*info,*f2,*O;
    line *np;
    int flag=0,add,L=1;
    char Pname[7],symbol[25],opc[25];
    int LOCCTR=0000,error=0,num,l;
    f2=fopen("Symbol.txt","w");                         //SYMTAB
    fclose(f2);
    f1=fopen(program,"r");
    if(f1==NULL)
    {
        printf("\nFile Doesn't Exists!");
        return 1;
    }
    if(f1!=NULL)
    {
        np=(line*)malloc(sizeof(line));
        fscanf(f1,"%s ",&np->lbl);
        strcpy(Pname,np->lbl);
        fscanf(f1,"%s ",&np->comm);
        if(strcmp(np->comm,"START")!=0)
        {
            printf("ERROR:invalid format!!");
            return 1;
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
        np->l=L;
        L++;
        strcpy(np->opp,"");
        fscanf(f1,"%X\n",&LOCCTR);
        *start=LOCCTR;
        while(!feof(f1))
        {
            np=(line*)malloc(sizeof(line));
            fscanf(f1,"%s ",&np->lbl);
            fscanf(f1,"%s ",&np->comm);
            np->l=L;                                    //including line numbers
            L++;
            if(strcmp(np->comm,"RSUB")!=0)
                fscanf(f1,"%s ",&np->opp);              //direct operand
            else
                strcpy(np->opp,"");
            if(strcmp(np->comm,"START")!=0)
                np->add=LOCCTR;
            else
            {
                printf("\nMultiple Start !! line :%d",np->l);
                getch();
                return 1;
            }
            O=fopen("opcode.txt","r");                      //OPTAB
            while(!feof(O))
            {
                fscanf(O,"%s ",opc);
                if(strcmp(np->comm,opc)==0 || strcmp(np->comm,"WORD")==0 || strcmp(np->comm,"CHAR")==0 || strcmp(np->comm,"HEX")==0 ||strcmp(np->comm,"RESW")==0||strcmp(np->comm,"RESB")==0 || strcmp(np->comm,"RSUB")==0 )
                {
                    flag=0;
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
                printf("\nInvalid mnemonic used... %s in line %d",np->comm,np->l);
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
                    printf("\nDuplicate Labels!! %s in line %d",np->lbl,np->l);
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
                info=fopen("Name.txt","w");
                fprintf(info,"%s\n%X",Pname,LOCCTR-*start+1);
                printf("\n%X",*start);
                fclose(info);
                return 0;
            }
            else if(strcmp(np->comm,"RESB")==0)
            {
                num=atoi(np->opp);
                LOCCTR+=num;
            }
            else if(strcmp(np->comm,"RESW")==0)
            {
                num=atoi(np->opp);
                LOCCTR+=num*3;
            }
            else if(strcmp(np->comm,"WORD")==0)
                LOCCTR+=3;
            else if(strcmp(np->comm,"CHAR")==0)
            {
                l=strlen(np->opp);
                LOCCTR+=l;
            }
            else if(strcmp(np->comm,"HEX")==0)
            {
                l=strlen(np->opp);
                if(l%2==0)
                    LOCCTR+=l/2;                //even
                else
                    LOCCTR+=(l+1)/2;            //odd
            }
            else
                LOCCTR+=3;

        }
    }
    return 1;
}

void interf(line *r,int start)                  //intermediate file
{
    line *np;
    FILE *in=fopen("mid.txt","w");
    if(r!=NULL)
    {
        np=r;
        while(np!=NULL)
        {
            if(strcmp(np->comm,"START")!=0 && strcmp(np->comm,"END")!=0)
                fprintf(in,"%d %04X %s %s %s\n",np->l,np->add,np->lbl,np->comm,np->opp);
            else if(strcmp(np->comm,"START")==0)
                fprintf(in,"%d     %s %s %04X\n",np->l,np->lbl,np->comm,start);
            else
                fprintf(in,"%d     %s %s %s\n",np->l,np->lbl,np->comm,np->opp);
            np=np->next;
        }
    }
    fclose(in);
}
int Pass2(line *r,int start)                //calculating object code
{
    line *p;
    FILE *op,*s,*file;
    file=fopen("object.txt","w");
    char sym[25],add[25],opr[25],c[30];
    int sf=0,f=0,opc,i,l,num,LOCCTR=start;
    if(r!=NULL)
    {
        p=r;                                //value of rare stored in a temporary pointer p
        while(p!=NULL)
        {

            if(strcmp(p->comm,"START")!=0 && strcmp(p->comm,"END")!=0 && strcmp(p->comm,"RESW")!=0 && strcmp(p->comm,"RESB")!=0 && strcmp(p->comm,"RSUB")!=0)
            {
                s=fopen("Symbol.txt","r");
                while(!feof(s))
                {
                    fscanf(s,"%s ",sym);
                    fscanf(s,"%s ",add);
                    if(strcmp(sym,p->opp)==0 && strcmp(p->comm,"CHAR")!=0 && strcmp(p->comm,"HEX")!=0 && strcmp(p->comm,"WORD")!=0 )
                    {
                        sf=1;
                        break;
                    }
                }
                fclose(s);
                op=fopen("opcode.txt","r");
                while(!feof(op))
                {
                    fscanf(op,"%s ",opr);
                    fscanf(op,"%d\n",&opc);
                    if(strcmp(p->comm,opr)==0)
                    {
                        f=1;
                        break;
                    }
                }
                fclose(op);
                if(f==1 && sf==1)                   //object code in correct and the symbol is in symbol table
                {
                    fprintf(file,"%d",opc);
                    fprintf(file,"%s ",add);
                    fprintf(file,"%X\n",LOCCTR);
                }
                else if(strcmp(p->comm,"CHAR")==0)
                {
                    l=strlen(p->opp);
                    for(i=0;i<l;i++)
                    {
                        fprintf(file,"%d",p->opp[i]);
                    }
                    fprintf(file," ");
                    fprintf(file,"%X\n",LOCCTR);
                }
                else if(strcmp(p->comm,"HEX")==0)
                {
                    fprintf(file,"%s ",p->opp);
                    fprintf(file,"%X\n",LOCCTR);
                }
                else if(strcmp(p->comm,"WORD")==0)
                {

                    fprintf(file,"%06s ",p->opp);
                    fprintf(file,"%X\n",LOCCTR);
                }
                else
                {
                    printf("\ninvalid operand!");
                    printf("\n%s\n",p->opp);
                    getch();
                    return 1;
                }
                f=0;
                sf=0;
            }
            if(strcmp(p->comm,"RESW")==0 || strcmp(p->comm,"RESB")==0)
            {
                fprintf(file,"NIL ");
                fprintf(file,"%X\n",LOCCTR);
            }
            else if(strcmp(p->comm,"RSUB")==0)
            {
                fprintf(file,"4C0000 ");
                fprintf(file,"%X\n",LOCCTR);
            }
            if(strcmp(p->comm,"RESB")==0)
            {
                num=atoi(p->opp);
                LOCCTR+=num;
            }
            else if(strcmp(p->comm,"RESW")==0)
            {
                num=atoi(p->opp);
                LOCCTR+=num*3;
            }
            else if(strcmp(p->comm,"WORD")==0)
                LOCCTR+=3;
            else if(strcmp(p->comm,"CHAR")==0)
            {
                l=strlen(p->opp);
                LOCCTR+=l;
            }
            else if(strcmp(p->comm,"HEX")==0)
            {
                l=strlen(p->comm);
                if(l%2==0)
                    LOCCTR+=l/2;
                else
                    LOCCTR+=(l+1)/2;
            }
            else if(strcmp(p->comm,"START")!=0)
                LOCCTR+=3;
            p=p->next;
        }
    }
    fclose(file);
    return 0;
}
void text(int start)                        //header and text record
{

    FILE *info,*obj,*F;
    char name[10],opjcode[30],address[20],st[350];
    int lp[20],l,i,cnt;
    info=fopen("Name.txt","r");
    fscanf(info,"%s\n",name);
    fscanf(info,"%s",lp);                   //lp is length of program
    obj=fopen("Oprogram.txt","w");
    fprintf(obj,"H^%s",name);               //header record
    l=strlen(name);
    for(i=0;i<6-l;i++)
    {
        fprintf(obj,"_");
    }
    fprintf(obj,"^%06X^%06s\n",start,lp);
    fclose(info);
    strcpy(st,"");
    F=fopen("object.txt","r");
    while(!feof(F))
    {
        cnt=0;
        fscanf(F,"%s ",opjcode);
        fscanf(F,"%s\n",address);
        if(strcmp(opjcode,"NIL")!=0)
        {
            fprintf(obj,"\nT^%06s^",address);               //text record
            strcat(st,"^");
            strcat(st,opjcode);
            l=strlen(opjcode);
            cnt+=l/2;
        }
        while(!feof(F))
        {
            if(cnt>=30)
            {
                break;
            }
            fscanf(F,"%s ",opjcode);
            fscanf(F,"%s\n",address);
            if(strcmp(opjcode,"NIL")==0)
                break;
            strcat(st,"^");
            strcat(st,opjcode);
            l=strlen(opjcode);
            cnt+=l/2;
        }
        if(cnt>0)
        {
            fprintf(obj,"%02X",cnt);
            fprintf(obj,"%s",st);
        }
        strcpy(st,"");
    }
    fprintf(obj,"\n\nE^%s",name);               //end record
    fclose(obj);
    fclose(F);
}
int mainp()                                     //calling several functions according to the procedure
{
    char program[25];
    int e=0,start;
    line *f=NULL,*r=NULL;
    printf("\nEnter the Input Program File Name:");
    fflush(stdin);
    gets(program);
    e=Pass1(program,&f,&r,&start);
    interf(r,start);
    if(e==0)
    {
        e=Pass2(r,start);
        if(e==0)
            text(start);
        else
            printf("\nERROR");
    }
    else
        printf("\nERROR");
    return e;
}
