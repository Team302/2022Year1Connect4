#pragma once
#include <string>
#include <mechanisms/base/StateMgr.h>
#include <mechanisms/example/Example.h>
#include <mechanisms/StateStruc.h>
#include <networktables/NetworkTable.h>
#include <frc/Timer.h>
#include <mechanisms\Intake\Intake.h>

 
class Intake;

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

    private:
        IntakeStateMgr();
        ~IntakeStateMgr() = default;

        Intake*                                m_intake;

        static IntakeStateMgr*	m_instance;
        const StateStruc m_offState = {INTAKE_STATE::INTAKE_OFF, StateType::INTAKE_STATE, true};
        const StateStruc m_onState = {INTAKE_STATE::INTAKE_ON, StateType::INTAKE_STATE, false};
        const StateStruc m_expelState = {INTAKE_STATE::INTAKE_EXPEL, StateType::INTAKE_STATE, false};
};
