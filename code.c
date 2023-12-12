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
int a=0,b=0;
int o=0;
int main()
{
    printf("\n\t\t WELCOME TO THE QUIZ \t\t\t\t\t\n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("Rules:\n1. You will be given 6 options: a, b, c, d, 1 and 2 where you will need to choose one.\n\t1 - 50-50\t2 - double dip\n");
    printf("2. Please note that you can use a lifeline only once throughout the entire game\n");
    printf("3. For every correct answer,10 points will be awarded and for every wrong answer 0 points will be deducted\n");
    printf("4. You will given 5 seconds before answering each question.\n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("\t\t All The Best. Have Fun\t\t\t\t\t\n");
    
    a:
    a=0,b=0,p=0;
    enter();
    question();
    update();
    display();
    c:
    printf("\nPlay again ? y/n \n");
    char c=fgetc(stdin);
    if(c=='y'||c=='Y')
    goto a;
    else if (c=='n'||c=='N')
    exit(1);
    else
    {
        printf("Invalid input");
        goto c;
    }
    return 0;
}


void enter()
{
    char name[50];
    FILE *fp = fopen("Userdata.txt","w");
    int d=1;
    if(fp==NULL)
    {
     exit(1);
    }
    printf("Enter Your Name: ");
    fgets(name, 50, stdin);
    fputs("Participant: ",fp);
    fputs(name,fp);
    if(o==1)
      while(getchar()!='\n');
    fclose(fp);
}


void StartTimer(int s)
{
    time_t st=time(NULL);
    time_t ct;
    do
    {
        ct=time(NULL);
    }
    while ((ct-st)<s);
    
}


int question()
{
    FILE *q;
    char ch;
    char a;
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
            s=5;
            StartTimer(s);
            a=fgetc(stdin);
            options(a,c);
            c++;
            printf("\n");
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


char options(char x,int y)
{
    char co[10]={'a','c','a','b','c','d','a','b','d','c'}; 
    if(x==co[y-1]||x==toupper(co[y-1]))
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
         if(x=='b'||x=='c'||x=='d'||x=='B'||x=='C'||x=='D')
         printf("Incorrect Answer");
         else
         printf("invalid choice");
        }
        else if(co[y-1]=='b')
        {
         if(x=='a'||x=='c'||x=='d'||x=='A'||x=='C'||x=='D')
         printf("Incorrect Answer");
         else
         printf("invalid choice");
        }
        else if(co[y-1]=='c')
        {
         if(x=='b'||x=='a'||x=='d'||x=='B'||x=='A'||x=='D')
         printf("Incorrect Answer");
         else
         printf("invalid choice");
        }
        else if(co[y-1]=='d')
        {
         if(x=='b'||x=='c'||x=='a'||x=='B'||x=='C'||x=='A')
         printf("Incorrect Answer");
         else
         printf("invalid choice");
        }
        else
        {
            printf("invalid coice");
        }
    }
    while(getchar()!='\n');
    return 0;
}


char life1(char correctanswer)
{
    if(a<1)
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
       printf("Correct Answer");
       p=p+10;
       ua=getchar();
     }
     else
     {
       if(correctanswer=='a')
        {
         if(ua=='b'||ua=='c'||ua=='d'||ua=='B'||ua=='C'||ua=='D')
         {
          printf("Incorrect Answer");
           ua=getchar();
         }
         else
          {
            printf("invalid choice");
             ua=getchar();
          }
        }
        else if(correctanswer=='b')
        {
         if(ua=='a'||ua=='c'||ua=='d'||ua=='A'||ua=='C'||ua=='D')
         {
          printf("Incorrect Answer");
           ua=getchar();
         }
         else
          {
            printf("invalid choice");
             ua=getchar();
          }
        }
        else if(correctanswer=='c')
        {
         if(ua=='b'||ua=='a'||ua=='d'||ua=='B'||ua=='A'||ua=='D')
         {
          printf("Incorrect Answer");
           ua=getchar();
         }
         else
          {
            printf("invalid choice");
             ua=getchar();
          }
        }
        else if(correctanswer=='d')
        {
         if(ua=='b'||ua=='c'||ua=='a'||ua=='B'||ua=='C'||ua=='A')
        {
          printf("Incorrect Answer");
           ua=getchar();
         }
         else
          {
            printf("invalid choice");
             ua=getchar();
          }
        }
     }
     a++;
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
        ua=getchar();
     }
     else
     if(correctanswer=='a')
        {
         if(ua=='b'||ua=='c'||ua=='d'||ua=='B'||ua=='C'||ua=='D')
         {
          printf("Incorrect Answer");
           ua=getchar();
         }
         else
          {
            printf("invalid choice");
             ua=getchar();
          }
        }
        else if(correctanswer=='b')
        {
         if(ua=='a'||ua=='c'||ua=='d'||ua=='A'||ua=='C'||ua=='D')
         {
          printf("Incorrect Answer");
           ua=getchar();
         }
         else
          {
            printf("invalid choice");
             ua=getchar();
          }
        }
        else if(correctanswer=='c')
        {
         if(ua=='b'||ua=='a'||ua=='d'||ua=='B'||ua=='A'||ua=='D')
         {
          printf("Incorrect Answer");
           ua=getchar();
         }
         else
          {
            printf("invalid choice");
             ua=getchar();
          }
        }
        else if(correctanswer=='d')
        {
         if(ua=='b'||ua=='c'||ua=='a'||ua=='B'||ua=='C'||ua=='A')
        {
          printf("Incorrect Answer");
           ua=getchar();
         }
         else
          {
            printf("invalid choice");
             ua=getchar();
          }
        }
    }
}

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



char life2(char correctanswer)
{
  char ua;
    if(b<1)
    {
        ua=getchar();
        printf("\n Enter your option: ");
        ua=getchar();
        if(ua!=correctanswer)
       {
        printf("\nWrong Answer. You can Choose Again.\n");
        ua=getchar();
        printf("\n Enter your option: ");
        ua=getchar();
        if(ua!=correctanswer)
        {
            if(correctanswer=='a')
        {
         if(ua=='b'||ua=='c'||ua=='d'||ua=='B'||ua=='C'||ua=='D')
         printf("Incorrect Answer");
         else
         printf("invalid choice");
        }
        else if(correctanswer=='b')
        {
         if(ua=='a'||ua=='c'||ua=='d'||ua=='A'||ua=='C'||ua=='D')
         printf("Incorrect Answer");
         else
         printf("invalid choice");
        }
        else if(correctanswer=='c')
        {
         if(ua=='b'||ua=='a'||ua=='d'||ua=='B'||ua=='A'||ua=='D')
         printf("Incorrect Answer");
         else
         printf("invalid choice");
        }
        else if(correctanswer=='d')
        {
         if(ua=='b'||ua=='c'||ua=='a'||ua=='B'||ua=='C'||ua=='A')
         printf("Incorrect Answer");
         else
         printf("invalid choice");
        }
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
     b++;
    }
    else
    {
      printf("\n Lifeline already used");
      ua=getchar();
      printf("\n Enter your option: ");
      ua=getchar();
      if(ua!=correctanswer)
      {
        if(correctanswer=='a')
        {
         if(ua=='b'||ua=='c'||ua=='d'||ua=='B'||ua=='C'||ua=='D')
         printf("Incorrect Answer");
         else
         printf("invalid choice");
        }
        else if(correctanswer=='b')
        {
         if(ua=='a'||ua=='c'||ua=='d'||ua=='A'||ua=='C'||ua=='D')
         printf("Incorrect Answer");
         else
         printf("invalid choice");
        }
        else if(correctanswer=='c')
        {
         if(ua=='b'||ua=='a'||ua=='d'||ua=='B'||ua=='A'||ua=='D')
         printf("Incorrect Answer");
         else
         printf("invalid choice");
        }
        else if(correctanswer=='d')
        {
         if(ua=='b'||ua=='c'||ua=='a'||ua=='B'||ua=='C'||ua=='A')
         printf("Incorrect Answer");
         else
         printf("invalid choice");
        }
      }
      else
      {
        printf("\n Correct Answer");
        p=p+10;
      }
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
    fprintf(fp,"\nYour Final Score: %d",p);
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
            printf("\n");
        }
    }
    printf("\n Good Game. Please Play Again\n");
    fclose(fp);
    printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    o=1;
}