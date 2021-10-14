#include "vector.hpp"
#include <vector>
#include <iostream>


int main()
{
	ft::vector<int> ciccio;
	std::vector<int> gamer;

	// std::cout << "Max size nostro: " << ciccio.max_size() << std::endl;
	// std::cout << "Max size origin: " << gamer.max_size() << std::endl;

	std::cout << "ft: " << ciccio.capacity() << std::endl;
	std::cout << "gamer: " << gamer.capacity() << std::endl;

	gamer.push_back(1);
	ciccio.push_back(1);
	ciccio.push_back(1);
	ciccio.push_back(1);
	ciccio.push_back(1);
	ciccio.push_back(1);
	ciccio.push_back(1);
	ciccio.push_back(1);
	ciccio.push_back(1);
	ciccio.push_back(1);
	ciccio.push_back(1);
	ciccio.push_back(1);
	ciccio.push_back(1);
	ciccio.push_back(1);
	ciccio.push_back(1);
	ciccio.push_back(1);
	ciccio.push_back(1);
	ciccio.push_back(1);
	ciccio.push_back(1);
	

	for (int i = 0; i < 10; i++)
		std::cout << "originale " << gamer[i] << " - " << ciccio[i] << " nostro" << std::endl;
	
	std::cout<<gamer.size();
	std::cout<<ciccio.size();
	
	
	
	

}