#include "mainwindow.hpp"
#include <boost/regex.hpp>

namespace event_handlers{
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
            std::string args = "youtube-dl";
            args += strdup(pLink.c_str());
            g_spawn_command_line_async(args.c_str(), NULL);
            pVideo->set_filename("");
        }
        else{
            pVideo->set_filename(pLink);
        }
    }

    void on_finishButton_click(){
        std::string args = "/bin/env wallman_desktop";
        g_spawn_command_line_async(args.c_str(), NULL);
    }

    void on_cancelButton_click(){
        pFileDialog->hide();
    }

    void on_openButton_click(){
        fileName = pWidget->get_file();
        pLink = fileName->get_path();
        pEntry->set_text(pLink);
        pVideo->set_filename(pLink);
        pFileDialog->hide();
    }
}