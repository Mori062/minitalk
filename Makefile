NAME_CLIENT = client
NAME_SERVER = server

M_CLIENT_SRCS = src/client.c
M_SERVER_SRCS = src/server.c

CC = cc
CFLAGS = -Wall -Wextra -Werror
INCS = include/minitalk.h

LIBFT = libft/libft.a
LIBFT_PATH = libft

GREEN = \e[38;5;118m
YELLOW = \e[38;5;226m
RESET = \e[0m
_SUCCESS = [$(GREEN)SUCCESS$(RESET)]
_INFO = [$(YELLOW)INFO$(RESET)]

CLIENT_OBJS = $(CLIENT_SRCS:.c=.o)
SERVER_OBJS = $(SERVER_SRCS:.c=.o)

all: $(NAME_CLIENT) $(NAME_SERVER)

bonus:
	rm -f $(NAME_CLIENT) $(NAME_SERVER)
	make BONUS=1

$(NAME_CLIENT): $(CLIENT_OBJS)
	@ make -C $(LIBFT_PATH)
	@ $(CC) $(CFLAGS) -I $(INCS) $(LIBFT) -o $(NAME_CLIENT) $(CLIENT_OBJS)
	@ ac rc $(NAME_CLIENT) $(CLIENT_OBJS)
	@printf "$(_SUCCESS) client ready\n"

$(NAME_SERVER): $(SERVER_OBJS)
	@ $(CC) $(CFLAGS) -I $(INCS) $(LIBFT) -o $(NAME_SERVER) $(SERVER_OBJS)
	@ ac rc $(NAME_SERVER) $(SERVER_OBJS)
	@printf "$(_SUCCESS) server ready\n"

.c.o:
	@ $(CC) $(CFLAGS) -I $(INCS) -c $< -o $@

clean:
	@ make clean -C $(LIBFT_PATH)
	@ $(RM) $(CLIENT_SRCS:.c=.o) $(SERVER_SRCS:.c=.o)
	@printf "$(_INFO) REMOVE object files\n"

fclean: clean
	@ make fclean -C $(LIBFT_PATH)
	@ $(RM) $(NAME_CLIENT) $(NAME_SERVER)
	@printf "$(_INFO) REMOVE $(NAME_CLIENT) and $(NAME_SERVER)\n"

re: fclean all

.PHONY: all bonus clean fclean re
