#include <gtkmm-3.0/gtkmm.h>
#include <iostream>
#include <webkitgtk-4.0/webkit2/webkit2.h>

int main( int argc, char **argv)
{
  const gchar *pWmName = "wallman_desktop";
  const gchar *pWmClass = "wallman_desktop";
  Glib::RefPtr<Gtk::Application> app = Gtk::Application::create( argc, argv, "" );
  Gtk::Window window;
  window.set_default_size( 1920, 1080 );
  WebKitWebView * pWebView =  WEBKIT_WEB_VIEW( webkit_web_view_new() );
  Gtk::Widget * pWidget = Glib::wrap( GTK_WIDGET( pWebView ) );
  window.set_decorated(0);
  window.set_keep_below(1);
  window.set_type_hint(Gdk::WINDOW_TYPE_HINT_DESKTOP);
  window.set_accept_focus(0);
  window.set_wmclass(pWmName, pWmClass);
  window.add( *pWidget );
  webkit_web_view_load_uri(pWebView, "http://duckduckgo.com");
  window.show_all();
  app->run( window );  
  exit( 0 );
}