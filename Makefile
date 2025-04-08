##
## EPITECH PROJECT, 2025
## PSU-strace
## File description:
## Makefile
##

CC         	= gcc

CFLAGS   	= -I./include -std=gnu17 \
          -Wall -Wextra -Werror -pedantic -Wconversion -g3 \
		  -O3

LDFLAGS   	= -lelf

SRC_DIR  	= src
OBJ_DIR		= objects
TEST_DIR  	= tests

PROGRAMS  	= strace

STRACE_SRC 	= $(wildcard $(SRC_DIR)/*.c) \
		$(wildcard $(SRC_DIR)/strace/*.c) \
		$(wildcard $(SRC_DIR)/utils/*.c)

STRACE_OBJ  = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, \
	$(STRACE_SRC))

STRACE_BIN  = strace

GREEN      	= \033[1;32m
RED        	= \033[1;31m
ILC			= \033[3m
ORANGE     	= \033[38;5;214m
RST		   	= \033[0m

all: $(PROGRAMS)

strace: $(STRACE_OBJ)
	@$(CC) $(CFLAGS) -o $(STRACE_BIN) $(STRACE_OBJ) $(LDFLAGS)
	@printf "$(GREEN)[✅] COMPILED: $(RST) $(ILC)$(STRACE_BIN)$(RST)\n"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -o $@ -c $<
	@printf "$(ORANGE)[🚧] BUILDING: $(RST) $(ILC)$<$(RST)\n"

clean:
	@rm -rf lib/$(OBJ_DIR)
	@rm -rf $(OBJ_DIR)
	@printf "$(RED)[❌] CLEAN:    $(RST) Removed $(ILC)$(OBJ_DIR)$(RST)\n"

fclean: clean
	@rm -f $(PROGRAMS) vgcore*
	@printf "$(RED)[❌] FCLEAN:   $(RST) Removed $(ILC)executables$(RST)\n"

re: fclean all

.PHONY: all strace clean fclean re
