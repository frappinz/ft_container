#include <iostream>
#include <utility>
#include <memory>
#include <string>
//#include <__tree>
#include "map.hpp"
//#include "binary_tree.hpp"
//#include <map>
//#include "mapprova.hpp"

int main()
{
	// ft::map<int, char> albero;
	ft::map<int, char> tree;
	// albero.insert ( std::pair<int, char>(1,'a') );
	tree.insert ( std::pair<int, char>(4,'a') );
	tree.insert ( std::pair<int, char>(2,'b') );

	tree.insert ( std::pair<int, char>(1,'c') );

	tree.insert ( std::pair<int, char>(3,'d') );
	tree.insert ( std::pair<int, char>(15,'e') );
	tree.insert ( std::pair<int, char>(12,'f') );



	ft::map<int, char>::iterator a = tree.begin();
	for (; a != tree.end(); a++)
	{
		std::cout << "first = " << (*a).first << " second = " << (*a).second << std::endl;
	}
	
	ft::map<int,char>::iterator low = tree.lower_bound(4);
	std::cout << "lower bound = " << (*low).first << std::endl;


}