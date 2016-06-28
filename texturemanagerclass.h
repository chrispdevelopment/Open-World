#ifndef _TEXTUREMANAGERCLASS_H_
#define _TEXTUREMANAGERCLASS_H_

#include <map>
#include <string>
#include <fstream>
#include <stdio.h>
using namespace std;

#include "textureclass.h"

typedef map<string, TextureClass*> TextureGroup;
typedef map<string, TextureGroup> TextureArray;

////////////////////////////////////////////////////////////////////////////////
// Class name: TextureManagerClass
////////////////////////////////////////////////////////////////////////////////
class TextureManagerClass
{
public:
	TextureManagerClass();
	TextureManagerClass(const TextureManagerClass&);
	~TextureManagerClass();

	bool Initialize(ID3D11Device*, ID3D11DeviceContext*, char*);
	void Shutdown();

	bool LoadTexture(ID3D11Device*, ID3D11DeviceContext*, char*, string, string);

	ID3D11ShaderResourceView* GetTexture(string, string);

private:
	TextureArray m_TextureArray;
	
	int m_textureCount;
};

#endif
