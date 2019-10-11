NAME=
	readcline.a

SRCS=
	readcline.c
	cline_cursor_motion.c

OBJS=$(SRCS:.c=.o)

LIBFT_DIR=libft
SIMPLIST_DIR=simplist
OBJS_PATH=$(addprefix $(OBJS_DIR)/, $(OBJS))
SRCS_PATH=$(addprefix $(SRCS_DIR)/, $(SRCS))
INCLUDES=includes

FLAGS= -Wall -Werror -Wextra

all: $(NAME)

$(NAME): $(OBJS_PATH) $(INCLUDES)/readcline.h 
	make -C $(LIBFT_DIR)
	make -C $(SIMPLIST_DIR)
	gcc $(FLAGS) $(OBJS_PATH) -ltermcap $(LIBFT_DIR)/libft.a $(SIMPLIST_DIR)/simplist.a  -o $(NAME)

$(OBJS_PATH): $(OBJS_DIR)/%.o : $(SRCS_DIR)/%.c | $(OBJS_DIR)
	gcc $(FLAGS) -I$(INCLUDES) -I$(LIBFT_DIR)/includes -I$(SIMPLIST_DIR) -c $< -o $@

$(OBJS_DIR):
	mkdir $(OBJS_DIR)

clean:
	make -C $(LIBFT_DIR) clean
	make -C $(SIMPLIST_DIR) clean
	rm -rf $(OBJS_DIR)

fclean: clean
	make -C $(LIBFT_DIR) fclean
	make -C $(SIMPLIST_DIR) fclean
	rm -rf $(NAME)

re: relib fclean all

relib:
	make -C $(LIBFT_DIR) re
	make -C $(SIMPLIST_DIR) re


