C++ = c++
CPP_FLAGS = -Wall -Werror -Wextra

SRCS =	main.cpp \
		FileSelecter.cpp \
		KoreanTextReader.cpp \
		WordFreq.cpp

HEADR = TextAnalyzer.hpp \
		KoreanTextReader.hpp \

OBJS = $(SRCS:.cpp=.o)

NAME = ../WordFreqProg

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
