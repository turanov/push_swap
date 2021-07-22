NAME	= push_swap
CHECKER = checker

CFLAGS	= -Wall -Wextra -Werror

CC		= gcc

HEADER		= push_swap.h

RM			= rm -f

SRCS	=  main.c ft_free_stack.c ft_stack.c ft_pa.c ft_pb.c ft_ra.c  ft_rb.c ft_rr.c  ft_rra.c \
          ft_rrb.c ft_rrr.c ft_sa.c  ft_sb.c ft_ss.c validation.c algorithms1.c algorithms2.c \
          algorithms3.c algorithms4.c algorithms5.c sort.c

CH_SRCS	=	checker.c get_next_line/get_next_line.c get_next_line/get_next_line_utils.c ft_stack.c \
			validation.c ft_free_stack.c ft_pa.c ft_pb.c ft_ra.c  ft_rb.c ft_rr.c  ft_rra.c \
            ft_rrb.c ft_rrr.c ft_sa.c  ft_sb.c ft_ss.c

OBJS 		= ${SRCS:.c=.o}
CH_OBJS 	= ${CH_SRCS:.c=.o}

all: 		${NAME} ${CHECKER}

.c.o:
			${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

$(NAME): 	$(OBJS)
			$(CC) $(OBJS) $(CFLAGS) libft/libft.a   -o $(NAME)
$(CHECKER):	$(CH_OBJS)
			$(CC) $(CH_OBJS) $(CFLAGS) libft/libft.a   -o $(CHECKER)


clean:
			${RM} ${OBJS} ${CH_OBJS}

fclean: 	clean
			${RM} ${NAME} ${CHECKER}

re: 		fclean all

.PHONY:		all clean fclean ree