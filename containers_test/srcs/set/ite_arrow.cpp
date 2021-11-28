#include "common.hpp"
#include <list>

#define T1 foo<int>

int		main(void)
{
	std::list<T1> lst;
	unsigned int lst_size = 5;
	for (unsigned int i = 0; i < lst_size; ++i)
		lst.push_back(2.5 + i);

	TESTED_NAMESPACE::set<T1> st(lst.begin(), lst.end());
	TESTED_NAMESPACE::set<T1>::iterator it(st.begin());
	TESTED_NAMESPACE::set<T1>::const_iterator ite(st.begin());
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
