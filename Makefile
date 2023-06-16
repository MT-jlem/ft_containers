CC = c++

CXXFLAGS = -Wall -Wextra -Werror -g

CPPFLAGS = -std=c++98

SRC = main.cpp vectorTests.cpp stackTest.cpp mapTests.cpp setTests.cpp

OBJ = $(SRC:.cpp=.o)

NAME = containers

HEADERS =	./includes/vector.hpp ./includes/iterator.hpp ./includes/pairs.hpp \
			./includes/utils.hpp ./includes/map.hpp ./includes/stack.hpp \
			./includes/set.hpp	./includes/SetTree.hpp

all :$(HEADERS) $(NAME)

$(NAME) :$(HEADERS) $(OBJ) 
	$(CC) $(CXXFLAGS) $(CPPFLAGS) $(OBJ) -o $(NAME)

%.o: %.cpp $(HEADERS)
	$(CC) $(CXXFLAGS) $(CPPFLAGS) -c $< -o $@

clean :
	@-rm *.o

fclean : clean
	@-rm $(NAME)

re : fclean all


