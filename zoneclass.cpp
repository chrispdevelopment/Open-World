////////////////////////////////////////////////////////////////////////////////
// Filename: zoneclass.cpp
////////////////////////////////////////////////////////////////////////////////
#include "zoneclass.h"


ZoneClass::ZoneClass()
{
	m_UserInterface = 0;
	m_Camera = 0;
	m_Light = 0;
	m_Position = 0;
	m_SkyDome = 0;
	m_Terrain = 0;
	m_Frustum = 0;
	m_Vehicle = 0;

	m_VehiclePostionsLeft = 0;
	m_VehiclePostionsRight = 0;
	m_VehiclePostionsFront = 0;
	m_VehiclePostionsBack = 0;

	m_pitch = 0.0f;
	m_roll = 0.0f;
}


ZoneClass::ZoneClass(const ZoneClass& other)
{
}


ZoneClass::~ZoneClass()
{
}


bool ZoneClass::Initialize(D3DClass* Direct3D, HWND hwnd, TextureManagerClass* textureManager, int screenWidth, int screenHeight, float screenDepth)
{
	bool result;

	m_screenDepth = screenDepth;
	XMFLOAT3 centerPoint;

	// Create the user interface object.
	m_UserInterface = new UserInterfaceClass;
	if (!m_UserInterface)
	{
		return false;
	}

	// Initialize the user interface object.
	result = m_UserInterface->Initialize(Direct3D, screenHeight, screenWidth);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the user interface object.", L"Error", MB_OK);
		return false;
	}

	// Create the camera object.
	m_Camera = new CameraClass;
	if (!m_Camera)
	{
		return false;
	}

	// Set the initial position of the camera and build the matrices needed for rendering.
	m_Camera->SetPosition(0.0f, 0.0f, -10.0f);
	m_Camera->Render();
	m_Camera->RenderBaseViewMatrix();

	// Create the light object.
	m_Light = new LightClass;
	if (!m_Light)
	{
		return false;
	}

	// Initialize the light object.
	m_Light->SetDiffuseColor(1.0f, 1.0f, 1.0f, 1.0f);
	m_Light->SetDirection(-0.5f, -1.0f, -0.5f);

	// Create the position object.
	m_Position = new PositionClass;
	if (!m_Position)
	{
		return false;
	}

	// Set the initial position and rotation.
	m_Position->SetPosition(512.0f, 85.0f, 400.0f);
	m_Position->SetRotation(0.0f, 0.0f, 0.0f);
	m_Position->GetPosition(centerPoint.x, centerPoint.y, centerPoint.z);

	// Setup the inital object postions
	m_initalCenterDir = XMFLOAT3(512.0f, 85.0f, 400.0f);
	m_initalCamDir = XMFLOAT3(m_initalCenterDir.x - 250, m_initalCenterDir.y, m_initalCenterDir.z - 4000);
	m_initalFrontDir = XMFLOAT3(m_initalCenterDir.x, m_initalCenterDir.y, m_initalCenterDir.z + 20);;
	m_initalBackDir = XMFLOAT3(m_initalCenterDir.x, m_initalCenterDir.y, m_initalCenterDir.z - 20);;
	m_initalLeftDir = XMFLOAT3(m_initalCenterDir.x + 20, m_initalCenterDir.y, m_initalCenterDir.z);;
	m_initalRightDir = XMFLOAT3(m_initalCenterDir.x - 20, m_initalCenterDir.y, m_initalCenterDir.z);;

	// Create the frustum object.
	m_Frustum = new FrustumClass;
	if (!m_Frustum)
	{
		return false;
	}

	// Initialize the frustum object.
	m_Frustum->Initialize(screenDepth);

	// Create the sky dome object.
	m_SkyDome = new SkyDomeClass;
	if (!m_SkyDome)
	{
		return false;
	}

	// Initialize the sky dome object.
	result = m_SkyDome->Initialize(Direct3D->GetDevice(), "data/objects/skydome/skyDomeModel.obj");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the sky dome object.", L"Error", MB_OK);
		return false;
	}

	// Create the vehicle object.
	m_Vehicle = new VehicleClass;
	if (!m_Vehicle)
	{
		return false;
	}

	// Initialize the terrain object.
	result = m_Vehicle->Initialize(Direct3D->GetDevice(), Direct3D->GetDeviceContext(), "data/objects/hovercar/hovercar.obj", L"data/objects/hovercar/hovercar.mtl", textureManager);

	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the vehicle object.", L"Error", MB_OK);
		return false;
	}

	// Create the vechicle position objects.
	m_VehiclePostionsFront = new PositionClass;
	if (!m_VehiclePostionsFront)
	{
		return false;
	}

	m_VehiclePostionsFront->SetPosition(centerPoint.x, centerPoint.y, centerPoint.z + 20);
	m_VehiclePostionsFront->SetRotation(0.0f, 90.0f, 0.0f);
	m_VehiclePostionsFront->IsForObject(true);

	m_VehiclePostionsBack = new PositionClass;
	if (!m_VehiclePostionsBack)
	{
		return false;
	}

	m_VehiclePostionsBack->SetPosition(centerPoint.x, centerPoint.y, centerPoint.z - 20);
	m_VehiclePostionsBack->SetRotation(0.0f, 270.0f, 0.0f);
	m_VehiclePostionsBack->IsForObject(true);

	m_VehiclePostionsLeft = new PositionClass;
	if (!m_VehiclePostionsLeft)
	{
		return false;
	}

	m_VehiclePostionsLeft->SetPosition(centerPoint.x - 20, centerPoint.y, centerPoint.z);
	//m_VehiclePostionsLeft->SetRotation(0.0f, 270.0f, 0.0f);
	m_VehiclePostionsLeft->IsForObject(true);

	m_VehiclePostionsRight = new PositionClass;
	if (!m_VehiclePostionsRight)
	{
		return false;
	}

	m_VehiclePostionsRight->SetPosition(centerPoint.x + 20, centerPoint.y, centerPoint.z);
	m_VehiclePostionsRight->SetRotation(0.0f, 180.0f, 0.0f);
	m_VehiclePostionsRight->IsForObject(true);

	// Create the terrain object.
	m_Terrain = new TerrainClass;
	if (!m_Terrain)
	{
		return false;
	}

	// Initialize the terrain object.
	result = m_Terrain->Initialize(Direct3D->GetDevice(), "data/terrainsetup.txt", (!USETERRAINCELLS) ? true : false);

	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the terrain object.", L"Error", MB_OK);
		return false;
	}

	// Set the UI to display by default.
	m_displayUI = true;

	// Set wire frame rendering initially to enabled.
	m_wireFrame = false;

	// Set the rendering of cell lines initially to enabled.
	m_cellLines = true;

	return true;
}


void ZoneClass::Shutdown()
{
	// Release the vehicle object.
	if (m_Vehicle)
	{
		m_Vehicle->Shutdown();
		delete m_Vehicle;
		m_Vehicle = 0;
	}

	// Release the terrain object.
	if (m_Terrain)
	{
		m_Terrain->Shutdown();
		delete m_Terrain;
		m_Terrain = 0;
	}

	// Release the sky dome object.
	if (m_SkyDome)
	{
		m_SkyDome->Shutdown();
		delete m_SkyDome;
		m_SkyDome = 0;
	}

	// Release the frustum object.
	if (m_Frustum)
	{
		delete m_Frustum;
		m_Frustum = 0;
	}

	// Release the vehicle position objects.
	if (m_VehiclePostionsFront)
	{
		delete m_VehiclePostionsFront;
		m_VehiclePostionsFront = 0;
	}

	if (m_VehiclePostionsBack)
	{
		delete m_VehiclePostionsBack;
		m_VehiclePostionsBack = 0;
	}

	if (m_VehiclePostionsLeft)
	{
		delete m_VehiclePostionsLeft;
		m_VehiclePostionsLeft = 0;
	}

	if (m_VehiclePostionsRight)
	{
		delete m_VehiclePostionsRight;
		m_VehiclePostionsRight = 0;
	}

	// Release the position object.
	if (m_Position)
	{
		delete m_Position;
		m_Position = 0;
	}

	// Release the light object.
	if (m_Light)
	{
		delete m_Light;
		m_Light = 0;
	}

	// Release the camera object.
	if (m_Camera)
	{
		delete m_Camera;
		m_Camera = 0;
	}

	// Release the user interface object.
	if (m_UserInterface)
	{
		m_UserInterface->Shutdown();
		delete m_UserInterface;
		m_UserInterface = 0;
	}

	return;
}

bool ZoneClass::Frame(D3DClass* Direct3D, InputClass* Input, ShaderManagerClass* ShaderManager, TextureManagerClass* TextureManager, float frameTime, int fps)
{
	bool result, foundHeight;
	float posX, posY, posZ, rotX, rotY, rotZ, height;;
	XMFLOAT3 cameraPosition;
	XMFLOAT3 postion, postionFront, postionBack, postionLeft, postionRight;
	float centerHeight, frontHeight, backHeight, leftHeight, rightHeight;

	// Do the frame input processing.
	HandleMovementInput(Input, frameTime);

	// Get the view point position/rotation.
	m_Position->GetPosition(posX, posY, posZ);
	m_Position->GetRotation(rotX, rotY, rotZ);

	// Do the frame processing for the user interface.
	result = m_UserInterface->Frame(Direct3D->GetDeviceContext(), fps, posX, posY, posZ, rotX, rotY, rotZ);
	if (!result)
	{
		return false;
	}

	// Do the terrain frame processing.
	m_Terrain->Frame();

	if (USETERRAINCELLS) {
		m_Position->GetPosition(postion.x, postion.y, postion.z);
		foundHeight = m_Terrain->GetHeightAtPosition(postion.x, postion.z, height);
		if (foundHeight)
		{
			// If there was a triangle under the postion object then position the postion object just above it by two units.
			m_Position->SetPosition(postion.x, height + 2.0f, postion.z);
			centerHeight = height + 2.0f;
		}

		m_VehiclePostionsFront->GetPosition(postion.x, postion.y, postion.z);
		foundHeight = m_Terrain->GetHeightAtPosition(postion.x, postion.z, height);
		if (foundHeight)
		{
			// If there was a triangle under the postion object then position the postion object just above it by two units.
			m_VehiclePostionsFront->SetPosition(postion.x, height + 2.0f, postion.z);
			frontHeight = height + 2;
		}

		m_VehiclePostionsBack->GetPosition(postion.x, postion.y, postion.z);
		foundHeight = m_Terrain->GetHeightAtPosition(postion.x, postion.z, height);
		if (foundHeight)
		{
			// If there was a triangle under the postion object then position the postion object just above it by two units.
			m_VehiclePostionsBack->SetPosition(postion.x, height + 2.0f, postion.z);
			backHeight = height + 2;
		}

		/*if (frontHeight < backHeight) {
			m_pitch = (backHeight - frontHeight) / 40;
		}
		else if (frontHeight > backHeight) {
			m_pitch = (backHeight - frontHeight) / 40;
		}
		else {
			m_pitch = 0.0f;
		}*/

		m_pitch = (backHeight - frontHeight) / 40;

		m_VehiclePostionsLeft->GetPosition(postion.x, postion.y, postion.z);
		foundHeight = m_Terrain->GetHeightAtPosition(postion.x, postion.z, height);
		if (foundHeight)
		{
			// If there was a triangle under the postion object then position the postion object just above it by two units.
			m_VehiclePostionsLeft->SetPosition(postion.x, height + 2.0f, postion.z);
			leftHeight = height + 2;
		}

		m_VehiclePostionsRight->GetPosition(postion.x, postion.y, postion.z);
		foundHeight = m_Terrain->GetHeightAtPosition(postion.x, postion.z, height);
		if (foundHeight)
		{
			// If there was a triangle under the postion object then position the postion object just above it by two units.
			m_VehiclePostionsRight->SetPosition(postion.x, height + 2.0f, postion.z);
			rightHeight = height + 2;
		}

		m_roll = (leftHeight - rightHeight) / 40;
	}

	// Render the graphics.
	result = Render(Direct3D, ShaderManager, TextureManager);

	if (!result)
	{
		return false;
	}

	return true;
}


void ZoneClass::HandleMovementInput(InputClass* Input, float frameTime)
{
	bool keyDown;
	float posX, posY, posZ, rotX, rotY, rotZ;

	m_Position->GetPosition(posX, posY, posZ);
	m_Position->GetRotation(rotX, rotY, rotZ);

	// Set the frame time for calculating the updated position.
	m_Position->SetFrameTime(frameTime);
	m_VehiclePostionsFront->SetFrameTime(frameTime);
	m_VehiclePostionsBack->SetFrameTime(frameTime);
	m_VehiclePostionsLeft->SetFrameTime(frameTime);
	m_VehiclePostionsRight->SetFrameTime(frameTime);

	// Handle the input.
	keyDown = Input->IsLeftPressed();
	m_Position->TurnLeft(keyDown);
	m_VehiclePostionsFront->TurnLeft(keyDown);
	m_VehiclePostionsBack->TurnLeft(keyDown);
	m_VehiclePostionsLeft->TurnLeft(keyDown);
	m_VehiclePostionsRight->TurnLeft(keyDown);

	keyDown = Input->IsRightPressed();
	m_Position->TurnRight(keyDown);
	m_VehiclePostionsFront->TurnRight(keyDown);
	m_VehiclePostionsBack->TurnRight(keyDown);
	m_VehiclePostionsLeft->TurnRight(keyDown);
	m_VehiclePostionsRight->TurnRight(keyDown);

	keyDown = Input->IsUpPressed();
	m_Position->MoveForward(keyDown);
	m_VehiclePostionsFront->MoveForward(keyDown, rotY);
	m_VehiclePostionsBack->MoveForward(keyDown, rotY);
	m_VehiclePostionsLeft->MoveForward(keyDown, rotY);
	m_VehiclePostionsRight->MoveForward(keyDown, rotY);

	keyDown = Input->IsDownPressed();
	m_Position->MoveBackward(keyDown);
	m_VehiclePostionsFront->MoveBackward(keyDown);
	m_VehiclePostionsBack->MoveBackward(keyDown);
	m_VehiclePostionsLeft->MoveBackward(keyDown);
	m_VehiclePostionsRight->MoveBackward(keyDown);

	// Get the view point position/rotation.
	m_Position->GetPosition(posX, posY, posZ);
	m_Position->GetRotation(rotX, rotY, rotZ);

	// Set the lookat of the camera.
	m_Camera->SetLookAt(posX, posY, posZ);

	// Determine if the user interface should be displayed or not.
	if (Input->IsF1Toggled())
	{
		m_displayUI = !m_displayUI;
	}

	// Determine if the terrain should be rendered in wireframe or not.
	if (Input->IsF2Toggled())
	{
		m_wireFrame = !m_wireFrame;
	}

	// Determine if we should render the lines around each terrain cell.
	if (Input->IsF3Toggled())
	{
		m_cellLines = !m_cellLines;
	}

	return;
}


bool ZoneClass::Render(D3DClass* Direct3D, ShaderManagerClass* ShaderManager, TextureManagerClass* TextureManager)
{
	XMMATRIX worldMatrix, viewMatrix, projectionMatrix, baseViewMatrix, orthoMatrix;
	bool result;
	XMFLOAT3 cameraPosition;
	XMFLOAT3 postion;
	int i;

	// Generate the view matrix based on the camera's position.
	m_Camera->Render();

	// Get the world, view, and projection matrices from the camera and d3d objects.
	Direct3D->GetWorldMatrix(worldMatrix);
	m_Camera->GetViewMatrix(viewMatrix);
	Direct3D->GetProjectionMatrix(projectionMatrix);
	m_Camera->GetBaseViewMatrix(baseViewMatrix);
	Direct3D->GetOrthoMatrix(orthoMatrix);

	// Get the position of the camera.
	cameraPosition = m_Camera->GetPosition();
	m_Position->GetPosition(postion.x, postion.y, postion.z);

	// Construct the frustum.
	m_Frustum->ConstructFrustum(projectionMatrix, viewMatrix);

	// Clear the buffers to begin the scene.
	Direct3D->BeginScene(0.0f, 0.0f, 0.0f, 1.0f);

	// Turn off back face culling and turn off the Z buffer.
	Direct3D->TurnOffCulling();
	Direct3D->TurnZBufferOff();

	// Translate the sky dome to be centered around the camera position.
	worldMatrix = XMMatrixTranslation(cameraPosition.x, cameraPosition.y, cameraPosition.z);

	// Render the sky dome using the sky dome shader.
	m_SkyDome->Render(Direct3D->GetDeviceContext());
	result = ShaderManager->RenderSkyDomeShader(Direct3D->GetDeviceContext(), m_SkyDome->GetIndexCount(), worldMatrix, viewMatrix,
		projectionMatrix, m_SkyDome->GetApexColor(), m_SkyDome->GetCenterColor());
	if (!result)
	{
		return false;
	}

	// Reset the world matrix.
	Direct3D->GetWorldMatrix(worldMatrix);

	//// Turn the Z buffer back and back face culling on.
	Direct3D->TurnZBufferOn();
	Direct3D->TurnOnCulling();

	// Turn on wire frame rendering of the terrain if needed.
	if (m_wireFrame)
	{
		Direct3D->EnableWireframe();
	}

	// Render the terrain cells (and cell lines if needed).
	for (i = 0; i < m_Terrain->GetCellCount(); i++)
	{
		// Render each terrain cell if it is visible only.
		result = m_Terrain->RenderCell(Direct3D->GetDeviceContext(), i, m_Frustum);
		if (result)
		{
			// Render the cell buffers using the terrain shader.
			result = ShaderManager->RenderTerrainShader(Direct3D->GetDeviceContext(), m_Terrain->GetCellIndexCount(i), worldMatrix, viewMatrix, projectionMatrix,
				TextureManager->GetTexture("terrainGrass", "diffuse"), TextureManager->GetTexture("terrainRock", "diffuse"), TextureManager->GetTexture("terrainSlope", "diffuse"),
				TextureManager->GetTexture("terrainGrass", "normal"), TextureManager->GetTexture("terrainRock", "normal"), TextureManager->GetTexture("terrainSlope", "normal"),
				m_Light->GetDirection(), m_Light->GetDiffuseColor());
			if (!result)
			{
				return false;
			}

			// If needed then render the bounding box around this terrain cell using the color shader. 
			if (m_cellLines)
			{
				m_Terrain->RenderCellLines(Direct3D->GetDeviceContext(), i);
				ShaderManager->RenderColorShader(Direct3D->GetDeviceContext(), m_Terrain->GetCellLinesIndexCount(i), worldMatrix,
					viewMatrix, projectionMatrix);
				if (!result)
				{
					return false;
				}
			}
		}
	}

	// Reset the world matrix.
	Direct3D->GetWorldMatrix(worldMatrix);

	XMMATRIX vehicleRotation, vehicleTranslation, vehicleScale, vehicleWorld;
	XMFLOAT3 rot;

	m_Position->GetRotation(rot.x, rot.y, rot.z);

	float pitch = m_pitch * 0.0174532925f;
	float yaw = rot.y * 0.0174532925f;
	float roll = m_roll * 0.0174532925f;

	vehicleTranslation = XMMatrixTranslation(postion.x, postion.y, postion.z);
	vehicleScale = XMMatrixScaling(0.01f, 0.01f, 0.01f);
	vehicleRotation = XMMatrixRotationRollPitchYaw(m_pitch, yaw, m_roll);
	worldMatrix = vehicleScale * vehicleRotation * vehicleTranslation;

	m_Vehicle->Render(Direct3D->GetDeviceContext());
	result = ShaderManager->RenderVehicleShader(Direct3D->GetDeviceContext(), m_Vehicle->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix, 
		TextureManager->GetTexture("vehicle", "diffuse"), m_Light->GetDirection(), 
		m_Vehicle->m_material->vAmbient, m_Vehicle->m_material->vDiffuse, 
		XMFLOAT4(m_Camera->GetPosition().x, m_Camera->GetPosition().y, m_Camera->GetPosition().z, 0), m_Vehicle->m_material->vSpecular, m_Vehicle->m_material->nShininess);
	if (!result)
	{
		return false;
	}

	XMVECTOR vecCameraNewDir;
	vecCameraNewDir = XMVector3TransformCoord(XMLoadFloat3(&m_initalCamDir), vehicleRotation);
	vecCameraNewDir = XMVector3Normalize(vecCameraNewDir);

	vecCameraNewDir *= 35;

	cameraPosition.x = postion.x + XMVectorGetX(vecCameraNewDir);
	cameraPosition.y = postion.y + XMVectorGetY(vecCameraNewDir) + 5;
	cameraPosition.z = postion.z + XMVectorGetZ(vecCameraNewDir);

	m_Camera->SetPosition(cameraPosition.x, cameraPosition.y, cameraPosition.z);

	// Turn off wire frame rendering of the terrain if it was on.
	if (m_wireFrame)
	{
		Direct3D->DisableWireframe();
	}

	// Reset the world matrix.
	Direct3D->GetWorldMatrix(worldMatrix);

	// Update the render counts in the UI.
	result = m_UserInterface->UpdateRenderCounts(Direct3D->GetDeviceContext(), m_Terrain->GetRenderCount(), m_Terrain->GetCellsDrawn(), m_Terrain->GetCellsCulled());
	if (!result)
	{
		return false;
	}

	// Render the user interface.
	if (m_displayUI)
	{
		result = m_UserInterface->Render(Direct3D, ShaderManager, worldMatrix, baseViewMatrix, orthoMatrix);
		if (!result)
		{
			return false;
		}
	}

	// Present the rendered scene to the screen.
	Direct3D->EndScene();

	return true;
}