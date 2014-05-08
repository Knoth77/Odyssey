/*
	Author: Richard McKenna
			Stony Brook University
			Computer Science Department

	DirectXTextureManager.cpp

	See DirectXTextureManager for a class description.
*/

#include "../../../../stdafx.h"
#include "../../graphics/GameGraphics.h"
#include "../../platforms/DirectX/DirectXGraphics.h"
#include "../../platforms/DirectX/DirectXTextureManager.h"

/*
	DirectXTextureManager - Default constructor, it constructs the map that
	will store all of the textures and file paths/names.
*/
DirectXTextureManager::DirectXTextureManager()
{
//	textures = new map<wstring, LPDIRECT3DTEXTURE9>();
}

/*
	~DirectXTextureManager - Destructor, it cleans up all the textures.
*/
DirectXTextureManager::~DirectXTextureManager()
{
	// TODO - GO THROUGH TEXTURE MANAGER AND DELETE EVERYTHING
//	delete textures;
}

/*
	getTexture - This method fetches the texture with the provided id. This
	is done by looking up the file path/name in the wchar_t table that corresponds
	to the id index, and then fetches the appropritate texture out of the map.
*/
LPDIRECT3DTEXTURE9 DirectXTextureManager::getTexture(unsigned int id)
{
	// WHAT'S THE FILE NAME FOR THIS ID?
	wstring fileName = wstringTable.getWStringFromTable(id);

	// RETURN THE TEXTURE MAPPED TO THAT FILE NAME
	return textures[fileName];
}

/*
	loadTexture - This method loads a texture with a path/file name key into
	the GPU memory. It registers the path/file name in the wchar_t table and
	returns the corresponding index. Once the texture is created, it loads
	it into the map.
*/
unsigned int DirectXTextureManager::loadTexture(wstring key)
{
	LPDIRECT3DTEXTURE9 textureToLoad;
	unsigned int result = fillTexture(key, &textureToLoad);
	if (result == S_OK)
	{
		// PUT OUR LOADED TEXTURE INTO OUR MAP
		textures[key.c_str()] = textureToLoad;

		// NOW PUT THE KEY IN THE wchar_t TABLE
		int indexOfTexture = wstringTable.putWStringInTable(key.c_str());

		// AND RETURN THE TEXTURE'S ID
		return indexOfTexture;
	}
	return -1;
}

unsigned int DirectXTextureManager::fillTexture(wstring key, LPDIRECT3DTEXTURE9 *textureToFill)
{
	// USED FOR READING BITMAP FILE INFO
    D3DXIMAGE_INFO info;

	// CONVERT THE FILE NAME INTO A WINDOW LONG CHAR wchar_t (LPCWSTR)
	LPCWSTR fileName = key.c_str();
	HRESULT result = D3DXGetImageInfoFromFile(fileName, &info);

	// IF THE IMAGE FILE WAS FOUND
	if (result == S_OK)
	{
		// GET THE COLOR KEY, WE'LL NEED THIS FOR LOADING OUR IMAGE
		D3DCOLOR colorKey = ((DirectXGraphics*)graphics)->getColorKey();

		LPDIRECT3DDEVICE9 graphicsDevice = ((DirectXGraphics*)graphics)->getGraphicsDevice();
		
		// CREATE A NEW TEXTURE
		//D3DXLoadSurfaceFromFileInMemory()

		result = D3DXCreateTextureFromFileEx(
			graphicsDevice,		// GPU
			fileName,			// BITMAP FILE PATH/NAME
			info.Width,			// BITMAP IMAGE WIDTH
			info.Height,		// BITMAP IMAGE HEIGHT
			1,					// MIP-MAP LEVELS (1 FOR NO CHAIN)
			D3DPOOL_DEFAULT,	// THE TYPE OF SURFACE (STANDARD)
			D3DFMT_UNKNOWN,		// SURFACE FORMAT (DEFAULT)
			D3DPOOL_DEFAULT,	// MEMORY CLASS FOR THE TEXTURE
			D3DX_DEFAULT,		// IMAGE FILTER
			D3DX_DEFAULT,		// MIP FILTER
			colorKey,			// COLOR KEY
			&info,				// BITMAP FILE INFO
			NULL,				// COLOR PALETTE
			textureToFill );	// THE TEXTURE WE ARE CREATING AND LOADING

		return S_OK;
	}
	else
		return -1;
}

/*
	reloadAllTextures - Should our game application lose access to the GPU
	the textures we loaded in may be lost. So, when we get the GPU back
	this method allows us to reload all of the textures in our map.
*/
void DirectXTextureManager::reloadAllTextures()
{
	unordered_map<wstring, LPDIRECT3DTEXTURE9>::iterator texturesIterator;

	wstring key;
	for (	texturesIterator = textures.begin();
				texturesIterator != textures.end();
				texturesIterator++ )
	{
		key = texturesIterator->first;
		loadTexture(key);
	}
}

/*
	clear - This method clears out all the textures in our map. It
	results in the deletion of all of these objects. The corresponding
	wchar_t table is then also cleared.
*/
void DirectXTextureManager::clear()
{
	unordered_map<wstring, LPDIRECT3DTEXTURE9>::iterator it;
	unordered_map<wstring, LPDIRECT3DTEXTURE9>::iterator itToErase;
	it = textures.begin();
	while (it != textures.end())
	{
		wstring keyToDelete = (*it).first;
		LPDIRECT3DTEXTURE9 textureToDelete = (*it).second;
		itToErase = it;
		it++;
		textures.erase(itToErase);
		textureToDelete->Release();
		textureToDelete = NULL;
	}
	textures.clear();
	wstringTable.clear();
}


bool DirectXTextureManager::loadTileSetFromTexture(Game *game,
	wstring dir,
	wstring sourceImageFileName,
	int tileWidth,
	int tileHeight)
{
	// CONVERT THE FILE NAME INTO A WINDOW LONG CHAR wchar_t (LPCWSTR)
	wstring sourcePath = dir + sourceImageFileName;

	LPDIRECT3DTEXTURE9 textureToDivide;
	LPDIRECT3DSURFACE9 surfaceToDivide;
	//DXLoad
	//D3DXLoadSurfaceFromMemory()
	unsigned int result = fillTexture(sourcePath, &textureToDivide);
	textureToDivide->GetSurfaceLevel(0, &surfaceToDivide);//~15 seconds
	if (result != S_OK) return false;

	// DETERMINE THE NUMBER OF TILE ROWS AND COLUMNS
	D3DSURFACE_DESC surfaceDesc;
	surfaceToDivide->GetDesc(&surfaceDesc);
	int textureWidth = surfaceDesc.Width;
	int textureHeight = surfaceDesc.Height;
	int columns = textureWidth / tileWidth;
	int rows = textureHeight / tileHeight;
	DirectXGraphics *dxg = (DirectXGraphics*)graphics;

	LPDIRECT3DDEVICE9 graphicsDevice = ((DirectXGraphics*)graphics)->getGraphicsDevice();

	// THE TILE SET IMAGE LOADED SUCCESSFULLY, SO LET'S CUT IT UP
	// MAYBE IF IM FEELING CRAZY LATER ILL MULTI THREAD THIS
	for (int row = 0; row < rows; row++)
	{
		for (int column = 0; column < columns; column++)
		{
			LPDIRECT3DTEXTURE9 extractedTexture;
			LPDIRECT3DSURFACE9 extractedSurface;
			result = graphicsDevice->CreateRenderTarget(tileWidth,
				tileHeight,
				D3DFMT_A8R8G8B8,
				D3DMULTISAMPLE_NONE, 0, false, &extractedSurface, NULL);
			if (result != S_OK) return false;

			RECT sourceRect;
			sourceRect.left = column * tileWidth;
			sourceRect.right = tileWidth + (column * tileWidth) - 1;
			sourceRect.top = row * tileHeight;
			sourceRect.bottom = tileHeight + (row * tileHeight) - 1;

			graphicsDevice->StretchRect(surfaceToDivide, &sourceRect, extractedSurface, NULL, D3DTEXF_NONE);

			// BUILD A UNIQUE FILE NAME FOR THIS TEXTURE
			wstring textureFilename = sourceImageFileName;

			unsigned int id = wstringTable.getNumWStringsInTable();
			wchar_t dot = '.';
			int dotIndex = textureFilename.rfind(dot);
			textureFilename = textureFilename.substr(0, dotIndex);
			wstringstream idWss;
			idWss << id;
			wstring idText;
			idWss >> idText;
			textureFilename = textureFilename + idText + L".png";
			textureFilename = wstring(dir.begin(), dir.end()) + textureFilename;

			//D3DXCreateTextureFromFile()
			//D3DxCreateTexture
			HRESULT result = D3DXCreateTexture(graphicsDevice, tileWidth, tileHeight, 1, D3DPOOL_DEFAULT, D3DFMT_UNKNOWN, D3DPOOL_DEFAULT, &extractedTexture);
			if (result != S_OK) return false;
			LPDIRECT3DSURFACE9 t;
			extractedTexture->GetSurfaceLevel(0, &t);
			D3DXLoadSurfaceFromSurface(t, NULL, NULL, extractedSurface, NULL, NULL, D3DX_FILTER_NONE, 0);
					

			// ADD IT TO THE STRING TABLE
			wstringTable.putWStringInTable(textureFilename);

			// AND ADD IT TO THE TEXTURES
			textures[textureFilename] = extractedTexture;
			extractedSurface->Release();
			t->Release();
		}
	}
	surfaceToDivide->Release();
	textureToDivide->Release();
	return true;
}