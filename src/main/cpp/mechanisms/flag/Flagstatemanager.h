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
#include <string>

// FRC includes
#include <networktables/NetworkTable.h>
#include <frc/Timer.h>

// Team 302 includes
#include <mechanisms/base/StateMgr.h>
#include <mechanisms/example/Example.h>
#include <mechanisms/StateStruc.h>




// Third Party Includes
class Flagarm;

class Flagstatemanager : public StateMgr
{
    public:
        /// @enum the various states of the Intake
        enum FLAG_ARM
        {
            Open,
            Closed
            
        };
        const std::string m_OpenXmlString = "Open";
        const std::string m_ClosedXmlString = "Closed";
        
        const std::map<const std::string, Flagstatemanager> m_FlagXmlStringToStateEnumMap
        {   {m_OpenXmlString, Flagstatemanager::Open},
            {m_ClosedXmlString, Flagstatemanager::Closed}
        };

        
		/// @brief  Find or create the state manmanager
		/// @return IntakeStateMgr* pointer to the state manager
		static Flagstatemanager* GetInstance();

        /// @brief Check if driver inputs or sensors trigger a state transition
        void CheckForStateTransition() override;
    private:

        Flagstatemanager();
        ~Flagstatemanager() = default;
        Flagarm*                               m_Flagarm;
        std::shared_ptr<nt::NetworkTable>       m_nt;

        static Flagstatemanager* m_instance;

        const double m_CHANGE_STATE_TARGET = 120.0; 
		static flagstatemanager*	m_instance;
        const StateStruc m_open = {Flagstatemanager::Open, StateType::Flag_State, true};
        const StateStruc m_closed = {Flagstatemanager::Closed, StateType::Flag_State, false};