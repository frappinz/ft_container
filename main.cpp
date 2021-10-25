#include "vector.hpp"
#include "stack.hpp"
#include <iostream>


int main()
{

	int ints[] = {1, 2, 3, 4};
	ft::stack<int> ciao(ints, ints+4);
	for (size_t i = 0; i < 4; i++)
		std::cout << ciao[i] << std::endl;

}