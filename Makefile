SRCS	=	tests/ft_vector2.cpp
OBJS	=	tests/ft_vector2.o

all: $(OBJS)

%.o: %.cpp
	c++ -Wall -Werror -Wextra -std=c++98 -c $< -o $@
	sh run_test.sh $<
