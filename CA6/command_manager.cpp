#include "command_manager.hpp"
#include "invert.hpp"
#include "gray.hpp"
#include "emboss.hpp"
#include "sharpen.hpp"
#include "blur.hpp"
#include <iostream>
#include <limits.h>

View CommandManager::getView(string viewString) {
    if (viewString.find(':') != string::npos) {
        istringstream ss(viewString);
        string x, y, w, h;
        getline(ss, x, ':');
        getline(ss, y, ':');
        getline(ss, w, ':');
        getline(ss, h, ':');
        return {stoi(x), stoi(y), stoi(w), stoi(h)};
    } else {
        return {0, 0, INT_MAX, INT_MAX};
    }
}

Filter *CommandManager::getFilter(const string &current, const string &next) {
    View commandView = getView(next);
    if (current == "-I") {
        return new InvertFilter(commandView);
    } else if (current == "-G") {
        return new GrayScale(commandView);
    } else if (current == "-E") {
        return new Emboss(commandView);
    } else if (current == "-S") {
        return new Sharpen(commandView);
    } else if (current == "-B") {
        return new Blur(commandView);
    } else {
        throw runtime_error("Unsupported filter given");
    }
}

vector<Filter *> CommandManager::getFiltersFromInput(int argc, char **argv) {
    vector<Filter *> filters;
    for (int i = 1; i < argc; ++i) {
        string current = argv[i];
        if (current.starts_with("-")) {
            string next = (i == argc - 1) ? "" : argv[i + 1];
            filters.push_back(getFilter(current, next));
        } else if (current.find(':') != string::npos) {
            continue;
        } else {
            throw domain_error("invalid input format");
        }
    }
    return filters;
}

void CommandManager::handle(int argc, char **argv) {
    if (argc <= 1) {
        throw domain_error("insufficient number of arguments provided");
    }
    vector<Filter *> filters = getFiltersFromInput(argc, argv);

    string outputFile;
    string inputFile;
    while (cin >> inputFile >> outputFile) {
        cout << inputFile << ":" << outputFile << endl;
        Bmp current = Filter::readBmp(inputFile);
        for (auto filter: filters) {
            filter->setPhoto(current);
            current = filter->apply();
        }
        Filter::writeBmp(outputFile, current);
    }
}
