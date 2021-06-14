WFLAGS := -Wall
INPUTFILE := mainwindow.cpp
OUTPUTDIR := build
OUTPUTFILE := Wallman
GTKLIBS := $(shell pkg-config --cflags --libs gtkmm-4.0)
CCFLAGS := $(WFLAGS) $(GTKLIBS) $(INPUTFILE) -o $(OUTPUTDIR)/$(OUTPUTFILE)
GTKBFLAGS := simplify --3to4
GTK3GLADE := main.glade
GTK4GLADE := window.glade

build:
	mkdir $(OUTPUTDIR)
	gtk4-builder-tool $(GTKBFLAGS) $(GTK3GLADE) > $(GTK4GLADE)
	g++ $(CCFLAGS)

clean:
	rm -r $(OUTPUTDIR)

run:
	$(OUTPUTDIR)/$(OUTPUTFILE)