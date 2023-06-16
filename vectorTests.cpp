#include "includes/vector.hpp"
#include <memory>
#include <iostream>
#include <vector>


// namespace ft = std;

template < typename T>
void	printVec(ft::vector<T>	&v){
	for (ft::vector<int>::iterator it = v.begin(); it != v.end(); ++it)
		std::cout << *it << " ";
	std::cout << std::endl;
}

void	vectorTests(){
	{//start of scope
	ft::vector<int> v;
	ft::vector<int> a((std::allocator<int>()));
	ft::vector<int> b(10, 69);
	ft::vector<int> c(b.begin(), b.end());
	ft::vector<int>	d(c);

	v = d;
	printVec(v);
	v.assign(5, 11);
	printVec(v);
	v.assign(b.begin(), b.end());
	printVec(v);
	v.get_allocator();
	try{
		v.at(500);}
	catch(const std::exception& e){
		std::cerr << e.what() << '\n';
	}
	std::cout << v[3] << " operator[] test\n";
	std::cout << v.front() << " front() test\n";
	std::cout << v.back() << " back() test\n";
	std::cout << v.data() << " data() test\n";

	ft::vector<int>::iterator it = v.begin();
	ft::vector<int>::iterator eit = v.end();
	ft::vector<int>::const_iterator cit = v.begin();
	ft::vector<int>::const_iterator ecit = v.end();
	ft::vector<int>::reverse_iterator rit = v.rbegin();
	ft::vector<int>::reverse_iterator reit = v.rend();
	ft::vector<int>::const_reverse_iterator rcit = v.rbegin();
	ft::vector<int>::const_reverse_iterator recit = v.rend();

	std::cout << *cit<< " first elm\n";
	std::cout << *(eit) << " last ell\n";
	std::cout << *it << " first elm\n";
	std::cout << *(ecit) << " last elm\n";

	std::cout << *rit<< " reverse begin it value\n";
	std::cout << *reit<< " reverse end it value\n";
	std::cout << *rcit<< " reverse begin it value\n";
	std::cout << *recit<< " reverse end it value\n";	

	std::cout << v.size() << " size test\n";
	std::cout << v.max_size() << " max_size test\n";
	std::cout << v.capacity() << " capacity test\n";
	if (v.empty())
		std::cout << "vector is empty\n";
	else
		std::cout << "vector is not empty\n";
	v.reserve(10);
	v.push_back(99); std::cout << "99 is pushed: ";
	printVec(v);
	v.pop_back(); std::cout << "99 is popped: ";
	printVec(v);
	v.insert(v.begin(), 100);
	printVec(v);
	v.insert(v.begin(), 5, 13);
	printVec(v);
	v.insert(v.begin(),b.begin(), b.end());
	printVec(v);
	// v.push_back(333);
	v.erase(v.begin());
	v.erase(v.begin() + 3, v.end() - 3);
	printVec(v);
	v.resize(10);
	printVec(v);
	v.clear();
	printVec(v);
	v.swap(d);
	printVec(v);

	}//end of scope

	//speed test
	// {
	// 	ft::vector<int> vec;

	// 	for (int i = 0; i < 1000000; ++i)
	// 		vec.push_back(i+1);
	// 	std::cout << "finished\n";
	// }
}