bin := bin test $(patsubst src/%,bin/%, $(wildcard src/*))
src := $(wildcard src/*/*.*)
obj := $(patsubst src/%,bin/%.o, $(src))
tests := $(patsubst %.cpp.o,test/%, $(filter %.test.cpp.o, $(notdir $(obj))))

includes := headers
libs := 

.PHONY: all
all: clean $(bin) $(obj)
tests: clean $(bin) $(obj) $(tests)

clean:
	@echo Clean UP...
	@rm -fr bin
	@rm -fr test

$(bin): 
	@mkdir $@

$(filter bin/%.c.o, $(obj)): bin/%.o: src/%
	@echo Compiling $^
	@$(CC) -c -o $@ $^ $(foreach x,$(includes), -I $(x))

$(filter bin/%.cpp.o, $(obj)): bin/%.o: src/%
	@echo Compiling $^
	@$(CXX) -c -o $@ $^ $(foreach x,$(includes), -I $(x)) -std=c++2a

$(tests):
	@echo Creating $@
	@$(LINK.cpp) -o $@ $(filter bin/$(basename $(notdir $@))/%, $(obj)) $(foreach x, $(libs), -l$(x))