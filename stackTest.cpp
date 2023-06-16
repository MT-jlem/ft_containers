#include "includes/stack.hpp"
#include <memory>
#include <iostream>
#include <stack>

// namespace ft = std;

void	stackTests(){
	ft::stack<int> s;
	s.push(1);
	s.push(2);
	s.push(3);
	s.push(4);
	s.push(5);
	ft::stack<int> a(s);
	a = s;
	std::cout << s.top() << " top of the stack\n";
	s.pop();
	std::cout << s.top() << " top of the stack\n";
	std::cout << s.size() << " size of the stack\n";
	if (s.empty())
		std::cout << "stack is empty\n";
	else
		std::cout << "stack is not empty\n";

	// ft::stack<int> st;

	// for (int i = 0; i < 1000000; ++i)
	// 	st.push(i+1);
	// std::cout << "stack test finished\n";
}