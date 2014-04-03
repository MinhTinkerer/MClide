//!
//! @file 			Option.hpp
//! @author 		Geoffrey Hunter <gbmhunter@gmail.com> (www.cladlab.com)
//! @created		2013/04/02
//! @last-modified 	2014/04/03
//! @brief 		 	The option class enables used of 'optional' parameters in the command-line interface.
//! @details
//!					See README.rst in repo root dir for more info.

#ifndef __cplusplus
	#error Please build with C++ compiler
#endif

//===============================================================================================//
//======================================== HEADER GUARD =========================================//
//===============================================================================================//

#ifndef CLIDE_OPTION_H
#define CLIDE_OPTION_H

#include <string>

//===============================================================================================//
//======================================== NAMESPACE ============================================//
//===============================================================================================//

namespace Clide
{

	//! @brief		Holds all option variables
	//! @details	Object of this type is passed into Rx.RegisterOption() or Tx.RegisterOption().
	class Option
	{
		
		public:
		
			//===============================================================================================//
			//=================================== CONSTRUCTORS/DESTRUCTOR ===================================//
			//===============================================================================================//
		
			//! @brief		Base constructor.
			//! @details	
			//! @param		shortName		The short name of this option (to look for in command-line).
			//! @param		longName		The long name of this option (to look for in command-line). Can be NULL.
			//! @param		callBackFunc	Call-back function which is called when option is discovered.
			//!								Can be set to NULL.
			//! @param		description		Used when help is requested.
			//! @param		associatedValue	Set to true if option has an associated value
			Option(
				const char shortName,
				std::string longName,
				bool (*callBackFunc)(char *optionVal),
				std::string description,
				bool associatedValue);

			//! @brief		Simplified constructor. Short name set to NULL, assoicatedValue set to false.
			//! @details	
			//! @param		longName		The long name of this option (to look for in command-line).
			//! @param		callBackFunc	Call-back function which is called when option is discovered.
			//!								Can be set to NULL.
			//! @param		description		Used when help is requested.
			Option(
				std::string longName,
				bool (*callBackFunc)(char *optionVal),
				std::string description);
			
			//! @brief		Simplified constructor. Long name set to NULL, assoicatedValue set to false.
			//! @details	
			//! @param		shortName		The short name of this option (to look for in command-line).
			//! @param		callBackFunc	Call-back function which is called when option is discovered.
			//!								Can be set to NULL.
			//! @param		description		Used when help is requested.
			Option(
				const char shortName,
				bool (*callBackFunc)(char *optionVal),
				std::string description);
		
			//! @brief		Destructor.
			//! @details	Deallocates memory.
			~Option();
		
			//===============================================================================================//
			//========================================= PUBLIC METHODS ======================================//
			//===============================================================================================//
			
			// none
			
			//===============================================================================================//
			//======================================= PUBLIC VARIABLES ======================================//
			//===============================================================================================//
		
			//! @brief		The short name of the option. Just a single character.
			//! @details	Optional, but at least 1 of shortName or longName must ne non-null.
			char shortName;
		
			//! @brief		The long name of the option. Optional, but at least 1 of shortName or longName must ne non-null.
			//! @details	Optional, but at least 1 of shortName or longName must ne non-null.
			std::string longName;
			
			//! @brief		Description of an option. Used with the "-h", "--help" flags.
			std::string description;
			
			//! @brief		The value of the option. Assigned to when receiving commands.
			//! @todo		Change so that dynamically allocated
			char value[clide_MAX_STRING_LENGTH];
			
			//! @brief		Optional callback function for when option is discovered.
			//! @details	Function is called before the callback function for the command that it 
			//! 			was sent in is called.
			bool (*callBackFunc)(char* optionVal);
			
			//! @brief		True if option was present the last time the command it is registered to was detected.
			//! @note		This is cleared whenever the command is received again by the RX controller.
			bool isDetected;
			
			//! @brief		Set to true if option has an associated value.
			//! @details	An option without an associated value follows the syntax "-s" while an option with an associated value follows the syntax "-s 20". Default value is false.
			bool associatedValue;
			
			//! @brief		Passed into getopt_long() so that it can be set if the function
			// 				detects the long option.
			//! @details	If this is set, than isDetected is set. isDetected cannot be passed
			//!				directly into getopt_long() (incompatible types).
			int longOptionDetected;
			
		private:
		
			//! @brief		All constructors end up calling this function.
			void Init(
				const char shortName,
				std::string longName,
				bool (*callBackFunc)(char *optionVal),
				std::string description,
				bool associatedValue);

	};

	//===============================================================================================//
	//==================================== PUBLIC DEFINES ===========================================//
	//===============================================================================================//

	// none			

	//===============================================================================================//
	//=================================== PUBLIC TYPEDEFS ===========================================//
	//===============================================================================================//

	// none

	//===============================================================================================//
	//================================== PUBLIC VARIABLES/STRUCTURES ================================//
	//===============================================================================================//

	// none

	//===============================================================================================//
	//=================================== PUBLIC FUNCTION PROTOTYPES ================================//
	//===============================================================================================//


} // namespace Clide

#endif	// #ifndef CLIDE_OPTION_H

// EOF
