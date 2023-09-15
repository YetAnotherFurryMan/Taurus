dir := bin test $(patsubst src/%,bin/%, $(wildcard src/*) $(wildcard src/test/*))

src := $(wildcard src/*/*.*)
obj := $(patsubst src/%,bin/%.o, $(src))

test_src := $(wildcard src/test/*/*.cpp)
test_obj := $(patsubst src/%,bin/%.o, $(test_src))
tests := $(patsubst src/%,%, $(wildcard src/test/*))

includes := headers
libs := 

.PHONY: all
all: clean $(dir) $(obj)
tests: all $(test_obj) $(tests)

clean:
	@echo Clean UP...
	@rm -fr bin
	@rm -fr test

$(dir):
	@mkdir $@

$(filter bin/%.c.o, $(obj)): bin/%.o: src/%
	@echo Compiling $^
	@$(CC) -c -o $@ $^ $(foreach x,$(includes), -I $(x))

$(filter bin/%.cpp.o, $(obj) $(test_obj)): bin/%.o: src/%
	@echo Compiling $^
	@$(CXX) -c -o $@ $^ $(foreach x,$(includes), -I $(x)) -std=c++2a

$(tests):
	@echo Creating $@
	@$(LINK.cpp) -o $@ $(patsubst %,bin/%/*.o,$@) $(patsubst test/%,bin/%/*.o, $@) $(foreach x, $(libs), -l$(x))