NAME		:= libftprintf.a
LIBFT_DIR	:= libft
LIBFT		:= $(LIBFT_DIR)/libft.a

CC := cc
CFLAGS := -Wall -Wextra -Werror -I$(LIBFT_DIR)

SRCS := \
		pf_char.c	pf_string.c		pf_int.c		pf_uint.c		\
		pf_ptr.c	pf_lowerhex.c	pf_upperhex.c	pf_percent.c	\
		ft_printf.c	ft_putnbrstr.c

BSRCS := \
		 pf_char_bonus.c		pf_string_bonus.c	pf_int_bonus.c		\
		 pf_uint_bonus.c		pf_ptr_bonus.c		pf_lowerhex_bonus.c	\
		 pf_upperhex_bonus.c	pf_percent_bonus.c	ft_printf_bonus.c	\
		 ft_putnbrstr_bonus.c

OBJS := $(SRCS:.c=.o)
BOBJS := $(BSRCS:.c=.o)

GREEN := \e[32m
CYAN := \e[36m
WHITE := \e[0m

.PHONY: all fclean clean re bonus

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS) 
	@ar rcs $@ $^
	@echo "Archiving $(GREEN)$(NAME)$(WHITE)..."

bonus: $(LIBFT) $(BOBJS)
	@ar rcs $(NAME) $^
	@echo "Appending bonuses into $(GREEN)$(NAME)$(WHITE)..."

$(LIBFT):
	@echo "Making $(GREEN)$(LIBFT)$(WHITE)..."
	@make -C $(LIBFT_DIR)
	@cp $(LIBFT) $(NAME)
	@echo "Copying $(GREEN)$(LIBFT)$(WHITE) -> $(GREEN)./$(NAME)$(WHITE)."

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "Compiling $(CYAN)$@$(WHITE)..."

fclean: clean
	@rm -f $(NAME) $(LIBFT)
	@echo "Removing library files..."

clean:
	@make -C $(LIBFT_DIR) clean
	@rm -f $(OBJS) $(BOBJS)
	@echo "Removing libftprintf object files..."

re: fclean all
