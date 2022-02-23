NAME := ft_containers

SOURCES_FOLDER = srcs/
SOURCES = main.cpp

SOURCES_PREFIXED = $(addprefix $(SOURCES_FOLDER), $(SOURCES))

INCLUDES_FOLDER = inc/
INCLUDES = main.hpp

INCLUDES_PREFIXED = $(addprefix $(INCLUDES_FOLDER), $(INCLUDES))

OBJECTS_FOLDER = objs/
OBJECT = $(SOURCES:.cpp=.o)
OBJECTS = $(addprefix $(OBJECTS_FOLDER), $(OBJECT))
DEPENDENCIES = $(OBJECTS:.o=.d)

CXX := clang++
CXXFLAGS := -Wall -Wextra -Werror -std=c++98

$(OBJECTS_FOLDER)%.o : $(SOURCES_FOLDER)%.cpp
	@mkdir -p $(OBJECTS_FOLDER)
	@echo "Compiling : $<"
	@$(CXX) $(CXXFLAGS) -c $< -o $@ -I$(INCLUDES_FOLDER)

$(NAME): $(OBJECTS)
	@echo "Create    : $(NAME)"
	@$(CXX) $(CXXFLAGS) $(OBJECTS) -o $(NAME)

all: $(NAME)

-include $(DEPENDENCIES)

clean:
	@rm -rf $(OBJECTS_FOLDER)

fclean: clean
	@rm -rf $(NAME)

re: fclean all

docker:
	@LOGNAME=`date +%Y%m%d%H%M%S` && ./docker_start.sh $${LOGNAME} && echo "log: "./make_log/$${LOGNAME}

log_clean:
	rm -rf ./make_log

.PHONY : all clean fclean re docker
