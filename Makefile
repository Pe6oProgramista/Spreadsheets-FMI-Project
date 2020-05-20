# functions
rec_wildcard = $(wildcard $1$2) $(foreach d,$(filter-out $1,$(sort $(dir $(wildcard $1*/)))),$(call $0,$d,$2))

#-----------------------------------------
OSFLAG:=
ifeq ($(OS),Windows_NT)
	OSFLAG=WIN
else
	UNAME_S := $(shell uname -s)
	ifeq ($(UNAME_S),Linux)
		OSFLAG=LINUX
	endif
	ifeq ($(UNAME_S),Darwin)
		OSFLAG=OSX
	endif
endif


CC = g++
CFLAGS = -g -Wall

BIN_DIR = bin
INCLUDE_DIR = include
SRC_DIR = src
TEST_DIR = tests
OBJ_DIR = build

INC = $(INCLUDE_DIR:%=-I%)

SRCS = $(call rec_wildcard,$(SRC_DIR)/,*.cpp)
OBJS = $(SRCS:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)

SUBDIRS = $(patsubst $(SRC_DIR)/%/.,%,$(call rec_wildcard,$(SRC_DIR)/,*/.))

TESTS = $(call rec_wildcard, $(TEST_DIR)/,*.cpp)

build_test: build | mk_bin_dir
ifeq ($(name),)
	$(info ERROR: Input test name: "make build_test name=test(.cpp)")
else
	$(eval NAME=$(subst .cpp,,$(name)))
	$(eval FULL_NAME=$(NAME).cpp)
	
	$(eval TEST_PATH=$(sort $(filter %$(FULL_NAME),$(TESTS))))

	$(CC) $(CFLAGS) $(INC) $(OBJS) $(TEST_PATH) -o $(BIN_DIR)/$(NAME).exe
endif

build: $(OBJS)

$(OBJS): $(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp $(INCLUDE_DIR)/%.hpp | mk_build_dirs
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

mk_build_dirs:
	$(foreach d, $(SUBDIRS), mkdir "$(OBJ_DIR)/$d" &)

mk_bin_dir:
	mkdir $(BIN_DIR)

clean_bin:
ifeq ($(OSFLAG),WIN)
	del /f /s "$(BIN_DIR)\*.exe"
else ifeq ($(OSFLAG),LINUX)
	rm -f -r "$(BIN_DIR)/*.exe"
endif

clean_build:
ifeq ($(OSFLAG),WIN)
	del /f /s "$(OBJ_DIR)\*.o"
else ifneq (,$(filter $(OSFLAG),LINUX OSX))
	rm -f -r "$(OBJ_DIR)/*.o"
endif

clean: clean_bin clean_build


os:
	$(info OS: $(OSFLAG))
	