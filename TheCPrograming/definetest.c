#include<stdio.h>
#define swap(t,x,y) {t temp=x;x=y;y=temp;}

int main()
{
 int x = 5;
 int y =10;
 printf("%d %d",x,y);
 swap(int, x,y);
 printf("%d %d",x,y);
 return 0;
}
