#include "vector.hpp"
#include <vector>
#include <iostream>


int main()
{
	int ints[] = {10, 20, 30, 40};



	ft::vector<int> ciccio (ints, ints+4);
	//ciccio.assign(ints, ints + 4);
	//ft::vector<int> ci(10, 5);


	std::vector<int> gamer (ints, ints + 4);
	//gamer.assign(ints, ints + 4);

	std::vector<int>::iterator it = gamer.begin();
	gamer.insert((it+1), 0);
	std::cout << "iter originale punta a " << *it << std::endl; 
	ft::vector<int>::iterator it2 = ciccio.begin();
	ciccio.insert((it2 + 1), 0);
	std::cout << "iter nostro punta a " << *it2 << std::endl; 




	//std::vector<int> sds (10, 5);

	for (std::vector<int>::iterator i = gamer.begin(); i != gamer.end(); i++)
		std::cout << *i << " originale" << std::endl;


	// std::cout << "ft::max_size  " << ciccio.max_size() << std::endl;
	// std::cout << "std::max_size  " << gamer.max_size() << std::endl;

	// gamer.push_back(1);
	// gamer.push_back(2);
	// gamer.push_back(3);
	// gamer.push_back(4);

	// ciccio.push_back(1);
	// ciccio.push_back(2);
	// ciccio.push_back(3);
	// ciccio.push_back(4);


	// if (gamer != sds) std::cout << "sono uguali\n";
	// if (ciccio != ci) std::cout << "sono diversi\n";

	// if (gamer <= sds) std::cout << "gamer minore uguale\n";
	// if (ciccio <= ci) std::cout << "ciccio minore uguale\n";

	


	// std::cout << "std::size [" << gamer.size() << "]" << std::endl;
	// std::cout << "ft::size [" << ciccio.size() << "]" << std::endl;

	// // std::cout << "std::at [" << gamer.at(6) << "]" << std::endl;
	// // std::cout << "ft::at [" << ciccio.at(6) << "]" << std::endl;

	// // std::cout << "std::front [" << gamer.front() << "]" << std::endl;
	// // std::cout << "ft::front [" << ciccio.front() << "]" << std::endl;

	// // std::cout << "std::back [" << gamer.back() << "]" << std::endl;
	// // std::cout << "ft::back [" << ciccio.back() << "]" << std::endl;

	// std::cout << "std::capacity [" << gamer.capacity() << "]" << std::endl;
	// std::cout << "ft::capacity [" << ciccio.capacity() << "]" << std::endl;

	// gamer.swap(sds);
	// ciccio.swap(ci);


	// std::vector<int>::iterator x = gamer.begin();
	// std::vector<int>::iterator j = gamer.end();

	// ft::vector<int>::iterator i = ciccio.begin();
	// ft::vector<int>::iterator y = ciccio.end();

	// ft::vector<int>::iterator i2 = y - 2;
	// 	std::cout << *i2 <<std::endl;
	// std::vector<int>::iterator i3 = j - 2;
	// 	std::cout << *i3 << std::endl;

	

	

	for (ft::vector<int>::iterator i = ciccio.begin(); i != ciccio.end(); i++)
		std::cout << *i << " nostro" << std::endl;

	
	// if (i == y)
	// 	std::cout << "minchia\n";


//		std::cout << "originale " << gamer[i] << " - " << ciccio[i] << " nostro" << std::endl;
	
	
	
	
	

}