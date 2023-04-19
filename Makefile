GPP = g++
SFML_VERSION=2.5.1

SFML_LIB=/usr/local/lib/SFML-$(SFML_VERSION)/lib
SFML_HEADERS=/usr/local/lib/SFML-$(SFML_VERSION)/include

FLAGS = -std=c++17 -Wall -L$(SFML_LIB) -I$(SFML_HEADERS)
LIBS= -lsfml-graphics -lsfml-window -lsfml-system

BIN = editor
TEST_BIN = tests

BUILD_DIR = ./build

APP_CPP = TextEditor.cpp $(wildcard src/*.cpp)
TEST_CPP = $(wildcard tests/*.cpp)

OBJ = $(APP_CPP:%.cpp=$(BUILD_DIR)/%.o)
TEST_OBJ = $(TEST_CPP:%.cpp=$(BUILD_DIR)/%.o)
DEP = $(OBJ:%.o=%.d) $(TEST_OBJ:%.o=%.d)

$(BIN) : $(BUILD_DIR)/$(BIN)

$(BUILD_DIR)/$(BIN) : $(OBJ)
	@mkdir -p $(@D)
	$(GPP) $(FLAGS) $^ -o $@ $(LIBS)
	@mv $(BUILD_DIR)/$(BIN) $(BIN)

$(TEST_BIN) : $(BUILD_DIR)/$(TEST_BIN)

$(BUILD_DIR)/$(TEST_BIN) : $(TEST_OBJ)
	@mkdir -p $(@D)
	$(GPP) $(FLAGS) $^ -o $@ $(LIBS)
	@mv $(BUILD_DIR)/$(TEST_BIN) $(TEST_BIN)

-include $(DEP)

$(BUILD_DIR)/%.o : %.cpp
	@mkdir -p $(@D)
	$(GPP) $(FLAGS) -MMD -c $< -I src/ -o $@

.PHONY : clean
clean :
	-rm -f $(BUILD_DIR)/$(BIN) $(BUILD_DIR)/$(TEST_BIN) $(OBJ) $(TEST_OBJ) $(DEP)
	rm -f editor tests
	rmdir build/src build/tests build
