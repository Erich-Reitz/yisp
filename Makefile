CXX := g++-12
CXXFLAGS := -pedantic -Wall -Wextra -Wcast-align -Wcast-qual -Wctor-dtor-privacy -Wdisabled-optimization -Wformat=2 -Winit-self -Wlogical-op -Wmissing-declarations -Wmissing-include-dirs -Wold-style-cast -Woverloaded-virtual -Wredundant-decls -Wshadow -Wsign-conversion -Wsign-promo -Wstrict-null-sentinel -Wstrict-overflow=5 -Wswitch-default -Wundef -Werror -Wno-unused -g --std=c++23


SRC_DIR := ./src
TEST_DIR := ./tests
OBJ_DIR := ./obj

SRC_FILES := $(shell find $(SRC_DIR) -type f -name "*.cpp")
SRC_HEADERS := $(shell find $(SRC_DIR)  -type f -name "*.h" -o -name "*.hpp")

OBJ_FILES := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRC_FILES))


TEST_OBJ_FILES := $(filter-out $(OBJ_DIR)/main.o, $(OBJ_FILES))

TEST_FILES := $(wildcard $(TEST_DIR)/*.cpp)
TEST_HEADERS := $(wildcard $(TEST_DIR)/*.h) $(wildcard $(TEST_DIR)/*.hpp)

DEP_FILES := $(OBJ_FILES:.o=.d)
PROGRAM_NAME := yisp
TEST_PROGRAM_NAME := test_yisp

.PHONY: clean format run test


$(PROGRAM_NAME): $(OBJ_FILES)
	$(CXX) $(CXXFLAGS) $(OBJ_FILES) $(LDFLAGS) -o $@

-include $(DEP_FILES)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(@D)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -MMD -c $< -o $@

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

test: $(PROGRAM_NAME) $(TEST_OBJ_FILES) $(TEST_FILES) 
	$(CXX) $(CXXFLAGS) $(TEST_OBJ_FILES) $(TEST_FILES) -o $(TEST_PROGRAM_NAME)
	./$(TEST_PROGRAM_NAME)


clean:
	rm -r $(PROGRAM_NAME) $(TEST_PROGRAM_NAME) $(OBJ_DIR)

format:
	astyle --style=google --mode=c --attach-return-type --align-pointer=name --indent=spaces=2 --max-code-length=140 --break-after-logical --suffix=none $(SRC_FILES) $(TEST_FILES) $(SRC_HEADERS) $(M_STD_HEADERS) $(TEST_HEADERS)

run: $(PROGRAM_NAME)
	./$(PROGRAM_NAME)
