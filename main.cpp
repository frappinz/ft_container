#include "vector.hpp"
#include <vector>
#include <iostream>


int main()
{
	ft::vector<int> ciccio;
	ft::vector<int> ci(10, 5);

	std::vector<int> gamer (10, 6);
	std::vector<int> sds (10, 5);


	// std::cout << "ft::max_size  " << ciccio.max_size() << std::endl;
	// std::cout << "std::max_size  " << gamer.max_size() << std::endl;

	// gamer.push_back(0);
	// gamer.push_back(0);
	// gamer.push_back(0);
	// gamer.push_back(0);

	ciccio.push_back(1);
	ciccio.push_back(0);
	ciccio.push_back(0);
	ciccio.push_back(0);

	gamer.data()

	// if (gamer != sds) std::cout << "sono uguali\n";
	// if (ciccio != ci) std::cout << "sono diversi\n";

	// if (gamer <= sds) std::cout << "gamer minore uguale\n";
	// if (ciccio <= ci) std::cout << "ciccio minore uguale\n";

	


	// std::cout << "std::size [" << gamer.size() << "]" << std::endl;
	// std::cout << "ft::size [" << ciccio.size() << "]" << std::endl;

	// std::cout << "std::at [" << gamer.at(6) << "]" << std::endl;
	// std::cout << "ft::at [" << ciccio.at(6) << "]" << std::endl;

	// std::cout << "std::front [" << gamer.front() << "]" << std::endl;
	// std::cout << "ft::front [" << ciccio.front() << "]" << std::endl;

	// std::cout << "std::back [" << gamer.back() << "]" << std::endl;
	// std::cout << "ft::back [" << ciccio.back() << "]" << std::endl;

	// std::cout << "std::capacity [" << gamer.capacity() << "]" << std::endl;
	// std::cout << "ft::capacity [" << ciccio.capacity() << "]" << std::endl;

	// gamer.swap(sds);
	// ciccio.swap(ci);



	for (int i = 0; i < ciccio.size(); i++)
		std::cout << "originale " << gamer[i] << " - " << ciccio[i] << " nostro" << std::endl;
	
	
	
	
	

}