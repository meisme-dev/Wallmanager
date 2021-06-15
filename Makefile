WFLAGS := -Wall
INPUTDIR := src
INPUTFILE := rootwindow.cpp
OUTPUTDIR := build
OUTPUTFILE := Wallman
GTKLIBS := $(shell pkg-config --cflags --libs gtkmm-3.0)
WEBKITLIBS := $(shell pkg-config --cflags --libs webkit2gtk-4.0)
CCFLAGS := $(WFLAGS) $(GTKLIBS) $(WEBKITLIBS) $(INPUTDIR)/$(INPUTFILE) -o $(OUTPUTDIR)/$(OUTPUTFILE)
GTKBFLAGS := simplify --3to4
GTK3GLADE := webview.glade
GTK4GLADE := web.glade
DESKTOP_FILE_LOCATION := src/.desktop
DESKTOP_INSTALLATION_LOCATION := /usr/share/applications
BINARY_LOCATION := /bin

build:
	mkdir $(OUTPUTDIR)
	g++ $(CCFLAGS)

convert:
	gtk4-builder-tool $(GTKBFLAGS) $(GTK3GLADE) > $(GTK4GLADE)

clean:
	rm -r $(OUTPUTDIR)

run:
	$(OUTPUTDIR)/$(OUTPUTFILE)

install:
	cp $(DESKTOP_FILE_LOCATION)/$(OUTPUTFILE).desktop $(DESKTOP_INSTALLATION_LOCATION)/$(OUTPUTFILE).desktop
	cp $(OUTPUTDIR)/$(OUTPUTFILE) $(BINARY_LOCATION)/$(OUTPUTFILE)
	chmod g+rx $(BINARY_LOCATION)/$(OUTPUTFILE)
	chmod g+rx $(DESKTOP_INSTALLATION_LOCATION)/$(OUTPUTFILE).desktop