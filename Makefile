C = g++

FLAGS = -Wall -Werror -Wextra

NAME = avm

SRC = main.cpp Lexer.cpp Parser.cpp Interpreter.cpp Exception.cpp Factory.cpp eOperand.cpp

OBJ = $(SRC:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJ)
	@$(C) $(FLAGS) -o $(NAME) $(OBJ)

%.o: %.cpp
	@$(C) $(FLAGS) -o $@ -c $<

clean:
	@rm -rf $(OBJ)

fclean: clean
	@rm -rf $(NAME)

re: fclean all