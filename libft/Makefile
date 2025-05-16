NAME = libft.a

# Betriebssystem-Erkennung
UNAME_S := $(shell uname -s)

# Farben für die Ausgabe
GREEN = \033[0;32m
YELLOW = \033[0;33m
RED = \033[0;31m
BLUE = \033[0;34m
MAGENTA = \033[0;35m
CYAN = \033[0;36m
RESET = \033[0m

# Compiler und Flags basierend auf Betriebssystem
ifeq ($(UNAME_S),Linux)
	CC = gcc
	CFLAGS = -Wall -Wextra -Werror
endif
ifeq ($(UNAME_S),Darwin)
	CC = cc
	CFLAGS = -Wall -Wextra -Werror
endif
ifeq ($(OS),Windows_NT)
	CC = gcc
	CFLAGS = -Wall -Wextra -Werror
endif

SRC = ft_memcmp.c ft_itoa.c ft_strmapi.c ft_strcmp.c\
	ft_striteri.c ft_putstr_fd.c ft_putendl_fd.c \
	ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c \
	ft_isalpha.c ft_isascii.c ft_isdigit.c ft_isprint.c \
	ft_memchr.c ft_memcpy.c ft_memmove.c ft_memset.c ft_split.c \
	ft_strchr.c ft_strdup.c ft_strjoin.c ft_strlcat.c ft_strlcpy.c \
	ft_strlen.c ft_strncmp.c ft_strnstr.c ft_strrchr.c ft_strtrim.c \
	ft_substr.c ft_tolower.c ft_putchar_fd.c ft_toupper.c ft_putnbr_fd.c \
	get_next_line.c ft_printf_src/ft_print_digit_hex.c \
	ft_printf_src/ft_print_digit.c ft_printf_src/ft_print_unsigned_digit.c \
	ft_printf_src/ft_printf_char.c ft_printf_src/ft_printf.c \
	ft_printf_src/ft_printstring.c ft_printf_src/ft_to_hex.c \
	ft_printf_src/ft_voidpointer.c

BONUS_SRC = ft_lstnew_bonus.c ft_lstadd_front_bonus.c ft_lstsize_bonus.c \
	ft_lstlast_bonus.c ft_lstadd_back_bonus.c ft_lstdelone_bonus.c \
	ft_lstclear_bonus.c ft_lstiter_bonus.c ft_lstmap_bonus.c

OBJ = $(SRC:.c=.o)
BONUS_OBJ = $(BONUS_SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	@echo "$(GREEN)Erstelle Bibliothek $@...$(RESET)"
	@ar rcs $(NAME) $(OBJ)
	@echo "$(GREEN)Bibliothek $(NAME) erfolgreich erstellt!$(RESET)"

%.o: %.c libft.h
	@echo "$(BLUE)Kompiliere $<...$(RESET)"
	@$(CC) $(CFLAGS) -c $< -o $@

bonus: $(OBJ) $(BONUS_OBJ)
	@echo "$(CYAN)Füge Bonus-Funktionen hinzu...$(RESET)"
	@ar rcs $(NAME) $(OBJ) $(BONUS_OBJ)
	@echo "$(CYAN)Bonus-Funktionen erfolgreich hinzugefügt!$(RESET)"

clean:
	@echo "$(YELLOW)Entferne Objekt-Dateien...$(RESET)"
	@rm -f *.o ft_printf_src/*.o
	@echo "$(YELLOW)Objekt-Dateien entfernt!$(RESET)"

fclean: clean
	@echo "$(RED)Entferne $(NAME)...$(RESET)"
	@rm -f $(NAME)
	@echo "$(RED)$(NAME) entfernt!$(RESET)"

re: fclean all

.PHONY: all clean fclean re bonus