//!
//! @file 			Clide-Param.cpp
//! @author 		Geoffrey Hunter <gbmhunter@gmail.com> (www.cladlab.com)
//! @created		2013/04/02
//! @last-modified 	2013/12/10
//! @brief 			Contains the Param class, which enables the use of required parameters on the command-line interface.
//! @details
//!					See README.rst in repo root dir for more info.

#ifndef __cplusplus
	#error Please build with C++ compiler
#endif

//===============================================================================================//
//========================================= INCLUDES ============================================//
//===============================================================================================//

// System includes
#include <stdio.h>		// snprintf()
#include <stdlib.h>		// realloc(), malloc(), free()
#include <cctype>		// isalnum() 
#include <getopt.h>		// getopt()	
#include <string.h>		// strlen()

// User includes
#include "./include/Clide-MemMang.hpp"
#include "./include/Clide-Config.hpp"
#include "./include/Clide-Port.hpp"
#include "./include/Clide-Option.hpp"
#include "./include/Clide-Param.hpp"
#include "./include/Clide-Cmd.hpp"

//===============================================================================================//
//======================================== NAMESPACE ============================================//
//===============================================================================================//

namespace Clide
{

	//===============================================================================================//
	//======================================= PUBLIC METHODS ========================================//
	//===============================================================================================//

	Param::Param(const char* description)
	{
		this->Init(NULL, description);
	}

	// Constructor
	Param::Param(bool (*callBackFunc)(char *paramVal), const char* description)
	{
		this->Init(callBackFunc, description);
	}
	
	Param::~Param()
	{
		// Destructor
		#if(clideDEBUG_PRINT_VERBOSE == 1)	
			Port::DebugPrint("CLIDE: Parameter destructor called.\r\n");
		#endif
		
		// Deallocate memory
		free(this->description);
	}

	//===============================================================================================//
	//====================================== PRIVATE METHODS ========================================//
	//===============================================================================================//

	void Param::Init(bool (*callBackFunc)(char *paramVal), const char* description)
	{
		#if(clideDEBUG_PRINT_VERBOSE == 1)	
			Port::DebugPrint("CLIDE: Parameter constructor called.\r\n");
		#endif

		// DECRIPTION
		
		uint32_t stringLen = strlen(description);
		
		// Make sure the description isn't to long
		if(stringLen <= clideMAX_DESCRIPTION_LENGTH)
		{
			// Create memory for description and store
			this->description = MemMang::MallocString(description);
		}
		else
		{
			#if(clideDEBUG_PRINT_ERROR == 1)	
				// Description too long, do not save it
				Port::DebugPrint("CLIDE: ERROR: Parameter description was too long.\r\n");
			#endif
		}
		
		// CALLBACK
		
		// Save call back function
		this->callBackFunc = callBackFunc;
	}

} // namespace Clide
