#ifndef IMAGEFILTER_COMMAND_MANAGER_HPP
#define IMAGEFILTER_COMMAND_MANAGER_HPP

#include <vector>
#include <istream>
#include <sstream>
#include "filter.hpp"

class CommandManager {
private:
    static View getView(string viewString);

    static Filter *getFilter(const string &current, const string &next);

    static vector<Filter*> getFiltersFromInput(int argc, char *argv[]);

public:
    static void handle(int argc, char *argv[]);
};

#endif //IMAGEFILTER_COMMAND_MANAGER_HPP
