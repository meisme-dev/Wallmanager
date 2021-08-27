#include <string>
#include <boost/regex.hpp>

namespace tools {
    
    boost::regex valid_url("((http|https)://)(www.)?[a-zA-Z0-9@:%._\\+~#?&//=]{2,256}\\.[a-z]{2,6}\\b([-a-zA-Z0-9@:%._\\+~#?&//=]*)");

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

    int do_youtube_dl(std::string const& url, std::string const& output_file) {
        std::string cmd = "youtube-dl -o " + output_file + " " + url;
        return system(cmd.c_str());
    }

    bool do_validate_url(std::string url){
        return boost::regex_match(url, valid_url);
    }
}