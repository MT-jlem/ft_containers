#include "includes/map.hpp"
#include <iostream>
#include <vector>
#include <memory>
#include <map>
#include <utility>

// namespace ft = std;

void	mapTests(){
	{
	//constructor tests
		ft::map<int, int>	a((std::less<int>()), std::allocator<std::pair<int, int> >());
		std::vector<ft::pair<int, int> > v;
		for (int i = 0; i < 10; ++i)
			v.push_back(ft::pair<int, int>(i+1, i*i));
		ft::map<int, int> 	b(v.begin(), v.end());
		ft::map<int, int> 	c(b);
		ft::map<int, int> 	m;
		//assignment operator test;
		m = c;
		// getters
		m.get_allocator();
		try
		{
			m.at(99);
		}
		catch(const std::exception& e)
		{
			std::cerr << e.what() << '\n';
		}
		std::cout << m[5] << " is the mapped value of 5\n";
		m[99] = 199;
		std::cout << m[99] << " is the mapped value of 99\n";

		ft::map<int, int>::iterator it = m.begin();
		ft::map<int, int>::iterator eit = m.end();
		ft::map<int, int>::const_iterator cit = m.begin();
		ft::map<int, int>::const_iterator ecit = m.end();
		ft::map<int, int>::reverse_iterator rit = m.rbegin();
		ft::map<int, int>::reverse_iterator reit = m.rend();
		ft::map<int, int>::const_reverse_iterator rcit = m.rbegin();
		ft::map<int, int>::const_reverse_iterator recit = m.rend();

		std::cout << cit->first << " first elm\n";
		std::cout << (eit)->first << " last ell\n";
		std::cout << it->first << " first elm\n";
		std::cout << (ecit)->first << " last elm\n";

		std::cout << rit->first << " reverse begin it value\n";
		std::cout << reit->first << " reverse end it value\n";
		std::cout << rcit->first << " reverse begin it value\n";
		std::cout << recit->first << " reverse end it value\n";	

		if (m.empty())
		 	std::cout << "map is empty\n";
		else
			std::cout << "map is not empty\n";
		std::cout << m.size() << " is the map size\n";
		std::cout << m.max_size() << " is the max size\n";
		m.clear();
		if (m.empty())
			std::cout << "map is cleared\n";
		ft::pair<ft::map<int, int>::iterator, bool> insertRet = m.insert(ft::pair<int, int>(22, 20));
		std::cout << insertRet.first->first << " | " << insertRet.second << " return value of insert \n";
		m.insert(v.begin(), v.end());
		for (ft::map<int, int>::iterator iter = m.begin(); iter != m.end(); ++iter){
			std::cout << "|" << iter->first << " - " << iter->second << "| >> ";
		}
		std::cout << std::endl;

		ft::map<int, int>::iterator eraseIter = m.erase(m.begin());
		std::cout << eraseIter->first << " - " << eraseIter->second << " erase(iter) return value\n";
		std::cout << m.erase(6) << " return value for erase(Key)\n";
		ft::map<int, int>::iterator eraseIter2 =  m.erase(m.begin(), m.end());
		std::cout << eraseIter2->first << " - " << eraseIter2->second << " erase(first, last) return value\n";

		m.swap(c);

		std::cout << m.count(5) << " return value of count\n";
		ft::map<int, int>::iterator findIter = m.find(5);
		std::cout << findIter->first << " - " << findIter->second << " find return value\n";

		ft::pair<ft::map<int, int>::iterator, ft::map<int, int>::iterator> eqRet = m.equal_range(5);
		std::cout << eqRet.first->first << " | " << eqRet.second->first << " equal range return val \n";
		ft::map<int, int>::iterator lowerBoundIter = m.lower_bound(5);
		std::cout << lowerBoundIter->first <<  " | " << lowerBoundIter->second << " lower bound return val\n";
			ft::map<int, int>::iterator upperBoundIter = m.upper_bound(5);
		std::cout << upperBoundIter->first <<  " | " << upperBoundIter->second << " upper bound return val\n";
		m.key_comp(); //i will do test later but it's working
		m.value_comp();
	}

	//speed test

	// ft::map<int, int> m;
	// for (int i = 0; i < 1000000; ++i){
	// 	m.insert(ft::pair<int, int>(i+1, i*i));
	// }
	// for (ft::map<int, int>::iterator it = m.begin(); it != m.end(); ++it)
	// 	std::cout << it->first << " ";
	// std::cout << "map test finished\n";
}