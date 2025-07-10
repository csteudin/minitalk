# REQUIREMENTS #
NAME = server 
NAME2 = client
CC = cc
CCFLAGS = -Wall -Wextra -Werror

# DIRECTORYZ #
SRC_DIR = src
INC_DIR = inc
OBJ_DIR = obj

# FILEZ #
SRC_SERVER = $(SRC_DIR)/server.c
SRC_CLIENT = $(SRC_DIR)/client.c

OBJ_SERVER = $(OBJ_DIR)/server.o
OBJ_CLIENT = $(OBJ_DIR)/client.o

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

# RULEZ #
.SILENT :

all : $(NAME) $(NAME2) 

$(NAME) : $(OBJ_SERVER) $(LIBFT)
	$(CC) $(CCFLAGS) -I$(INC_DIR) -L$(LIBFT_DIR) -lft $^ -o $@

$(NAME2) : $(OBJ_CLIENT) $(LIBFT)
	$(CC) $(CCFLAGS) -I$(INC_DIR) -L$(LIBFT_DIR) -lft $^ -o $@
	echo "$(NAME) && $(NAME2) got compiled"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(OBJ_DIR)
	$(CC) $(CCFLAGS) -c $< -o $@

$(LIBFT) :
	make -C $(LIBFT_DIR)

clean :
	rm -rf $(OBJ_DIR)
	echo "deleted object files"

fclean : clean
	rm -rf $(NAME) $(NAME2)
	make -C $(LIBFT_DIR) fclean
	echo "deleted all files"

re : fclean all
	echo "re-creating . . ."

.PHONY : all clean fclean re