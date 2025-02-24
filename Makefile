##
## EPITECH PROJECT, 2024
## Makefile
## File description:
## Makefile
##

.PHONY: all clean fclean re tests_run

GREEN 	=	\033[0;32m
YELLOW 	=	\033[0;33m
RED =	\033[0;31m
NC 	=	\033[0m

%.o: %.cpp
	@echo "$(YELLOW)⚙️  Compiling $(GREEN)$<$(YELLOW)$(NC)"
	@g++ $(CPPFLAGS) -c $< -o $@
	@echo "$(GREEN)✅ Generated $(YELLOW)$@$(GREEN) successfully$(NC)"

NAME	=	nanotekspice

MAIN_SRC	=	src/Main.cpp

SRC	=	src/commandLineHandling/CommandLineInput.cpp	\
		src/fileHandling/FileReader.cpp	\
		src/fileHandling/Parser.cpp		\
		src/components/AComponent.cpp	\
		src/components/Pin.cpp			\
		src/components/basic/ADoor.cpp	\
		src/components/basic/And.cpp	\
		src/components/basic/Not.cpp	\
		src/components/basic/Xor.cpp	\
		src/components/special/True.cpp	\

TESTS_SRC =	tests/tests.cpp	\
			tests/randomTests.cpp	\

OBJ =	$(SRC:.cpp=.o)

MAIN_OBJ =	$(MAIN_SRC:.cpp=.o)

CPPFLAGS =	-std=c++20 -Wall -Wextra -Werror -O2 -g

CPPTESTFLAGS =	--coverage -lcriterion -Wall -Wextra -Werror -O2 -g

all: 	$(NAME)

$(NAME):	$(OBJ) $(MAIN_OBJ)
	@echo "$(GREEN)🔨 Building $(NAME)...$(NC)"
	@g++ -o $(NAME) $(OBJ) $(MAIN_OBJ)

run: re
	@echo "$(GREEN)🚀 Running $(NAME)...$(NC)"
	@echo "$(YELLOW)-----------------------------------$(NC)"
	@./$(NAME)

valgrind: $(NAME)
	@echo "$(YELLOW)🔍 Running Valgrind...$(NC)"
	@valgrind --leak-check=full --show-leak-kinds=all ./$(NAME)

tests_run:
	@echo "$(YELLOW)🧪 Running tests...$(NC)"
	@g++ -o unit_tests $(SRC) $(TESTS_SRC) $(CPPTESTFLAGS)
	@./unit_tests
	@gcovr --exclude tests/

clean:
	@echo "$(RED)🧹 Cleaning up...$(NC)"
	@rm -f $(OBJ) $(MAIN_OBJ)
	@rm -f *.gcda
	@rm -f *.gcno

fclean: clean
	@echo "$(RED)🧹 Removing binaries...$(NC)"
	@rm -f $(NAME)
	@rm -f unit_tests

re: fclean all
