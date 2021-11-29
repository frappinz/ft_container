SRCS			= main.cpp
SRCS2			= test.cpp

OBJ				= $(SRCS:.cpp=.o)
OBJ2			= $(SRCS2:.cpp=.o)


CC				= clang++
RM				= rm -f
CFLAGS			= -Wall -Wextra -Werror -std=c++98
NAME			= containers
NAME2			= containers2


%.o:			%.cpp
				$(CC) $(CFLAGS) -c $< -o $@

all:				$(NAME) $(NAME2)

run:
				./containers ./containers2

diff:
				diff mySTL.txt originalSTL.txt

$(NAME):		$(OBJ)
				$(CC) $(CFLAGS) -o $(NAME) $(OBJ)

$(NAME2):		$(OBJ2)
				$(CC) $(CFLAGS) -o $(NAME2) $(OBJ2)

clean:
				$(RM) $(OBJ) $(OBJ_BONUS)

fclean:			clean
				$(RM) $(NAME) $(NAME_BONUS)

re:				fclean $(NAME)

g:				fclean $(OBJS)
				$(CC) -g -o $(NAME) ${SRCS} ${LIBS} 

.PHONY:			all clean fclean re g
