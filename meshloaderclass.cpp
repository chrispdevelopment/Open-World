#include "meshloaderclass.h"

MeshLoaderClass::MeshLoaderClass() 
{
	m_Material = 0;
	m_faceCount = 0;
	m_normalCount = 0;
	m_textureCount = 0;
	m_vertexCount = 0;
	m_indexCount = 0;
}

MeshLoaderClass::MeshLoaderClass(const MeshLoaderClass& other) {}

MeshLoaderClass::~MeshLoaderClass() {}

bool MeshLoaderClass::Initialize()
{
	return true;
}

void MeshLoaderClass::Shutdown()
{
	delete m_Material;

	return;
}

bool MeshLoaderClass::ReadFileCounts(char* filename, int& vertexCount, int& textureCount, int& normalCount, int& faceCount)
{
	ifstream fin;
	char input;

	// Initialize the counts.
	vertexCount = 0;
	textureCount = 0;
	normalCount = 0;
	faceCount = 0;

	// Open the file.
	fin.open(filename);

	// Check if it was successful in opening the file.
	if (fin.fail() == true)
	{
		return false;
	}

	// Read from the file and continue to read until the end of the file is reached.
	fin.get(input);
	while (!fin.eof())
	{
		// If the line starts with 'v' then count either the vertex, the texture coordinates, or the normal vector.
		if (input == 'v')
		{
			fin.get(input);
			if (input == ' ') { vertexCount++; }
			if (input == 't') { textureCount++; }
			if (input == 'n') { normalCount++; }
		}

		// If the line starts with 'f' then increment the face count.
		if (input == 'f')
		{
			fin.get(input);
			if (input == ' ') { faceCount++; }
		}

		// Otherwise read in the remainder of the line.
		while (input != '\n')
		{
			fin.get(input);
		}

		// Start reading the beginning of the next line.
		fin.get(input);
	}

	// Close the file.
	fin.close();

	return true;
}

bool MeshLoaderClass::LoadMesh(char* filename)
{
	std::vector <CordType> vertices, textcoords, normals;
	std::vector <FaceType> faces;
	ifstream fin;
	char input, input2;

	ReadFileCounts(filename, m_vertexCount, m_textureCount, m_normalCount, m_faceCount);

	// Open the file.
	fin.open(filename);

	// Check if it was successful in opening the file.
	if (fin.fail() == true)
	{
		return false;
	}

	// Read in the objectData, texture coordinates, and normals into the data structures.
	fin.get(input);
	while (!fin.eof())
	{
		if (input == 'v')
		{
			fin.get(input);

			// Read in the objectData.
			if (input == ' ')
			{
				CordType vertCord;
				fin >> vertCord.x >> vertCord.y >> vertCord.z;

				vertices.push_back(vertCord);
			}

			// Read in the texture uv coordinates.
			if (input == 't')
			{
				CordType textCord;
				fin >> textCord.x >> textCord.y;

				textcoords.push_back(textCord);
			}

			// Read in the normals.
			if (input == 'n')
			{
				CordType normalCord;
				fin >> normalCord.x >> normalCord.y >> normalCord.z;

				normals.push_back(normalCord);
			}
		}

		// Read in the faces.
		if (input == 'f')
		{
			fin.get(input);
			if (input == ' ')
			{
				FaceType face;

				fin >> face.vIndex1 >> input2 >> face.tIndex1 >> input2 >> face.nIndex1
					>> face.vIndex2 >> input2 >> face.tIndex2 >> input2 >> face.nIndex2
					>> face.vIndex3 >> input2 >> face.tIndex3 >> input2 >> face.nIndex3;

				faces.push_back(face);
			}
		}

		// Read in the remainder of the line.
		while (input != '\n')
		{
			fin.get(input);
		}

		// Start reading the beginning of the next line.
		fin.get(input);
	}

	// Close the file.
	fin.close();

	for (int i = 0; i < m_faceCount; i++)
	{
		MeshType objectData;

		objectData.x = vertices[faces[i].vIndex1 - 1].x;
		objectData.y = vertices[faces[i].vIndex1 - 1].y;
		objectData.z = vertices[faces[i].vIndex1 - 1].z;
		objectData.tu = textcoords[faces[i].tIndex1 - 1].x;
		objectData.tv = 1 - textcoords[faces[i].tIndex1 - 1].y;
		objectData.nx = normals[faces[i].nIndex1 - 1].x;
		objectData.ny = normals[faces[i].nIndex1 - 1].y;
		objectData.nz = normals[faces[i].nIndex1 - 1].z;

		m_Mesh.push_back(objectData);

		objectData.x = vertices[faces[i].vIndex2 - 1].x;
		objectData.y = vertices[faces[i].vIndex2 - 1].y;
		objectData.z = vertices[faces[i].vIndex2 - 1].z;
		objectData.tu = textcoords[faces[i].tIndex2 - 1].x;
		objectData.tv = 1 - textcoords[faces[i].tIndex2 - 1].y;
		objectData.nx = normals[faces[i].nIndex2 - 1].x;
		objectData.ny = normals[faces[i].nIndex2 - 1].y;
		objectData.nz = normals[faces[i].nIndex2 - 1].z;

		m_Mesh.push_back(objectData);

		objectData.x = vertices[faces[i].vIndex3 - 1].x;
		objectData.y = vertices[faces[i].vIndex3 - 1].y;
		objectData.z = vertices[faces[i].vIndex3 - 1].z;
		objectData.tu = textcoords[faces[i].tIndex3 - 1].x;
		objectData.tv = 1 - textcoords[faces[i].tIndex3 - 1].y;
		objectData.nx = normals[faces[i].nIndex3 - 1].x;
		objectData.ny = normals[faces[i].nIndex3 - 1].y;
		objectData.nz = normals[faces[i].nIndex3 - 1].z;

		m_Mesh.push_back(objectData);

	}

	m_vertexCount = m_Mesh.size();
	m_indexCount = m_vertexCount;

	return true;

}

bool MeshLoaderClass::LoadMaterial(const WCHAR* strFileName)
{
	// File input
	WCHAR strCommand[256] = { 0 };
	std::wifstream InFile;
	std::wstring line;

	InFile.open(strFileName);

	m_Material = new Material;

	//Set texture paths to null as they might not be used
	*m_Material->diffuseTexture = NULL;
	*m_Material->illumTexture = NULL;

	if (!m_Material)
	{
		return false;
	}

	for (; ;)
	{
		InFile >> strCommand;
		if (!InFile)
			break;

		if (0 == wcscmp(strCommand, L"newmtl"))
		{
			// Switching active materials
			WCHAR materialName[MAX_PATH] = { 0 };
			InFile >> m_Material->materialName;

			//m_Material = NULL;
			//for (int i = 0; i < m_Material.GetSize(); i++)
			//{
			//	Material* pCurMaterial = m_Material.GetAt(i);
			//	if (0 == wcscmp(pCurMaterial->materialName, materialName))
			//	{
			//		m_Material = pCurMaterial;
			//		break;
			//	}
			//}
		}

		// The rest of the commands rely on an active material
		//if (m_Material == NULL)
		//	continue;

		if (0 == wcscmp(strCommand, L"#"))
		{
			// Comment
		}
		else if (0 == wcscmp(strCommand, L"Ka"))
		{
			// Ambient color
			float r, g, b;
			InFile >> r >> g >> b;
			m_Material->vAmbient = XMFLOAT4(r, g, b, 1);
		}
		else if (0 == wcscmp(strCommand, L"Kd"))
		{
			// Diffuse color
			float r, g, b;
			InFile >> r >> g >> b;
			m_Material->vDiffuse = XMFLOAT4(r, g, b, 1);
		}
		else if (0 == wcscmp(strCommand, L"Ks"))
		{
			// Specular color
			float r, g, b;
			InFile >> r >> g >> b;
			m_Material->vSpecular = XMFLOAT4(r, g, b, 1);
		}
		else if (0 == wcscmp(strCommand, L"d") ||
			0 == wcscmp(strCommand, L"Tr"))
		{
			// Alpha
			InFile >> m_Material->fAlpha;
		}
		else if (0 == wcscmp(strCommand, L"Ns"))
		{
			// Shininess
			int nShininess;
			InFile >> nShininess;
			m_Material->nShininess = nShininess;
		}
		else if (0 == wcscmp(strCommand, L"illum"))
		{
			// Specular on/off
			int illumination;
			InFile >> illumination;
			m_Material->bSpecular = (illumination == 2);
		}
		else if (0 == wcscmp(strCommand, L"map_Kd"))
		{
			// Texture
			InFile >> m_Material->diffuseTexture;
		}
		else if (0 == wcscmp(strCommand, L"map_Ke"))
		{
			InFile >> m_Material->illumTexture;
		}
		else
		{
			// Unimplemented or unrecognized command
		}

		InFile.ignore(1000, L'\n');
	}

	InFile.close();

	return true;
}

void MeshLoaderClass::GetMesh(std::vector <MeshType>& mesh)
{
	mesh = m_Mesh;
}

MeshLoaderClass::Material* MeshLoaderClass::GetMaterial()
{
	return m_Material;
}

int MeshLoaderClass::getIndexCount()
{
	return m_indexCount;
}

int MeshLoaderClass::getVertexCount()
{
	return m_vertexCount;
}

