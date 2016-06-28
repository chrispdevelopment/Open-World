#ifndef _SKYDOMECLASS_H_
#define _SKYDOMECLASS_H_

//////////////
// INCLUDES //
//////////////
#include "modelabstractclass.h"

class SkyDomeClass : public ModelAbstractClass
{
private:

	struct VertexType
	{
		XMFLOAT3 position;
	};

public:
	SkyDomeClass();
	SkyDomeClass(const SkyDomeClass&);
	~SkyDomeClass();

	bool Initialize(ID3D11Device*, char*, bool = false);
	void Shutdown();

	XMFLOAT4 GetApexColor();
	XMFLOAT4 GetCenterColor();

private:
	bool InitializeBuffers(ID3D11Device*);
	void RenderBuffers(ID3D11DeviceContext*);

private:
	XMFLOAT4 m_apexColor, m_centerColor;
};

#endif