#ifndef _TERRAINCLASS_H_
#define _TERRAINCLASS_H_

//////////////
// INCLUDES //
//////////////
#include "modelabstractclass.h"
#include "terraincellclass.h"
#include "frustumclass.h"

////////////////////////////////////////////////////////////////////////////////
// Class name: TerrainClass
////////////////////////////////////////////////////////////////////////////////
class TerrainClass : public ModelAbstractClass
{
private:
	struct VertexType
	{
		XMFLOAT3 position;
		XMFLOAT2 texture;
		XMFLOAT3 normal;
		XMFLOAT3 tangent;
		XMFLOAT3 binormal;
		XMFLOAT3 color;
	};

	struct HeightMapType
	{
		float x, y, z;
		float nx, ny, nz;
		float r, g, b;
	};

	struct TempVertexType
	{
		float x, y, z;
		float tu, tv;
		float nx, ny, nz;
	};

public:
	TerrainClass();
	TerrainClass(const TerrainClass&);
	~TerrainClass();

	bool Initialize(ID3D11Device*, char*, bool);
	void Shutdown();

	void Frame();

	int GetVertexCount();
	void CopyVertexArray(void*);

	bool RenderCell(ID3D11DeviceContext*, int, FrustumClass*);
	void RenderCellLines(ID3D11DeviceContext*, int);

	int GetCellIndexCount(int);
	int GetCellLinesIndexCount(int);
	int GetCellCount();

	int GetRenderCount();
	int GetCellsDrawn();
	int GetCellsCulled();

	bool GetHeightAtPosition(float, float, float&);

private:
	bool LoadSetupFile(char*);
	bool LoadBitmapHeightMap();
	bool LoadRawHeightMap();
	void ShutdownHeightMap();
	void SetTerrainCoordinates();
	bool CalculateNormals();

	bool LoadColorMap();
	bool BuildTerrainModel();

	void CalculateTerrainVectors();
	void CalculateTangentBinormal(TempVertexType, TempVertexType, TempVertexType, VectorType&, VectorType&);

	bool InitializeBuffers(ID3D11Device*);
	void RenderBuffers(ID3D11DeviceContext*);
	void ShutdownVertices();

	bool LoadTerrainCells(ID3D11Device*);
	void ShutdownTerrainCells();

	void FindCell(float, float, float&);
	bool CheckHeightOfTriangle(float, float, float&, float[3], float[3], float[3]);

private:
	int m_terrainHeight, m_terrainWidth;
	bool m_initializeBuffers;

	float m_heightScale;

	char *m_terrainFilename, *m_colorMapFilename;

	HeightMapType* m_heightMap;
	VertexType* m_vertices;

	TerrainCellClass* m_TerrainCells;
	int m_cellCount, m_renderCount, m_cellsDrawn, m_cellsCulled;
};

#endif