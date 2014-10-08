//!
//! @file 			CmdGroup.hpp
//! @author 		Geoffrey Hunter <gbmhunter@gmail.com> (www.mbedded.ninja)
//! @created		2014-01-06
//! @last-modified 	2014-10-07
//! @brief 			The CmdGroup object is used to create "groups" that commands can belong too, which can be then be utilised to display selective help information.
//! @details
//!					See README.rst in root dir for more info.

#ifndef __cplusplus
	#error Please build with C++ compiler
#endif

//===============================================================================================//
//======================================== HEADER GUARD =========================================//
//===============================================================================================//

#ifndef MCLIDE_CMD_GROUP_H
#define MCLIDE_CMD_GROUP_H

//===============================================================================================//
//==================================== FORWARD DECLARATION ======================================//
//===============================================================================================//

namespace MbeddedNinja
{
	namespace MClideNs
	{
		class CmdGroup;
	}
}

//===============================================================================================//
//========================================== INCLUDES ===========================================//
//===============================================================================================//

#include <stdint.h>
#include <string>

#include "Config.hpp"
#include "Param.hpp"
#include "Option.hpp"


namespace MbeddedNinja
{
	namespace MClideNs
	{

		//! @brief		This class is used to create CmdGroup objects that can be assigned to commands, so that they belong to that group.
		//! @details
		class CmdGroup
		{
			
			public:

			//===============================================================================================//
			//========================================= PUBLIC METHODS ======================================//
			//===============================================================================================//

			//! @brief		Constructor.
			CmdGroup(MString name, MString description);
			
			//===============================================================================================//
			//======================================= PUBLIC VARIABLES ======================================//
			//===============================================================================================//

			//! @brief		The command group name. Used for recognising the command group in command-line input.
			//! @details
			MString name;
			
			//! @brief		The command group description.
			MString description;


			protected:

			// none

		};


	} // namespace MClide
} // namespace MbeddedNinja

#endif	// #ifndef MCLIDE_CMD_GROUP_H

// EOF
