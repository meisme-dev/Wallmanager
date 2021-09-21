#include <string>
#include <boost/regex.hpp>
#include <unistd.h>
#include <limits.h>
#include "mainwindow.hpp"

namespace tools {
    
    boost::regex valid_url("((http|https)://)(www.)?[a-zA-Z0-9@:%._\\+~#?&//=]{2,256}\\.[a-z]{2,6}\\b([-a-zA-Z0-9@:%._\\+~#?&//=]*)");

    std::string do_readlink(std::string const& path) {
        char buf[PATH_MAX];
        ssize_t len = readlink(path.c_str(), buf, sizeof(buf)-1);
        if (len != -1) {
            buf[len] = '\0';
            return std::string(buf);
        }
        std::cerr << "Readlink failed for " << path << std::endl;
        return std::string(NULL);
    }

    int do_youtube_dl(std::string const& url, std::string const& output_file) {
        std::string args = "/bin/env youtube-dl" + url + " -o " + output_file;
        g_spawn_command_line_async(args.c_str(), NULL);
    }

    bool do_validate_url(std::string url){
        return boost::regex_match(url, valid_url);
    }

}