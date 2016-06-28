#ifndef _MODELABSTRACTCLASS_H_
#define _MODELABSTRACTCLASS_H_

//////////////
// INCLUDES //
//////////////
#include <d3d11.h>
#include <directxmath.h>
using namespace DirectX;

#include <fstream>
#include <vector>
using namespace std;

#include "meshloaderclass.h"
#include "texturemanagerclass.h"

////////////////////////////////////////////////////////////////////////////////
// Class name: ModelAbstractClass
////////////////////////////////////////////////////////////////////////////////
class ModelAbstractClass
{
protected:
	struct ModelType
	{
		float x, y, z;
		float tu, tv;
		float nx, ny, nz;
		float tx, ty, tz;
		float bx, by, bz;
		float r, g, b;
	};

	struct VectorType
	{
		float x, y, z;
	};

public:
	ModelAbstractClass();
	ModelAbstractClass(const ModelAbstractClass&);
	~ModelAbstractClass();

	virtual bool Initialize(ID3D11Device*, char* = "", bool = false);
	virtual bool Initialize(ID3D11Device*, ID3D11DeviceContext*, char*, const WCHAR*, TextureManagerClass*);
	virtual void Shutdown() = 0;
	
	int GetIndexCount();
	void Render(ID3D11DeviceContext*);
	bool LoadMesh(char*, const WCHAR* = NULL);

protected:
	virtual bool InitializeBuffers(ID3D11Device*) = 0;
	virtual void RenderBuffers(ID3D11DeviceContext*) = 0;

	void ReleaseBuffers();
	void ReleaseModel();

protected:
	ID3D11Buffer *m_vertexBuffer, *m_indexBuffer;
	MeshLoaderClass *m_meshLoader;
	ModelType* m_model;

	int m_vertexCount, m_indexCount;
public:
	MeshLoaderClass::Material* m_material;
};

#endif
