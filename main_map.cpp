#include <iostream>
#include <utility>
#include <memory>
#include <string>
//#include <__tree>
#include "map.hpp"
//#include "binary_tree.hpp"
#include <map>
//#include "mapprova.hpp"

int main()
{
	std::map<int, char> tree;
	std::map<int, char> tree2;
	// albero.insert( std:: pair<int, char> (2,'a'));
	// albero.insert( std:: pair<int, char> (3,'a'));


	// albero.insert ( std::pair<int, char>(1,'a') );
	tree.insert ( std::pair<int, char>(4,'a') );
	tree.insert ( std::pair<int, char>(2,'b') );

	tree.insert ( std::pair<int, char>(1,'c') );

	tree.insert ( std::pair<int, char>(3,'d') );
	tree.insert ( std::pair<int, char>(15,'e') );
	tree.insert ( std::pair<int, char>(12,'f') );

	tree2.insert ( std::pair<int, char>(4,'a') );
	tree2.insert ( std::pair<int, char>(2,'b') );
	tree2.insert ( std::pair<int, char>(1,'c') );
	tree2.insert ( std::pair<int, char>(3,'d') );
	tree2.insert ( std::pair<int, char>(15,'e') );
	tree2.insert ( std::pair<int, char>(12,'f') );

	if (tree < tree2)
		std::cout << "valgono anche i data \n";

	std::map<int, char>::iterator i;
	std::map<int, char>::iterator b;

	i = tree.begin();
	b = tree.begin();

	// std::cout << i->first << std::endl;


	// std::map<int, char>::iterator a = tree.begin();
	// for (; a != tree.end(); a++)
	// {
	// 	std::cout << "first = " << (*a).first << " second = " << (*a).second << std::endl;
	// }
	
	// ft::map<int,char>::iterator low = tree.lower_bound(4);
	// std::cout << "lower bound = " << (*low).first << std::endl;

	// std::map<int, char>::iterator a = tree.end();
	// std::cout << "end  " << a->second << std::endl;






}