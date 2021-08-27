CC := c++
SRC_DIR := src
APP_NAME := wallman
MAIN_SRC := $(SRC_DIR)/mainwindow.cpp
ROOT_SRC := $(SRC_DIR)/rootwindow.cpp
OUTPUT_DEST := build
GTK3LIBS := $(shell pkg-config --cflags --libs gtkmm-3.0)
GTK4LIBS := $(shell pkg-config --cflags --libs gtkmm-4.0)
WEBKITLIBS := $(shell pkg-config --cflags --libs webkit2gtk-4.0)
GSTLIBS := $(shell pkg-config --cflags --libs gstreamer-1.0)
CCFLAGS := -Wall
MAIN_BIN := wallman
ROOT_BIN := wallman_desktop
PREFIX := /usr/share/wallman
DESKTOP_DIR := config/desktop
DESKTOP_DEST := /usr/share/applications
GUI_DIR := config/gui
GUI_DEST := $(PREFIX)/wallman/config/gui
BIN_DEST := $(PREFIX)/wallman/bin
BIN_DIR := /usr/bin

build:
	mkdir $(OUTPUT_DEST)
	c++ $(CCFLAGS) $(GTK4LIBS) $(GSTLIBS) $(MAIN_SRC) -o $(OUTPUT_DEST)/$(MAIN_BIN)
	c++ $(CCFLAGS) $(GTK3LIBS) $(WEBKITLIBS) $(ROOT_SRC) -o $(OUTPUT_DEST)/$(ROOT_BIN)

clean:
	rm -r $(OUTPUT_DEST)

run:
	$(MAIN_BIN)

install:
	mkdir -p $(GUI_DEST)
	mkdir -p $(BIN_DEST)
	mkdir -p $(DESKTOP_DEST)
	mkdir -p $(BIN_DIR)
	cp -Tr $(DESKTOP_DIR) $(DESKTOP_DEST)
	cp -Tr $(GUI_DIR) $(GUI_DEST)
	cp $(OUTPUT_DEST)/$(MAIN_BIN) $(BIN_DEST)/$(MAIN_BIN)
	cp $(OUTPUT_DEST)/$(ROOT_BIN) $(BIN_DEST)/$(ROOT_BIN)
	chmod g+rx $(OUTPUT_DEST)/$(MAIN_BIN)
	chmod g+rx $(OUTPUT_DEST)/$(ROOT_BIN)
	chmod g+rx $(DESKTOP_DEST)/$(APP_NAME).desktop
	ln -sf $(BIN_DEST)/$(MAIN_BIN) $(BIN_DIR)/$(MAIN_BIN)
	

uninstall:
	rm -r $(BIN_DEST)
	rm -r $(GUI_DEST)
	rm $(DESKTOP_DEST)/$(APP_NAME).desktop