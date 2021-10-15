#include "vector.hpp"
#include <vector>
#include <iostream>


int main()
{
	ft::vector<int> ciccio(3, 4);
	std::vector<int> gamer (3, 4);

	std::cout << "ft::max_size  " << ciccio.max_size() << std::endl;
	std::cout << "std::max_size  " << gamer.max_size() << std::endl;

	gamer.push_back(0);
	gamer.push_back(2);
	gamer.push_back(3);
	gamer.push_back(4);

	ciccio.push_back(0);
	ciccio.push_back(2);
	ciccio.push_back(3);
	ciccio.push_back(4);


	std::cout << "std::size: " << gamer.size() << std::endl;
	std::cout << "ft::size: " << ciccio.size() << std::endl;

	std::cout << "std::at -> " << gamer.at(6) << std::endl;
	std::cout << "ft::at -> " << ciccio.at(6) << std::endl;

	std::cout << "std::front: " << gamer.front() << std::endl;
	std::cout << "ft::front: " << ciccio.front() << std::endl;





	for (int i = 0; i < ciccio.size(); i++)
		std::cout << "originale " << gamer[i] << " - " << ciccio[i] << " nostro" << std::endl;
	
	
	
	
	

}