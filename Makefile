WFLAGS := -Wall
INPUTDIR := src
GUIINPUTFILE := mainwindow.cpp
DESKTOPINPUTFILE := rootwindow.cpp
OUTPUTDIR := build
GUIOUTPUTFILE := Wallman
DESKTOPOUTPUTFILE := Wallman-Desktop
GTK3LIBS := $(shell pkg-config --cflags --libs gtkmm-3.0)
GTK4LIBS := $(shell pkg-config --cflags --libs gtkmm-4.0)
WEBKITLIBS := $(shell pkg-config --cflags --libs webkit2gtk-4.0)
GSTLIBS := $(shell pkg-config --cflags --libs gstreamer-1.0)
CCFLAGS := $(WFLAGS)
GTKBFLAGS := simplify --3to4
GTK3GLADE := main.glade
GTK4GLADE := window.glade
DESKTOP_FILE_LOCATION := src/.desktop
DESKTOP_INSTALLATION_LOCATION := /usr/share/applications
BINARY_LOCATION := /usr/share/Wallman/bin
GUI_LOCATION := gui
GUI_INSTALLATION_LOCATION := /usr/share/Wallman/gui

build:
	mkdir $(OUTPUTDIR)
	g++ $(CCFLAGS) $(GTK4LIBS) $(GSTLIBS) -lX11 $(INPUTDIR)/$(GUIINPUTFILE) -o $(OUTPUTDIR)/$(GUIOUTPUTFILE)
	g++ $(CCFLAGS) $(GTK3LIBS) $(WEBKITLIBS) $(INPUTDIR)/$(DESKTOPINPUTFILE) -o $(OUTPUTDIR)/$(DESKTOPOUTPUTFILE)

convert:
	gtk4-builder-tool $(GTKBFLAGS) $(GUI_LOCATION)/$(GTK3GLADE) > $(GUI_LOCATION)/$(GTK4GLADE)

clean:
	rm -r $(OUTPUTDIR)

run:
	$(OUTPUTDIR)/$(GUIOUTPUTFILE)

install:
	mkdir -p $(BINARY_LOCATION)
	cp $(DESKTOP_FILE_LOCATION)/$(GUIOUTPUTFILE).desktop $(DESKTOP_INSTALLATION_LOCATION)/$(GUIOUTPUTFILE).desktop
	cp $(OUTPUTDIR)/$(GUIOUTPUTFILE) $(BINARY_LOCATION)/$(GUIOUTPUTFILE)
	cp $(OUTPUTDIR)/$(DESKTOPOUTPUTFILE) $(BINARY_LOCATION)/$(DESKTOPOUTPUTFILE)
	cp -r $(GUI_LOCATION) $(BINARY_LOCATION)/
	chmod g+rx $(BINARY_LOCATION)/$(GUIOUTPUTFILE)
	chmod g+rx $(BINARY_LOCATION)/$(DESKTOPOUTPUTFILE)
	chmod g+rx $(DESKTOP_INSTALLATION_LOCATION)/$(GUIOUTPUTFILE).desktop

uninstall:
	rm -r $(BINARY_LOCATION)
	rm $(DESKTOP_INSTALLATION_LOCATION)/$(GUIOUTPUTFILE).desktop
	rm $(BINARY_LOCATION)/$(GUIOUTPUTFILE)
	rm $(BINARY_LOCATION)/$(DESKTOPOUTPUTFILE)