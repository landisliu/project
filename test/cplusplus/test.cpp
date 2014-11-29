#include<cstdio>
#include<iostream>
#include<string>
using std::cout;
using std::endl;
using std::string;

enum points{p2d=2,p3d=3,p2w=3,p3w=4};
class Item_base
{
	public:
		Item_base():isbn("hello,world"){
			std::cout<<"item_base construct"<<std::endl;			
			}
		Item_base(const Item_base& ib)
		{
			this->isbn = ib.isbn;
			std::cout<<"item_base copy construct"<<std::endl;
		}
		Item_base& operator =(const Item_base& ib)
		{
			std::cout<<"item base copy operation"<<std::endl;
			this->isbn = ib.isbn;
			return *this;
		}
		static int count;
		virtual double net_price() const
		{
			count++;
			return 10;
		}
	private:
		std::string isbn;
		
};

int Item_base::count = 5;

class Bulk:public Item_base
{
	public:
		Bulk():rate(5){
			std::cout<<"Bulk construct"<<std::endl;			
		}

		Bulk(const Bulk& b)
		{
			this->rate = b.rate;
			std::cout<<"Bulk copy construct"<<std::endl;
		}
		Bulk& operator= (const Bulk& b)
		{
			std::cout<<"bulk copy operation "<<std::endl;
			this->rate = b.rate;
			return *this;
		}
		static int getcount()
		{
			return count;
		}
		virtual double net_price() const
		{
			count++;
			return Item_base::net_price()*rate;			
		}
	private:
		int rate;
};

class Person
{
public:

	Person()
	{
		cout<<"constructure called."<<endl;
	}

	Person(const Person& p)
	{
		cout<<"copy constructure called."<<endl;
	}
	Person& operator=(const Person& p)
	{
		cout<<"override equal called."<<endl;
	}
	~Person()
	{
		cout<<"decon called."<<endl;
	}

private:
};

Person getPerson()
{
	Person p;
	return p;
}

int main()
{
	Person p = getPerson();
}
/*int main(int argc,char *argv[])
{
	Item_base b;
	Item_base b2(b);
	Item_base b3 =b;	
	//Item_base ib(b);

	//Item_base ib2 =b;
	//Item_base ib3;
	//ib3 = b;
	
	//std::cout<<b.getcount()<<std::endl;
	return 0;
}*/
