#include "common.hpp"
#include <list>

#define T1 float
#define T2 foo<int>
typedef _pair<const T1, T2> T3;

int		main(void)
{
	std::list<T3> lst;
	unsigned int lst_size = 5;
	for (unsigned int i = 0; i < lst_size; ++i)
		lst.push_back(T3(2.5 - i, (i + 1) * 7));

	TESTED_NAMESPACE::multimap<T1, T2> mp(lst.begin(), lst.end());
	TESTED_NAMESPACE::multimap<T1, T2>::reverse_iterator it(mp.rbegin());
	TESTED_NAMESPACE::multimap<T1, T2>::const_reverse_iterator ite(mp.rbegin());
	printSize(mp);

	printpair(++ite);
	printpair(ite++);
	printpair(ite++);
	printpair(++ite);

	it->second.m();
	ite->second.m();

	printpair(++it);
	printpair(it++);
	printpair(it++);
	printpair(++it);

	printpair(--ite);
	printpair(ite--);
	printpair(--ite);
	printpair(ite--);

	(*it).second.m();
	(*ite).second.m();

	printpair(--it);
	printpair(it--);
	printpair(it--);
	printpair(--it);

	return (0);
}
