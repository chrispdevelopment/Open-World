////////////////////////////////////////////////////////////////////////////////
// Filename: positionclass.cpp
////////////////////////////////////////////////////////////////////////////////
#include "positionclass.h"


PositionClass::PositionClass()
{
	m_positionX = 0.0f;
	m_positionY = 0.0f;
	m_positionZ = 0.0f;
	
	m_rotationX = 0.0f;
	m_rotationY = 0.0f;
	m_rotationZ = 0.0f;

	m_frameTime = 0.0f;

	m_forwardSpeed   = 0.0f;
	m_backwardSpeed  = 0.0f;
	m_upwardSpeed    = 0.0f;
	m_downwardSpeed  = 0.0f;
	m_leftTurnSpeed  = 0.0f;
	m_rightTurnSpeed = 0.0f;
	m_lookUpSpeed    = 0.0f;
	m_lookDownSpeed  = 0.0f;

	m_forObject = false;
}


PositionClass::PositionClass(const PositionClass& other)
{
}


PositionClass::~PositionClass()
{
}


void PositionClass::SetPosition(float x, float y, float z)
{
	m_positionX = x;
	m_positionY = y;
	m_positionZ = z;
	return;
}


void PositionClass::SetRotation(float x, float y, float z)
{
	m_rotationX = x;
	m_rotationY = y;
	m_rotationZ = z;
	return;
}


void PositionClass::GetPosition(float& x, float& y, float& z)
{
	x = m_positionX;
	y = m_positionY;
	z = m_positionZ;
	return;
}


void PositionClass::GetRotation(float& x, float& y, float& z)
{
	x = m_rotationX;
	y = m_rotationY;
	z = m_rotationZ;
	return;
}


void PositionClass::SetFrameTime(float time)
{
	m_frameTime = time;
	return;
}


void PositionClass::MoveForward(bool keydown, float baseRoation)
{
	float radians;


	// Update the forward speed movement based on the frame time and whether the user is holding the key down or not.
	if(keydown)
	{
		m_forwardSpeed += m_frameTime * 1.0f;
		if(m_forwardSpeed > (m_frameTime * 50.0f))
		{
			m_forwardSpeed = m_frameTime * 50.0f;
		}
	}
	else
	{
		m_forwardSpeed -= m_frameTime * 0.5f;

		if(m_forwardSpeed < 0.0f)
		{
			m_forwardSpeed = 0.0f;
		}
	}

	if (m_forObject) 
	{
		// Convert degrees to radians.
		radians = baseRoation * 0.0174532925f;
	}
	else {
		radians = m_rotationY * 0.0174532925f;
	}
	

	// Update the position.
	m_positionX += sinf(radians) * m_forwardSpeed;
	m_positionZ += cosf(radians) * m_forwardSpeed;

	return;
}


void PositionClass::MoveBackward(bool keydown, float baseRoation)
{
	float radians;


	// Update the backward speed movement based on the frame time and whether the user is holding the key down or not.
	if(keydown)
	{
		m_backwardSpeed += m_frameTime * 1.0f;

		if(m_backwardSpeed > (m_frameTime * 50.0f))
		{
			m_backwardSpeed = m_frameTime * 50.0f;
		}
	}
	else
	{
		m_backwardSpeed -= m_frameTime * 0.5f;
		
		if(m_backwardSpeed < 0.0f)
		{
			m_backwardSpeed = 0.0f;
		}
	}

	if (m_forObject)
	{
		// Convert degrees to radians.
		radians = baseRoation * 0.0174532925f;
	}
	else {
		radians = m_rotationY * 0.0174532925f;
	}

	// Update the position.
	m_positionX -= sinf(radians) * m_backwardSpeed;
	m_positionZ -= cosf(radians) * m_backwardSpeed;

	return;
}


void PositionClass::MoveUpward(bool keydown)
{
	// Update the upward speed movement based on the frame time and whether the user is holding the key down or not.
	if(keydown)
	{
		m_upwardSpeed += m_frameTime * 1.5f;

		if(m_upwardSpeed > (m_frameTime * 15.0f))
		{
			m_upwardSpeed = m_frameTime * 15.0f;
		}
	}
	else
	{
		m_upwardSpeed -= m_frameTime * 0.5f;

		if(m_upwardSpeed < 0.0f)
		{
			m_upwardSpeed = 0.0f;
		}
	}

	// Update the height position.
	m_positionY += m_upwardSpeed;

	return;
}


void PositionClass::MoveDownward(bool keydown)
{
	// Update the downward speed movement based on the frame time and whether the user is holding the key down or not.
	if(keydown)
	{
		m_downwardSpeed += m_frameTime * 1.5f;

		if(m_downwardSpeed > (m_frameTime * 15.0f))
		{
			m_downwardSpeed = m_frameTime * 15.0f;
		}
	}
	else
	{
		m_downwardSpeed -= m_frameTime * 0.5f;

		if(m_downwardSpeed < 0.0f)
		{
			m_downwardSpeed = 0.0f;
		}
	}

	// Update the height position.
	m_positionY -= m_downwardSpeed;

	return;
}


void PositionClass::TurnLeft(bool keydown)
{
	float radians;

	// Update the left turn speed movement based on the frame time and whether the user is holding the key down or not.
	if(keydown)
	{
		m_leftTurnSpeed += m_frameTime * 5.0f;

		if(m_leftTurnSpeed > (m_frameTime * 150.0f))
		{
			m_leftTurnSpeed = m_frameTime * 150.0f;
		}
	}
	else
	{
		m_leftTurnSpeed -= m_frameTime* 3.5f;

		if(m_leftTurnSpeed < 0.0f)
		{
			m_leftTurnSpeed = 0.0f;
		}
	}

	m_rotationY -= m_leftTurnSpeed;

	// Keep the rotation in the 0 to 360 range.
	if (m_rotationY > 360.0f)
	{
		m_rotationY = 0.0f;
	}

	if (m_forObject) {

		float test;

		// Convert degrees to radians.
		radians = m_rotationY * 0.0174532925f;

		if (m_leftTurnSpeed > 0)
		{
			m_positionX -= sinf(radians) * m_leftTurnSpeed;
			m_positionZ -= cosf(radians) * m_leftTurnSpeed;
		}

	}
	

	return;
}

void PositionClass::IsForObject(bool forObject) 
{
	m_forObject = forObject;
}

void PositionClass::TurnRight(bool keydown)
{
	float radians, rotation;

	// Update the right turn speed movement based on the frame time and whether the user is holding the key down or not.
	if(keydown)
	{
		m_rightTurnSpeed += m_frameTime * 5.0f;

		if(m_rightTurnSpeed > (m_frameTime * 150.0f))
		{
			m_rightTurnSpeed = m_frameTime * 150.0f;
		}
	}
	else
	{
		m_rightTurnSpeed -= m_frameTime* 3.5f;

		if(m_rightTurnSpeed < 0.0f)
		{
			m_rightTurnSpeed = 0.0f;
		}
	}

	m_rotationY += m_rightTurnSpeed;

	// Keep the rotation in the 0 to 360 range.
	if (m_rotationY > 360.0f)
	{
		m_rotationY = 0.0f;
	}

	if (m_forObject) {

		float test;

		// Convert degrees to radians.
		radians = m_rotationY * 0.0174532925f;

		if (m_rightTurnSpeed > 0)
		{
			m_positionX += sinf(radians) * m_rightTurnSpeed;
			m_positionZ += cosf(radians) * m_rightTurnSpeed;
		}
		
	}

	return;
}


void PositionClass::LookUpward(bool keydown)
{
	// Update the upward rotation speed movement based on the frame time and whether the user is holding the key down or not.
	if(keydown)
	{
		m_lookUpSpeed += m_frameTime * 7.5f;

		if(m_lookUpSpeed > (m_frameTime * 75.0f))
		{
			m_lookUpSpeed = m_frameTime * 75.0f;
		}
	}
	else
	{
		m_lookUpSpeed -= m_frameTime* 2.0f;

		if(m_lookUpSpeed < 0.0f)
		{
			m_lookUpSpeed = 0.0f;
		}
	}

	// Update the rotation.
	m_rotationX -= m_lookUpSpeed;

	// Keep the rotation maximum 90 degrees.
	if(m_rotationX > 90.0f)
	{
		m_rotationX = 90.0f;
	}

	return;
}


void PositionClass::LookDownward(bool keydown)
{
	// Update the downward rotation speed movement based on the frame time and whether the user is holding the key down or not.
	if(keydown)
	{
		m_lookDownSpeed += m_frameTime * 7.5f;

		if(m_lookDownSpeed > (m_frameTime * 75.0f))
		{
			m_lookDownSpeed = m_frameTime * 75.0f;
		}
	}
	else
	{
		m_lookDownSpeed -= m_frameTime* 2.0f;

		if(m_lookDownSpeed < 0.0f)
		{
			m_lookDownSpeed = 0.0f;
		}
	}

	// Update the rotation.
	m_rotationX += m_lookDownSpeed;

	// Keep the rotation maximum 90 degrees.
	if(m_rotationX < -90.0f)
	{
		m_rotationX = -90.0f;
	}

	return;
}