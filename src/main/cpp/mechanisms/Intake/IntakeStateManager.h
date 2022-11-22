#include <string>



 

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
        {   {m_intakeOffXmlString, INTAKE_STATE::OFF},
            {m_intakeIntakeXmlString, INTAKE_STATE::INTAKE},
            {m_intakeExpelXmlString, INTAKE_STATE::EXPEL}
        };
        static ShooterStateMgr* GetInstance();
        void CheckForStateTransition() override;
};
protected:
   IntakeState()
   ~IntakeState()

const std::map<const std::string, INTAKE_STATE> m_intakeXmlStringToStateEnumMap
        {   {m_intake_onXmlString, INTAKE_STATE::INTAKE_ON},
            {m_intake_offXmlString, INTAKE_STATE::INTAKE_OFF},
            {m_intakeExpelXmlString, INTAKE_STATE::INTAKE_EXPEL}
        };
