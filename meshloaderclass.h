#ifndef _MESHLOADERCLASS_H_
#define _MESHLOADERCLASS_H_

/////////////
// GLOBALS //
/////////////

///////////////////////
// MY CLASS INCLUDES //
///////////////////////
#include <d3d11.h>
#include <directxmath.h>
#include <fstream>
using namespace DirectX;
using namespace std;

#include <vector>

////////////////////////////////////////////////////////////////////////////////
// Class name: MeshLoaderClass
////////////////////////////////////////////////////////////////////////////////
class MeshLoaderClass
{
private:
	struct CordType
	{
		float x, y, z;
	};

	struct FaceType
	{
		int vIndex1, vIndex2, vIndex3;
		int tIndex1, tIndex2, tIndex3;
		int nIndex1, nIndex2, nIndex3;
	};
public:
	struct MeshType
	{
		float x, y, z;
		float tu, tv;
		float nx, ny, nz;
	};

	struct Material
	{
		WCHAR   materialName[MAX_PATH];

		XMFLOAT4 vAmbient;
		XMFLOAT4 vDiffuse;
		XMFLOAT4 vSpecular;

		int nShininess;
		float fAlpha;

		bool bSpecular;

		WCHAR diffuseTexture[MAX_PATH];
		WCHAR illumTexture[MAX_PATH];
	};

public:
	MeshLoaderClass();
	MeshLoaderClass(const MeshLoaderClass&);
	~MeshLoaderClass();

	bool Initialize();
	void Shutdown();

	bool LoadMesh(char*);
	bool LoadMaterial(const WCHAR*);
	void GetMesh(std::vector <MeshType>&);
	Material* GetMaterial();
	int getIndexCount();
	int getVertexCount();

private:
	bool ReadFileCounts(char*, int&, int&, int&, int&);

private:
	std::vector <MeshType> m_Mesh;
	Material* m_Material;
	int m_vertexCount, m_indexCount, m_textureCount, m_normalCount, m_faceCount;
};

#endif
