SRCS=Serializable.ixx\
	LinkedList.ixx\
	Tree.ixx

OBJS=$(SRCS:.ixx=.o)

name=libcedilla.a

all: $(name)

%.o: %.ixx
	clang++ -fmodules-ts --std=c++20 -I./ -c $< -o $@

$(name): $(OBJS)
	ar -rcs $(OBJS) $@

clean:
	rm $(OBJS)

fclean: clean
	rm $(name)

re: fclean all

.PHONY: clean fclean
