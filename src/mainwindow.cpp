#include <gtkmm-4.0/gtkmm.h>
#include <iostream>
#include <boost/regex.hpp>
#include "mainwindow.hpp"

std::string current_path;
std::string gui_file = "config/gui/wallman.ui";

void initialize(){
    auto builder = Gtk::Builder::create_from_file(current_path.append(gui_file));
    pButton = builder->get_widget<Gtk::Button>("addButton");
    pCancelButton = builder->get_widget<Gtk::Button>("cancelButton");
    pFileChooserButton = builder->get_widget<Gtk::Button>("fileChooserButton");
    pFinishButton = builder->get_widget<Gtk::Button>("finishButton");
    pOpenButton = builder->get_widget<Gtk::Button>("openButton");
    pEntry = builder->get_widget<Gtk::Entry>("fileLocation");
    pWidget = builder->get_widget<Gtk::FileChooserWidget>("fileWidget");
    pGrid = builder->get_widget<Gtk::Grid>("childGrid");
    pVideo = builder->get_widget<Gtk::Video>("vPlayer");
    pFileDialog = builder->get_widget<Gtk::Window>("fileDialog");
    pWindow = builder->get_widget<Gtk::Window>("windowMain");
    pWizard = builder->get_widget<Gtk::Window>("windowWizard");
    pButton->signal_clicked().connect([] () { event_handlers::on_addButton_click(); }); 
    pCancelButton->signal_clicked().connect([] () { event_handlers::on_cancelButton_click(); }); 
    pFileChooserButton->signal_clicked().connect([] () { event_handlers::on_fileButton_click(); }); 
    pFinishButton->signal_clicked().connect([] () { event_handlers::on_finishButton_click(); }); 
    pOpenButton->signal_clicked().connect([] () { event_handlers::on_openButton_click(); }); 
    pEntry->signal_changed().connect([] () { event_handlers::on_entry_changed(); }); 
    app->add_window(*pWindow);
    pWindow->show();
}


int main(int argc, char **argv){
    current_path = tools::do_readlink("/proc/self/cwd");
    if (!current_path.empty() && *current_path.rbegin() != '/'){
        current_path += '/';
    }
    app = Gtk::Application::create();
    app->signal_activate().connect([] () { initialize(); }); 
    return app->run(argc, argv);
} 
