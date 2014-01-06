//!
//! @file 			Clide-Cmd.hpp
//! @author 		Geoffrey Hunter <gbmhunter@gmail.com> (www.cladlab.com)
//! @created		2013/03/19
//! @last-modified 	2013/12/18
//! @brief 			Contains the command object, which can be registered with the RX or TX controller (or both).
//! @details
//!					See README.rst in root dir for more info.

#ifndef __cplusplus
	#error Please build with C++ compiler
#endif

//===============================================================================================//
//======================================== HEADER GUARD =========================================//
//===============================================================================================//

#ifndef CLIDE_CMD_H
#define CLIDE_CMD_H

// Added this to prevent circular references
namespace Clide
{
	class Cmd;
}

//===============================================================================================//
//========================================== INCLUDES ===========================================//
//===============================================================================================//

#include <stdint.h>
#include "Clide-Config.hpp"
#include "Clide-Param.hpp"
#include "Clide-Option.hpp"
#include "Clide-Comm.hpp"    //!< Used for save a reference to the parent comm object in each cmd object.
#include "Clide-CmdGroup.hpp"

//===============================================================================================//
//======================================== NAMESPACE ============================================//
//===============================================================================================//

namespace Clide
{

	//! @brief		Holds all command variables, including parameters and options
	//! @details	Object of this type is created with malloc()
	//!				when RegisterCmd() is called, and removed
	//!				with RemoveCmd(). A command needs to be registered to a controller.
	class Cmd
	{	
		
		public:
			
			//===============================================================================================//
			//==================================== CONSTRUCTORS/DESTRUCTOR ==================================//
			//===============================================================================================//
			
			//! @brief		Constructor
			//! @param		name			This is the string that is matched with the first argument in
			//!								a command-line message.
			//! @param		callBackFunc	The function to call when command is received. Any specific option
			//!								or parameter callbacks which are part of this command
			//!								are called before this one.
			//! @param		description		Used when the "help" command or "-h" option is called.
			Cmd(
				const char *name,
				bool (*callBackFunc)(Cmd* foundCmd),
				const char *description);
				
			//! @brief		Destructor. Deallocates memory.
			~Cmd();
			
			//===============================================================================================//
			//========================================= PUBLIC METHODS ======================================//
			//===============================================================================================//
			
		
			//! @brief		Register a parameter with a cmd.
			//! @param		param	Parameter to register.
			void RegisterParam(Param* param);
			
			//! @brief		Register a option with a cmd.
			//! @param		option	Option to register.
			void RegisterOption(Option* option);
			
			//! @brief		Returns the number of options registered to the command which have long option names.
			//! @returns	Number of options with long options names (i.e. longName != NULL).
			uint32_t NumLongOptions();
			
			//! @brief		Adds the command to the provided command group.
			//! @param		cmdGroup	Pointer to the command group you want the command added to.
			void AddToGroup(CmdGroup *cmdGroup);

			//! @brief		Returns the number of command groups that the command belongs to.
			uint32_t GetNumCmdGroups();

			//! @brief		Returns a specific command group that the command belongs to, based of an index.
			CmdGroup* GetCmdGroup(uint32_t cmdGroupNum);

			//===============================================================================================//
			//======================================= PUBLIC VARIABLES ======================================//
			//===============================================================================================//
			
			//! @brief		The command name. Used for recognising command in command-line input. 
			//! @details	This must be the first word sent on the command-line, followed by a space.
			char* name;
			
			//! @brief		Points to the description. Used when the help command is called.
			char* description;
			
			//! @brief 		Pointer to an array of pointers to command parameters. Parameters are dynamically allocated.
			Param** paramA;
			
			//! @brief		Remembers the number of parameters
			uint32_t numParams;
			
			//! @brief		Pointer to an array of pointers to options. Options are dynamically allocated.
			Option** optionA;
			
			//! @brief		Remembers the number of options
			uint32_t numOptions;
			
			//! @brief		Optional callback function for when command is discovered. 
			//! @details	Called after all callback functions for individual options are executed.
			bool (*callBackFunc)(Cmd* foundCmd);
			
			//! @brief		True if command was detected the last time Rx.Run() was called.
			//! @details	You can use this for basic determination if a command was received,
			//!				without having to use a callback function.
			//! @note		This flag is reset for ALL commands every time Rx.Run() is called.
			bool isDetected;
			
			//! @brief		The parent Comm object that this command is registered to. Could either be a
			//!				Tx or Rx object.
			Comm* parentComm;

			//! @brief		A pointer to an array of pointers to CmdGroup objects, which signify which command groups this command belongs to.
			CmdGroup** cmdGroupA;

			uint32_t numCmdGroups;

		protected:


		
	};


} // namespace Clide

#endif	// #ifndef CLIDE_CMD_H

// EOF
