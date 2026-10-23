##
## EPITECH PROJECT, 2024
## FTP
## File description:
## Makefile
##

.PHONY: all clean fclean re coverage test_run tests_run

# Couleurs ANSI
GREEN=\033[1;32m
BLUE=\033[1;34m
RED=\033[1;31m
YELLOW=\033[1;33m
NC=\033[0m

MAIN =  main.c

SRC  = 	src/command_handler.c		\
		src/data_transfer.c			\
		src/server_init.c			\
		src/server_run.c			\
		src/response.c				\
		src/signal_handler.c		\
		src/command/handle_cdup.c	\
		src/command/handle_cwd.c	\
		src/command/handle_dele.c	\
		src/command/handle_help.c	\
		src/command/handle_list.c	\
		src/command/handle_noop.c	\
		src/command/handle_port.c	\
		src/command/handle_pasv.c	\
		src/command/handle_pwd.c	\
		src/command/handle_quit.c	\
		src/command/handle_retr.c	\
		src/command/handle_stor.c	\
		src/command/handle_user.c	\
		src/command/handle_pass.c	\

OBJ = $(SRC:.c=.o)

OBJMAIN = $(MAIN:.c=.o)

TEST_SRC =	tests/tests_server_init.c	\

INCLUDES = -I./src/

CFLAGS = -Wall -Wextra -Werror

NAME =	myftp

CC = gcc

all: $(NAME)

$(NAME): $(OBJ) $(OBJMAIN)
	@echo -e "$(BLUE)ᒥ🔧ᒧ Compilation de $(NAME)...$(NC)"
	$(CC) -o $(NAME) $(OBJ) $(OBJMAIN) $(CFLAGS) $(INCLUDES)
	@echo -e "$(GREEN)ᒥ✅ᒧ Compilation terminée avec succès !$(NC)"

%.o: %.c
	@echo -e "$(YELLOW)ᒥ🚀ᒧ Compilation de $<...$(NC)"
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@echo -e "$(RED)ᒥ🔥ᒧ Suppression des fichiers objets...$(NC)"
	@rm -rf $(OBJ)
	@rm -rf $(OBJMAIN)
	@echo -e "$(GREEN)ᒥ✅ᒧ Clean terminé !$(NC)"

fclean: clean
	@echo -e "$(RED)ᒥ🔥ᒧ Suppression de $(NAME)...$(NC)"
	@rm -rf $(NAME)
	@rm -rf unit_tests
	@rm -rf *.gcno
	@rm -rf *.gcda
	@rm -rf vgcore.*
	@echo -e "$(GREEN)ᒥ✅ᒧ Full clean terminé !$(NC)"

re: fclean all

coverage: test_run
	@echo -e "$(BLUE)ᒥ📊ᒧ Génération du rapport de couverture...$(NC)"
	@gcovr
	@echo -e "$(GREEN)ᒥ✅ᒧ Rapport généré !$(NC)"

test_run: $(OBJ)
	@echo -e "$(BLUE)ᒥ🧪ᒧ Compilation des tests...$(NC)"
	@gcc -o unit_tests $(SRC) $(TEST_SRC) $(CFLAGS) $(INCLUDES) \
		--coverage -lcriterion
	@echo -e "$(GREEN)ᒥ✅ᒧ Tests compilés ! Lancement...$(NC)"
	@./unit_tests

tests_run: test_run
