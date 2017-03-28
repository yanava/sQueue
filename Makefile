################################################################################
# Makefile for sQueue
#
# 22/03/2017 - 1st version
################################################################################

# Variable definitions
PROJ_NAME:=sQueue
FULL_NAME:= $(PROJ_NAME)
RM:= rm -rf
MKDIR:= mkdir -p 
CC:= gcc
SRC_DIR:= src
OUT_DIR:= output
TEST_DIR:= test
UNITY_DIR:= unity
CFLAGS = -Wall -I$(UNITY_DIR) -I$(SRC_DIR)
LDLIBS =
LDFLAGS =

# Source objects for both Test build and Release build
SRC_OBJS  = $(addprefix $(OUT_DIR)/$(SRC_DIR)/, squeue.o	 )

# Source dependencies
SRC_DEPS  = $(addprefix $(SRC_DIR)/, squeue.h	   )

# Test objects
TEST_OBJS  = $(addprefix $(OUT_DIR)/$(TEST_DIR)/, squeue_test.o 	)

# Unity objects
UNITY_OBJS = $(addprefix $(OUT_DIR)/$(UNITY_DIR)/, unity.o) 
UNITY_OBJS += $(addprefix $(OUT_DIR)/$(UNITY_DIR)/, unity_fixture.o) 

# All - Builds release and testing
all : test

# Test build
test : $(OUT_DIR)/$(FULL_NAME)_test

# Builds test binary
$(OUT_DIR)/$(FULL_NAME)_test : $(OUT_DIR)/$(TEST_DIR)/main_test.o $(SRC_OBJS) $(TEST_OBJS) $(UNITY_OBJS)
	@echo 	Building target: $(FULL_NAME)-test
	@$(CC) -o $@ $^ $(CFLAGS) $(LDLIBS) $(LDFLAGS)
	@echo 	Done building $(PROJ_NAME) Testing
	
# Compile all source objects, except main.o
$(OUT_DIR)/$(SRC_DIR)/%.o : $(SRC_DIR)/%.c  $(SRC_DEPS) | $(OUT_DIR)/$(SRC_DIR)
	@echo 	[CC] $<
	@$(CC) -c $< -o $@ $(CFLAGS)
	
# Compile all test objects, except main_test.o
$(OUT_DIR)/$(TEST_DIR)/%.o : $(TEST_DIR)/%.c  $(SRC_DEPS) | $(OUT_DIR)/$(TEST_DIR)
	@echo 	[CC] $<
	@$(CC) -c $< -o $@ $(CFLAGS)
	
# Compile all Unity objects
$(OUT_DIR)/$(UNITY_DIR)/%.o : $(UNITY_DIR)/%.c  $(SRC_DEPS) | $(OUT_DIR)/$(UNITY_DIR)
	@echo 	[CC] $<
	@$(CC) -c $< -o $@ $(CFLAGS)

# Creates output directory for SRC Objects
# We don't use mkdir -p because Windows has some weird issues with it
$(OUT_DIR)/$(SRC_DIR) : $(OUT_DIR)
	@echo 	Creating output directory: $@
	@cd $(OUT_DIR) && $(MKDIR) $(SRC_DIR)

# Creates output directory for TEST Objects
# We don't use mkdir -p because Windows has some weird issues with it
$(OUT_DIR)/$(TEST_DIR) : $(OUT_DIR)
	@echo 	Creating output directory: $@
	@cd $(OUT_DIR) && $(MKDIR) $(TEST_DIR)

# Creates output directory for UNITY Objects
# We don't use mkdir -p because Windows has some weird issues with it
$(OUT_DIR)/$(UNITY_DIR) : $(OUT_DIR)
	@echo 	Creating output directory: $@
	@cd $(OUT_DIR) && $(MKDIR) $(UNITY_DIR)
	
# Action for output directory, creates the output directory
# We don't use mkdir -p because Windows has some weird issues with it
$(OUT_DIR):
	@echo 	Creating output directory: $@
	@$(MKDIR) $(OUT_DIR)

# Cleans the output directory
clean: 
	@echo 	Deleting output directory
	@$(RM) $(OUT_DIR)
	@echo 	Done cleaning the project	
