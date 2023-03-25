
CFLAGC = -Wall -Wextra -Werror
CC = cc
server = server 
client = client
server_bonus = server_bonus
client_bonus = client_bonus
all: $(server) $(client)

bonus:$(server_bonus) $(client_bonus)

$(server_bonus): minitalk.h server_bonus.c
			$(CC) $(CFLAGS) server_bonus.c  -o $(server_bonus)
$(client_bonus): minitalk.h client_bonus.c
			$(CC) $(CFLAGS) client_bonus.c  -o $(client_bonus)

$(server): minitalk.h server.c
			$(CC) $(CFLAGS) server.c -o $(server)
$(client): minitalk.h client.c
			$(CC) $(CFLAGS) client.c  -o $(client)

clean:
	rm -rf $(c_obj) 
fclean: clean
	rm -rf $(client) $(server) $(client_bonus) $(server_bonus)
re: fclean all