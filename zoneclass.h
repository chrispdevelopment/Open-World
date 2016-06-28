////////////////////////////////////////////////////////////////////////////////
// Filename: zoneclass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _ZONECLASS_H_
#define _ZONECLASS_H_

const bool USETERRAINCELLS = true;

///////////////////////
// MY CLASS INCLUDES //
///////////////////////
#include "d3dclass.h"
#include "inputclass.h"
#include "shadermanagerclass.h"
#include "texturemanagerclass.h"
#include "timerclass.h"
#include "userinterfaceclass.h"
#include "cameraclass.h"
#include "lightclass.h"
#include "positionclass.h"
#include "skydomeclass.h"
#include "terrainclass.h"
#include "frustumclass.h"
#include "vehicleclass.h"

////////////////////////////////////////////////////////////////////////////////
// Class name: ZoneClass
////////////////////////////////////////////////////////////////////////////////
class ZoneClass
{
public:
	ZoneClass();
	ZoneClass(const ZoneClass&);
	~ZoneClass();

	bool Initialize(D3DClass*, HWND, TextureManagerClass*, int, int, float);
	void Shutdown();
	bool Frame(D3DClass*, InputClass*, ShaderManagerClass*, TextureManagerClass*, float, int);

private:
	void HandleMovementInput(InputClass*, float);
	bool Render(D3DClass*, ShaderManagerClass*, TextureManagerClass*);

private:
	UserInterfaceClass* m_UserInterface;
	CameraClass* m_Camera;
	LightClass* m_Light;
	PositionClass* m_Position;
	SkyDomeClass* m_SkyDome;
	TerrainClass* m_Terrain;
	FrustumClass* m_Frustum;
	VehicleClass* m_Vehicle;
	bool m_displayUI, m_wireFrame, m_cellLines;
	float m_screenDepth;
	XMFLOAT3 m_initalCamDir, m_initalCenterDir, m_initalFrontDir, m_initalBackDir, m_initalLeftDir, m_initalRightDir;
	float m_pitch;
	float m_roll;

	PositionClass* m_VehiclePostionsLeft;
	PositionClass* m_VehiclePostionsRight;
	PositionClass* m_VehiclePostionsFront;
	PositionClass* m_VehiclePostionsBack;
};

#endif