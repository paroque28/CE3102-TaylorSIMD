#include <iostream>
#include "src/ln_profe.h"
#include "src/test.h"
#include "src/ref.h"
#include "src/opt.h"
#include "lib/optionparser.h"
#include "lib/matplotlibcpp.h"
#define MAX_TERMS 13
#define CENTER 10
using namespace anpi;
namespace plt = matplotlibcpp;

void graph(vector<double> a,vector<double> b, vector<double> c ,string bname,string cname,string graphName,string output) {
    plt::plot(a, b, "r-", a, c, "k-");
    plt::named_plot(bname, a, b);
    plt::named_plot(cname, a, c);
    plt::title(graphName);
    plt::legend();
    cout<< "Saving graph"<<endl;
    plt::save(output);

}
int main(int argc, char* argv[]) {
    try{

        cxxopts::Options options("anpiSIMD", " anpiSIMD - SIMD optimization for aproximation of functions");

        options.add_options()
                ("l,log", "Use log for example")
                ("c,cos", "Use cos for example")
                ("g,graph", "Make a graph")
                ("i,start", "Set graph start point", cxxopts::value<double>())
                ("f,end", "Set graph end point", cxxopts::value<double>())
                ("o,output", "Output of the graph",cxxopts::value<std::string>())
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
        if (options.count("ntests")) {
            int ntests = options["ntests"].as<int>();
            int terms = MAX_TERMS;
            if (options.count("terms")) terms = options["terms"].as<int>(); //set number of coefs
            if (terms > MAX_TERMS) {cout << "Terms exceed max value"; return 1;}
            if (options.count("graph")) {
                string title, atext,btext, output;
                ref::ln_a<double> ref_log;  ref_log.init<CENTER, MAX_TERMS>(terms);
                opt::ln_a<double> opt_log;  opt_log.init<CENTER, MAX_TERMS>(terms);
                opt::cos_a<double> opt_cos; opt_cos.init<CENTER, MAX_TERMS>(terms);
                ref::cos_a<double> ref_cos; ref_cos.init<CENTER, MAX_TERMS>(terms);
                vector<double> x, y1, y2;
                if (options.count("o")) output = options["o"].as<std::string>();
                else {
                    cout << "Required output path";
                    return 1;
                }
                if(options.count("time"))
                {
                    title = "Time vs number of terms";
                    atext = "ref";
                    btext = "opt";
                    int valor = 11;
                    if (options.count("x")) valor = options["x"].as<int>();
                    for (int i = 1; i < 13; ++i) {
                        ref_cos.setTerms(i);
                        x.push_back(0.0+i);
                        if (options.count("log")) {
                            y1.push_back(tests::time(ref_log, 25000, valor));
                            y2.push_back(tests::time(opt_log, 25000, valor));
                        } else if (options.count("cos")) {
                            y1.push_back(tests::time(ref_cos, 25000, valor));
                            y2.push_back(tests::time(opt_cos, 25000, valor));
                        } else {
                                std::cout << "Need log or cos flag";
                                return 1;
                            }
                    }
                    int a ;
                }
                else if(options.count("error"))
                {
                    title = "Error vs h";
                    atext = "opt";
                    btext = "std";
                    for (double i = CENTER; i < CENTER +3; i+=0.001) {
                        x.push_back(i-CENTER);
                        if (options.count("log")) {
                            y1.push_back(tests::errorVSh(opt_log,i,std::log));
                            y2.push_back(0);
                        } else if (options.count("cos")) {
                            y1.push_back(tests::errorVSh(opt_cos,i,std::cos));
                            y2.push_back(0);
                        } else {
                            std::cout << "Need log or cos flag";
                            return 1;
                        }
                    }

                }
                else {
                    atext = "std";
                    btext = "opt";
                    double start = 0.0;
                    if (options.count("start")) start = options["start"].as<double>(); // set start
                    double end = 20.;
                    if (options.count("end")) end = options["end"].as<double>(); // set end
                    if (end < start) {
                        std::cout << "Error: start in greater than end";
                        return 1;
                    }

                    double step = (end - start) / ntests;
                    for (double i = start; i < end; i += step) {
                        x.push_back(i);
                        if (options.count("log")) {
                            y1.push_back(std::log(i));
                            y2.push_back(opt_log(i));
                            title = "Function log with " + std::to_string(terms) + " terms";
                        } else if (options.count("cos")) {
                            y1.push_back(std::cos(i));
                            y2.push_back(opt_cos(i));
                            title = "Function cos with " + std::to_string(terms) + " terms";
                        } else {
                            std::cout << "Need log or cos flag";
                            return 1;
                        }
                    }

                }
                graph(x, y1, y2, atext, btext, title, output);
                exit(0);
            }
            else if (options.count("x")) {
                int p = 10;
                if (options.count("p")) p = options["p"].as<int>(); // set precission
                int x = options["x"].as<int>(); //set x to evaluate
                std::cout.precision(p);
                if (options.count("log")) {
                    ref::ln_a<double> ref_log;
                    ref_log.init<CENTER, MAX_TERMS>(terms);
                    opt::ln_a<double> opt_log;
                    opt_log.init<CENTER, MAX_TERMS>(terms);

                    std::cout << "f(x)=" << ref_log(x) << std::endl;

                    if (options.count("time")) {
                        std::cout << "Reference time: " << tests::time(ref_log, ntests, x) << std::endl;
                        std::cout << "Optimized time: " << tests::time(opt_log, ntests, x) << std::endl;
                    } else if (options.count("error")) {
                        tests::error(ref_log, ntests, x, &std::log);
                    }
                    else std::cout << "Required flag for time or error" << std::endl;


                    exit(0);
                } else if (options.count("cos")) {
                    opt::cos_a<double> opt_cos;
                    opt_cos.init<CENTER, MAX_TERMS>(terms);

                    ref::cos_a<double> ref_cos;
                    ref_cos.init<CENTER, MAX_TERMS>(terms);

                    std::cout << "f(x)=" << ref_cos(x) << std::endl;

                    if (options.count("time")) {
                        std::cout << "Reference time: " << tests::time(ref_cos, ntests, x) << std::endl;
                        std::cout << "Optimized time: " << tests::time(opt_cos, ntests, x) << std::endl;
                    } else if (options.count("error")) {
                        tests::error(ref_cos, ntests, x, &std::cos);
                    }
                    else std::cout << "Required flag for time or error" << std::endl;


                    exit(0);
                }
            }
        } else std::cout << "Required number of tests" << std::endl;

        std::cout << options.help({""}) << std::endl;
        exit(0);
    }
    catch (const cxxopts::OptionException& e)
    {
        std::cout << "error parsing options: " << e.what() << std::endl;
        exit(1);
    }

}

