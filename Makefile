CC		=	c++

NAME	=	computor

CFLAGS	=	-Wall -Wextra -Werror

HEADERS	=	Parser.hpp Polynome.hpp Solver.hpp

SRCS	= 	Parser.cpp Polynome.cpp Solver.cpp main.cpp

OBJS	=	$(SRCS:.cpp=.o)

all		: 	$(NAME)

$(NAME)	: 	$(OBJS)
			$(CC) $(CFLAGS) $^ -o $@

%.o		: 	%.cpp $(HEADERS)
			$(CC) $(CFLAGS) -c $< -o $@

clean	:
			rm -rf $(OBJS)

fclean 	: 	clean
			rm -rf $(NAME)

re		: 	fclean all

.PHONY	: 	fclean all clean re