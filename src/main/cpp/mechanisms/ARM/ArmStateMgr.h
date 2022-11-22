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

// FRC includes
#include <networktables/NetworkTable.h>
#include <frc/Timer.h>

// Team 302 includes
#include <states/StateMgr.h>
#include <states/StateStruc.h>
#include <hw/DragonLimelight.h>
#include <subsys/Shooter.h>




// Third Party Includes

class ShooterStateMgr : public StateMgr
{
    public:
        /// @enum the various states of the Intake
        enum ARM_STATE
        {
           
        };
        const std::string  = "";
        const std::string  = "";
        const std::string  = "";
        const std::string  = "";
        const std::string  = "";
        const std::string  = "";
        
        const std::map<const std::string, SHOOTER_STATE> m_shooterXmlStringToStateEnumMap
        {   {m_shooterOffXmlString, SHOOTER_STATE::OFF},
            {m_shooterHighGoalCloseXmlString, SHOOTER_STATE::AUTO_SHOOT_HIGH_GOAL_CLOSE},
            {m_shooterHighGoalFarXmlString, SHOOTER_STATE::AUTO_SHOOT_HIGH_GOAL_FAR},
            {m_shooterLowGoalXmlString, SHOOTER_STATE::SHOOT_LOW_GOAL},
            {m_shooterManualXmlString, SHOOTER_STATE::SHOOT_MANUAL},
            {m_shooterPrepareXmlString, SHOOTER_STATE::PREPARE_TO_SHOOT}
        };

        
		/// @brief  Find or create the state manmanager
		/// @return IntakeStateMgr* pointer to the state manager
		static ShooterStateMgr* GetInstance();

        void CheckForStateTransition() override;
};