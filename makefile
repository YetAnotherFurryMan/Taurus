targets := t_core
cleans := $(patsubst t_%,c_%,$(targets)) c_test

.PHONY: all
all: $(targets)
tests: all 
	@$(MAKE) -C test

clean: $(cleans)

$(targets):
	@$(MAKE) -C $(patsubst t_%,%,$@)

$(cleans):
	@$(MAKE) -C $(patsubst c_%,%,$@) clean