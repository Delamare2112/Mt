/*
	Mt.hh - Generic and core includes and definitions
*/
#pragma once
// Named this way because str is defined in a *lot* of
// the standard headers, so I had do improvise
#define mk__str(s) __mkstr(s)
#define __mkstr(s) #s

#include <iostream>
#include <string>
#include <iomanip>
#include <csignal>
#include <thread>
#include <chrono>
#if (defined(__linux__) || defined(__APPLE__)) && (defined(_DEBUG) || defined(DEBUG))
#include <unistd.h>	
void RuntimeDump(void);
#endif

#if !defined(_NOFUN)
#include <random>
	std::string quotes[] = {
		"\"If you don't make mistakes, you're not working on hard enough problems. And that is a big mistake.\"\n\t - Frank Wilczek",
		"Gliiv likes colons.",
		"\"I think Computation is destined to be the defining idea of our future.\"\n\t- Stephen Wolfram",
		"\"The essence of mathematics lies in its freedom.\"\n\t - Georg Cantor",
		"Math problems? Call 1-800-[(10x)(13i)^2]-[sin(xy)/2.362x].",
		"Mathematics teachers call retirement 'the aftermath'.",
		"Required Hardware: ~200 TB of RAM\nRecommended Hardware: ~666 TB of RAM",
		"\"Nothing brings fear to my heart more than a floating point number.\"\n\t - Gerald Jay Sussman",
		"\"Computer science is the continuation of logic by other means.\"\n\t - Georg Gottlob",
		"First make it work. Then make it work better.",
		"For science, fudge the numbers so that everything fits.",
		"Ooh and our gods and heroes, are only ones and zeroes",
		"Buy your tickets, have a good time\nBring your friends, dear boys and girls\nBuy my toys, they make you happy\nFund my plan to rule the world",
		"We were building rocket ships, while you were carrying boulders on your shoulders.",
		"Features tend to be added, spontaneously at best.",
		"You are all terrible people and I hope you die in a chemical fire.",
		"With the divine inspiration from the omniscient prof bush, we took it upon our humble selves to produce a work of art",
		"\n?> LIST GAMES;\n\nBRIDGE\nCHECKERS\nCHESS\nPOKER\nFIGHTER COMBAT\nGUERILLA ENGAGEMENT\nDESERT WARFARE\nAIR-TO-GROUND ACTIONS\nTHEATERWIDE TACTICAL WARFARE\nTHEATERWIDE BIOTOXIC AND CHEMICAL WARFARE\nGLOBAL THERMONUCLEAR WAR\n\n",
		"lp0 on fire",
		"ENOTTY: Not a typewriter"
	};
#endif
// Check to see if we are on a machine with SSE or AVX
#if defined(__SSE__) 
#include <immintrin.h>
#endif

#include <core/Config.hh>
#include <core/ModuleEngine.hh>
#include <remote/RPCServer.hh>
#include <frontend/REPL.hh>

#define ERROR_SUCCESS 0
#define ERROR_FAILURE 1

#if !defined(VERSION)
#define VERSION "N/A"
#endif

#if defined(_MSC_VER)
#define COMPILER "MSVC " mk__str(_MSC_VER)
#elif defined(__clang__)
#define COMPILER "clang " __clang_version__
#elif defined(__GNUC__)
#define COMPILER "GCC " mk__str( __GNUC__) "." mk__str(__GNUC_MINOR__)  "." mk__str(__GNUC_PATCHLEVEL__)
#endif

#if defined(_DEBUG) || defined(DEBUG)
#define MODE "DEBUG"
#else
#define MODE "RELEASE"
#endif

#define VERSION_STRING "Mt: Simple math and linear algebra environment. " << std::endl << "\tVer " VERSION " (" COMPILER ") " MODE " Build"

// Misc handlers
void Term(int Signal);
void Kawaii(int Signal);


/*! \namespace Mt
	\brief Core Mt functionality

	The Mt namespace contains all functionality related to Mt itself.
*/
namespace Mt {
	/*! \namespace Mt::core
		\brief Core Mt Functionality

		This namespace contains all of the core functionality of Mt
	*/
	namespace core {
		/*! \namespace Mt::core::lang
			\brief SML Components
	
			All components for the simple math language reside in this namespace.
			This also includes the bison generated code, however that is under the yy namespace.
		*/
		namespace lang {}
		/*! \namespace Mt::core::symbolic
			\brief Symbolic operations

			All operations and methods to deal with symbolic operations such as solving on unknowns
		*/
		namespace symbolic {}
	}
	/*! \namespace Mt::frontend
		\brief User-intractable features

		This namespace contains things such as the REPL and anything the user will interact with whilst using Mt
		
	*/
	namespace frontend {}
	/*! \namespace Mt::objects
		\brief Mt Operable Objects

		All items in this namespace are objects that Mt can operate on, such as Mt::objects::Complex
	*/
	namespace objects {}
	/*! \namespace Mt::remote
		\brief Mt remote operation

		This namespace contains the PRC server and client for talking to other Mt processes and any other application that wishes to use Mt
	*/
	namespace remote {}

}

/*! \namespace yy
	\brief Parser and Lexer
	
	This namespace contains all code generated by the SML grammar files to build the SML parser and lexer.
	Nothing in this namespace is written by hand, it is all auto generated.
*/
namespace yy {}

/*! \mainpage Mt - Mathematics Environment

	\section intro Introduction

	This documentation details the working of Mt at a mid-level for understanding.

	This provides a means for anyone who is new on the project, or that wants to know
	how the project works, to get antiquated with some of the in-s and outs.

	Each member and class will have it's own documentation on it's finite details and it's
	internal workings, allowing for an in-depth look at explicit functionality.

	\section overview Overview

	Mt is developed as a part of MAT342 - Linear Algebra as a free, cross-platform student made 
	replacement for MathWorks MatLab. Mt uses a new language called SML, or Simple[Sane] Math Language.
	SML allows for one to describe mathematical problems in a simple, succinct way.

	Mt is also built to be extensible and open, anyone can build a module that can expand Mt or SML and have it
	work with any other Mt setup.

	\section sml SML

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

	\section modules Modules

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

	\section build Building From Source

	In order to build MT from source, you need a few things

	- clang ( >= 3.5 ), g++ ( >= 4.9 )
	- flex ( >= 2.5 ), bison ( >= 3.4 )
	- libc++, libc++abi (http://libcxx.llvm.org/ , http://libcxxabi.llvm.org/)
	- gperftools (https://code.google.com/p/gperftools/)
	- Protocol Buffers AKA. protobuf (https://github.com/google/protobuf)
	- doxygen
	- latex, pdflatex

	Once you have everything, you can issue a `make` and it should build a
	debug build for you. If you wish for a release build `make release` is what you want.

	To build the documentation, issue a `make docs` and it will build the docs for you.

	If you wish to enable CPU profiling, `make prof` will build the profiling library into the binary.
	
	\section license License

	The MIT License (MIT)

	Copyright (c) 2015- by the contributors listed in the CREDITS file

	Permission is hereby granted, free of charge, to any person obtaining a copy
	of this software and associated documentation files (the "Software"), to deal
	in the Software without restriction, including without limitation the rights
	to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
	copies of the Software, and to permit persons to whom the Software is
	furnished to do so, subject to the following conditions:

	The above copyright notice and this permission notice shall be included in all
	copies or substantial portions of the Software.

	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
	AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
	OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
	SOFTWARE.

	\section thirdparty_legal Third Party Licenses
	
	The following licenses apply to the respective libraries used within Mt.
	You may find a copy of each of the licenses in the ./etc/third_party_licenses directory

	\subsection libquadmath libquadmath

	libquadmath is licensed under the GPL, you may find a copy of the license in ./etc/third_party_licenses/libquadmath.license

	\subsection gperftools gperftools

	Copyright (c) 2005, Google Inc.
	All rights reserved.

	Redistribution and use in source and binary forms, with or without
	modification, are permitted provided that the following conditions are
	met:

		* Redistributions of source code must retain the above copyright
	notice, this list of conditions and the following disclaimer.
		* Redistributions in binary form must reproduce the above
	copyright notice, this list of conditions and the following disclaimer
	in the documentation and/or other materials provided with the
	distribution.
		* Neither the name of Google Inc. nor the names of its
	contributors may be used to endorse or promote products derived from
	this software without specific prior written permission.

	THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
	"AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
	LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
	A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
	OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
	SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
	LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
	DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
	THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
	(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
	OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

	\subsection libcppabi libc++ and libc++abi

	University of Illinois/NCSA
	Open Source License

	Copyright (c) 2003-2014 University of Illinois at Urbana-Champaign.
	All rights reserved.

	Developed by:

		LLVM Team

		University of Illinois at Urbana-Champaign

		http://llvm.org

	Permission is hereby granted, free of charge, to any person obtaining a copy of
	this software and associated documentation files (the "Software"), to deal with
	the Software without restriction, including without limitation the rights to
	use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
	of the Software, and to permit persons to whom the Software is furnished to do
	so, subject to the following conditions:

		* Redistributions of source code must retain the above copyright notice,
		  this list of conditions and the following disclaimers.

		* Redistributions in binary form must reproduce the above copyright notice,
		  this list of conditions and the following disclaimers in the
		  documentation and/or other materials provided with the distribution.

		* Neither the names of the LLVM Team, University of Illinois at
		  Urbana-Champaign, nor the names of its contributors may be used to
		  endorse or promote products derived from this Software without specific
		  prior written permission.

	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
	FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL THE
	CONTRIBUTORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
	OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS WITH THE
	SOFTWARE.

	\subsection linenoise linenoise

	Copyright (c) 2010-2014, Salvatore Sanfilippo <antirez at gmail dot com>
	Copyright (c) 2010-2013, Pieter Noordhuis <pcnoordhuis at gmail dot com>

	All rights reserved.

	Redistribution and use in source and binary forms, with or without
	modification, are permitted provided that the following conditions are met:

	* Redistributions of source code must retain the above copyright notice,
	  this list of conditions and the following disclaimer.

	* Redistributions in binary form must reproduce the above copyright notice,
	  this list of conditions and the following disclaimer in the documentation
	  and/or other materials provided with the distribution.

	THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
	ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
	WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
	DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
	ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
	(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
	LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
	ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
	(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
	SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

	\section protobuf Protocol Buffers (protobuf)

	This license applies to all parts of Protocol Buffers except the following:

	  - Atomicops support for generic gcc, located in
	    src/google/protobuf/stubs/atomicops_internals_generic_gcc.h.
	    This file is copyrighted by Red Hat Inc.

	  - Atomicops support for AIX/POWER, located in
	    src/google/protobuf/stubs/atomicops_internals_aix.h.
	    This file is copyrighted by Bloomberg Finance LP.

	  - Andorid.mk, which is copyrighted by The Android Open Source Project.

	Copyright 2014, Google Inc.  All rights reserved.

	Redistribution and use in source and binary forms, with or without
	modification, are permitted provided that the following conditions are
	met:

	    * Redistributions of source code must retain the above copyright
	notice, this list of conditions and the following disclaimer.
	    * Redistributions in binary form must reproduce the above
	copyright notice, this list of conditions and the following disclaimer
	in the documentation and/or other materials provided with the
	distribution.
	    * Neither the name of Google Inc. nor the names of its
	contributors may be used to endorse or promote products derived from
	this software without specific prior written permission.

	THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
	"AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
	LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
	A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
	OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
	SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
	LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
	DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
	THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
	(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
	OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

	Code generated by the Protocol Buffer compiler is owned by the owner
	of the input file used when generating it.  This code is not
	standalone and requires a support library to be linked with it.  This
	support library is itself covered by the above license.

 */
