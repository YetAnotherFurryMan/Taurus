BUILD ?= build

src :=  $(wildcard trsap/src/*) $(wildcard trscli/src/*) $(wildcard trsre/src/*) $(wildcard trsre/ext/*) $(wildcard trsrec/src/*) $(wildcard testware/trsre_match_char/*.c testware/trsre_match_char/*.cpp) $(wildcard testware/trsre_match_group/*.c testware/trsre_match_group/*.cpp) $(wildcard testware/trsre_get_token/*.c testware/trsre_get_token/*.cpp)
obj := $(patsubst %,$(BUILD)/%.o,$(subst /ext/,-ext.dir/,$(subst /src/,.dir/,$(src)))) $(patsubst %,$(BUILD)/%.o,$(subst /trsre_match_char/,/trsre_match_char.dir/,$(filter testware/%,$(src)))) $(patsubst %,$(BUILD)/%.o,$(subst /trsre_match_group/,/trsre_match_group.dir/,$(filter testware/%,$(src)))) $(patsubst %,$(BUILD)/%.o,$(subst /trsre_get_token/,/trsre_get_token.dir/,$(filter testware/%,$(src))))

.PHONY: all
all: dirs  $(BUILD)/libtrsap.a $(BUILD)/libtrscli.a $(BUILD)/libtrsre.a $(BUILD)/libtrsre-ext.a $(BUILD)/trsrec $(BUILD)/testware/trsre_match_char $(BUILD)/testware/trsre_match_group $(BUILD)/testware/trsre_get_token

dirs: $(BUILD) $(BUILD)/trsap.dir $(BUILD)/trscli.dir $(BUILD)/trsre-ext.dir $(BUILD)/trsre.dir $(BUILD)/trsrec.dir $(BUILD)/testware $(BUILD)/testware/trsre_match_char.dir $(BUILD)/testware/trsre_match_group.dir $(BUILD)/testware/trsre_get_token.dir
$(BUILD) $(BUILD)/trsap.dir $(BUILD)/trscli.dir $(BUILD)/trsre-ext.dir $(BUILD)/trsre.dir $(BUILD)/trsrec.dir $(BUILD)/testware $(BUILD)/testware/trsre_match_char.dir $(BUILD)/testware/trsre_match_group.dir $(BUILD)/testware/trsre_get_token.dir:
	@mkdir $@

clean:
	$(RM) -r $(BUILD)

$(filter build/trsap.dir/%.c.o, $(obj)):build/trsap.dir/%.o:trsap/src/%
	@echo Building object $@
	@$(CC) -Wall -Wextra -Wpedantic -Itrsap/headers -o $@ -c $^

$(filter build/trsap.dir/%.cpp.o, $(obj)):build/trsap.dir/%,o:trsap/src/%
	@echo Building object $@
	@$(CXX) -Wall -Wextra -Wpedantic -Itrsap/headers -o $@ -c $^

build/libtrsap.a: $(filter build/trsap.dir/%, $(obj))
	@echo Building library $@
	@$(AR) qc $@ $^

$(filter build/trscli.dir/%.c.o, $(obj)):build/trscli.dir/%.o:trscli/src/%
	@echo Building object $@
	@$(CC) -Wall -Wextra -Wpedantic -Itrscli/headers -o $@ -c $^

$(filter build/trscli.dir/%.cpp.o, $(obj)):build/trscli.dir/%,o:trscli/src/%
	@echo Building object $@
	@$(CXX) -Wall -Wextra -Wpedantic -Itrscli/headers -o $@ -c $^

build/libtrscli.a: $(filter build/trscli.dir/%, $(obj))
	@echo Building library $@
	@$(AR) qc $@ $^

$(filter build/trsre.dir/%.c.o, $(obj)):build/trsre.dir/%.o:trsre/src/%
	@echo Building object $@
	@$(CC) -Wall -Wextra -Wpedantic -Itrsre/headers -o $@ -c $^

$(filter build/trsre.dir/%.cpp.o, $(obj)):build/trsre.dir/%,o:trsre/src/%
	@echo Building object $@
	@$(CXX) -Wall -Wextra -Wpedantic -Itrsre/headers -o $@ -c $^

build/libtrsre.a: $(filter build/trsre.dir/%, $(obj))
	@echo Building library $@
	@$(AR) qc $@ $^

$(filter build/trsre-ext.dir/%.c.o, $(obj)):build/trsre-ext.dir/%.o:trsre/ext/%
	@echo Building object $@
	@$(CC) -Wall -Wextra -Wpedantic -Itrsre/headers -o $@ -c $^

$(filter build/trsre-ext.dir/%.cpp.o, $(obj)):build/trsre-ext.dir/%,o:trsre/ext/%
	@echo Building object $@
	@$(CXX) -Wall -Wextra -Wpedantic -Itrsre/headers -o $@ -c $^

build/libtrsre-ext.a: $(filter build/trsre-ext.dir/%, $(obj))
	@echo Building library $@
	@$(AR) qc $@ $^

$(filter $(BUILD)/trsrec.dir/%.c.o, $(obj)):$(BUILD)/trsrec.dir/%.o:trsrec/src/%
	@echo Building object $@
	@$(CC) -Wall -Wextra -Wpedantic -Itrsrec/headers -Itrsap/headers -Itrscli/headers -Itrsre/headers -Itrsre-ext/headers -o $@ -c $^

$(filter $(BUILD)/trsrec.dir/%.cpp.o, $(obj)):$(BUILD)/trsrec.dir/%.o:trsrec/src/%
	@echo Building object $@
	@$(CXX) -Wall -Wextra -Wpedantic -Itrsrec/headers -Itrsap/headers -Itrscli/headers -Itrsre/headers -Itrsre-ext/headers -o $@ -c $^

$(BUILD)/trsrec: $(filter $(BUILD)/trsrec.dir/%, $(obj)) $(BUILD)/libtrsap.a $(BUILD)/libtrscli.a $(BUILD)/libtrsre.a $(BUILD)/libtrsre-ext.a
	@echo Building executable $@
	@$(CXX) -o $@ $^

$(filter $(BUILD)/testware/trsre_match_char.dir/%.c.o, $(obj)):$(BUILD)/testware/trsre_match_char.dir/%.o:testware/trsre_match_char/%
	@echo Building object $@
	@$(CC) -Wall -Wextra -Wpedantic -Itrsre/headers -o $@ -c $^

$(filter $(BUILD)/testware/trsre_match_char.dir/%.cpp.o, $(obj)):$(BUILD)/trsre_match_char.dir/%.o:trsre_match_char/%
	@echo Building object $@
	@$(CXX) -Wall -Wextra -Wpedantic -Itrsre/headers -o $@ -c $^

$(BUILD)/testware/trsre_match_char: $(filter $(BUILD)/testware/trsre_match_char.dir/%, $(obj)) $(BUILD)/libtrsre.a
	@echo Building executable $@
	@$(CXX) -o $@ $^

$(filter $(BUILD)/testware/trsre_match_group.dir/%.c.o, $(obj)):$(BUILD)/testware/trsre_match_group.dir/%.o:testware/trsre_match_group/%
	@echo Building object $@
	@$(CC) -Wall -Wextra -Wpedantic -Itrsre/headers -o $@ -c $^

$(filter $(BUILD)/testware/trsre_match_group.dir/%.cpp.o, $(obj)):$(BUILD)/trsre_match_group.dir/%.o:trsre_match_group/%
	@echo Building object $@
	@$(CXX) -Wall -Wextra -Wpedantic -Itrsre/headers -o $@ -c $^

$(BUILD)/testware/trsre_match_group: $(filter $(BUILD)/testware/trsre_match_group.dir/%, $(obj)) $(BUILD)/libtrsre.a
	@echo Building executable $@
	@$(CXX) -o $@ $^

$(filter $(BUILD)/testware/trsre_get_token.dir/%.c.o, $(obj)):$(BUILD)/testware/trsre_get_token.dir/%.o:testware/trsre_get_token/%
	@echo Building object $@
	@$(CC) -Wall -Wextra -Wpedantic -Itrsre/headers -Itrsre-ext/headers -o $@ -c $^

$(filter $(BUILD)/testware/trsre_get_token.dir/%.cpp.o, $(obj)):$(BUILD)/trsre_get_token.dir/%.o:trsre_get_token/%
	@echo Building object $@
	@$(CXX) -Wall -Wextra -Wpedantic -Itrsre/headers -Itrsre-ext/headers -o $@ -c $^

$(BUILD)/testware/trsre_get_token: $(filter $(BUILD)/testware/trsre_get_token.dir/%, $(obj)) $(BUILD)/libtrsre.a $(BUILD)/libtrsre-ext.a
	@echo Building executable $@
	@$(CXX) -o $@ $^

