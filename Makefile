C++ = c++
CPP_FLAGS = -Wall -Werror -Wextra

SRCS =	main.cpp \
		FileSelecter.cpp \

HEADR =  TextAnalyzer.hpp \

OBJS = $(SRCS:.cpp=.o)

NAME = TextAnalyzer

all: $(NAME)

$(NAME):$(OBJS)
		$(C++) $(CPP_FLAGS) $(OBJS) -o $(NAME)

%.o: %.cpp
		$(C++) $(CPP_FLAGS) -c $< -o $@

clean:
		rm -f $(OBJS)

fclean:
		make clean
		rm -f $(NAME)

re:
	make fclean
	make all

.PHONY: all clean fclean re
 