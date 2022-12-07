#include <map>

// FRC includes

// Team 302 includes
#include <auton/PrimitiveParams.h>
#include <mechanisms/base/StateMgr.h>
#include <mechanisms/MechanismFactory.h>
#include <mechanisms/StateStruc.h>
#include <mechanisms\Intake\IntakeStateManager.h>
#include <TeleopControl.h>

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
                                   m_intake(MechanismFactory::GetMechanismFactory()->GetIntake())
{
    map<string, StateStruc> stateMap;
    stateMap[m_intakeOffXmlString] = m_offState;
    stateMap[m_intakeIntakeXmlString] = m_onState;
    stateMap[m_intakeExpelXmlString] = m_expelState;  

    Init(m_intake, stateMap);
    if (m_intake != nullptr)
    {
        m_intake->AddStateMgr(this);
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

/// @brief  Get the current Parameter parm value for the state of this mechanism
/// @param PrimitiveParams* currentParams current set of primitive parameters
/// @returns int state id - -1 indicates that there is not a state to set
int IntakeStateMgr::GetCurrentStateParam
(
    PrimitiveParams*    currentParams
) 
{
    return currentParams != nullptr ? currentParams->GetIntakeState() : StateMgr::GetCurrentStateParam(currentParams);
}