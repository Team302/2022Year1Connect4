
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
#include <frc/Timer.h>
#include <frc/kinematics/ChassisSpeeds.h>

// Team 302 includes
#include <auton/drivePrimitives/IPrimitive.h>
#include <auton/drivePrimitives/SuperDrive.h>
#include <auton/PrimitiveParams.h>
#include <chassis/ChassisFactory.h>
#include <hw/DragonPigeon.h>
#include <hw/factories/PigeonFactory.h>

// Third Party Includes


using namespace std;
using namespace frc;


SuperDrive::SuperDrive() : m_chassis( ChassisFactory::GetChassisFactory()->GetIChassis()),
						   m_timer( make_unique<Timer>() ),
						   m_targetSpeed(0),
						   m_startHeading(0),
						   m_currentTime(0)
{
}

void SuperDrive::Init(PrimitiveParams* params) 
{
	m_targetSpeed = params->GetDriveSpeed() / 12.0; // convert from inches per second to feet per second
	m_currentTime = 0.0;
	m_pigeon = PigeonFactory::GetFactory()->GetPigeon(DragonPigeon::PIGEON_USAGE::CENTER_OF_ROBOT);
	m_startHeading = m_pigeon != nullptr ? m_pigeon->GetYaw() : 0.0;
}

void SuperDrive::Run() 
{
	auto currentHeading = m_pigeon != nullptr ? m_pigeon->GetYaw() : 0.0;
	auto delta = currentHeading - m_startHeading;

	ChassisSpeeds speeds;
	speeds.vx = units::velocity::feet_per_second_t(m_targetSpeed);
	speeds.vy = units::velocity::feet_per_second_t(0.0);
	speeds.omega = units::angular_velocity::degrees_per_second_t(delta * 0.1);
	m_currentTime += IPrimitive::LOOP_LENGTH;
}

bool SuperDrive::IsDone() 
{
	return false;
}


