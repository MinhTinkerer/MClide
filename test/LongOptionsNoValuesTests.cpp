//!
//! @file 			LongOptionsNoValuesTests.cpp
//! @author 		Geoffrey Hunter <gbmhunter@gmail.com> (www.mbedded.ninja)
//! @created		2013-07-08
//! @last-modified 	2014-10-07
//! @brief 			Contains test functions for MClide command long options with no values.
//! @details
//!					See README.rst in root dir for more info.

//===== SYSTEM LIBRARIES =====//
// none

//====== USER LIBRARIES =====//
#include "MUnitTest/api/MUnitTestApi.hpp"

//===== USER SOURCE =====//
#include "../api/MClideApi.hpp"

using namespace MbeddedNinja::MClideNs;

namespace MClideTest
{

	static bool Callback(Cmd * cmd)
	{
		return true;
	}

	MTEST(OnePosLongOptionNoValuesTest)
	{
		Rx rxController;
		Tx txController;

		Cmd cmdTest("test", &Callback, "A test command.");
		Option testOption("long", NULL, "A test long option.");

		// Register option
		cmdTest.RegisterOption(&testOption);

		// Register command
		rxController.RegisterCmd(&cmdTest);

		// Create fake input buffer
		char rxBuff[50] = "test --long";

		// Run rx controller
		rxController.Run(rxBuff);

		CHECK_EQUAL(testOption.isDetected, true);
	}

	MTEST(TwoPosLongOptionNoValuesTest)
	{
		Rx rxController;
		Tx txController;

		Cmd cmdTest("test", &Callback, "A test command.");
		Option testOption1("long1", NULL, "Test option 1.");
		Option testOption2("long2", NULL, "Test option 2.");

		// Register options
		cmdTest.RegisterOption(&testOption1);
		cmdTest.RegisterOption(&testOption2);

		// Register command
		rxController.RegisterCmd(&cmdTest);

		// Create fake input buffer
		char rxBuff[50] = "test --long1 --long2";
		
		// Run rx controller
		rxController.Run(rxBuff);
		
		CHECK_EQUAL(testOption1.isDetected, true);
		CHECK_EQUAL(testOption2.isDetected, true);
	}
			
	MTEST(OnePosOneNegOptionNoValuesTest)
	{

		Rx rxController;
		Tx txController;

		Cmd cmdTest("test", &Callback, "A test command.");
		Option testOption1("long1", NULL, "Test option 1.");
		Option testOption2("long2", NULL, "Test option 2.");

		// Register options
		cmdTest.RegisterOption(&testOption1);
		cmdTest.RegisterOption(&testOption2);

		// Register command
		rxController.RegisterCmd(&cmdTest);

		// Create input buffer
		char rxBuff[50] = "test --long1";

		// Run rx controller
		rxController.Run(rxBuff);
		
		CHECK_EQUAL(testOption1.isDetected, true);
		CHECK_EQUAL(testOption2.isDetected, false);
	}

} // namespace MClideTest
