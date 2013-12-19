//!
//! @file 			Clide-Cmd.cpp
//! @author 		Geoffrey Hunter <gbmhunter@gmail.com> (www.cladlab.com)
//! @created		2013/04/02
//! @last-modified 	2013/12/10
//! @brief 			Command-line style communications protocol
//! @details
//!				See README.rst in repo root dir for more info.

#ifndef __cplusplus
	#error Please build with C++ compiler
#endif

//===============================================================================================//
//========================================= INCLUDES ============================================//
//===============================================================================================//

// System includes
#include <stdint.h>		// int8_t, int32_t e.t.c
#include <stdio.h>		// snprintf()
#include <stdlib.h>		// realloc(), malloc(), free()
#include <cctype>		// isalnum() 
#include <string.h>		// strlen()

// User includes
#include "include/Clide-MemMang.hpp"
#include "include/Clide-Config.hpp"
#include "include/Clide-Global.hpp"
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
	//======================================= PUBLIC METHODS ========================================//
	//===============================================================================================//



	// Constructor
	Cmd::Cmd(const char *name, bool (*callBackFunc)(Cmd* foundCmd), const char *description)
	{
		#if(clideDEBUG_PRINT_VERBOSE == 1)	
			// Description too long, do not save it
			Port::DebugPrint("CLIDE: Cmd constructor called1.\r\n");
		#endif
		
		// INITIALISATION
		
		this->numParams = 0;
		this->numOptions = 0;
		
		// Set pointers to null. If not NULL, this causes realloc() is exhibit undefined behaviour,
		// since it expects a previously defined location or NULL
		this->paramA = NULL;
		this->optionA = NULL;

		// NAME
		
		uint32_t descLen = strlen(name);
		
		// Make sure the description isn't to long
		if(descLen <= clideMAX_NAME_LENGTH)
		{
			// Create memory for description and store
			//this->name = (char*)MemMang::MallocString(name);

			// Don't need to allocate memory, just take note of pointer
			this->name = (char*)name;
		}
		else
		{
			#if(clideDEBUG_PRINT_ERROR == 1)	
				// Description too long, do not save it
				Port::DebugPrint("CLIDE: ERROR: Command name was too long.\r\n");
			#endif
		}
		
		// DECRIPTION
		
		descLen = strlen(description);
		
		// Make sure the description isn't to long
		if(descLen <= clideMAX_DESCRIPTION_LENGTH)
		{
			// Create memory for description and store
			//this->description = MemMang::MallocString(description);
			this->description = (char*)description;
		}
		else
		{
			#if(clideDEBUG_PRINT_ERROR == 1)	
				// Description too long, do not save it
				Port::DebugPrint("CLIDE: ERROR: Command description was too long.\r\n");
			#endif
		}
		
		// CALLBACK
		this->callBackFunc = callBackFunc;
		
		#if(clide_ENABLE_AUTO_HELP == 1)
			#if(clideDEBUG_PRINT_VERBOSE == 1)
				Port::DebugPrint("CLIDE: Registering help option.\r\n");
			#endif
			// HELP OPTION
			Option* help = new Option('h', "help", NULL, "Prints help for the command.", false);
			this->RegisterOption(help);
		#endif
		
		// DETECTED FLAG
		this->isDetected = false;
		
		// PARENT COMM OBJECT

		// Set to null, this gets assigned when the command is registered.
		// Will be either set to a Clide::Tx or Clide::Rx object
		this->parentComm = NULL;

		#if(clideDEBUG_PRINT_VERBOSE == 1)
			// Description too long, do not save it
			Port::DebugPrint("CLIDE: Cmd constructor finished.\r\n");
		#endif
	}

	Cmd::~Cmd()
	{
		// Destructor
		#if(clideDEBUG_PRINT_VERBOSE == 1)	
			Port::DebugPrint("CLIDE: Cmd destructor called.\r\n");
		#endif
		
		// Free up parameter and option memory
		free(paramA);
		free(optionA);
	}
	
	void Cmd::RegisterParam(Param* param)
	{
		#if(clideDEBUG_PRINT_VERBOSE == 1)	
			// Description too long, do not save it
			Port::DebugPrint("CLIDE: Registering parameter...\r\n");
		#endif

		//this->numParams = 0;
			
		// MALLOC
		this->paramA = (Param**)MemMang::AppendNewArrayElement(this->paramA, this->numParams, sizeof(Param*));
		
		if(this->paramA == NULL)
		{
			#if(clideDEBUG_PRINT_ERROR == 1)	
				// Description too long, do not save it
				Port::DebugPrint("CLIDE: ERROR - Malloc failed while registering parameter.\r\n");
			#endif
			return;	
		}
		
		// Increase parameter count
		this->numParams++;
		
		// Remember the pointer
		paramA[numParams - 1] = param;
	}


	// Register option
	void Cmd::RegisterOption(Option* option)
	{
		#if(clideDEBUG_PRINT_VERBOSE == 1)	
			// Description too long, do not save it
			Port::DebugPrint("CLIDE: Registering option...\r\n");
		#endif

		// Create option pointer at end of option pointer array.
		this->optionA = (Option**)MemMang::AppendNewArrayElement(this->optionA, this->numOptions, sizeof(Option*));
		
		// Increase option count
		this->numOptions++;
		
		// Remember option
		optionA[this->numOptions - 1] = option;
		
		#if(clideDEBUG_PRINT_VERBOSE == 1)	
			if(optionA[this->numOptions - 1]->shortName != '\0')
			{
				snprintf(
					Global::debugBuff,
					sizeof(Global::debugBuff),
					"CLIDE: Option short name = '%c'. Option long name = '%s'.\r\n",
					optionA[this->numOptions - 1]->shortName,
					optionA[this->numOptions - 1]->longName);
			}
			else
			{
				snprintf(
					Global::debugBuff,
					sizeof(Global::debugBuff),
					"CLIDE: Option short name = '%s'. Option long name = '%s'.\r\n",
					"none",
					optionA[this->numOptions - 1]->longName);
			}
			
			Port::DebugPrint(Global::debugBuff);
			
		#endif
	}

	uint32_t Cmd::NumLongOptions()
	{
		#if(clideDEBUG_PRINT_VERBOSE == 1)	
			// Description too long, do not save it
			Port::DebugPrint("CLIDE: Calculating num. of long options...\r\n");
		#endif
		
		uint32_t numLongOptions = 0;
		
		uint32_t x;
		for(x = 0; x < this->numOptions; x++)
		{
			if(this->optionA[x]->longName != NULL)
				numLongOptions++;
		}
		
		#if(clideDEBUG_PRINT_VERBOSE == 1)	
			snprintf(
				Global::debugBuff,
				sizeof(Global::debugBuff),
				"CLIDE: Num. long options = '%" STR(ClidePort_PF_UINT32_T) "'.\r\n",
				numLongOptions);
			Port::DebugPrint(Global::debugBuff);
		#endif
		
		return numLongOptions;		
	}

	//===============================================================================================//
	//==================================== PRIVATE FUNCTIONS ========================================//
	//===============================================================================================//

	// none

} // namespace Clide
