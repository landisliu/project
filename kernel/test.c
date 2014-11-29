#include<stdio.h>
#include<string.h>
#include<sys/time.h>
#include<time.h>
#include"helper.h"


struct teacher
{
	char * name;
	char * desc;
};
struct student
{
	char * name;
	char * desc;
	int age;
	struct teacher * teacher;
};

int main()
{
	struct teacher t1 = {.name="morina",.desc="bad girl"};
	struct student s1 ={
		.name ="landis",
		.desc="good student",
		.age = 10,
		.teacher=&t1
	};
	struct student * ps = (struct student *)container_of(&t1,struct student,teacher);

	printf("%s,%s,%d\n",ps->name,ps->desc,ps->age);
	return 0;
}
