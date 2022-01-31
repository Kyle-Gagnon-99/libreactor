# Google Protocol Buffer
PROTOC					:= /usr/local/bin/protoc

PROTOC_FILES_OUTPUT		?= $(HOME)/reactorPrj/proto

PROTOC_INPUT_PREFIX 	?= $(PRJ_DIR)/protoc

PROTOC_FILE				?=

PROTOC_INPUT_FILE		?= $(PROTOC_INPUT_PREFIX)/$(PROTOC_FILE)
PROTOC_OUTPUT			?= $(PROTOC_FILES_OUTPUT)

#####################################################
### Protocol Target
###
### This target will use the google protocol buffer
### to generate a header and cpp file for the given
### data structure
###
### The protoc needs the file to generate the header
### from (the protoc file) and where to generate it
### to. They will both be variables so they can change
### if need be
#####################################################
.PHONY: protoc-generate
protoc-generate:
	$(VERBOSE)$(MKDIR) -p $(PROTOC_OUTPUT)
	$(VERBOSE)$(PROTOC) -I=$(PROTOC_INPUT_PREFIX) --cpp_out=$(PROTOC_OUTPUT) --java_out=$(PROTOC_OUTPUT) --python_out=$(PROTOC_OUTPUT) $(PROTOC_INPUT_FILE)
#	$(VERBOSE)$(RM) $(PROTOC_OUTPUT)/$(PROTOC_INPUT_FILE).*
	$(VERBOSE)$(RENAME) 's/.pb.cc/.cpp/' $(PROTOC_OUTPUT)/*
	$(VERBOSE)$(RENAME) 's/.pb.h/.h/' $(PROTOC_OUTPUT)/*
	$(VERBOSE)$(RENAME) 's/_pb2.py/.py/' $(PROTOC_OUTPUT)/*

.PHONY: help-protoc
help-protoc:
	@$(ECHO) Protocol Buffer Help Page
	@$(ECHO)
	@$(ECHO) To generate a file you must define PROTOC_INPUT_FILE
