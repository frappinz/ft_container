#include "vector.hpp"
#include <vector>
#include <iostream>


int main()
{
	ft::vector<int> ciccio(5, 6);
	std::vector<int> gamer(5, 6);

	std::cout << "Max size nostro: " << ciccio.max_size() << std::endl;
	std::cout << "Max size origin: " << gamer.max_size() << std::endl;

	ciccio.reserve(12);
	gamer.reserve(12);
	gamer.clear();
	ciccio.clear();

	// for (int i = 0; i < 10; i++)
	// 	std::cout << "originale " << gamer[i] << " - " << ciccio[i] << " nostro" << std::endl;
	
	std::cout<<gamer.size();
	std::cout<<ciccio.size();
	
	
	
	

}