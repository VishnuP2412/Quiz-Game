/* This Program is a simple question-answer based project 
 where we create a question bank for various topics
 and will ask questions to each contestant and 
 give them a score based on their reply*/


#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>


void enter();
int question();
char options(char x, int y);
char life1(char correctanswer);
void lifehelp1(char optoins[],char corretanswer);
char life2(char correctanswer);
void update();
void display();

int p=0;
int z=0,y=0;
void main()
{
    printf("\n\t\t WELCOME TO THE QUIZ \t\t\t\t\t\n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("Rules:\n1. You will be given 4 options and you havve to press a,b,c or 1 or 2 for lifelines\n");
    printf("2. Please note that you can use a lifeline only once throughout the entire game\n");
    printf("3. For every correct option,10 points will be added and for every wrong answer 0 points will be deducted\n");
    printf("4. You will given 10 secinds before answering each question and 5 seconds after answering the question.\n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("\t\t All The Best. Have Fun\t\t\t\t\t\n");
    
    enter();
    question();
    update();
    display();
}
// To enter User Data and store it in file
void enter()
{
    char name[50];
    FILE *fp = fopen("Userdata.txt","w");;
    char a[5];
    int d=1;
    if(fp==NULL)
    {
     exit(1);
    }
    printf("Enter Your Name: ");
    fgets(name, 50, stdin);
    fputs("Participant: ",fp);
    fputs(name,fp);
    fclose(fp);
}
// To delay the time between answers and questions (Timer)
void StartTimer(int s)
{
    time_t st=time(NULL);
    time_t ct;
    do
    {
        ct=time(NULL);
    } while ((ct-st)<s);
    
}
// To print questions
int question()
{
     FILE *q;
    char ch,a;
    int i;
    int s;
    int c=1;
    q=fopen("qb.txt","r");
    if(q==NULL)
    {
        printf("file does not exist");
        exit(1);
    }
    label1:
    s=2;
    StartTimer(s);
    //for(i=1;i<=40;i++)
    while(!feof(q))
    {
        if(!feof(q))
        {
            ch=fgetc(q);
         if(ch!='-')
         {
          printf("%c",ch);
         }
         else if (ch=='-')
         {
            s=2;
            StartTimer(s);
            a=fgetc(stdin);
            options(a,c);
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
    return 0;
}
// To check the answer given by the participant and check it
char options(char x,int y)
{
    char co[10]={'a','c','a','b','c','d','a','b','d','c'};
    char *s;
    if(x==co[y-1])
    {
        printf("Correct Answer");
        p=p+10;
    }
    else if (isdigit(x))
    {
        if(x=='1')
        {
            life1(co[y-1]);
        }
        else if(x=='2')
        {
            life2(co[y-1]);
        }
        else 
        goto l1;
    }
    else
    {
        l1:
        if(co[y-1]=='a')
        {
         if(x=='b'||x=='c'||x=='d')
         printf("Incorrect Answer");
        }
        else if(co[y-1]=='b')
        {
         if(x=='a'||x=='c'||x=='d')
         printf("Incorrect Answer");
        }
        else if(co[y-1]=='c')
        {
         if(x=='b'||x=='a'||x=='d')
         printf("Incorrect Answer");
        }
        else if(co[y-1]=='d')
        {
         if(x=='b'||x=='c'||x=='a')
         printf("Incorrect Answer");
        }
        else
        {
            printf("invalid coice");
        }
    }
    while(getchar()!='\n');
    return 0;
}
// First Lifeline: 50-50
char life1(char correctanswer)
{
    FILE *check=fopen("qb.txt","r");
    if(z<1)
    {
     char options[]={'a','b','c','d'};
     srand(time(NULL));
     char ua;
     lifehelp1(options,correctanswer);
     lifehelp1(options,correctanswer);
     int i;
     for(i=0;i<4;++i)
     {
        if(options[i]!='*')
        {
            printf("%c  ",options[i]);
        }
     }
     printf("\n Enter Your Answer: ");
     
     int s=scanf("%c",&ua);
     ua=fgetc(stdin);
     if(s==1 && ua==correctanswer)
     {
       printf("\nCorrect Answer\n");
       p=p+10;
     }
     else
     {
       printf("\nIncorrect Answer\n");
     }
     while(getchar()!='\n');
     z++;
    }
    else
    {
     printf("\nAlready Used. Cannot Use Anymore");
     char ua=getchar();
     printf("\n Enter Your option: ");
     ua=getchar();
     if (ua==correctanswer)
     {
        printf("\n Correct Answer");
        p=p+10;
     }
     else
     printf("\n Wrong answer");
    }
    fclose(check);
}
// Helps the lifeline 50-50 in removing the wrong answers
void lifehelp1(char options[],char correctanswer)
{
    int i,j,a;
    do
    {
        i=rand()%4;
        j=rand()%4;
    } while (options[i]==' '||options[i]=='*'||options[i]==options[j]||options[i]==correctanswer);
    for(a=0;a<4;a++)
    {
        if(a!=i&&a!=j)
        options[i]='*';
    }
}
// Second lifeline: Double Dip (Can answer twice for the same question)
char life2(char correctanswer)
{
    if(y<1)
    {
        char ua;
        ua=getchar();
        printf("\n Enter your option: ");
        ua=getchar();
        if(ua!=correctanswer)
       {
        printf("\nWrong Answer. You can Choose Again.\n");
        ua=getchar();
        ua=getchar();
        printf("\n Enter your option: ");
        if(ua!=correctanswer)
        {
            printf("\n Wrong Answer");
        }
        else
        {
            printf("\n Correct Answer");
            p=p+10;
        }
      }
     else 
     {
        printf("\nCorrect Answer");
        p=p+10;
     }
     y++;
    }
    else
    {
        printf("\n Lifeline already used");
        return 0;
    }
}
void update()
{
    FILE *fp;
    fp=fopen("Userdata.txt","a");
    if(fp==NULL)
    {
        exit(1);
    }
    fprintf(fp,"\nYour Fotal Score: %d",p);
    fclose(fp);
}
void display()
{
    FILE *fp;
    char c;
    printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("\t\t Game Has Ended \t\t\n");
    fp=fopen("Userdata.txt","r");
    if(fp==NULL)
    {
        exit(1);
    }
    while(!feof(fp))
    {
        c=getc(fp);
        if(c!='\n')
        printf("%c",c);
        else
        {
            //printf();
            printf("\n");
        }
    }
    fclose(fp);
    printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
}