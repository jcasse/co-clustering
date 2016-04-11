#include <cstdlib>
#include <iostream>     // ostream
#include <unistd.h>
#include <getopt.h>     // getopt_long, optind

#include "command.h"
#include "utility.h"

namespace cocl {

Command::Options::Options():
		help(false), test(false) {}

Command::Params::Params():
        inpdir(""), outdir("") {}

void Command::print_help(std::ostream& os, char* cmd) const {
	os << std::endl;
	os << "PROGRAM NAME: " << cmd << std::endl;
	os << std::endl;
	os << "USAGE: " << cmd << " inpdir outdir [OPTION]..." << std::endl;
	os << std::endl;
	os << "OPTIONS:                                          \n";
	cocl::lineacross(os, "", '-');
	os << "  -h, --help                  ";
	os << "print this menu                                   \n";
	os << "  -t, --test                  ";
	os << "run unit tests                                    \n";
	cocl::lineacross(os, "", '-');
	os << std::endl;
	os << std::endl;
	os << "EXAMPLES:" << std::endl;
	cocl::lineacross(os, "", '-');
	os << "Minimal";
	os << std::endl;
	os << cmd << " /Experiments/X/data";
	os << " /Experiments/X/data/pcim";
	os << std::endl;
	os << std::endl;
}

Command::Command(int argc, char* argv[]): options(), params() {

    int digit_optind = 0;
    progname = std::string(argv[0]);

    while (true) {
        int this_option_optind = optind ? optind : 1;
        int lngidx = 0;
        const struct option lngopts[] = {
            {"help",		no_argument,		0,	'h'},
            {"test",		no_argument,		0,	't'},
            {0,				0,					0,   0 }
        };

        const std::string optstr("ht");
        const int c = getopt_long(argc, argv, optstr.c_str(), lngopts, &lngidx);

        if (c == -1) break;

        switch (c) {
        case 0:
            break;

        case '0':
        case '1':
        case '2':
            if (digit_optind != 0 && digit_optind != this_option_optind)
                printf("digits occur in two different argv-elements.\n");
            digit_optind = this_option_optind;
            printf("option %c\n", c);
            break;

        case 'h':
            print_help(std::cout, argv[0]);
            exit(0);

        case 't':
            options.test = true;
            break;

        case '?':
            // getopt already printed a messsage (set opterr = 0 to suppress)
            exit(1);
            break;

        default:
            printf("?? getopt returned character code 0%o ??\n", c);
        }
    }

    if (options.test) return;

    // get input dir
    if (optind == argc) cocl::stop("too few parameters");
    params.inpdir = std::string(argv[optind++]);

    // get output dir
    if (optind == argc) cocl::stop("too few parameters");
    params.outdir = std::string(argv[optind++]);

    // check number of parameters
    if (optind != argc) {
        const std::string str(argv[optind++]);
        if (!cocl::is_numeric(str)) cocl::stop("invalid parameter" + str);
        if (optind != argc) cocl::stop("too many parameters");
    }
}

} // namespace cocl
