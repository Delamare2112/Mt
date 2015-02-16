/*
	Mt - MAT342 Application 
*/

#include "Mt.hh"

/*! \mainpage Mt - Mathematics Environment

    \section Introduction

    This documentation details the working of Mt at a mid-level for understanding.

    This provides a means for anyone who is new on the project, or that wants to know
    how the project works, to get antiquated with some of the in-s and outs.

    Each member and class will have it's own documentation on it's finite details and it's
    internal workings, allowing for an in-depth look at explicit functionality.

    \section Overview

    Mt is developed as a part of MAT342 - Linear Algebra as a free, cross-platform student made 
    replacement for MathWorks MatLab. Mt uses a new language called SML, or Simple[Sane] Math Language.
    SML allows for one to describe mathematical problems in a simple, succinct way.

    Mt is also built to be extensible and open, anyone can build a module that can expand Mt or SML and have it
    work with any other Mt setup.

    \section SML

    Simple[Sane] Math Language is the language that is used by Mt. It allows for the user to express mathematical
    constructs in a way that seems as natural as possible. Disbanding all of the forced pragmatic constructs such
    as for loops, allowing one to express even things like summations in a succinct way.

    A mathematic expression written in SML looks just like it would on paper

    ~~~
    1+2-sin(4)
    ~~~

    More complex examples can be expressed as well, like functions

    ~~~
    F := (x) {
        ret sin(x)+x/1
    }
    ~~~

    For more information see the SML.md document

    \section Modules

    Mt is modular by default, allowing for anyone to build extensions onto the core Mt engine,
    to do so, all one needs to do is implement the Mt::Module class in their module and call the
    MODULE macro to make it a module, a simple module will look like this.

    ~~~{.cpp}
    #include <Module.hh>

    Mt::Module::Module(void) {
        // Initialization Code
    }

    Mt::Module::~Module(void) {
        // Teardown Code
    }

    MODULE("SuperMath")

    ~~~

    And that is all there is to it.
 */
auto main(int argc, char* argv[], char* env[]) -> int {
#if defined(__SSE__) 
    // Fix flush mode, gives us just a little bit better floating points
    _MM_SET_FLUSH_ZERO_MODE(_MM_FLUSH_ZERO_ON);
#endif
    signal(SIGINT, Term);

    // Argument Parsing
    if(argc < 1) {
        // Pass off the the argument parser.
        std::cout << argv[0] << std::endl;
    }

    // Banner
	std::cout << VERSION_STRING << std::endl << std::endl;
	std::cout << QUOTE << std::endl << std::endl;

	// Configuration bits and bobs
	Mt::core::Config::GetInstance()->OpenFile("mt.cfg");
    Mt::core::Config::GetInstance()->ReadEnvForConfig(env);
	Mt::core::Config::GetInstance()->LoadFromFile();

    // Print out the config settings
    if(Mt::core::Config::GetInstance()->GetValue("show_env") == "yes")
	    std::cout << "Environment settings:" << std::endl << (*Mt::core::Config::GetInstance()) << std::endl;

	// Etc
	unsigned long long InterpLineNum = 1ULL;

	// REPL
	std::string strBuffLine;

    // Init the parser
    Mt::SParser::GetInstance();
	while (true) {
		std::cout << "mt:" << InterpLineNum++ << "> ";
		std::getline(std::cin, strBuffLine);
#if defined(_DEBUG) || defined(DEBUG)
		std::cout << " " << strBuffLine << std::endl;
        Mt::SParser::GetInstance()->Eval(strBuffLine);
#endif
	}	
	return ERROR_SUCCESS;
}


void Term(int Signal) {
    if(Signal == SIGTERM); // Nop out, removes the warning...
    std::cout << std::endl << "SIGTERM Caught, releasing resources" << std::endl;
    exit(0);
}
