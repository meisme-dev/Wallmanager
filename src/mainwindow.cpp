#include <gtkmm-4.0/gtkmm.h>
#include <iostream>

Glib::RefPtr<Gtk::Application> app;
Gtk::Window *pWindow = nullptr;
Gtk::Button *pButton = nullptr;
Gtk::Label *pLabel = nullptr;

void on_addButton_click(){
    pLabel->set_text("hello");
    g_print("hi\n");
}

void on_app_activate(){
    auto builder = Gtk::Builder::create_from_file("window.glade");
    pWindow = builder->get_widget<Gtk::Window>("windowMain");
    pLabel = builder->get_widget<Gtk::Label>("label");
    pButton = builder->get_widget<Gtk::Button>("addButton");
    pButton->signal_clicked().connect([] () { on_addButton_click(); }); 
    app->add_window(*pWindow);
    pWindow->show();
}

int main(int argc, char** argv){
    app = Gtk::Application::create();
    app->signal_activate().connect([] () { on_app_activate(); }); 
    return app->run(argc, argv);
}