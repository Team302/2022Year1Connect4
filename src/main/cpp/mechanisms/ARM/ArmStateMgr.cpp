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
#include <hw/DragonLimelight.h>
#include <hw/factories/LimelightFactory.h>
#include <mechanisms/MechanismFactory.h>
#include <mechanisms/MechanismTypes.h>
#include <mechanisms/base/StateMgr.h>
#include <mechanisms/StateStruc.h>
#include <mechanisms/base/IState.h>
#include <mechanisms\ARM\arm.h>
//#include <mechanisms/example/ExampleState.h>
#include <mechanisms\ARM\ArmStateMgr.h>
#include <utils/Logger.h>
#include <mechanisms/controllers/StateDataXmlParser.h>


// Third Party Includes

using namespace std;

ArmStateMgr* ArmStateMgr::m_instance = nullptr;
ArmStateMgr* ArmStateMgr::GetInstance()
{
	if ( ArmStateMgr::m_instance == nullptr )
	{
	    auto mechFactory = MechanismFactory::GetMechanismFactory();
	    auto arm = mechFactory->GetExample();
	    if (arm != nullptr)
        {
		    ArmStateMgr::m_instance = new ArmStateMgr();
        }
	}
	return ArmStateMgr::m_instance;
    
}

/// @brief    initialize the state manager, parse the configuration file and create the states.
ArmStateMgr::ArmStateMgr() : StateMgr(),
                                     m_arm(MechanismFactory::GetMechanismFactory()->GetExample()),
                                     m_nt()
{
    map<string, StateStruc> stateMap;
    stateMap[m_armOffXmlString] = m_offState;
    stateMap[m_armForwardXmlString] = m_forwardState;
    stateMap[m_exampleReverseXmlString] = m_reverseState;  

    Init(m_example, stateMap);
    if (m_example != nullptr)
    {
        auto m_nt = m_example->GetNetworkTableName();
    }
}   
