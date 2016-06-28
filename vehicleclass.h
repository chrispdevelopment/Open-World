#ifndef _VEHICLECLASS_H_
#define _VEHICLECLASS_H_

//////////////
// INCLUDES //
//////////////
#include "modelabstractclass.h"

class VehicleClass : public ModelAbstractClass
{
private:
	struct VertexType
	{
		XMFLOAT3 position;
		XMFLOAT2 texture;
		XMFLOAT3 normal;
	};
public:
	VehicleClass();
	VehicleClass(const VehicleClass&);
	~VehicleClass();

	bool Initialize(ID3D11Device*, ID3D11DeviceContext*, char*, const WCHAR*, TextureManagerClass*);
	void Shutdown();

private:
	bool InitializeBuffers(ID3D11Device*);
	void RenderBuffers(ID3D11DeviceContext*);
};

#endif
