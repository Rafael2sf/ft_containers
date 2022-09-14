# PROGRAM #

NAME	=

# TERMINAL #

RMV		=		rm -f
MKD		=		mkdir -p
PRT		=		printf
MKE		=		make
CPY		=		cp

# COLORS #

--GRN	=		[32m
--RED	=		[31m
--WHT	=		[39m

# DIRS #

_SRC	=		./tests/
_OBJ	=		./objs/
_LIB	=
_BIN	=		./bin/

# COMPILER #

CXX		=		c++
AR		=		ar rcs
CXXFLAGS=		-Wall -Werror -Wextra -std=c++98

# FILES #

SRCS_	=		ft_vector.cpp \
				ft_map.cpp

SRCS	=		$(addprefix $(_SRC), $(SRCS_))
STD_SRCS=		$(addprefix $(_SRC), $(patsubst ft_%, std_%, $(notdir $(SRCS))))

OBJS	=		$(patsubst $(_SRC)%.cpp,$(_OBJ)%.o,$(SRCS))
OBJS	+=		$(patsubst $(_SRC)%.cpp,$(_OBJ)%.o,$(STD_SRCS))

BINS	=		$(patsubst $(_OBJ)%.o, $(_BIN)% ,$(OBJS))

# RULES #

all: $(_BIN) $(BINS)

test:
	$(CXX) $(CXXFLAGS) tests/ft_rbt.cpp -o test.exe

$(_OBJ)%.o: $(_SRC)%.cpp
	@$(MKD) $(_OBJ)
	@$(CXX) $(CXXFLAGS) -c $< -o $@
	@echo -e "$(--GRN)compiling\t$(<)\t->\t$(@)$(--WHT)"

$(_SRC)std_%.cpp: $(_SRC)ft_%.cpp
	@cat $< | sed 's/ft::/std::/g' > $(addprefix $(_SRC), $(patsubst ft_%, std_%, $(notdir $<)))
	@echo -e "$(--GRN)creating\t$(<)\t->\t$(@)$(--WHT)"

$(_BIN)%: $(_OBJ)%.o
	@$(MKD) $(_BIN)
	@$(CXX) $(CXXFLAGS) $(<) -o $(@)
	@echo -e "$(--GRN)executable\t$(<)\t->\t$(@)$(--WHT)"

%/:
	@$(MKD) $(@)

# CLEAN #

clean:
	$(RMV) $(OBJS) $(STD_SRCS) output.*

fclean: clean
	$(RMV) -r $(_OBJ) $(_BIN) $(NAME)

re: fclean all

.PHONY		: all clean fclean re
.PRECIOUS	: $(STD_SRCS) $(OBJS)
