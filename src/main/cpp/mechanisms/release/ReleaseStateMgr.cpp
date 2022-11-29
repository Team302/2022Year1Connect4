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
#include <map>
#include <memory>
#include <vector>

// FRC includes
#include <networktables/NetworkTableInstance.h>
#include <networktables/NetworkTable.h>
#include <networktables/NetworkTableEntry.h>

// Team 302 includes
#include <mechanisms/controllers/MechanismTargetData.h>
#include <TeleopControl.h>

#include <mechanisms/MechanismFactory.h>
#include <mechanisms/MechanismTypes.h>
#include <mechanisms/base/StateMgr.h>
#include <mechanisms/StateStruc.h>
#include <mechanisms/base/IState.h>
#include <mechanisms/release/Release.h>
// #include <mechanisms/release/ReleaseState.h>
#include <mechanisms/release/ReleaseStateMgr.h>
#include <mechanisms/controllers/StateDataXmlParser.h>


// Third Party Includes

using namespace std;


ReleaseStateMgr* ReleaseStateMgr::m_instance = nullptr;
ReleaseStateMgr* ReleaseStateMgr::GetInstance()
{
	if ( ReleaseStateMgr::m_instance == nullptr )
	{
	    auto mechFactory = MechanismFactory::GetMechanismFactory();
	    auto release = mechFactory->GetRelease();
	    if (release != nullptr)
        {
		    ReleaseStateMgr::m_instance = new ReleaseStateMgr();
        }
	}
	return ReleaseStateMgr::m_instance;
    
}


/// @brief    initialize the state manager, parse the configuration file and create the states.
ExampleStateMgr::ExampleStateMgr() : StateMgr(),
                                     m_example(MechanismFactory::GetMechanismFactory()->GetExample()),
                                     m_nt()
{
    map<string, StateStruc> stateMap;
    stateMap[m_exampleOffXmlString] = m_offState;
    stateMap[m_exampleForwardXmlString] = m_forwardState;
    stateMap[m_exampleReverseXmlString] = m_reverseState;  

    Init(m_example, stateMap);
    if (m_example != nullptr)
    {
        auto m_nt = m_example->GetNetworkTableName();
    }
}   

/// @brief Check if driver inputs or sensors trigger a state transition
void ExampleStateMgr::CheckForStateTransition()
{

    if ( m_example != nullptr )
    {    
        auto currentState = static_cast<EXAMPLE_STATE>(GetCurrentState());
        auto targetState = currentState;

        auto controller = TeleopControl::GetInstance();
        auto isForwardSelected   = controller != nullptr ? controller->IsButtonPressed(TeleopControl::FUNCTION_IDENTIFIER::EXAMPLE_FORWARD) : false;
        auto isReverseSelected   = controller != nullptr ? controller->IsButtonPressed(TeleopControl::FUNCTION_IDENTIFIER::EXAMPLE_REVERSE) : false;

        if (isForwardSelected)
        {
            targetState = EXAMPLE_STATE::FORWARD;
        }
        else if (isReverseSelected)
        {
            targetState = EXAMPLE_STATE::REVERSE;
        }
        else
        {
            targetState = EXAMPLE_STATE::OFF;
        }

        if (targetState != currentState)
        {
            SetCurrentState(targetState, true);
        }
        
    }
}



