#include<string>
#include<iostream>
class screen
{
public:
	screen(const int& w,const int & h,const std::string& c=""):width(w),height(h),content(c),cursor(0){

}

screen& move(const int &,const int &);
screen& set(const char&);
screen& display(ostream& o);

private:
	typedef string::size_type index;
	int width;
	int height;
	index cursor;
	std::string content;
};
screen& screen::move(const int& w,const int& h)
{
	this->width=w;
	
}

int main()
{
	screen(100,200,"you are the one");
	return 0;
}
