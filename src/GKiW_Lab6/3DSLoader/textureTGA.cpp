/*
    TGA texture loader
    © Keith O'Conor 2005
    keith.oconor @ {cs.tcd.ie, gmail.com}
*/
#include "stdafx.h"
#include "textureTGA.h"

textureTGA::textureTGA(const char *filename, const int textureId){
    byte *fileData;
    
    // Open file
	HANDLE hTextureFile = CreateFile(filename, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    
    if(hTextureFile == INVALID_HANDLE_VALUE){
        std::cout<<"[TGA] ERROR: Could not open '"<<filename<<"'"<<std::endl;
        return;   
    }
    if(GetFileSize(hTextureFile,NULL) == 0){
        std::cout<<"[TGA] ERROR: Texture '"<<filename<<"' is empty"<<std::endl;
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

	// Get relevant info from header
    int colorMapType = fileData[1];
	int imageType = fileData[2];
    m_width = fileData[12] + (fileData[13] << 8);
    m_height = fileData[14] + (fileData[15] << 8);
    m_bpp = fileData[16];

	// We only support uncompressed 24 or 32 bits per pixel TGAs
    if(colorMapType == 1 || imageType != 2){
        std::cout<<"[TGA] ERROR: '"<<filename<<"' is an texture invalid format\n[TGA] ERROR: It should be an uncompressed 24/32bpp TGA"<<std::endl;
		UnmapViewOfFile(fileData);
		CloseHandle(hTextureFileMapping);
        CloseHandle(hTextureFile);
        return;
    }
    if(m_bpp != 32 && m_bpp != 24){
        std::cout<<"[TGA] ERROR: Invalid texture color depth, '"<<filename<<"' must be uncompressed 24/32bpp TGA"<<std::endl;
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
            std::cout<<"[TGA] ERROR: Invalid texture color depth, '"<<filename<<"' must be uncompressed 24/32bpp TGA"<<std::endl;
            UnmapViewOfFile(fileData);
			CloseHandle(hTextureFileMapping);
			CloseHandle(hTextureFile);
            return;
            break;
    }


    
    // Bind texture ID to load
    glBindTexture(GL_TEXTURE_2D, textureId);
    
    // Set texture parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
    
    // Upload texture to card with bound texture ID
/*	glTexImage2D (GL_TEXTURE_2D, 0, 4, // 4 wartosci dla ka¿dego teksela
                    m_width, m_height, 0, GL_RGBA,    // tekstura w trybie RGBA (!)
                   GL_UNSIGNED_BYTE, &fileData[18]);
*/
//	glTexImage2D( GL_TEXTURE_2D, 0, 0, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, &fileData[18]  );
	gluBuild2DMipmaps(GL_TEXTURE_2D, internalFormat, m_width, m_height, fileFormat, GL_UNSIGNED_BYTE, &fileData[18]);

    
    // Texture's uploaded, don't need data any more   
    UnmapViewOfFile(fileData);
	CloseHandle(hTextureFileMapping);
	CloseHandle(hTextureFile);
    
    std::cout<<"[TGA] Texture '"<<filename<<"' loaded "<< textureId<<std::endl;
}
