//!
//! @file 			OptionFindByLongNameTests.cpp
//! @author 		Geoffrey Hunter <gbmhunter@gmail.com> (www.cladlab.com)
//! @created		2014/05/16
//! @last-modified 	2014/05/16
//! @brief 			Contains test functions for finding options by their long name.
//! @details
//!					See README.rst in root dir for more info.

#include "../api/Clide.hpp"

#include "./UnitTest++/src/UnitTest++.h"

namespace ClideTest
{
	SUITE(OptionFindByLongNameTests)
	{
		using namespace Clide;

		bool Callback(Cmd *cmd)
		{	
			return true;
		}
		
		TEST(OneOptionFindByLongNameTest)
		{
			Rx rxController;
			Tx txController;
			
			Cmd cmdTest("test", &Callback, "A test command.");
			Option testOption('a', "opta", NULL, "A test option.", true);
			
			// Register option
			cmdTest.RegisterOption(&testOption);
			
			// Register command
			rxController.RegisterCmd(&cmdTest);
			
			// Create fake input buffer
			char rxBuff1[50] = "test --opta optVal";
			
			// Run rx controller
			rxController.Run(rxBuff1);
			
			Option* returnedOption = cmdTest.FindOptionByLongName("opta");

			if(returnedOption == nullptr)
				CHECK(false);
			else
				CHECK_EQUAL(true, returnedOption->isDetected);
		}

		TEST(TwoPosOptionFindByLongNameTest)
		{
			Rx rxController;
			Tx txController;

			Cmd cmdTest("test", &Callback, "A test command.");
			Option testOption1('a', "opta", NULL, "Test option a.", true);

			// Register option
			cmdTest.RegisterOption(&testOption1);

			Option testOption2('b', "optb", NULL, "Test option b.", true);

			// Register option
			cmdTest.RegisterOption(&testOption2);

			// Register command
			rxController.RegisterCmd(&cmdTest);

			// Create fake input buffer
			char rxBuff1[50] = "test --opta optVal -optb optVal";

			// Run rx controller
			rxController.Run(rxBuff1);

			Option* returnedOption = cmdTest.FindOptionByLongName("opta");

			if(returnedOption == nullptr)
				CHECK(false);
			else
				CHECK_EQUAL(true, returnedOption->isDetected);

			returnedOption = cmdTest.FindOptionByLongName("optb");

			if(returnedOption == nullptr)
				CHECK(false);
			else
				CHECK_EQUAL(true, returnedOption->isDetected);
		}

		TEST(OnePosOneNegOptionFindByNameTest)
		{
			Rx rxController;
			Tx txController;

			Cmd cmdTest("test", &Callback, "A test command.");
			Option testOption1('a', "opta", NULL, "Test option a.", true);

			// Register option
			cmdTest.RegisterOption(&testOption1);

			Option testOption2('b', "optb", NULL, "Test option b.", true);

			// Register option
			cmdTest.RegisterOption(&testOption2);

			// Register command
			rxController.RegisterCmd(&cmdTest);

			// Create fake input buffer
			char rxBuff1[50] = "test --opta optVal";

			// Run rx controller
			rxController.Run(rxBuff1);

			Option* returnedOption = cmdTest.FindOptionByLongName("opta");

			if(returnedOption == nullptr)
				CHECK(false);
			else
				CHECK_EQUAL(true, returnedOption->isDetected);

			returnedOption = cmdTest.FindOptionByLongName("optb");

			if(returnedOption == nullptr)
				CHECK(false);
			else
				// Should of not been detected
				CHECK_EQUAL(false, returnedOption->isDetected);
		}

		TEST(FindNonexistantOptionByLongNameTest)
		{
			Rx rxController;
			Tx txController;

			Cmd cmdTest("test", &Callback, "A test command.");
			Option testOption('a', "opta", NULL, "A test option.", true);

			// Register option
			cmdTest.RegisterOption(&testOption);

			// Register command
			rxController.RegisterCmd(&cmdTest);

			// Create fake input buffer
			char rxBuff1[50] = "test --opta optVal";

			// Run rx controller
			rxController.Run(rxBuff1);

			// Look for an option that doesn't exist
			Option* returnedOption = cmdTest.FindOptionByLongName("optb");

			// Should of returned a null-pointer
			if(returnedOption == nullptr)
				CHECK(true);
			else
				CHECK(false);
		}
		
	} // SUITE(OptionFindByLongNameTests)
} // namespace ClideTest
