//!
//! @file 			RxBuff.hpp
//! @author 		Geoffrey Hunter <gbmhunter@gmail.com> (www.mbedded.ninja)
//! @created		2014-01-09
//! @last-modified 	2014-10-07
//! @brief 			An input buffer for the Rx engine. This can accept a stream of characters and call Rx::Go when the CR character is detected.
//! @details
//!					See README.rst in repo root dir for more info.

#ifndef __cplusplus
	#error Please build with C++ compiler
#endif

//===============================================================================================//
//======================================== HEADER GUARD =========================================//
//===============================================================================================//

#ifndef MCLIDE_RX_BUFF_H
#define MCLIDE_RX_BUFF_H

//===============================================================================================//
//==================================== FORWARD DECLARATION ======================================//
//===============================================================================================//

namespace MbeddedNinja
{
	namespace MClideNs
	{
		class RxBuff;
	}
}


//===============================================================================================//
//========================================== INCLUDES ===========================================//
//===============================================================================================//

//===== SYSTEM LIBRARIES =====//
#include <stdint.h>

//===== USER SOURCE =====//
#include "Config.hpp"


namespace MbeddedNinja
{
	namespace MClideNs
	{
	
		//! @brief		An input buffer for the Rx engine. It can accept a stream of characters and call Rx::Go() when the clide_END_OF_COMMAND_CHAR character is detected.
		class RxBuff
		{
		
			public:
			
				//! @brief		Set to the character you want to use for end-of-command recognition. When this command is
				//!				detected in the input buffer, the command is send to the Clide::Rx object for processing.
				//! @details	'\r' and '\n' are common choices for this value. Set in the constructor.
				char endOfCmdChar;

				//===============================================================================================//
				//==================================== CONSTRUCTORS/DESTRUCTOR ==================================//
				//===============================================================================================//

				//! @brief		Constructor
				//! @param		rxController	The Clide::Rx object that the command will be passed to once endOfCmdChar is
				//!								detected.
				//! @param		endOfCmdChar	Set to the character you want to use for end-of-command recognition. When this command is
				//!								detected in the input buffer, the command is send to the Clide::Rx object for processing.
				//!								Can be changed by writing to RxBuff::endOfCmdChar.
				RxBuff(Rx* rxController, char endOfCmdChar);

				//===============================================================================================//
				//======================================= PUBLIC METHODS ========================================//
				//===============================================================================================//

				//! @brief		Write a single character to the RxBuff.
				//! @sa			WriteString()
				bool WriteChar(const char character);

				//! @brief		Writes a null-terminated string of characters to the RxBuff.
				//! @sa			WriteChar()
				bool WriteString(const char* characters);

			private:

				//===============================================================================================//
				//================================== PRIVATE VARIABLES/STRUCTURES ===============================//
				//===============================================================================================//

				//! @brief		Pointer to the rx controller RxBuff will send characters too once CR had been detected.
				Rx* rxController;

				//! @brief		Rx buffer for storing characters sent to RxBuff by Write().
				char buff[clide_RX_BUFF_SIZE];

				//! @brief		Pointer to current write location in buffer
				uint8_t buffWritePos;

				//===============================================================================================//
				//======================================= PRIVATE METHODS =======================================//
				//===============================================================================================//

				// none

		};


		// none

	} // namespace MClide
} // namespace MbeddedNinja

#endif	// #ifndef MCLIDE_RX_BUFF_H

// EOF
