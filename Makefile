NAME = codexion
CC = cc
CFLAGS = -Wall -Wextra -Werror -pthread -g
SRCS = args_utils.c \
	finish_simulation.c \
	free_all.c \
	main.c \
	startup_utils.c \
	time_utils.c \
	heap/cmp_functions/cmp_burnout.c \
	heap/cmp_functions/cmp_timeof_req.c \
	heap/management/pop_at.c \
	heap/management/push.c \
	heap/management/sift_down.c \
	heap/management/sift_up.c \
	heap/management/swap.c \
	heap/utils/init_heap.c \
	threads/coder/coder_routine.c \
	threads/coder/coder_utils/add_request.c \
	threads/coder/coder_utils/init_coder_p.c \
	threads/coder/coder_utils/log_and_sleep.c \
	threads/coder/coder_utils/update_both_dongles.c \
	threads/monitor/monitor_routine.c \
	threads/monitor/monitor_utils/condition_checkers.c \
	threads/monitor/monitor_utils/earliest_dead_line.c \
	threads/monitor/monitor_utils/handle_request.c \
	threads/monitor/monitor_utils/stop_wake_all.c
OBJDIR = Objects
VPATH = $(sort $(dir $(SRCS) $(SRCS_BONUS)))
OBJS = $(addprefix $(OBJDIR)/,$(notdir $(SRCS:.c=.o)))
OBJS_BONUS = $(addprefix $(OBJDIR_BONUS)/,$(notdir $(SRCS_BONUS:.c=.o)))

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

$(OBJDIR)/%.o: %.c codexion.h
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -rf $(OBJDIR)

fclean: clean
	@rm -f $(NAME)

re: fclean $(NAME)

.PHONY: all clean fclean re
