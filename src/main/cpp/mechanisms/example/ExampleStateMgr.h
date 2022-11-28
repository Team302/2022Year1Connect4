//====================================================================================================================================================
/// Copyright 2022 Lake Orion Robotics FIRST Team 302 
///
/// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"),
/// to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense,
/// and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
///
/// The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
///
/// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
/// MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
/// DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE
/// OR OTHER DEALINGS IN THE SOFTWARE.
//====================================================================================================================================================

#pragma once

// C++ Includes
#include <string>

// FRC includes
#include <networktables/NetworkTable.h>
#include <frc/Timer.h>

// Team 302 includes
#include <mechanisms/base/StateMgr.h>
#include <mechanisms/example/Example.h>
#include <mechanisms/StateStruc.h>




// Third Party Includes

class ExampleStateMgr : public StateMgr
{
    public:
        /// @enum the various states of the Intake
        enum EXAMPLE_STATE
        {
            OFF,
            FORWARD,
            REVERSE
        };
        const std::string m_exampleOffXmlString = "EXAMPLE_OFF";
        const std::string m_exampleForwardXmlString = "EXAMPLE_FORWARD";
        const std::string m_exampleReverseXmlString = "EXAMPLE_REVERSE";
        
        const std::map<const std::string, EXAMPLE_STATE> m_exampleXmlStringToStateEnumMap
        {   {m_exampleOffXmlString, EXAMPLE_STATE::OFF},
            {m_exampleForwardXmlString, EXAMPLE_STATE::FORWARD},
            {m_exampleReverseXmlString, EXAMPLE_STATE::REVERSE}
        };

        
		/// @brief  Find or create the state manmanager
		/// @return IntakeStateMgr* pointer to the state manager
		static ExampleStateMgr* GetInstance();

        /// @brief Check if driver inputs or sensors trigger a state transition
        void CheckForStateTransition() override;
    private:

        ExampleStateMgr();
        ~ExampleStateMgr() = default;
        
        Example*                                m_example;
        std::string                             m_nt;


        const double m_CHANGE_STATE_TARGET = 120.0; 
		static ExampleStateMgr*	m_instance;
        const StateStruc m_offState = {EXAMPLE_STATE::OFF, StateType::EXAMPLE_STATE, true};
        const StateStruc m_forwardState = {EXAMPLE_STATE::FORWARD, StateType::EXAMPLE_STATE, false};
        const StateStruc m_reverseState = {EXAMPLE_STATE::REVERSE, StateType::EXAMPLE_STATE, false};
};