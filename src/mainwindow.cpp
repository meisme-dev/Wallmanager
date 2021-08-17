#include <gtkmm-4.0/gtkmm.h>
#include <iostream>
#include <boost/regex.hpp>
#include "mainwindow.hpp"
#include <sstream>
#include <unistd.h>
#include <limits.h>

namespace mainWindow{
    boost::regex valid_url("((http|https)://)(www.)?[a-zA-Z0-9@:%._\\+~#?&//=]{2,256}\\.[a-z]{2,6}\\b([-a-zA-Z0-9@:%._\\+~#?&//=]*)");
    std::string pLink;
    Glib::RefPtr<Gio::File> fileName = NULL;
    char cwd[PATH_MAX];
    std::string current_path;
    std::string gui_file = "gui/window.glade";

    class Widgets {
        public:
            int widgetId;
            Glib::RefPtr<Gtk::Application> app;
            Gtk::Button *pButton = nullptr;
            Gtk::Button *pCancelButton = nullptr;
            Gtk::Button *pFileChooserButton = nullptr;
            Gtk::Button *pFinishButton = nullptr;
            Gtk::Button *pOpenButton = nullptr;
            Gtk::Entry *pEntry = nullptr;
            Gtk::FileChooserWidget *pWidget = nullptr;
            Gtk::Grid *pGrid = nullptr;
            Gtk::Video *pVideo = nullptr;
            Gtk::Window *pFileDialog = nullptr;
            Gtk::Window *pWindow = nullptr;
            Gtk::Window *pWizard = nullptr;
        ~Widgets(){
            std::cout << "Widget with ID: " << widgetId << " destroyed." << std::endl;
        };
    };
    Widgets widgets;
    
    void on_addButton_click(){
        widgets.pWizard->show();
    }

    void on_fileButton_click(){
        widgets.pFileDialog->show();
    }

    bool url_valid(std::string url){
        return boost::regex_match(url, valid_url);
    }

    void on_entry_changed(){
        pLink = widgets.pEntry->get_text();
        if(url_valid(pLink) && pLink.find("youtube")){
            std::string args = "youtube-dl";
            args += strdup(pLink.c_str());
            g_spawn_command_line_async(args.c_str(), NULL);
            widgets.pVideo->set_filename("");
        }
        else{
            widgets.pVideo->set_filename(pLink);
        }
    }

    void on_finishButton_click(){
        system("/usr/share/Wallman/bin/Wallman-Desktop &");
    }

    void on_cancelButton_click(){
        widgets.pFileDialog->hide();
    }

    void on_openButton_click(){
        fileName = widgets.pWidget->get_file();
        pLink = fileName->get_path();
        widgets.pEntry->set_text(pLink);
        widgets.pVideo->set_filename(pLink);
        widgets.pFileDialog->hide();
    }

    void initialize(){
        auto builder = Gtk::Builder::create_from_file(current_path.append(gui_file));
        widgets.pButton = ADD_BUTTON;
        widgets.pCancelButton = CANCEL_BUTTON;
        widgets.pFileChooserButton = FILE_CHOOSER_BUTTON;
        widgets.pFinishButton = FINISH_BUTTON;
        widgets.pOpenButton = OPEN_BUTTON;
        widgets.pEntry = FILE_LOCATION_ENTRY;
        widgets.pWidget = FILE_WIDGET;
        widgets.pGrid = CHILD_GRID;
        widgets.pVideo = VIDEO_PLAYER;
        widgets.pFileDialog = FILE_DIALOG;
        widgets.pWindow = MAIN_WINDOW;
        widgets.pWizard = WIZARD_WINDOW;
        widgets.pButton->signal_clicked().connect([] () { on_addButton_click(); }); 
        widgets.pCancelButton->signal_clicked().connect([] () { on_cancelButton_click(); }); 
        widgets.pFileChooserButton->signal_clicked().connect([] () { on_fileButton_click(); }); 
        widgets.pFinishButton->signal_clicked().connect([] () { on_finishButton_click(); }); 
        widgets.pOpenButton->signal_clicked().connect([] () { on_openButton_click(); }); 
        widgets.pEntry->signal_changed().connect([] () { on_entry_changed(); }); 
        widgets.app->add_window(*widgets.pWindow);
        widgets.pWindow->show();
    }
}

std::string do_readlink(std::string const& path) {
    char buff[PATH_MAX];
    ssize_t len = ::readlink(path.c_str(), buff, sizeof(buff)-1);
    if (len != -1) {
      buff[len] = '\0';
      return std::string(buff);
    }
    std::cerr << "Readlink failed for " << path << std::endl;
    return std::string(NULL);
}

using namespace mainWindow;

int main(int argc, char **argv){
    current_path = do_readlink("/proc/self/cwd");
    if (!current_path.empty() && *current_path.rbegin() != '/'){
        current_path += '/';
    }
    widgets.app = Gtk::Application::create();
    widgets.app->signal_activate().connect([] () { initialize(); }); 
    return widgets.app->run(argc, argv);
} 
