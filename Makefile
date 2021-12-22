SRCS			= main.cpp
SRCS2			= test.cpp

OBJ				= $(SRCS:.cpp=.o)
OBJ2			= $(SRCS2:.cpp=.o)


CC				= clang++
RM				= rm -rf
CFLAGS			= -Wall -Wextra -Werror -std=c++98
NAME			= containers
NAME2			= containers2


%.o:			%.cpp
				$(CC) $(CFLAGS) -c $< -o $@

all:				$(NAME) $(NAME2)

run:
				./containers 
				./containers2

clone:
				git clone  https://github.com/mli42/containers_test.git

test:			
				cd containers_test && ./do.sh

diff:
				diff mySTL.txt originalSTL.txt

$(NAME):		$(OBJ)
				$(CC) $(CFLAGS) -o $(NAME) $(OBJ)

$(NAME2):		$(OBJ2)
				$(CC) $(CFLAGS) -o $(NAME2) $(OBJ2)

clean:
				$(RM) $(OBJ) $(OBJ2) $(OBJ_BONUS) containers_test/

fclean:			clean
				$(RM) $(NAME) $(NAME2) $(NAME_BONUS) mySTL.txt originalSTL.txt

re:				fclean $(NAME) $(NAME2)

g:				fclean $(OBJS)
				$(CC) -g -o $(NAME) ${SRCS} ${LIBS} 

.PHONY:			all clean fclean re g
