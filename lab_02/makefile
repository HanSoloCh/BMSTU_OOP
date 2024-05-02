CC := g++
CPPFLAGS := -std=c++20
LINKFLAGS :=
DEBUGFLAGS := -g3 --coverage
INC_DIRS := inc imp tests
INC_DIRS := $(INC_DIRS:%=-I%)
SRC_DIR := src
OUT_DIR := out
SRCS := $(wildcard $(SRC_DIR)/*.cpp)
OBJS := $(SRCS:$(SRC_DIR)/%.cpp=$(OUT_DIR)/%.o)
DEPENDS := $(SRCS:$(SRC_DIR)/%.cpp=$(OUT_DIR)/%.d)

_MAKE_OUT_DIR_ := $(shell mkdir -p $(OUT_DIR))

.PHONY: run clean

app.exe: $(OBJS)
	$(CC) $^ -o $@ $(LINKFLAGS)

run: app.exe
	./app.exe

$(OUT_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CC) $(CPPFLAGS) $(INC_DIRS) -MMD -o $@ -c $<

-include $(DEPENDS)

clean:
	rm -f $(OUT_DIR)/* *.exe *.lastbuildstate
