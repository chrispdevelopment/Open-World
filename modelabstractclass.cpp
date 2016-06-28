#include "modelabstractclass.h"

ModelAbstractClass::ModelAbstractClass() {
	m_meshLoader = new MeshLoaderClass;
	m_material = 0;
}

ModelAbstractClass::ModelAbstractClass(const ModelAbstractClass& other) {}

ModelAbstractClass::~ModelAbstractClass() {}

bool ModelAbstractClass::Initialize(ID3D11Device*, char*, bool) { return true; };
bool ModelAbstractClass::Initialize(ID3D11Device*, ID3D11DeviceContext*, char*, const WCHAR*, TextureManagerClass*) { return true; };

void ModelAbstractClass::Render(ID3D11DeviceContext* deviceContext)
{
	// Render the sky dome.
	RenderBuffers(deviceContext);

	return;
}

int ModelAbstractClass::GetIndexCount()
{
	return m_indexCount;
}

void ModelAbstractClass::ReleaseBuffers()
{
	// Release the index buffer.
	if (m_indexBuffer)
	{
		m_indexBuffer->Release();
		m_indexBuffer = 0;
	}

	// Release the vertex buffer.
	if (m_vertexBuffer)
	{
		m_vertexBuffer->Release();
		m_vertexBuffer = 0;
	}

	return;
}

bool ModelAbstractClass::LoadMesh(char* meshFilename, const WCHAR* mtlfilename)
{
	std::vector <MeshLoaderClass::MeshType> mesh;
	bool result;

	//Load the mesh from file
	result = m_meshLoader->LoadMesh(meshFilename);
	if (!result) {
		return false;
	}

	//Get the mesh information
	m_meshLoader->GetMesh(mesh);

	if (mtlfilename != NULL) {
		result = m_meshLoader->LoadMaterial(mtlfilename);
		if (!result) {
			return false;
		}

		m_material = m_meshLoader->GetMaterial();
	}

	//Load the vertex and index counts
	m_vertexCount = m_meshLoader->getVertexCount();
	m_indexCount = m_meshLoader->getIndexCount();

	m_model = new ModelType[m_vertexCount];

	for (int i = 0; i < m_vertexCount; i++) {
		m_model[i].x = mesh[i].x;
		m_model[i].y = mesh[i].y;
		m_model[i].z = mesh[i].z;
		m_model[i].tu = mesh[i].tu;
		m_model[i].tv = mesh[i].tv;
		m_model[i].nx = mesh[i].nx;
		m_model[i].ny = mesh[i].ny;
		m_model[i].nz = mesh[i].nz;
	}

	return true;

}

void ModelAbstractClass::ReleaseModel() {

	if (m_model)
	{
		delete m_model;
		m_model = 0;

		//delete m_meshLoader;
		//m_meshLoader = 0;
	}

}