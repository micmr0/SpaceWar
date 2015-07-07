/*
    BMP texture loader
    © Keith O'Conor 2005
    keith.oconor @ {cs.tcd.ie, gmail.com}
*/
#include "stdafx.h"
#include "textureBMP.h"

textureBMP::textureBMP(const char *filename, const int textureId){
    byte *fileData;
    BITMAPFILEHEADER fileHeader;
	BITMAPINFOHEADER infoHeader;
    
    // Open file
    HANDLE hTextureFile = CreateFile(filename, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    
    if(hTextureFile == INVALID_HANDLE_VALUE){
        std::cout<<"[BMP] ERROR: Could not open '"<<filename<<"'"<<std::endl;
        return;   
    }
    if(GetFileSize(hTextureFile,NULL) == 0){
        std::cout<<"[BMP] ERROR: Texture '"<<filename<<"' is empty"<<std::endl;
        CloseHandle(hTextureFile);
        return;
    }  
    
	// Create file mapping
	HANDLE hTextureFileMapping = CreateFileMapping(hTextureFile, NULL, PAGE_READONLY, 0, 0, NULL);    
	if(hTextureFileMapping == NULL){
        std::cout<<"[TGA] ERROR: Could not map '"<<filename<<"' in memory"<<std::endl;
        CloseHandle(hTextureFile);
        return;
    }  
	fileData = (byte*)MapViewOfFile(hTextureFileMapping, FILE_MAP_READ, 0, 0, 0);

    // Read BMP header
	memcpy(&fileHeader, fileData, sizeof(fileHeader));
	memcpy(&infoHeader, fileData+sizeof(fileHeader), sizeof(infoHeader));
	
    m_width = infoHeader.biWidth;
    m_height = infoHeader.biHeight;
    m_bpp = infoHeader.biBitCount;

    // We only support uncompressed 24 or 32 bits per pixel BMPs
    if(infoHeader.biCompression != BI_RGB || fileHeader.bfType != 19778){
        std::cout<<"[BMP] ERROR: '"<<filename<<"' is an texture invalid format\n[BMP] ERROR: It should be an uncompressed 24/32bpp BMP"<<std::endl;
        UnmapViewOfFile(fileData);
		CloseHandle(hTextureFileMapping);
        CloseHandle(hTextureFile);
        return;
    }
    if(m_bpp != 32 && m_bpp != 24){
        std::cout<<"[BMP] ERROR: Invalid texture color depth, '"<<filename<<"' must be uncompressed 24/32bpp BMP"<<std::endl;
        UnmapViewOfFile(fileData);
		CloseHandle(hTextureFileMapping);
        CloseHandle(hTextureFile);
        return;
    }
    
    // Determine format
    int fileFormat, internalFormat;
    switch(m_bpp){
        case 24:fileFormat = GL_BGR_EXT; internalFormat = GL_RGB; break;   
        case 32:fileFormat = GL_BGRA_EXT; internalFormat = GL_RGBA; break;
        default:
            std::cout<<"[BMP] ERROR: Invalid texture color depth, '"<<filename<<"' must be uncompressed 24/32bpp BMP"<<std::endl;
            UnmapViewOfFile(fileData);
			CloseHandle(hTextureFileMapping);
			CloseHandle(hTextureFile);
			return;
            break;
    }

		gluBuild2DMipmaps(	GL_TEXTURE_2D, 
						3, 
						m_height,
						m_width,
						internalFormat,
						GL_UNSIGNED_BYTE,
						fileData);
    
	// Bind texture ID to load
    glBindTexture(GL_TEXTURE_2D, textureId);
    
    // Set texture parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    
    // Upload texture to card with bound texture ID
    gluBuild2DMipmaps(GL_TEXTURE_2D, internalFormat, m_width, m_height, fileFormat, GL_UNSIGNED_BYTE, &fileData[fileHeader.bfOffBits]);
    
    // Texture's uploaded, don't need data any more   
    UnmapViewOfFile(fileData);
	CloseHandle(hTextureFileMapping);
	CloseHandle(hTextureFile);


    
    std::cout<<"[BMP] Texture '"<<filename<<"' loaded"<<textureId<<std::endl;
}
