REGEX_OBJS= $(mario_OBJS) $(mario_js_OBJS) \
	$(REGEX)/native_regex.o 

CXXFLAGS += -std=c++11

$(REGEX_TARGET): $(REGEX_OBJS)
	$(LD) -shared -o $(REGEX_TARGET) $(REGEX_OBJS) $(LDFLAGS)

CLEAN += $(REGEX_TARGET) $(REGEX_OBJS)
