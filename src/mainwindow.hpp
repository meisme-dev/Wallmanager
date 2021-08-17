#pragma once

#define ADD_BUTTON builder->get_widget<Gtk::Button>("addButton")
#define CANCEL_BUTTON builder->get_widget<Gtk::Button>("cancelButton")
#define FILE_CHOOSER_BUTTON builder->get_widget<Gtk::Button>("fileChooserButton")
#define FINISH_BUTTON builder->get_widget<Gtk::Button>("finishButton")
#define OPEN_BUTTON builder->get_widget<Gtk::Button>("openButton")
#define FILE_LOCATION_ENTRY builder->get_widget<Gtk::Entry>("fileLocation")
#define FILE_WIDGET builder->get_widget<Gtk::FileChooserWidget>("fileWidget")
#define CHILD_GRID builder->get_widget<Gtk::Grid>("childGrid")
#define VIDEO_PLAYER builder->get_widget<Gtk::Video>("vPlayer")
#define FILE_DIALOG builder->get_widget<Gtk::Window>("fileDialog")
#define MAIN_WINDOW builder->get_widget<Gtk::Window>("windowMain")
#define WIZARD_WINDOW builder->get_widget<Gtk::Window>("windowWizard")
