/*
    ModuleEngine.cc - Module Engine implementation
*/
#include "core/ModuleEngine.hh"

namespace Mt {
    ModuleEngine* ModuleEngine::instance = nullptr;

    ModuleEngine::ModuleEngine(void) {
        
    }

    ModuleEngine::~ModuleEngine(void) {
    
    }

    ModuleEngine* ModuleEngine::GetInstance(void) {
        if (ModuleEngine::instance == nullptr)
            return (ModuleEngine::instance = new ModuleEngine());
    }


}