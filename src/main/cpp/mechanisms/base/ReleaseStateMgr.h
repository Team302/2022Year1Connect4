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
#include <mechanisms\base\StateMgr.h>
#include <mechanisms\StateStruc.h>




// Third Party Includes

class ReleaseStateMgr : public StateMgr
{
    public:
        /// @enum the various states of the Intake
        enum RELEASE_STATE
        {
            OPEN_CLOSED,
            OPEN_OPEN,
            CLOSED_OPEN,
            CLOSED_CLOSED,
            
        };
        const std::string m_releaseOpenClosedXMLString = "RELEASE_OPEN_CLOSED";
        const std::string m_releaseOpenOpenXMLString = "RELEASE_OPEN_OPEN";
        const std::string m_releaseClosedOpenXmlString = "RELEASE_CLOSED_OPEN";
        const std::string m_releaseClosedClosedXmlString = "RELEASE_CLOSED_CLOSED";
        
        const std::map<const std::string, RELEASE_STATE> m_releaseXmlStringToStateEnumMap
        {   {m_releaseOpenClosedXMLString, RELEASE_STATE::OPEN_CLOSED},
            {m_releaseOpenOpenXMLString, RELEASE_STATE::OPEN_OPEN},
            {m_releaseClosedOpenXmlString, RELEASE_STATE::CLOSED_OPEN},
            {m_releaseClosedClosedXmlString, RELEASE_STATE::CLOSED_CLOSED},
        };

        
		/// @brief  Find or create the state manmanager
		/// @return IntakeStateMgr* pointer to the state manager
		static ReleaseStateMgr* GetInstance();

        void CheckForStateTransition() override;
        bool AtTarget() const;
        bool IsShooting() const;
    private:

        ReleaseStateMgr();
        ~ReleaseStateMgr() = default;
        
        std::shared_ptr<nt::NetworkTable>       m_nt;
        bool m_buttonTriggerStateChange;

		static ReleaseStateMgr*	m_instance;

        const StateStruc m_openClosedState = {RELEASE_STATE::OPEN_CLOSED, StateType::RELEASE, false};
        const StateStruc m_openOpenState = {RELEASE_STATE::OPEN_OPEN, StateType::RELEASE, false};
        const StateStruc m_closedOpenState = {RELEASE_STATE::CLOSED_OPEN, StateType::RELEASE, false};
        const StateStruc m_closedClosedState = {RELEASE_STATE::CLOSED_CLOSED, StateType::RELEASE, true};
};