################################################################
TARGET			:= prog
SRC_DIR			:= src
INC_DIR			:= inc
BUILD_DIR		:= build
TARGET_DIR		:= $(BUILD_DIR)/bin

CXX             := g++
CXXFLAGS        := -std=c++11 -Wall
LDFLAGS         := -lglfw3 -lGL -lX11 -lpthread -lXrandr -lXi -ldl

SRCS			:= $(shell find $(SRC_DIR) -name *.cpp -or -name *.c)
OBJS			:= $(addprefix $(BUILD_DIR)/, $(notdir $(SRCS:%=%.o)))
DEPS			:= $(OBJS:.o=.d)

################################################################
.PHONY: all clean

all: $(TARGET_DIR)/$(TARGET)

$(TARGET_DIR)/$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

$(BUILD_DIR)/%.c.o: $(SRC_DIR)/%.c
	$(CC) -I $(INC_DIR) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/%.cpp.o: $(SRC_DIR)/%.cpp
	$(CXX) -I $(INC_DIR) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR)
	@mkdir -p $(TARGET_DIR)
