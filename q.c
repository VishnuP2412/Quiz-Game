#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>

#define MAX_NAME_LENGTH 50
#define NUM_QUESTIONS 10
#define OPTIONS_PER_QUESTION 4
#define QUESTION_TIMER 2

void enter();
int question();
char options(char x, int y);
char life1(char correctanswer);
void lifehelp1(char options[], char correctanswer);
char life2(char correctanswer);
void update();
void display();

int p = 0;
int z = 0, y = 0;

int main() {
    printf("\n\t\t WELCOME TO THE QUIZ \t\t\t\t\t\n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("Rules:\n1. You will be given 4 options, and you have to press a, b, c, or d for answers.\n");
    printf("2. Please note that you can use a lifeline only once throughout the entire game.\n");
    printf("3. For every correct option, 10 points will be added, and for every wrong answer, 0 points will be deducted.\n");
    printf("4. You will be given 10 seconds before answering each question and 5 seconds after answering the question.\n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("\t\t All The Best. Have Fun\t\t\t\t\t\n");

    enter();
    question();
    update();
    display();

    return 0;
}

void enter() {
    char name[MAX_NAME_LENGTH];
    FILE *fp = fopen("Userdata.txt", "w");
    if (fp == NULL) {
        perror("Error opening Userdata.txt for writing");
        exit(1);
    }

    printf("Enter Your Name: ");
    fgets(name, MAX_NAME_LENGTH, stdin);
    fprintf(fp, "Participant: %s", name);
    fclose(fp);
}

void StartTimer(int s) {
    time_t st = time(NULL);
    time_t ct;
    do {
        ct = time(NULL);
    } while ((ct - st) < s);
}

int question() {
    FILE *q;
    char ch, a;
    int c = 1;
    q = fopen("qb.txt", "r");
    if (q == NULL) {
        perror("Error opening qb.txt for reading");
        exit(1);
    }

    for (int q_num = 1; q_num <= NUM_QUESTIONS; q_num++) {
        StartTimer(QUESTION_TIMER);
        while ((ch = fgetc(q)) != '-' && ch != EOF) {
            printf("%c", ch);
        }

        a = fgetc(stdin);
        options(a, c);
        c++;
    }

    fclose(q);
    return 0;
}

char options(char x, int y) {
    const char correct_answers[NUM_QUESTIONS] = {'a', 'c', 'a', 'b', 'c', 'd', 'a', 'b', 'd', 'c'};
    if (x == correct_answers[y - 1]) {
        printf("Correct Answer");
        p += 10;
    } else if (isdigit(x)) {
        if (x == '1') {
            life1(correct_answers[y - 1]);
        } else if (x == '2') {
            life2(correct_answers[y - 1]);
        } else {
            printf("Invalid choice");
        }
    } else {
        if (correct_answers[y - 1] == x) {
            printf("Incorrect Answer");
        } else {
            printf("Invalid choice");
        }
    }

    while (getchar() != '\n');

    return 0;
}

char life1(char correctanswer) {
    FILE *check = fopen("qb.txt", "r");
    if (z < 1) {
        char options[OPTIONS_PER_QUESTION] = {'a', 'b', 'c', 'd'};
        srand(time(NULL));
        char ua;
        lifehelp1(options, correctanswer);
        lifehelp1(options, correctanswer);

        for (int i = 0; i < OPTIONS_PER_QUESTION; ++i) {
            if (options[i] != '*') {
                printf("%c  ", options[i]);
            }
        }

        printf("\n Enter Your Answer: ");
        scanf(" %c", &ua);
        while (getchar() != '\n');

        if (ua == correctanswer) {
            printf("\nCorrect Answer\n");
            p += 10;
        } else {
            printf("\nIncorrect Answer\n");
        }

        z++;
    } else {
        printf("\nAlready Used. Cannot Use Anymore");
        char ua;
        printf("\n Enter Your option: ");
        scanf(" %c", &ua);

        if (ua == correctanswer) {
            printf("\n Correct Answer");
            p += 10;
        } else {
            printf("\n Wrong answer");
        }
    }

    fclose(check);
    return 0;
}

void lifehelp1(char options[], char correctanswer) {
    int i, j, a;
    do {
        i = rand() % OPTIONS_PER_QUESTION;
        j = rand() % OPTIONS_PER_QUESTION;
    } while (options[i] == ' ' || options[i] == '*' || options[i] == options[j] || options[i] == correctanswer);

    for (a = 0; a < OPTIONS_PER_QUESTION; a++) {
        if (a != i && a != j)
            options[a] = '*';
    }
}

char life2(char correctanswer) {
    if (y < 1) {
        char ua;
        getchar();
        printf("\n Enter your option: ");
        scanf(" %c", &ua);
        while (getchar() != '\n');

        if (ua != correctanswer) {
            printf("\nWrong Answer. You can Choose Again.\n");
            getchar();
            scanf(" %c", &ua);
            printf("\n Enter your option: ");

            if (ua != correctanswer) {
                printf("\n Wrong Answer");
            } else {
                printf("\n Correct Answer");
                p += 10;
            }
        } else {
            printf("\nCorrect Answer");
            p += 10;
        }

        y++;
    } else {
        printf("\n Lifeline already used");
        return 0;
    }

    return 0;
}

void update() {
    FILE *fp = fopen("Userdata.txt", "a");
    if (fp == NULL) {
        perror("Error opening Userdata.txt for appending");
        exit(1);
    }

    fprintf(fp, "\nYour total Score: %d", p);
    fclose(fp);
}

void display() {
    FILE *fp;
    char c;
    printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("\t\t Game Has Ended \t\t\n");

    fp = fopen("Userdata.txt", "r");
    if (fp == NULL) {
        perror("Error opening Userdata.txt for reading");
        exit(1);
    }

    while ((c = getc(fp)) != EOF) {
        if (c != '\n') {
            printf("%c", c);
        } else {
            printf("\n");
        }
    }

    fclose(fp);
    printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
}
