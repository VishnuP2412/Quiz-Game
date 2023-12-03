#include<stdio.h>
#include <stdlib.h>
#include<ctype.h>
void ans(char x,int y)
{
    char co[10]={'a','c','a','b','c','d','a','b','c','d',};
    if(x==co[y])
    printf("correct option");
    else if (isdigit(x))
    printf("number");
}
void main()
{
    FILE *q;
    char ch,a;
    int i;
    int c=0;
    q=fopen("qb.txt","r");
    if(q==NULL)
    {
        printf("file does not exist");
        exit(1);
    }
     label1:
    for(i=1;i<=47;i++)
    {
        if(!feof(q))
        {
            ch=fgetc(q);
         if(ch!='-')
         {
          printf("%c",ch);
          //c=fgetc(q);
         }
         else if (c=='-')
         {
            scanf("%c",&a);
            ans(a,c);
            c++;
           break;
         }
        }
        else
        goto label2;
    }
    if(!feof(q))
    goto label1;
    label2:
    fclose(q);
}
    /*switch(x)
    {
        case('a'):check(a);break;
        case('b'):check(a);break;
        case('c'):check(a);break;
        case('d'):check(a);break;
        case('1'):break;
        default:printf("Invalid");
    }
}
void check(char n)
{*/
    