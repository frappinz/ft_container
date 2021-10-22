#include "vector.hpp"
#include <vector>
#include <iostream>


int main()
{
	ft::vector<int> ciao; //ci metteremo dentro i push back

	ciao.push_back(1);
	ciao.push_back(2);
	ciao.push_back(3);
	ciao.push_back(4);

	int ints[] = {10, 20, 30, 40};

	ft::vector<int> ciccio (ints, ints + 4);
	ft::vector<int> pasq(10, 4);


	//ciccio.assign(ints, ints + 4);
	//ft::vector<int> ci(10, 5);


	//std::vector<int> gamer (ints, ints + 4);
	//gamer.assign(ints, ints + 4);

	//std::vector<int>::iterator it = (gamer.end());
	// gamer.insert(it - 2, ints, ints+4);
	//gamer.insert(it, 3, 100);

	// it = gamer.erase(it - 2, it);
	// std::cout << "gamer punta " << *it << std::endl;
	
	ft::vector<int>::iterator it2 = pasq.end();
	it2 = pasq.erase(it2 - 2, it2);
	pasq.insert(it2 - 2, ints, ints+4);





	//std::cout << "std::size [" << gamer.size() << "]" << std::endl;
	std::cout << "ft::size [" << ciccio.size() << "]" << std::endl;

	// std::cout << "std::at [" << gamer.at(6) << "]" << std::endl;
	std::cout << "ft::at [" << ciccio.at(2) << "]" << std::endl;

	// std::cout << "std::front [" << gamer.front() << "]" << std::endl;
	std::cout << "ft::front [" << ciccio.front() << "]" << std::endl;

	// std::cout << "std::back [" << gamer.back() << "]" << std::endl;
	std::cout << "ft::back [" << ciccio.back() << "]" << std::endl;

	//std::cout << "std::capacity [" << gamer.capacity() << "]" << std::endl;
	std::cout << "ft::capacity [" << ciccio.capacity() << "]" << std::endl;

	//gamer.swap(sds);
	ciccio.swap(ciao);


	//std::vector<int>::iterator x = gamer.begin();
	//std::vector<int>::iterator j = gamer.end();
	



	for (ft::vector<int>::iterator i = ciccio.begin(); i != ciccio.end(); i++)
		std::cout << *i << " nostro" << std::endl;

	
	// if (i == y)
	// 	std::cout << "minchia\n";


//		std::cout << "originale " << gamer[i] << " - " << ciccio[i] << " nostro" << std::endl;
	
	
	
	
	

}