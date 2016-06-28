#include "texturemanagerclass.h"

TextureManagerClass::TextureManagerClass()
{
}

TextureManagerClass::TextureManagerClass(const TextureManagerClass& other)
{
}

TextureManagerClass::~TextureManagerClass()
{
}

bool TextureManagerClass::Initialize(ID3D11Device* device, ID3D11DeviceContext* deviceContext, char* infoFilePath)
{
	ifstream fin;
	TextureClass* texture;
	TextureGroup textureGroup;

	char input;
	char* fileName;

	int stringLength;

	string groupName = "";
	
	bool result;

	stringLength = 256;
	fileName = new char[stringLength];

	// Open the setup file.  If it could not open the file then exit.
	fin.open(infoFilePath);
	if (fin.fail())
	{
		return false;
	}

	fin.get(input);
	while (!fin.eof())
	{

		if (input == '#')
		{
				fin >> groupName;
		}

		if (input == 'd') 
		{
			fin >> fileName;

			texture = new TextureClass;
			if (!texture)
			{
				return false;
			}
			
			result = texture->Initialize(device, deviceContext, fileName);
			if (!result) {
				return false;
			}

			textureGroup["diffuse"] = texture;
			m_TextureArray[groupName] = textureGroup;
		}

		if (input == 'n')
		{
			fin >> fileName;

			texture = new TextureClass;
			if (!texture)
			{
				return false;
			}

			result = texture->Initialize(device, deviceContext, fileName);
			if (!result) {
				return false;
			}

			textureGroup["normal"] = texture;
			m_TextureArray[groupName] = textureGroup;
		}

		// Read in the remainder of the line.
		while (input != '\n')
		{
			fin.get(input);
		}

		// Start reading the beginning of the next line.
		fin.get(input);
	}

	return true;
}

bool TextureManagerClass::LoadTexture(ID3D11Device* device, ID3D11DeviceContext* deviceContext, char* fileName, string groupName, string textureType)
{
	TextureClass* texture;
	TextureGroup textureGroup;

	bool result;

	texture = new TextureClass;
	if (!texture)
	{
		return false;
	}

	result = texture->Initialize(device, deviceContext, fileName);
	if (!result) {
		return false;
	}

	if (m_TextureArray.count(groupName) > 0) {
		textureGroup = m_TextureArray.find(groupName)->second;
		textureGroup[textureType] = texture;
	}
	else {
		textureGroup[textureType] = texture;
	}

	m_TextureArray[groupName] = textureGroup;

	return true;
}

void TextureManagerClass::Shutdown()
{
	int i, j;

	// Release the texture objects.
	for (auto it = m_TextureArray.cbegin(); it != m_TextureArray.end(); ++it )
	{
		for (auto it2 = it->second.cbegin(); it2 != it->second.end(); ++it2)
		{
			it2->second->GetTexture();
			delete it2->second;
		}
	}

	m_TextureArray.clear();

	return;
}

ID3D11ShaderResourceView* TextureManagerClass::GetTexture(string groupName, string textureType)
{
	return m_TextureArray.find(groupName)->second.find(textureType)->second->GetTexture();
}