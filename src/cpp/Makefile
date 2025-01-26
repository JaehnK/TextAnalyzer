CXX = g++-9
PYTHON_INCLUDE = $(shell python3-config --includes)
PYBIND11_INCLUDE = $(shell python3 -m pybind11 --includes)
CPP_FLAGS = -Wall -Werror -Wextra -O3 -shared -std=c++11 -fPIC $(PYBIND11_INCLUDE)
PY_FLAGS = -O3 -shared -std=c++14 -fPIC $(PYTHON_INCLUDE) $(PYBIND11_INCLUDE)

SRCS = ./bindings/main.cpp \
    ./analyzers/WordFreq.cpp
HEADR = ./includes/TextAnalyzer.hpp
OBJS = $(SRCS:.cpp=.o)
NAME = ../WordFreqAnalyzer
PY_TARGET = ../WordFreqAnalyzer$(shell python3-config --extension-suffix)

all: $(NAME) $(PY_TARGET)

$(NAME): $(OBJS)
	$(CXX) $(CPP_FLAGS) $(OBJS) -o $(NAME)

$(PY_TARGET): $(OBJS)
	$(CXX) $(PY_FLAGS) $(OBJS) -o $(PY_TARGET)

%.o: %.cpp
	$(CXX) $(CPP_FLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME) $(PY_TARGET)

re: fclean all

.PHONY: all clean fclean re