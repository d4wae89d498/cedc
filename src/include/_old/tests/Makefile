TESTS =	Ast.cpp \
		LinkedList.cpp

EXECS = $(TESTS:.cpp=)

DEPS = $(wildcard ./../src/*.hpp)

all: $(EXECS)

$(EXECS): %: %.cpp $(DEPS)
	clang++ -O0 -g --std=c++2b $< -o $@

test: $(EXECS)
	@for exec in $(EXECS); do \
		./$$exec; \
		rc=$$?; \
		if [ $$rc -eq 0 ]; then \
			echo "$$exec : SUCCESS"; \
		else \
			echo "$$exec : FAILURE"; \
		fi; \
	done


clean:
	rm -f $(EXECS)
