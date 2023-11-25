#include "Mechanics.h"
#include <filesystem>
#include <cstdlib>
#include <string>
#include <fstream>

void Mechanics::Create_File(const char* file_name){
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
	#ifdef _WIN64
		system((std::string{"cd .>"}+file_name).c_str());
	#endif
	#ifdef _WIN32
		system((std::string{"cd .>"}+file_name).c_str());
	#endif
#endif
#if __APPLE__ || __linux__
	system((std::string{"touch "} + file_name).c_str());	
#endif

}
