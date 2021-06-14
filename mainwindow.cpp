#include <gtkmm-4.0/gtkmm.h>
#include <iostream>

namespace mainwindow{
    Glib::RefPtr<Gtk::Application> app;
    Gtk::Window *pWindow = nullptr;

    void on_app_activate(){
        auto builder = Gtk::Builder::create_from_file("window.glade");
        pWindow = builder->get_widget<Gtk::Window>("windowMain");
        //pWindow->signal().connect([] () { on_window_destroy(); }); 
        app->add_window(*pWindow);
        pWindow->show();
    }
}

using namespace mainwindow;

int main(int argc, char** argv){
    app = Gtk::Application::create();
    app->signal_activate().connect([] () { on_app_activate(); }); 
    return app->run(argc, argv);
}