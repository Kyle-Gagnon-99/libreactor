include make_rules/config.mk

# Output of the program
OUTPUT		:= Examples.exe

# All CPP files to compile
CPP_SRC += $(SRC)/Main.cpp
CPP_SRC += $(SRC)/FullReactor.cpp

# Compile OBJ files (.o) to a build directory
CPP_OBJ		:= $(addprefix $(BLD_DIR), $(subst $(PRJ_DIR), ,$(CPP_SRC:.cpp=.o)))

# Directories on where to include header files
INC_DIR		+= $(SRC)
INC_DIR		+= /usr/include
INC_DIR		+= /usr/local/include

# Dependency files
DEP			:= $(CPP_OBJ:.o=.d)

# The directory to look for the libraries
LIBS_DIR	+= /usr/lib/
LIBS_DIR	+= /usr/lib/x86_64-linux-gnu/
LIBS_DIR	+= /usr/local/lib

# The library to link
LIBS		+= spdlog
LIBS		+= pthread
LIBS		+= reactor

# Custom defines
#DEFINES		+= DEBUG_ROUTER_RECV

# Whether or not to include a full installation of libreactor
INCLUDE_FULL_INSTALLATION	?= n

all: $(OUTPUT)

$(OUTPUT): $(CPP_OBJ)
ifeq ($(INCLUDE_FULL_INSTALLATION),y)
	$(VERBOSE)$(MAKE) -C ../ full-installation
endif
	@$(ECHO)
	@$(ECHO) Compiling all object files...
	@$(ECHO) Linking....
	$(VERBOSE)$(CXX) $(CPPFLAGS) $(CXXFLAGS) $(INC) $(CPP_OBJ) -o $@ $(LIBSPATHS) $(LDLIBS)

$(CPP_OBJ):
	$(VERBOSE)$(MKDIR) -p '$(@D)'
	$(eval CPP_FILE := $(addprefix $(PRJ_DIR), $(subst $(BLD_DIR), ,$(subst .o,.cpp,$@))))
	@$(ECHO) 'Compiling $(CPP_FILE)'
	$(VERBOSE)$(CXX) $(CPPFLAGS) $(CXXFLAGS) $(INC) -c $(CPP_FILE) -o $@
	
.PHONY: clean
clean:
	$(RM) -rf $(BLD_DIR)
	$(RM) -rf $(OUTPUT)
	

# Include the dependencies. Since the dependency files won't exist at first the -include supresses the warnings
-include $(DEP)

	
include make_rules/debug_rules.mk