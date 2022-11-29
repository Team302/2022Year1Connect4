
//====================================================================================================================================================
// Copyright 2022 Lake Orion Robotics FIRST Team 302 
//
// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"),
// to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense,
// and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
// MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
// DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE
// OR OTHER DEALINGS IN THE SOFTWARE.
//====================================================================================================================================================


// C++ Includes
#include <memory>
#include <string>

// FRC includes
#include <networktables/NetworkTableInstance.h>
#include <networktables/NetworkTable.h>
#include <networktables/NetworkTableEntry.h>

// Team 302 includes
#include <mechanisms/base/Mech.h>
#include <mechanisms/base/Mech1IndMotor.h>
#include <mechanisms/base/Mech2IndMotors.h>
#include <mechanisms/controllers/ControlData.h>
#include <hw/interfaces/IDragonMotorController.h>
#include <utils/Logger.h>
#include <mechanisms/Intake/intake.h>
// Third Party Includes
#include <units/time.h>

using namespace std;

/// @brief Create a generic mechanism wiht 2 independent motors 
/// @param [in] MechanismTypes::MECHANISM_TYPE the type of mechansim
/// @param [in] std::string the name of the file that will set control parameters for this mechanism
/// @param [in] std::string the name of the network table for logging information
/// @param [in] std::shared_ptr<IDragonMotorController> primary motor used by this mechanism
/// @param [in] std::shared_ptr<IDragonMotorController> secondary motor used by this mechanism
Intake::Intake
(
    MechanismTypes::MECHANISM_TYPE              type,
    std::string                                 controlFileName,
    std::string                                 networkTableName,
    shared_ptr<IDragonMotorController>          primaryMotor,
    shared_ptr<IDragonMotorController>          secondaryMotor
) : Mech(type, controlFileName, networkTableName),
    m_primaryMotor( primaryMotor),
    m_secondaryMotor( secondaryMotor)
    
{
    if ( primaryMotor.get() == nullptr )
    {
        Logger::GetLogger()->LogData( LOGGER_LEVEL::ERROR_ONCE, networkTableName, string( "Mech2IndMotors constructor" ), string( "failed to create primary control" ) );
    }    
    
    if ( secondaryMotor.get() == nullptr )
    {
        Logger::GetLogger()->LogData( LOGGER_LEVEL::ERROR_ONCE, networkTableName, string( "Mech2IndMotors constructor" ), string( "failed to create secondary control" ) );
    }
}



