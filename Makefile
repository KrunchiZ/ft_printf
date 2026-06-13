NAME		:= libftprintf.a
LIBFT_DIR	:= libft
LIBFT		:= $(LIBFT_DIR)/libft.a

CC		:= cc
CFLAGS	:= -Wall -Wextra -Werror
SRCS	:= \
		   pf_char_string.c			pf_int.c		\
		   pf_ptr.c		pf_hex.c	pf_percent.c	\
		   ft_printf.c	ft_putnbrstr.c

OBJS	:= $(SRCS:.c=.o)

GREEN	:= \e[32m
CYAN	:= \e[36m
WHITE	:= \e[0m

.PHONY: all fclean clean re bonus

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS) 
	@ar rcs $@ $^
	@printf "Archiving $(GREEN)$(NAME)$(WHITE)...\n"

$(LIBFT):
	@printf "Making $(GREEN)$(LIBFT)$(WHITE)...\n"
	@make -C $(LIBFT_DIR)
	@cp $(LIBFT) $(NAME)
	@printf "Copying $(GREEN)$(LIBFT)$(WHITE) -> $(GREEN)./$(NAME)$(WHITE).\n"

%.o: %.c
	@$(CC) $(CFLAGS) -I$(LIBFT_DIR)/include -c $< -o $@
	@printf "Compiling $(CYAN)$@$(WHITE)...\n"

fclean: clean
	@rm -f $(NAME) $(LIBFT)
	@printf "Removing library files...\n"

clean:
	@make -C $(LIBFT_DIR) clean
	@rm -f $(OBJS)
	@printf "Removing libftprintf object files...\n"

re: fclean all

bonus: all
