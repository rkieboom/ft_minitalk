CLIENT_NAME = client
SERVER_NAME = server

CC := gcc
CFLAGS = -Wall -Wextra -Werror

ifeq ($(DEBUG), 1)
	CFLAGS += -D DEBUG -g3 -fsanitize=address
endif

SRCDIR = src
PRINTFDIR = src/printf
INCDIR = inc
OBJDIR = obj

LIBFT = libft/libft.a
LIBFT_DIR = libft

SRCS_FILES_CLIENT := client.c
SRCS_FILES_SERVER := server.c signal_data.c signal_list.c

SRCS_CLIENT := $(addprefix $(SRCDIR)/, $(SRCS_FILES_CLIENT))
SRCS_SERVER := $(addprefix $(SRCDIR)/, $(SRCS_FILES_SERVER))

OBJS_CLIENT := $(addprefix $(OBJDIR)/, $(notdir $(SRCS_CLIENT:.c=.o)))
OBJS_SERVER := $(addprefix $(OBJDIR)/, $(notdir $(SRCS_SERVER:.c=.o)))

all: init-submodules $(LIBFT) $(SERVER_NAME) $(CLIENT_NAME)

$(CLIENT_NAME): $(OBJS_CLIENT) $(LIBFT)
	$(CC) $(CFLAGS) $^ -o $@

$(SERVER_NAME): $(OBJS_SERVER) $(LIBFT)
	$(CC) $(CFLAGS) $^ -o $@

$(LIBFT):
	make -C $(LIBFT_DIR)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@ -I$(INCDIR) -I$(LIBFT_DIR)/inc

$(OBJDIR)/%.o: $(PRINTFDIR)/%.c
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@ -I$(INCDIR) -I$(LIBFT_DIR)/inc

init-submodules:
	git submodule update --init --recursive

clean:
	@/bin/rm -rf $(OBJDIR)

fclean: clean
	@/bin/rm -f $(SERVER_NAME) $(CLIENT_NAME)

re: fclean all

.PHONY: all clean fclean re init-submodules