//!
//! @file 			Clide-Comm.cpp
//! @author 		Geoffrey Hunter <gbmhunter@gmail.com> (www.cladlab.com)
//! @created		2013/12/18
//! @last-modified 	2013/12/19
//! @brief			The base communications class. This is extended by both Clide::Tx and Clide::Rx which are the classes manipulated by the user.
//! @details
//!					See README.rst in repo root dir for more info.

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
#include <cstring>		// memset()

// User includes
#include "./include/Clide-Config.hpp"
#include "./include/Clide-Global.hpp"
#include "./include/Clide-MemMang.hpp"
#include "./include/Clide-StringSplit.hpp"
#include "./include/Clide-Param.hpp"
#include "./include/Clide-Option.hpp"
#include "./include/Clide-Cmd.hpp"
#include "./include/Clide-Port.hpp"
#include "./include/Clide-Rx.hpp"
#include "./include/Clide-GetOpt.hpp"

//===============================================================================================//
//======================================== NAMESPACE ============================================//
//===============================================================================================//

namespace Clide
{

	using namespace std;

	bool HelpCmdCallback(Cmd *cmd)
	{
		// Print the help for the parent Comm object that
		// the called help command was assigned to
		cmd->parentComm->PrintHelp();
		return true;
	}

	//===============================================================================================//
	//====================================== PUBLIC METHODS ========================================//
	//===============================================================================================//

	Comm::Comm()
	{
		// Initialise class variables
		this->numCmds = 0;
		this->cmdA = NULL;
	}

	void Comm::RegisterCmd(Cmd* cmd)
	{
		// Save this Rx object as the parent object for this command. This is used
		// for the automatically added help command.
		cmd->parentComm = this;

		// Add new pointer to cmd object at end of array
		cmdA = (Cmd**)MemMang::AppendNewArrayElement(cmdA, numCmds, sizeof(Cmd*));

		// Increment command count
		numCmds++;

		// Store pointer to cmd in array of pointers (Cmd**)
		cmdA[numCmds - 1] = cmd;

	}

	void Comm::RemoveCmd(Cmd* cmd)
	{
		// Remove description
		free(cmd->description);
		// Remove command from memory
		free(cmd);
		// Decrement command count
		numCmds--;
	}

	// Prints out the help info
	void Comm::PrintHelp()
	{
		#if(clideDEBUG_PRINT_GENERAL == 1)	
			Port::DebugPrint("CLIDE: Print help function called.");
		#endif
		
		// Title
		Port::CmdLinePrint("**********LIST OF COMMANDS***********\r\n");

		#if(clide_ENABLE_ADV_TEXT_FORMATTING)
			Port::CmdLinePrint(clide_TABLE_HEADER_ROW_COLOUR_CODE);
			Port::CmdLinePrint(clide_TERM_TEXT_FORMAT_BOLD);
		#endif

		Port::CmdLinePrint("\tcmd\tdescription\r\n");

		#if(clide_ENABLE_ADV_TEXT_FORMATTING)
			Port::CmdLinePrint(clide_TERM_TEXT_FORMAT_NORMAL);
		#endif

		// Iterate through cmd array and print commands
		uint32_t x;
		for(x = 0; x < numCmds; x++)
		{
			Port::CmdLinePrint("\t");
			#if(clide_ENABLE_ADV_TEXT_FORMATTING == 1)
				Port::CmdLinePrint(clide_TERM_TEXT_FORMAT_BOLD);
				Port::CmdLinePrint(cmdA[x]->name);
				Port::CmdLinePrint(clide_TERM_TEXT_FORMAT_NORMAL);
			#else
				// No special formatting
				Port::CmdLinePrint(cmdA[x]->name);
			#endif

			// Add tab character
			Port::CmdLinePrint("\t");
			// Print description
			Port::CmdLinePrint(cmdA[x]->description);
			// \r is enough for PuTTy to format onto a newline also
			// (adding \n causes it to add two new lines)
			Port::CmdLinePrint("\r\n");
		}

	}

	void Comm::PrintHelpForCmd(Cmd* cmd)
	{
		#if(clideDEBUG_PRINT_GENERAL == 1)
			Port::DebugPrint("CLIDE: Printing help for command.\r\n");
		#endif

		Port::CmdLinePrint("\r\n**********COMMAND HELP:**********\r\n");

		// CMD NAME AND DESCRIPTION

		// Tabbing in
		Port::CmdLinePrint("\t");
		#if(clide_ENABLE_ADV_TEXT_FORMATTING == 1)
			Port::CmdLinePrint(clide_TERM_TEXT_FORMAT_BOLD);
			Port::CmdLinePrint(cmd->name);
			Port::CmdLinePrint(clide_TERM_TEXT_FORMAT_NORMAL);
		#else
			// No advanced text formatting
			Port::CmdLinePrint(cmd->name);
		#endif

		// Add tab character
		Port::CmdLinePrint("\t");
		// Print description
		Port::CmdLinePrint(cmd->description);
		// \r is enough for PuTTy to format onto a newline also
		// (adding \n causes it to add two new lines)
		Port::CmdLinePrint("\r\n");

		// CMD PARAMETERS

		Port::CmdLinePrint("Command Parameters:\r\n");


		// Special case if there are no parameters to list
		if(cmd->numParams == 0)
		{
			Port::CmdLinePrint("\t");
			Port::CmdLinePrint("NO PARAMS");
			Port::CmdLinePrint("\r\n");
		}
		else
		{
			// Print top table row 'header'
			#if(clide_ENABLE_ADV_TEXT_FORMATTING)
				Port::CmdLinePrint(clide_TABLE_HEADER_ROW_COLOUR_CODE);
			#endif
			Port::CmdLinePrint("\tindex\tdescription\r\n");
			#if(clide_ENABLE_ADV_TEXT_FORMATTING)
				Port::CmdLinePrint(clide_TERM_TEXT_FORMAT_NORMAL);
			#endif
			// Iterate through cmd array and print commands
			uint32_t x;
			for(x = 0; x < cmd->numParams; x++)
			{
				Port::CmdLinePrint("\t");
				char tempBuff[50];
				snprintf(
					tempBuff,
					sizeof(tempBuff),
					"%" STR(ClidePort_PF_UINT32_T),
					x);
				Port::CmdLinePrint(tempBuff);
				// Add tab character
				Port::CmdLinePrint("\t");
				// Print description
				Port::CmdLinePrint(cmd->paramA[x]->description);
				// \r is enough for PuTTy to format onto a newline also
				// (adding \n causes it to add two new lines)
				Port::CmdLinePrint("\r\n");
			}
		}

		// CMD OPTIONS

		Port::CmdLinePrint("Command Options:\r\n");

		// Special case if there are no parameters to list
		if(cmd->numOptions == 0)
		{
			Port::CmdLinePrint("\t");
			Port::CmdLinePrint("NO OPTIONS");
			Port::CmdLinePrint("\r\n");
		}
		else
		{
			// Print top table row 'header'
			#if(clide_ENABLE_ADV_TEXT_FORMATTING)
				// gold = Port::CmdLinePrint("\x1B[33m");
				// Yellow
				Port::CmdLinePrint(clide_TABLE_HEADER_ROW_COLOUR_CODE);
			#endif
			Port::CmdLinePrint("\tshort\tlong\tdescription\r\n");
			#if(clide_ENABLE_ADV_TEXT_FORMATTING)
				Port::CmdLinePrint("\x1B[0m");
			#endif

			// Iterate through cmd array and print commands
			uint32_t x;
			for(x = 0; x < cmd->numOptions; x++)
			{
				// Print short option
				Port::CmdLinePrint("\t");
				char tempShortOption[2];
				tempShortOption[0] = cmd->optionA[x]->shortName;
				tempShortOption[1] = '\0';
				Port::CmdLinePrint(tempShortOption);

				// Print long option
				Port::CmdLinePrint("\t");
				Port::CmdLinePrint(cmd->optionA[x]->longName);
				// Add tab character
				Port::CmdLinePrint("\t");
				// Print description
				Port::CmdLinePrint(cmd->optionA[x]->description);
				// \r is enough for PuTTy to format onto a newline also
				// (adding \n causes it to add two new lines)
				Port::CmdLinePrint("\r\n");
			}
		}
	}

	//===============================================================================================//
	//==================================== PRIVATE FUNCTIONS ========================================//
	//===============================================================================================//



} // namespace Clide

// EOF
