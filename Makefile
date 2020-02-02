NAME=readcline.a

SRCS=cline_clipboard_utilities.c \
	cline_cursor_motion.c \
	readcline_utilities.c \
	cline_io.c \
	cline_wordline_motion.c \
	middlewares.c \
	cline_history.c \
	readcline.c \
	terminal_configuration.c \
	error_handling.c

OBJS=$(SRCS:.c=.o)

LIBS_DIR=libraries
OBJS_DIR=build
SRCS_DIR=sources
OBJS_PATH=$(addprefix $(OBJS_DIR)/, $(OBJS))
SRCS_PATH=$(addprefix $(SRCS_DIR)/, $(SRCS))
INCLUDES=includes modules/centropy/includes modules/cdata_structures/shared_includes

FLAGS= -Wall -Werror -Wextra
INCLUDES_FLAGS =$(addprefix -I, $(INCLUDES))

all: $(NAME)

$(NAME): $(OBJS_PATH)
	ar rc  $(NAME) $(OBJS_PATH)
	ranlib $(NAME)

$(OBJS_PATH): $(OBJS_DIR)/%.o : $(SRCS_DIR)/%.c | $(OBJS_DIR)
	gcc $(FLAGS) $(INCLUDES_FLAGS) -c $< -o $@

$(OBJS_DIR):
	mkdir $(OBJS_DIR)

clean:
	rm -rf $(OBJS_DIR)

fclean: clean
	rm -rf $(NAME)

re: fclean all
