#include<string>
#include<stdio.h>
#include<iostream>
class Person
{
public:
Person(const std::string&,const std::string&);
void display() const
{
	std::cout<<name<<address<<std::endl;
}

std::string getname();

private:
std::string name;
std::string address;
};
inline std::string Person::getname()
{
	return this->name;
}

Person::Person(const std::string& name,const std::string &address)
{
	this->name = name;
	this->address= address;
}

int main()
{
	Person p1("landis","beijing");
	std::cout<<p1.getname()<<std::endl;
	return 0;
}

