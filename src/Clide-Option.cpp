//!
//! @file 			Clide-Option.hpp
//! @author 		Geoffrey Hunter <gbmhunter@gmail.com> (www.cladlab.com)
//! @created		2013/04/02
//! @last-modified 	2013/12/10
//! @brief 		 	The option class enables used of 'optional' parameters in the command-line interface.
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
#include <string.h>		// strlen()

// User includes
#include "include/Clide-MemMang.hpp"
#include "include/Clide-Config.hpp"
#include "include/Clide-Port.hpp"
#include "include/Clide-Option.hpp"
#include "include/Clide-Param.hpp"
#include "include/Clide-Cmd.hpp"

//===============================================================================================//
//======================================== NAMESPACE ============================================//
//===============================================================================================//

namespace Clide
{

	//===============================================================================================//
	//===================================== MEMBER FUNCTIONS ========================================//
	//===============================================================================================//

	Option::Option(
		const char shortName,
		const char* longName,
		bool (*callBackFunc)(char *optionVal),
		const char* description,
		bool associatedValue)
	{
		// Base constructor
		
		#if(clideDEBUG_PRINT_VERBOSE == 1)	
			Port::DebugPrint("CLIDE: Base option constructor called.\r\n");
		#endif
		Init(
			shortName,
			longName,
			callBackFunc,
			description,
			associatedValue);
	}
	
	Option::Option(
		const char* longName,
		bool (*callBackFunc)(char *optionVal),
		const char* description)
	{	
		// Simplified constructor. No short name.
		
		#if(clideDEBUG_PRINT_VERBOSE == 1)	
			Port::DebugPrint("CLIDE: Simplified option constructor called (no short name).\r\n");
		#endif
		Init(
			'\0',
			longName,
			callBackFunc,
			description,
			false);
	}
	
	Option::Option(
		const char shortName,
		bool (*callBackFunc)(char *optionVal),
		const char* description)
	{	
		// Simplified constructor. No long name.
		
		#if(clideDEBUG_PRINT_VERBOSE == 1)	
			Port::DebugPrint("CLIDE: Simplified option constructor called (no long name).\r\n");
		#endif
		Init(
			shortName,
			NULL,
			callBackFunc,
			description,
			false);
	}
	
	

	Option::~Option()
	{
		// Destructor
		#if(clideDEBUG_PRINT_VERBOSE == 1)	
			Port::DebugPrint("CLIDE: Option destructor called.\r\n");
		#endif
		
		// Free memory
		free(this->longName);
		free(this->description);
	}
	
	//===============================================================================================//
	//==================================== PRIVATE FUNCTIONS ========================================//
	//===============================================================================================//

	void Option::Init(
		const char shortName,
		const char* longName,
		bool (*callBackFunc)(char *optionVal),
		const char* description,
		bool associatedValue)
	{
		#if(clideDEBUG_PRINT_VERBOSE == 1)	
			Port::DebugPrint("CLIDE: Option constructor called.\r\n");
		#endif		
		
		// Input checks
		uint32_t stringLen = 0;
		
		// Check long name length
		if(longName != NULL)
		{
			stringLen = strlen(longName);
			if(stringLen > clideMAX_NAME_LENGTH)
			{
				#if(clideDEBUG_PRINT_ERROR == 1)	
					// Description too long, do not save it
					Port::DebugPrint("CLIDE: ERROR: Option name was too long.\r\n");
				#endif
				
				return;
			}
		}
		
		// Check too-long description
		if(description != NULL)
		{
			stringLen = strlen(description);
			if(stringLen > clideMAX_DESCRIPTION_LENGTH)
			{
				#if(clideDEBUG_PRINT_ERROR == 1)	
					// Description too long, do not save it
					Port::DebugPrint("CLIDE: ERROR: Option description was too long.\r\n");
				#endif
				
				return;
			}
		}
	
		// NAME

		// Store short name directly (only one char, no memory alloc needed)
		this->shortName = shortName;
		
		// Create memory for long name and store
		if(longName != NULL)
			this->longName = MemMang::MallocString(longName);
		else
			this->longName = NULL;
		
		// DECRIPTION
		
		
		
		// Create memory for description and store
		if(description != NULL)
			this->description = MemMang::MallocString(description);
		else
			description = NULL;
		
		// CALLBACK
		
		this->callBackFunc = callBackFunc;
		
		// DETECTED?
		
		this->isDetected = false;
		
		// ASSOCIATED VALUE?
		
		this->associatedValue = associatedValue;
		
		#if(clideDEBUG_PRINT_VERBOSE == 1)	
			Port::DebugPrint("CLIDE: Option constructor finished.\r\n");
		#endif
	}

} // namespace Clide

// EOF
