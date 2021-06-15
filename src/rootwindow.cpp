#include <gtkmm-3.0/gtkmm.h>
#include <iostream>
#include <webkitgtk-4.0/webkit2/webkit2.h>

int main( int argc, char **argv)
{
  const gchar *pWmName = "wallman_desktop";
  const gchar *pWmClass = "InputOutput";
  Glib::RefPtr<Gtk::Application> app = Gtk::Application::create( argc, argv, "" );
  Gtk::Window window;
  window.set_default_size( 1920, 1080 );
  WebKitWebView * one =  WEBKIT_WEB_VIEW( webkit_web_view_new() );
  Gtk::Widget * three = Glib::wrap( GTK_WIDGET( one ) );
  window.set_decorated(0);
  window.set_keep_below(1);
  window.set_type_hint(Gdk::WINDOW_TYPE_HINT_DESKTOP);
  window.set_accept_focus(0);
  window.set_wmclass(pWmName, pWmClass);
  window.add( *three );
  webkit_web_view_load_uri(one, "http://google.com");
  window.show_all();
  app->run( window );  
  exit( 0 );
}