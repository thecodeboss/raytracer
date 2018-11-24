#
# Compiler Settings
#
CXX       := g++
CXXFLAGS  := -pedantic-errors -Wall -Wextra -Werror -std=c++17
LDFLAGS   := -L/usr/lib -lstdc++ -lm

#
# Project files
#
SRCS    := $(shell find src/ -type f -name '*.cpp')
OBJS    := $(SRCS:%.cpp=%.o)
INCLUDE := -Iinclude/
TARGET  := raytracer

#
# Debug Settings
#
DEBUG_DIR    := build/debug
DEBUG_TARGET := $(DEBUG_DIR)/apps/$(TARGET)
DEBUG_OBJS   := $(addprefix $(DEBUG_DIR)/objects/, $(OBJS))
DEBUG_FLAGS  := -g -O0 -DDEBUG

#
# Release Settings
#
RELEASE_DIR    := build/release
RELEASE_TARGET := $(RELEASE_DIR)/apps/$(TARGET)
RELEASE_OBJS   := $(addprefix $(RELEASE_DIR)/objects/, $(OBJS))
RELEASE_FLAGS  := -O3 -DNDEBUG

.PHONY: all clean debug release

# Default Build
all: release

#
# Debug Rules
#
debug: $(DEBUG_TARGET)

$(DEBUG_DIR)/objects/%.o: %.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(DEBUG_FLAGS) $(INCLUDE) -o $@ -c $<

$(DEBUG_TARGET): $(DEBUG_OBJS)
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(DEBUG_FLAGS) $(INCLUDE) $(LDFLAGS) -o $(DEBUG_TARGET) $^

#
# Release Rules
#
release: $(RELEASE_TARGET)

$(RELEASE_DIR)/objects/%.o: %.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(RELEASE_FLAGS) $(INCLUDE) -o $@ -c $<

$(RELEASE_TARGET): $(RELEASE_OBJS)
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(RELEASE_FLAGS) $(INCLUDE) $(LDFLAGS) -o $(RELEASE_TARGET) $^

#
# Other rules
#
clean:
	rm -rf $(RELEASE_TARGET) $(RELEASE_OBJS) $(DEBUG_TARGET) $(DEBUG_OBJS)
