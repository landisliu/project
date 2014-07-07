#ifndef CALC
#define CALC
#include<stdio.h>
#include<math.h>
#include<string.h>
#include<stdlib.h>
#define MAXOP 100
#define BUFSIZE 100
#define NUMBER '0'

int getch(void);
void ungetch(int);
void push(double ch);
void trypop(void);
double copypop(void);
double pop(void);
void clear(void);
void exchange(void);
int getop(char s[]);
#endif
