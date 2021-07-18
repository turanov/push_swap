NAME	= push_swap

CFLAGS	= -Wall -Wextra -Werror

CC		= gcc

HEADER		= push_swap.h

RM			= rm -f

SRCS	=  main.c ft_free_stack.c ft_stack.c ft_pa.c ft_pb.c ft_ra.c  ft_rb.c ft_rr.c  ft_rra.c \
          ft_rrb.c ft_rrr.c ft_sa.c  ft_sb.c ft_ss.c validation.c algorithms1.c algorithms2.c algorithms3.c algorithms4.c algorithms5.c


OBJS 		= ${SRCS:.c=.o}

all: 		${NAME}

.c.o:
			${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

$(NAME): 	$(OBJS)
			$(CC) $(OBJS) $(CFLAGS) libft/libft.a   -o $(NAME)

clean:
			${RM} ${OBJS}

fclean: 	clean
			${RM} ${NAME}

re: 		fclean all

.PHONY:		all clean fclean ree