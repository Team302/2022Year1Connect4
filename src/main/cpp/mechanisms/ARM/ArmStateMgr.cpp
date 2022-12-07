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
#include <auton/PrimitiveParams.h>
#include <mechanisms/controllers/MechanismTargetData.h>
#include <mechanisms/MechanismFactory.h>
#include <mechanisms/ARM/arm.h>
#include <mechanisms/ARM/ArmStateMgr.h>
#include <TeleopControl.h>

// Third Party Includes

using namespace std;

ArmStateMgr *ArmStateMgr::m_instance = nullptr;
ArmStateMgr *ArmStateMgr::GetInstance()
{
    if (ArmStateMgr::m_instance == nullptr)
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
                             m_arm(MechanismFactory::GetMechanismFactory()->GetArm()),
                             m_nt()
{
    map<string, StateStruc> stateMap;
    stateMap[m_armOFFXmlString] = m_offState;
    stateMap[m_armARM_UPXmlString] = m_upState;
    stateMap[m_armARM_DOWNXmlString] = m_downState;
    stateMap[m_armARM_MOVING_UPXmlString] = m_movingDownState;
    stateMap[m_armARM_MOVING_DOWNXmlString] = m_movingUpState;

    Init(m_arm, stateMap);
    if (m_arm != nullptr)
    {
        auto m_nt = m_arm->GetNetworkTableName();
    }
}

/// @brief Check if driver inputs or sensors trigger a state transition
void ArmStateMgr::CheckForStateTransition()
{

    if (m_arm != nullptr)
    {
        auto currentState = static_cast<ARM_STATE>(GetCurrentState());
        auto targetState = currentState;

        auto controller = TeleopControl::GetInstance();
        auto isForwardSelected = controller != nullptr ? controller->IsButtonPressed(TeleopControl::FUNCTION_IDENTIFIER::EXAMPLE_FORWARD) : false;
        auto isReverseSelected = controller != nullptr ? controller->IsButtonPressed(TeleopControl::FUNCTION_IDENTIFIER::EXAMPLE_REVERSE) : false;

        if (isForwardSelected)
        {
            targetState = ARM_STATE::MOVING_UP;
        }
        else if (isReverseSelected)
        {
            targetState = ARM_STATE::MOVING_DOWN;
        }
        else
        {
            targetState = ARM_STATE::OFF;
        }

        if (targetState != currentState)
        {
            SetCurrentState(targetState, true);
        }
    }
}

/// @brief  Get the current Parameter parm value for the state of this mechanism
/// @param PrimitiveParams* currentParams current set of primitive parameters
/// @returns int state id - -1 indicates that there is not a state to set
int ArmStateMgr::GetCurrentStateParam
(
    PrimitiveParams*    currentParams
) 
{
    return currentParams != nullptr ? currentParams->GetArmState() : StateMgr::GetCurrentStateParam(currentParams);
}
