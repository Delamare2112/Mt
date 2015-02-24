/*
	ModuleEngine.cc - Module Engine implementation
*/
#include "core/ModuleEngine.hh"

namespace Mt {
	namespace core {
		ModuleEngine* ModuleEngine::instance = nullptr;
		// Shut up, I can call the module extension what ever I damn well please.
		// MOdulE - Thats how I'm justifying it.
		std::string ModuleEngine::ending = ".moe";

		ModuleEngine::ModuleEngine(void) {
			
		}

		ModuleEngine::~ModuleEngine(void) {
			this->UnloadAll();
		}

		ModuleEngine* ModuleEngine::GetInstance(void) {
			if (ModuleEngine::instance == nullptr)
				return (ModuleEngine::instance = new ModuleEngine());
			return ModuleEngine::instance;
		}
#if defined(__linux__) // Linux implementation
		bool ModuleEngine::LoadModule(std::string module) {
#if defined(DEBUG) | defined(_DEBUG)
			std::cout << "Attempting to load module '" << module << "'" << std::endl;
#endif
			//ModulePackage *mdl = new  ModulePackage;
			return true;
		}

		bool ModuleEngine::UnloadModule(std::string module) {


		}

		bool ModuleEngine::LoadAll(std::string directory) {
#if defined(DEBUG) | defined(_DEBUG)
			std::cout << "Attempting to load modules from '" << directory << "'" << std::endl;
#endif
			std::vector<std::string> files;
			// If we get an error, pop out.
			if(!this->__LX_GetDirContent(directory, files)) return false;
			
			// Filter out the garbage in the directory
			files.erase(std::remove_if(files.begin(), files.end(), IsValidModule), files.end());
#if defined(DEBUG) | defined(_DEBUG)
			std::cout << "Found " << files.size() << " modules" << std::endl << std::endl;
#endif
			// Ungodly amount of allocation happens here
			// ~140 TB of ram was attempted to be allocated.
			// Iterate over all of the files
			for(auto module : files){
				// Try to load the module, if not bail out.
				if(!this->LoadModule(module)) return false;
			}
			return true;
		}

		bool ModuleEngine::UnloadAll(void) {
			// Perform unloading
			for(auto mod : this->Modules) {

			}
		}
#elif defined(_WIN32) // Windows implementation
		bool ModuleEngine::LoadModule(std::string module) {
			
		}

		bool ModuleEngine::UnloadModule(std::string module) {


		}

		bool ModuleEngine::LoadAll(std::string directory) {

		}

		bool ModuleEngine::UnloadAll(void) {


		}
#endif


#if defined(__linux__)
		bool ModuleEngine::__LX_GetDirContent(std::string directory, std::vector<std::string> &files) {
			// Yay! File-system interaction. 
			DIR *dp;
			struct dirent *dirp;
			if((dp  = opendir(directory.c_str())) == NULL) {
				std::cout << "Error: Unable to open '" << directory << "'. Does it exist? (" << errno << ") " << strerror(errno) << std::endl;
				return false;
			}

			while ((dirp = readdir(dp)) != NULL) {
					files.push_back(std::string(dirp->d_name));
			}
			closedir(dp);
			return true;
		}
#endif

		bool ModuleEngine::IsValidModule(std::string ModuleName) {
			// Check to see if it the symbol for the current directory or the parent
			if(ModuleName == ".." || ModuleName == ".") return true;
			// Check the file extension to see if it is a .moe
			return  (0 != ModuleName.compare(ModuleName.length() - ModuleEngine::ending.length(), ModuleEngine::ending.length(), ModuleEngine::ending));            
		}
	}
}
