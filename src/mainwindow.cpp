#include <gtkmm-4.0/gtkmm.h>
#include <iostream>
#include <boost/regex.hpp>

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
boost::regex valid_url("((http|https)://)(www.)?[a-zA-Z0-9@:%._\\+~#?&//=]{2,256}\\.[a-z]{2,6}\\b([-a-zA-Z0-9@:%._\\+~#?&//=]*)");
std::string pLink;
Glib::RefPtr<Gio::File> fileName = NULL;

void on_addButton_click(){
    pWizard->show();
}

void on_fileButton_click(){
    pFileDialog->show();
}

bool url_valid(std::string url){
    return boost::regex_match(url, valid_url);
}

void on_entry_changed(){
    pLink = pEntry->get_text();
    if(url_valid(pLink) && pLink.find("youtube")){
        std::string commandLine = std::string("youtube-dl ") + std::string(pLink) + std::string(" > tmp.log");
        system(commandLine.c_str());
        pVideo->set_filename("");
    }
    else{
        pVideo->set_filename(pLink);
    }
}

void on_finishButton_click(){
    system("/usr/share/Wallman/bin/Wallman-Desktop &");
}

void on_cancelButton_click(){
    pFileDialog->close();
}

void on_openButton_click(){
    fileName = pWidget->get_file();
    pLink = fileName->get_path();
    pEntry->set_text(pLink);
    pVideo->set_filename(pLink);
}

void initialize(){
    auto builder = Gtk::Builder::create_from_file("/usr/share/Wallman/bin/gui/window.glade");
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
    pButton->signal_clicked().connect([] () { on_addButton_click(); }); 
    pCancelButton->signal_clicked().connect([] () { on_cancelButton_click(); }); 
    pFileChooserButton->signal_clicked().connect([] () { on_fileButton_click(); }); 
    pFinishButton->signal_clicked().connect([] () { on_finishButton_click(); }); 
    pOpenButton->signal_clicked().connect([] () { on_openButton_click(); }); 
    pEntry->signal_changed().connect([] () { on_entry_changed(); }); 
    app->add_window(*pWindow);
    pWindow->show();
}

int main(int argc, char** argv){
    app = Gtk::Application::create();
    app->signal_activate().connect([] () { initialize(); }); 
    return app->run(argc, argv);
}