include make_rules/config.mk

# Output of the program
OUTPUT		:= libreactor.so

# All CPP files to compile
CPP_SRC += $(SRC)/EventService.cpp
CPP_SRC += $(SRC)/Reactor.cpp

# Compile OBJ files (.o) to a build directory
CPP_OBJ		:= $(addprefix $(BLD_DIR), $(subst $(PRJ_DIR), ,$(CPP_SRC:.cpp=.o)))

# All h files. The so needs it for installation
CPP_H		+= $(SRC)/EventService.h
CPP_H		+= $(SRC)/Reactor.h
CPP_H		+= $(SRC)/event_message_types.h

# Directories on where to include header files
INC_DIR		+= $(SRC)
INC_DIR		+= /usr/include
INC_DIR		+= /usr/local/include

# Dependency files
DEP			:= $(CPP_OBJ:.o=.d)

# The directory to look for the libraries
LIBS_DIR	+= /usr/lib/
LIBS_DIR	+= /usr/lib/x86_64-linux-gnu/
LIBS_DIR	+= /usr/local/lib/

# The library to link
LIBS		+= zmq
LIBS		+= spdlog
LIBS		+= pthread

# Defines
#DEFINES 	+= DEBUG_OUTPUT
DEFINES		+= ENABLE_ROUTER_ERROR

# Where to install the library to. Can be overriden
INSTALL_SO_DIR	?= /usr/local/lib

# Where to put the header files
INSTALL_H_DIR	?= /usr/local/include

all: $(OUTPUT)

$(OUTPUT): $(CPP_OBJ)
	@$(ECHO)
	@$(ECHO) Compiling all object files...
	@$(ECHO) Linking....
	$(VERBOSE)$(CXX) -shared $(CPPFLAGS) $(CXXFLAGS) $(INC) -o $@ $(CPP_OBJ) $(LIBSPATHS) $(LDLIBS)

$(CPP_OBJ):
	$(VERBOSE)$(MKDIR) -p '$(@D)'
	$(eval CPP_FILE := $(addprefix $(PRJ_DIR), $(subst $(BLD_DIR), ,$(subst .o,.cpp,$@))))
	@$(ECHO) 'Compiling $(CPP_FILE)'
	$(VERBOSE)$(CXX) -fPIC $(CPPFLAGS) $(CXXFLAGS) $(INC) -c $(CPP_FILE) -o $@

# Target for copying the header files
.PHONY: $(CPP_H)
$(CPP_H): pre-install
	@$(ECHO) Copying $@ to $(INSTALL_H_DIR)/$(PRJ_NAME)/$(notdir $@)
	$(VERBOSE)$(CP) $@ $(INSTALL_H_DIR)/$(PRJ_NAME)/$(notdir $@)

# Target for anything that should be done before the library actuall installs
.PHONY: pre-install
pre-install:
	@$(ECHO) Installing libreactor
	$(VERBOSE)$(MKDIR) -p $(INSTALL_SO_DIR)
	$(VERBOSE)$(MKDIR) -p $(INSTALL_H_DIR)/$(PRJ_NAME)/

# Target to install the so library only
.PHONY: install-so
install-so: pre-install
	@$(ECHO) Copying library
	$(VERBOSE)$(CP) $(OUTPUT) $(INSTALL_SO_DIR)/$(OUTPUT)

# Target to clean the project for development
.PHONY: clean-development
clean-development: clean
	$(VERBOSE)$(RM) -rf $(OUTPUT)
	@$(ECHO) Project cleaned

# Cleans just the build directory but leaves the output
.PHONY: clean
clean:
	$(VERBOSE)$(RM) -rf $(subst $(PRJ_DIR)/,,$(BLD_DIR))
	
# Target to do a full installation which includes building and copying
.PHONY: install
install: pre-install $(OUTPUT) $(CPP_H) install-so
	@$(ECHO) Successfully built and installed library

# Target to just copy
.PHONY: install-only
install-only: $(CPP_H) install-so
	@$(ECHO) Successfully installed library

# Remove the installation files from the system
.PHONY: install-clean
install-clean:
	$(VERBOSE)$(RM) -rf $(INSTALL_SO_DIR)/$(OUTPUT)
	$(VERBOSE)$(RM) -rf $(INSTALL_H_DIR)/$(PRJ_NAME)

# Completley remove the installation
.PHONY: remove-installation
remove-installation: install-clean
	@$(ECHO) Successfully removed installation

# Do a full installation from front to back
.PHONY: full-installation
full-installation: remove-installation clean $(OUTPUT) $(CPP_H) install-so clean
	@$(ECHO) Successfully fully installed library
	

# Include the dependencies. Since the dependency files won't exist at first the -include supresses the warnings
-include $(DEP)

	
include make_rules/debug_rules.mk