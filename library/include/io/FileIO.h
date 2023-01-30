#pragma once
#include <string>

namespace Files {
    int load_highscore(std::string path);
    int save_highscore(std::string path, int in);
}
