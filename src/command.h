#ifndef COCL_COMMAND_H
#define COCL_COMMAND_H

#include <iostream>
#include <string>

namespace cocl {

class Command {
public:
    Command(int argc, char* argv[]);

    struct Options {
        bool help;
        bool test;
        Options();
    };

    struct Params {
        std::string inpdir;
        std::string outdir;
        Params();
    };

    std::string progname;
    Options options;
    Params params;

private:
    void print_help(std::ostream& os, char* cmd) const;
};

} // namespace cocl

#endif // COCL_COMMAND_H
