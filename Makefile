NAME = ft_gkrellm
FLAG = -Wall -Wextra -Werror -lncurses -o
SRC = ft_gkrellm.cpp Console.cpp


all:
	@clang++ $(FLAG) $(NAME) $(SRC)
	@echo "\033[32mBuilt $(NAME).\033[0m"
clean:
	@/bin/rm -f $(NAME)
	@echo "\033[32mCleaned up compiled files.\033[0m"
run: all
	./$(NAME)
