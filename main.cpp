#include "vector.hpp"
#include <vector>
#include <iostream>


int main()
{
	ft::vector<int> ciccio(5, 6);
	std::vector<int> gamer (5, 6);

	for (int i = 0; i < 6; i++)
		std::cout << ciccio[i] << std::endl;
	


}