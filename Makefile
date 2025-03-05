##
## EPITECH PROJECT, 2024
## Makefile
## File description:
## Makefile
##

.PHONY: all clean fclean re tests_run

GREEN 	=	\033[0;32m
YELLOW 	=	\033[0;33m
RED		=	\033[0;31m
NC 		=	\033[0m

%.o: %.cpp
	@echo "$(YELLOW)⚙️  Compiling $(GREEN)$<$(YELLOW)$(NC)"
	@g++ $(CPPFLAGS) -c $< -o $@
	@echo "$(GREEN)✅ Generated $(YELLOW)$@$(GREEN) successfully$(NC)"

NAME	=	nanotekspice

MAIN_SRC	=	src/Main.cpp

SRC	=	src/commandLineHandling/CommandLineInput.cpp	\
		src/fileHandling/FileReader.cpp					\
		src/fileHandling/Parser.cpp						\
		src/factory/Factory.cpp							\
		src/components/AComponent.cpp					\
		src/components/Pin.cpp							\
		src/components/basic/ADoor.cpp					\
		src/components/basic/And.cpp					\
		src/components/basic/Not.cpp					\
		src/components/basic/Xor.cpp					\
		src/components/basic/Or.cpp						\
		src/components/basic/Nand.cpp					\
		src/components/special/True.cpp					\
		src/components/special/False.cpp				\
		src/components/special/ASpecial.cpp				\
		src/components/special/Input.cpp				\
		src/components/special/Output.cpp				\
		src/components/special/Clock.cpp				\

TESTS_SRC	=	tests/tests.cpp			\
				tests/basicGates.cpp	\
				tests/specialGates.cpp	\
				tests/factoryTests.cpp	\

OBJ	=	$(SRC:.cpp=.o)

MAIN_OBJ	=	$(MAIN_SRC:.cpp=.o)

INCLUDES	=	-I ./include

CPPFLAGS	+=	-std=c++20 -Wall -Wextra -Werror $(INCLUDES) -O2 -g

CPPTESTFLAGS	=	--coverage -lcriterion $(CPPFLAGS)

all: $(NAME)

$(NAME):	$(OBJ) $(MAIN_OBJ)
	@echo "$(GREEN)🔨 Building $(NAME)...$(NC)"
	@g++ -o $(NAME) $(OBJ) $(MAIN_OBJ)

run: re
	@echo "$(GREEN)🚀 Running $(NAME)...$(NC)"
	@echo "$(YELLOW)-----------------------------------$(NC)"
	@./$(NAME)

valgrind: $(NAME)
	@echo "$(YELLOW)🔍 Running Valgrind...$(NC)"
	@echo exit | valgrind --leak-check=full	--error-exitcode=1 \
	--show-leak-kinds=all ./$(NAME) ./tests/xor.nts

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
	@rm -f vgcore.*

fclean: clean
	@echo "$(RED)🧹 Removing binaries...$(NC)"
	@rm -f $(NAME)
	@rm -f unit_tests

re: fclean all
