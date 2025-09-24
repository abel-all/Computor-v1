CC		=	c++

NAME	=	computor

CFLAGS	=	-Wall -Wextra -Werror

HEADERS	=	Parser.hpp

SRCS	= 	Parser.cpp main.cpp

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