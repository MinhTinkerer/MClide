//!
//! @file 		Clide-Config.h
//! @author 	Geoffrey Hunter <gbmhunter@gmail.com> (www.cladlab.com)
//! @date 		2013/04/02
//! @brief 		Configuration file for Clide.
//! @details
//!		<b>Last Modified:			</b> 2013/05/14					\n
//!		<b>File Version:			</b> v1.0.0.0					\n
//!		<b>Company:					</b> CladLabs					\n
//!		<b>Project:					</b> Free Code Libraries		\n
//!		<b>Language:				</b> C++						\n
//!		<b>Compiler:				</b> GCC						\n
//! 	<b>uC Model:				</b> PSoC5						\n
//!		<b>Computer Architecture:	</b> ARM						\n
//! 	<b>Operating System:		</b> FreeRTOS v7.2.0			\n
//!		<b>Documentation Format:	</b> Doxygen					\n
//!		<b>License:					</b> GPLv3						\n
//!	

#ifndef __cplusplus
	#error Please build with C++ compiler
#endif

//===============================================================================================//
//======================================== HEADER GUARD =========================================//
//===============================================================================================//

#ifndef CLIDE_CONFIG_H
#define CLIDE_CONFIG_H

//===============================================================================================//
//========================================== INCLUDES ===========================================//
//===============================================================================================//

// none

//===============================================================================================//
//======================================== NAMESPACE ============================================//
//===============================================================================================//

namespace Clide
{

	//===============================================================================================//
	//==================================== PUBLIC DEFINES ===========================================//
	//===============================================================================================//

	//=============== DEBUG SWITCHES ============//

	#define clideDEBUG_PRINT_GENERAL		1				//!< Print general debug msgs
	#define clideDEBUG_PRINT_VERBOSE		1				//!< Print verbose debug msgs
	#define clideDEBUG_PRINT_ERROR			1				//!< Print error debug msgs

	#define clideDEBUG_PRINT_ANY	(clideDEBUG_PRINT_GENERAL | clideDEBUG_PRINT_VERBOSE | clideDEBUG_PRINT_ERROR)

	//! @brief		Set to 1 to enable automatic help generation.
	#define clide_ENABLE_AUTO_HELP			0	
	
	//! Sets the maximum string length for a single command, parameter, or option name/option value
	//! @todo Use dynamic allocation, so not required.
	#define clideMAX_STRING_LENGTH			(20)	

	//! Maximum length for the cmd name
	#define clideMAX_NAME_LENGTH			(20)

	//! Maximum length for the cmd description
	#define clideMAX_DESCRIPTION_LENGTH		(100)	
	
	//! @brief		The size of the debug buffer.
	//! @details	All writes use snprintf so should be safe if too small.
	#define clide_DEBUG_BUFF_SIZE			(200)
		


} // namespace Clide

#endif	// #ifndef CLIDE_CONFIG_H

// EOF
