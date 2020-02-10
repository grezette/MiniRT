.SUFFIXES:

NAME			=	miniRT

LIBFT			=	Libft/libft.a

LIBFT_DIR		=	Libft

SRCS			=	./srcs/minirt.c \
					./srcs/ft_pars_minirt.c \
					./srcs/minirt_utils.c \

OBJS			=	$(SRCS:.c=.o)

RM				= 	rm -rf

INC_PATH		= 	-I./includes

CC      		=   gcc

CFLAGS       	=   -Wall -Wextra -Werror -g

LIBS			=	-lSDLmain -lSDL -L./Libft -lft

all:			$(LIBFT) $(NAME)

$(NAME):		 $(OBJS) 
					$(CC) ${CFLAGS} $^ ${LIBS} -o $@

%.o:			%.c	
				$(CC) $(CFLAGS) -c $< -o $@ 

$(LIBFT):
				make every -C $(LIBFT_DIR)

clean:
				make clean -C $(LIBFT_DIR)
				$(RM) $(OBJS)

fclean:			clean
				make fclean -C $(LIBFT_DIR)
				$(RM) $(NAME)

re:				fclean all
