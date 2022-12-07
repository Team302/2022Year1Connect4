#pragma once
#include <string>
#include <mechanisms/base/StateMgr.h>
#include <mechanisms/StateStruc.h>

 
class Intake;
class PrimitiveParams;

class IntakeStateMgr : public StateMgr
{
    public:
        /// @enum the various states of the Intake
        enum INTAKE_STATE
        {
            OFF,
            INTAKE_OFF,
            INTAKE_ON,
            INTAKE_EXPEL
        };

        const std::string m_intakeOffXmlString = "INTAKE_OFF";
        const std::string m_intakeIntakeXmlString = "INTAKE_ON";
        const std::string m_intakeExpelXmlString = "INTAKE_EXPEL";
        
        
        const std::map<const std::string, INTAKE_STATE> m_intakeXmlStringToStateEnumMap
        {   {m_intakeOffXmlString, INTAKE_STATE::INTAKE_OFF},
            {m_intakeIntakeXmlString, INTAKE_STATE::INTAKE_ON},
            {m_intakeExpelXmlString, INTAKE_STATE::INTAKE_EXPEL}
        };
        static IntakeStateMgr* GetInstance();
        void CheckForStateTransition() override;

        /// @brief  Get the current Parameter parm value for the state of this mechanism
        /// @param PrimitiveParams* currentParams current set of primitive parameters
        /// @returns int state id - -1 indicates that there is not a state to set
        int GetCurrentStateParam
        (
            PrimitiveParams*    currentParams
        ) override;

    private:
        IntakeStateMgr();
        ~IntakeStateMgr() = default;

        Intake*                                m_intake;

        static IntakeStateMgr*	m_instance;
        const StateStruc m_offState = {INTAKE_STATE::INTAKE_OFF, StateType::INTAKE_STATE, false};
        const StateStruc m_onState = {INTAKE_STATE::INTAKE_ON, StateType::INTAKE_STATE, true};
        const StateStruc m_expelState = {INTAKE_STATE::INTAKE_EXPEL, StateType::INTAKE_STATE, false};
};
