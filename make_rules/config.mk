#############################
### General Config Rules
#############################

# Commands
ECHO		:= echo
MAKE		:= make
CAT			:= cat
RM			:= rm
MKDIR		:= mkdir
LS			:= ls
CP			:= cp
CD			:= cd
PWD			:= pwd
RENAME		:= rename
BASENAME	:= basename
CUT			:= cut

# Top Level Variables
CUR_DIR		:= $(shell $(PWD))
PRJ_DIR		?= $(CUR_DIR)
BLD_DIR		:= $(PRJ_DIR)/build_dir
SRC			:= $(PRJ_DIR)/src
PRJ_NAME	?= reactor

# This is empty because we can add actual defines in the Makefile
DEFINES 	+=

# Compiler
CXX			:= g++

# Compiler flags
CXXFLAGS	+= -Wall -Wextra -Wsign-conversion -g -MMD -MP

# Preprocessor Flags
CPPFLAGS	+=
CPPFLAGS 	+=	$(addprefix -D, $(DEFINES))

# Directories on where to include header files
INC_DIR		+=

# Append -I to each directory
INC			+= $(INC_DIR:%=-I%)

# LIBS_DIR is used to specify the directories of the libraries
LIBS_DIR	+=

# Take LIBS_DIR and add -L to each
LIBSPATHS	+= $(LIBS_DIR:%=-L%)

# The library to link
LIBS		+=

# Add -l to each library
LDLIBS		+= $(LIBS:%=-l%)