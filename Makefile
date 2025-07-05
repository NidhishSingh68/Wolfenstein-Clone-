CC := g++
TARGET_EXEC := Raycaster
BUILD_DIR := ./build
SRCS := $(shell find . -type f -name '*.cpp')
INC_DIR := /usr/include .
INC_FLAGS := $(addprefix -I,$(INC_DIR))
LD_LIB := SDL3 SDL3_ttf
LD_FLAGS := $(addprefix -l,$(LD_LIB))
OBJS := $(patsubst %.cpp, $(BUILD_DIR)/%.o,$(SRCS))


all : $(BUILD_DIR)/$(TARGET_EXEC)


$(BUILD_DIR)/%.o : %.cpp 
	mkdir -p build
	$(CC) -c -g -std=c++20 $< -o $@
	echo $<

$(BUILD_DIR)/$(TARGET_EXEC):$(OBJS)
	$(CC) $(LD_FLAGS) $(OBJS) -o $@

.phony: clean

log:
	echo $(OBJS)
	echo $(SRCS)
	echo $(INC_FLAGS)
clean: 
	rm -r build

