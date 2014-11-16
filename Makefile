CC=gcc
SHELL:=$(shell which bash) -e -o pipefail
UNAME_S:=$(shell uname -s)
_CFLAGS=-Wall -Wextra -Werror -Wshadow -Winline -D_GNU_SOURCE -std=c99 -g

BIN_DIR=$(CURDIR)/bin
SRC_DIR=$(CURDIR)/src
DATA_DIR=$(CURDIR)/etc/data
SCRIPT_DIR=$(CURDIR)/scripts
SERVER_DIR=$(SRC_DIR)/server
CLIENT_DIR=$(SRC_DIR)/client
SENDER_DIR=$(SRC_DIR)/sender
LIB_DIR=$(SRC_DIR)/lib

# All header files in libraries
INCLUDES_SERVER=-I$(SRC_DIR) -I$(CURDIR) \
	        -I$(CURDIR)/deps/uthash \
	        -I$(SERVER_DIR) \
	        -I$(LIB_DIR) \
	        -lpthread \
            -lpcap \

INCLUDES_SENDER=-I$(SRC_DIR) -I$(CURDIR) \
	        -I$(CURDIR)/deps/uthash \
	        -I$(SENDER_DIR) \
	        -I$(LIB_DIR) \
	        -lpthread \
            -lpcap \


# All .c files in src folder
_SOURCES=$(shell find $(SRC_DIR) -type f -iname '*.[c]')
_SOURCES_SERVER=$(shell find $(SERVER_DIR) -type f -iname '*.[c]')
_SOURCES_SENDER=$(shell find $(SENDER_DIR) -type f -iname '*.[c]')
_SOURCES_LIB=$(shell find $(LIB_DIR) -type f -iname '*.[c]')

# Create 1GB file
create:
	@echo "Run some script :"
	$(SCRIPT_DIR)/test.sh

# Build
build_server:
	    -mkdir -p $(BIN_DIR)
	    $(CC) -o $(BIN_DIR)/server $(_SOURCES_LIB) $(_SOURCES_SERVER) $(INCLUDES_SERVER) -g

build_sender:
	    -mkdir -p $(BIN_DIR)
	    $(CC) -o $(BIN_DIR)/sender $(_SOURCES_LIB) $(_SOURCES_SENDER) $(INCLUDES_SENDER)

clean:
	@echo "Deleting bin folder"
	rm -rf $(BIN_DIR)/*
