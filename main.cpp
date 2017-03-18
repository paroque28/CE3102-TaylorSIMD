#include <iostream>
#include "src/ln_profe.h"
#include "src/test.h"
#include "src/ref.h"
#include "src/opt.h"
#include "src/optionparser.h"
#define MAX_TERMS 13
using namespace anpi;

int main(int argc, char* argv[]) {
    try{

        cxxopts::Options options("TaylorSIMD", " - SIMD optimization");

        options.add_options()
                ("l,log", "Use log for example")
                ("c,cos", "Use cos for example")
                ("g,graph", "Make a graph")
                ("t,time", "Make a time test for both algorithms")
                ("e,error", "Make an error percentage test")
                ("x,value", "X to be evaluated", cxxopts::value<int>())
                ("a,terms", "Number of terms for coeficients", cxxopts::value<int>())
                ("n,ntests", "Number of tests", cxxopts::value<int>())
                ("p,precission", "Precission std::cout", cxxopts::value<int>())
                ("h,help", "Print help");
        options.parse(argc, argv);


        if (options.count("help")) {
            std::cout << options.help({""}) << std::endl;
            exit(0);
        }
        if (options.count("x")) {
            int p = 10;
            if (options.count("p")) p = options["p"].as<int>(); // set precission
            int x = options["x"].as<int>(); //set x to evaluate
            int terms = MAX_TERMS;
            if (options.count("terms")) terms = options["terms"].as<int>(); //set number of coefs
            std::cout.precision(p);
            if (options.count("log")) {
                ref::ln_a<double> ref_log;
                ref_log.init<10, MAX_TERMS>(terms);
                opt::ln_a<double> opt_log;
                opt_log.init<10, MAX_TERMS>(terms);

                std::cout << "f(x)=" << ref_log(x) << std::endl;

                if (options.count("ntests")) {
                    int ntests = options["ntests"].as<int>();
                    if (options.count("time")) {
                        std::cout << "Reference time: "<< tests::time(ref_log,ntests , x) << std::endl;
                        std::cout << "Optimized time: "<< tests::time(opt_log, ntests, x) << std::endl;
                    } else if (options.count("error")) {
                        tests::error(ref_log,ntests,x,&std::log);
                    }
                }

                exit(0);
            } else if (options.count("cos")) {
                opt::cos_a<double> opt_cos;
                opt_cos.init<10, MAX_TERMS>(terms);

                ref::cos_a<double> ref_cos;
                ref_cos.init<10, MAX_TERMS>(terms);

                std::cout << "f(x)=" << ref_cos(x) << std::endl;

                if (options.count("ntests")) {
                    int ntests = options["ntests"].as<int>();
                    if (options.count("time")) {
                        std::cout << "Reference time: "<< tests::time(ref_cos,ntests , x) << std::endl;
                        std::cout << "Optimized time: "<< tests::time(opt_cos, ntests, x) << std::endl;
                    } else if (options.count("error")) {
                        tests::error(ref_cos,ntests,x,&std::cos);
                    }
                }

                exit(0);
            }
        }
        else if (options.count("graph")) {

            exit(0);
        }


        std::cout << options.help({""}) << std::endl;
        exit(0);
    }
    catch (const cxxopts::OptionException& e)
    {
        std::cout << "error parsing options: " << e.what() << std::endl;
        exit(1);
    }

}

