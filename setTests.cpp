#include "includes/set.hpp"
#include <iostream>
#include <vector>
#include <memory>
#include <set>
#include <utility>

// namespace ft = std;

void	setTests(){
	{
	//constructor tests
		ft::set<int>	a((std::less<int>()), std::allocator<int>());
		std::vector<int > v;
		for (int i = 0; i < 10; ++i)
			v.push_back(i+1);
		ft::set<int> 	b(v.begin(), v.end());
		ft::set<int> 	c(b);
		ft::set<int> 	m;
		//assignment operator test;
		m = c;
		// getters
		m.get_allocator();

		ft::set<int>::iterator it = m.begin();
		ft::set<int>::iterator eit = m.end();
		ft::set<int>::const_iterator cit = m.begin();
		ft::set<int>::const_iterator ecit = m.end();
		ft::set<int>::reverse_iterator rit = m.rbegin();
		ft::set<int>::reverse_iterator reit = m.rend();
		ft::set<int>::const_reverse_iterator rcit = m.rbegin();
		ft::set<int>::const_reverse_iterator recit = m.rend();

		std::cout << *cit<< " first elm\n";
		std::cout << *(eit) << " last ell\n";
		std::cout << *it << " first elm\n";
		std::cout << *(ecit) << " last elm\n";

		std::cout << *rit<< " reverse begin it value\n";
		std::cout << *reit<< " reverse end it value\n";
		std::cout << *rcit<< " reverse begin it value\n";
		std::cout << *recit<< " reverse end it value\n";	

		if (m.empty())
		 	std::cout << "set is empty\n";
		else
			std::cout << "set is not empty\n";
		std::cout << m.size() << " is the set size\n";
		std::cout << m.max_size() << " is the max size\n";
		m.clear();
		if (m.empty())
			std::cout << "set is cleared\n";
		ft::pair<ft::set<int>::iterator, bool> insertRet = m.insert(20);
		std::cout << *insertRet.first<< " | " << insertRet.second << " return value of insert \n";
		m.insert(v.begin(), v.end());
		for (ft::set<int>::iterator iter = m.begin(); iter != m.end(); ++iter){
			std::cout << "|" << *iter << "| >> ";
		}
		std::cout << std::endl;

		ft::set<int>::iterator eraseIter = m.erase(m.begin());
		std::cout << *eraseIter << " erase(iter) return value\n";
		std::cout << m.erase(6) << " return value for erase(Key)\n";
		ft::set<int>::iterator eraseIter2 =  m.erase(m.begin(), m.end());
		std::cout << *eraseIter2 << " erase(first, last) return value\n";

		m.swap(c);

		std::cout << m.count(5) << " return value of count\n";
		ft::set<int>::iterator findIter = m.find(5);
		std::cout << *findIter << " find return value\n";

		ft::pair<ft::set<int>::iterator, ft::set<int>::iterator> eqRet = m.equal_range(5);
		std::cout << *eqRet.first << " - " << *eqRet.second <<" equal range return val \n";
		ft::set<int>::iterator lowerBoundIter = m.lower_bound(5);
		std::cout << *lowerBoundIter << " lower bound return val\n";
			ft::set<int>::iterator upperBoundIter = m.upper_bound(5);
		std::cout << *upperBoundIter << " upper bound return val\n";
		m.key_comp(); //i will do test later but it's working
		m.value_comp();
	}

	//speed test

	// ft::set<int> s;

	// for(int i = 0; i < 1000000; ++i)
	// 	s.insert(i+1);
	// std::cout << "set test finished\n";
}