#include "binary_tree.hpp"
#include <iostream>

int main()
{
	ft::_tree<int> albero;
	albero.insertValue(albero.getRoot(), 10);
	albero.insertValue(albero.getRoot(), 2);
	albero.insertValue(albero.getRoot(), 11);
	albero.insertValue(albero.getRoot(), 3);
	
	std::cout << albero;
}