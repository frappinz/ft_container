#include "common.hpp"
#include <list>

#define T1 foo<int>

int		main(void)
{
	std::list<T1> lst;
	unsigned int lst_size = 5;
	for (unsigned int i = 0; i < lst_size; ++i)
		lst.push_back((i + 1) * 7);

	TESTED_NAMESPACE::multiset<T1> st(lst.begin(), lst.end());
	TESTED_NAMESPACE::multiset<T1>::reverse_iterator it(st.rbegin());
	TESTED_NAMESPACE::multiset<T1>::const_reverse_iterator ite(st.rbegin());
	printSize(st);

	printpair(++ite);
	printpair(ite++);
	printpair(ite++);
	printpair(++ite);

	it->m();
	ite->m();

	printpair(++it);
	printpair(it++);
	printpair(it++);
	printpair(++it);

	printpair(--ite);
	printpair(ite--);
	printpair(--ite);
	printpair(ite--);

	(*it).m();
	(*ite).m();

	printpair(--it);
	printpair(it--);
	printpair(it--);
	printpair(--it);

	return (0);
}