NAME_C = client
NAME_S = server
NAME_BONUS_C = client_bonus 
NAME_BONUS_S = server_bonus 
HEADER = minitalk.h 

SRCM = client.c server.c utiles.c
SRCB = client_bonus.c server_bonus.c utiles_bonus.c

OBJM = $(SRCM:.c=.o)
OBJB = $(SRCB:.c=.o)

CC = gcc
FLAGE = -Wall -Wextra -Werror

%.o: %.c
	$(CC) $(FLAGE) -c $< -o $@

$(NAME_C) : $(OBJM) $(HEADER) 
	$(CC) $(FLAGE) client.o utiles.o -o $(NAME_C)
	$(CC) $(FLAGE) server.o utiles.o -o $(NAME_S)

$(NAME_BONUS_C) : $(OBJB) $(HEADER)
	$(CC) $(FLAGE) client_bonus.o utiles_bonus.o -o $(NAME_BONUS_C)
	$(CC) $(FLAGE) server_bonus.o utiles_bonus.o -o $(NAME_BONUS_S)


all: $(NAME_C)

bonus: $(NAME_BONUS_C)

clean:
	rm -rf $(OBJM) $(OBJB)

fclean: clean
	rm -rf $(NAME_C) $(NAME_S) $(NAME_BONUS_C) $(NAME_BONUS_S)

re: fclean $(NAME_C) $(NAME_S) $(NAME_BONUS_C) $(NAME_BONUS_S)

.PHONY: re clean fclean all