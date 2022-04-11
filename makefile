NAME := ft_containers

TIMENAME := time_test

SOURCES_FOLDER = srcs/
SOURCES = main.cpp\
		  Tester.cpp

SOURCES_PREFIXED = $(addprefix $(SOURCES_FOLDER), $(SOURCES))

TIME_SOURCES = time_test.cpp\
			   Tester.cpp

TIME_SOURCES_PREFIXED = $(addprefix $(SOURCES_FOLDER), $(SOURCES_PREFIXED))

INCLUDES_FOLDER = inc/
INCLUDES = Tester.hpp\
		   iterator_traits.hpp\
		   enable_if.hpp\
		   is_integral.hpp\
		   equal.hpp\
		   lexicographical_compare.hpp\
		   iterator.hpp\
		   pair.hpp\
		   reverse_iterator.hpp\
		   vector.hpp\

INCLUDES_PREFIXED = $(addprefix $(INCLUDES_FOLDER), $(INCLUDES))

OBJECTS_FOLDER = objs/
OBJECT = $(SOURCES:.cpp=.o)
OBJECTS = $(addprefix $(OBJECTS_FOLDER), $(OBJECT))
DEPENDENCIES = $(OBJECTS:.o=.d)

TIME_OBJECT = $(TIME_SOURCES:.cpp=.o)
TIME_OBJECTS = $(addprefix $(OBJECTS_FOLDER), $(TIME_OBJECT))
DEPENDENCIES = $(TIME_OBJECTS:.o=.d)

FT_EQUAL_STD = 0

CXX := clang++
ifeq ($(FT_EQUAL_STD), 1)
	CXXFLAGS := -Wall -Wextra -Werror
else
	CXXFLAGS := -Wall -Wextra -Werror -std=c++98
endif

$(OBJECTS_FOLDER)%.o : $(SOURCES_FOLDER)%.cpp
	@mkdir -p $(OBJECTS_FOLDER)
	@echo "Compiling : $<"
	@$(CXX) $(CXXFLAGS) -D FT_EQUAL_STD=$(FT_EQUAL_STD) -c $< -o $@ -I$(INCLUDES_FOLDER)

$(NAME): $(OBJECTS)
	@echo "Create    : $(NAME)"
	@$(CXX) $(CXXFLAGS) $(OBJECTS) -o $(NAME)

$(TIMENAME): $(TIME_OBJECTS)
	@echo "Create    : $(TIMENAME)"
	@$(CXX) $(CXXFLAGS) $(TIME_OBJECTS) -o $(TIMENAME)

all: $(NAME)

-include $(DEPENDENCIES)

clean:
	@rm -rf $(OBJECTS_FOLDER)

fclean: clean
	@rm -rf $(NAME)
	@rm -rf $(TIMENAME)

re: fclean all

docker:
	@LOGNAME=`date +%Y%m%d%H%M%S` && ./docker_start.sh $${LOGNAME} && echo "log: "./make_log/$${LOGNAME}

docker_time:
	@LOGNAME=`date +%Y%m%d%H%M%S` && ./docker_time_start.sh $${LOGNAME} && echo "log: "./make_log/$${LOGNAME}

log_clean:
	rm -rf ./make_log

.PHONY : all clean fclean re docker docker_time
