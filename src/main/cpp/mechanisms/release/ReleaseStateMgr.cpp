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
#include <mechanisms/release/ReleaseState.h>
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
ReleaseStateMgr::ReleaseStateMgr() : StateMgr(),
                                     m_release(MechanismFactory::GetMechanismFactory()->GetRelease()),
                                     m_nt()
{
    map<string, StateStruc> stateMap;
    stateMap[m_releaseOpenClosedXMLString] = m_openClosedState;
    stateMap[m_releaseOpenOpenXMLString] = m_openOpenState;
    stateMap[m_releaseClosedOpenXmlString] = m_closedOpenState;  
    stateMap[m_releaseClosedClosedXmlString] = m_closedClosedState;

    Init(m_release, stateMap);
    if (m_release != nullptr)
    {
        auto m_nt = m_release->GetNetworkTableName();
    }
}   

/// @brief Check if driver inputs or sensors trigger a state transition
void ReleaseStateMgr::CheckForStateTransition()
{

    if ( m_release != nullptr )
    {    
        auto currentState = static_cast<RELEASE_STATE>(GetCurrentState());
        auto targetState = currentState;

        auto controller = TeleopControl::GetInstance();
        auto isForwardSelected   = controller != nullptr ? controller->IsButtonPressed(TeleopControl::FUNCTION_IDENTIFIER::EXAMPLE_FORWARD) : false;
        auto isReverseSelected   = controller != nullptr ? controller->IsButtonPressed(TeleopControl::FUNCTION_IDENTIFIER::EXAMPLE_REVERSE) : false;

        if (isForwardSelected)
        {
            targetState = RELEASE_STATE::CLOSED_OPEN;
        }
        else if (isReverseSelected)
        {
            targetState = RELEASE_STATE::OPEN_CLOSED;
        }
        else
        {
            targetState = RELEASE_STATE::OPEN_OPEN;
        }

        if (targetState != currentState)
        {
            SetCurrentState(targetState, true);
        }
        
    }
}


