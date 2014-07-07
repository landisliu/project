#include<stdlib.h>
#include<stdio.h>
#ifndef USERLIB_H
#define USERLIB_H
void word_length_ver(char *str);
void word_length_hor(char *str);
char * max_dup_char(char * src,char ch,int * count);
void firstdiffline(char * fp1,char * fp2);
int wordcount(FILE * fp);
void memorytest();
int day_of_year(int year,int month,int day);
void month_day(int year,int yearday,int *pmonth,int *pday);
double expr(int argc,char ** argv);
void sizeoftype();
size_t arraysize(void *,size_t);
void miniprintf(char * fmt,...);
void miniscanf(char * fmt,...);
void filecopy(FILE * ,FILE *);
void cat(int argc,char *argv[]);
void stringlib();
void mystrncpy(char * dest,const char * source,size_t num);
#endif
