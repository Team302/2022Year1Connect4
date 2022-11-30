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
#include <hw/factories/LimelightFactory.h>
#include <mechanisms/MechanismFactory.h>
#include <mechanisms/MechanismTypes.h>
#include <mechanisms/base/StateMgr.h>
#include <mechanisms/StateStruc.h>
#include <mechanisms/base/IState.h>
#include <utils/Logger.h>
#include <mechanisms/controllers/StateDataXmlParser.h>
#include <mechanisms\Intake\IntakeStateManager.h>
// Third Party Includes

using namespace std;


IntakeStateMgr* IntakeStateMgr::m_instance = nullptr;
IntakeStateMgr* IntakeStateMgr::GetInstance()
{
	if ( IntakeStateMgr::m_instance == nullptr )
	{
	    auto mechFactory = MechanismFactory::GetMechanismFactory();
	    auto intake = mechFactory->GetExample();
	    if (intake != nullptr)
        {
		    IntakeStateMgr::m_instance = new IntakeStateMgr();
        }
	}
	return IntakeStateMgr::m_instance;
    
}


/// @brief    initialize the state manager, parse the configuration file and create the states.
IntakeStateMgr::IntakeStateMgr() : StateMgr(),
                                     m_intake(MechanismFactory::GetMechanismFactory()->GetIntake()),
                                     m_nt()
{
    map<string, StateStruc> stateMap;
    stateMap[m_intakeOffXmlString] = m_offState;
    stateMap[m_intakeIntakeXmlString] = m_onState;
    stateMap[m_intakeExpelXmlString] = m_expelState;  

    Init(m_intake, stateMap);
    if (m_intake != nullptr)
    {
        auto m_nt = m_intake->GetNetworkTableName();
    }
}   

/// @brief Check if driver inputs or sensors trigger a state transition
void IntakeStateMgr::CheckForStateTransition()
{

    if ( m_intake != nullptr )
    {    
        auto currentState = static_cast<INTAKE_STATE>(GetCurrentState());
        auto targetState = currentState;

        auto controller = TeleopControl::GetInstance();
        auto isOnSelected   = controller != nullptr ? controller->IsButtonPressed(TeleopControl::FUNCTION_IDENTIFIER::INTAKE_ON) : false;
        auto isExpelSelected   = controller != nullptr ? controller->IsButtonPressed(TeleopControl::FUNCTION_IDENTIFIER::INTAKE_EXPEL) : false;

        if (isOnSelected)
        {
            targetState = INTAKE_STATE::INTAKE_ON;
        }
        else if (isExpelSelected)
        {
            targetState = INTAKE_STATE::INTAKE_EXPEL;
        }
        else
        {
            targetState = INTAKE_STATE::INTAKE_OFF;
        }

        if (targetState != currentState)
        {
            SetCurrentState(targetState, true);
        }
        
    }
}
