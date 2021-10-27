
#include <iostream>
#include <map>

bool fncomp (char lhs, char rhs) {return lhs<rhs;}

struct classcomp {
  bool operator() (const char& lhs, const char& rhs) const
  {return lhs<rhs;}
};

int main ()
{
	std::map<char,int> first;

	first['a']=10;
	first['b']=30;
	first['c']=50;
	first['d']=70;

	std::map<char,int> second;
	second['a']=11;
  	second['b']=22;
  	second['c']=33;

	std::cout << second.at('a');
	//std::map<char,int> third (second);



  	return 0;
}