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

// Team 302 includes
#include <hw/DragonServo.h>
#include <mechanisms/base/Mech.h>
#include <mechanisms/base/Mech2Servos.h>
#include <utils/Logger.h>
#include <mechanisms/release/release.h>

using namespace std;

release::release
(
    std::string                                 controlFileName,
    std::string                                 networkTableName,
    DragonServo*                                servo,
    DragonServo*                                servo2
) : Mech2Servos(MechanismTypes::MECHANISM_TYPE::RELEASE, controlFileName, networkTableName, servo, servo2),
    m_servo(servo)
{
    if (m_servo == nullptr )
    {
        Logger::GetLogger()->LogData( LOGGER_LEVEL::ERROR_ONCE, networkTableName, string( "release constructor" ), string( "servo is nullptr" ) );
    }
}

void release::SetAngle
(
    double angle       
) 
{
    if ( m_servo != nullptr )
    {
        m_servo->SetAngle( angle );
    }
}
/// @brief      Move servo to the desired angle
/// @param [in] double angle: Target angle in degrees
/// @return     void
void release::SetAngle2
(
    double angle       
) 
{
    if ( m_servo2 != nullptr )
    {
        m_servo2->SetAngle( angle );
    }
}

double release::GetAngle() const
{
    if ( m_servo != nullptr )
    {
        return m_servo->GetAngle();
    }
    return 0.0;
}

double release::GetAngle2() const
{
    if ( m_servo2 != nullptr )
    {
        return m_servo2->GetAngle();
    }
    return 0.0;
}