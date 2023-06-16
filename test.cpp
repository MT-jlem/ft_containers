#include "includes/vector.hpp"
#include "includes/pairs.hpp"
#include "includes/iterator.hpp"
#include "includes/utils.hpp"
#include "includes/Tree.hpp"
#include "includes/map.hpp"

#include <vector>
#include <utility>
#include <memory>
#include <list>
#include <sstream>
#include <map>
#include <stack>

void	vectorTests();
void	stackTests();
void	mapTests();
void	setTests();

int main(){

	vectorTests();
	std::cout << "--------------------vector test pass-------------------\n";
	stackTests();
	std::cout << "--------------------stack test pass---------------------\n";
	mapTests();
	std::cout << "---------------------map test pass---------------------\n";
	setTests();
	std::cout << "---------------------set test pass---------------------\n";
    return 0;
}
