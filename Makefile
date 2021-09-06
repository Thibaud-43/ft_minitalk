SRCS_CLIENT = client.c
SRCS_SERVER = server.c

NAME	= client
NAME2 = server

CXX		= clang
CXXFLAGS = -Wall -Wextra -Werror

RM		= rm -rf

SRCS_PATH	=	./
OBJS_PATH	=	objs/
LIBFT 		= 	./libft/libft.a
INC			= 	-I./Libft


OBJS_CLIENT		= $(addprefix $(OBJS_PATH),$(SRCS_CLIENT:.c=.o))
OBJS_SERVER		= $(addprefix $(OBJS_PATH),$(SRCS_SERVER:.c=.o))

$(OBJS_PATH)%.o: %.c
	@ mkdir -p $(OBJS_PATH)
	$(CXX) $(INC) $(CXXFLAGS) -c $< -o $@

all: $(NAME) $(NAME2)

$(LIBFT):
	cd ./Libft ; make

$(NAME): $(OBJS_CLIENT)
	$(CXX) $(OBJS_CLIENT) $(INC) -o $(NAME) $(LIBFT)

$(NAME2): $(OBJS_SERVER)
	$(CXX) $(OBJS_SERVER) $(INC) -o $(NAME2) $(LIBFT)

clean: 
	$(RM) $(OBJS_CLIENT) $(OBJS_SERVER) $(OBJS_PATH)

fclean: clean
	$(RM) $(NAME) $(NAME2)

re: clean all

.PHONY: all clean fclean re