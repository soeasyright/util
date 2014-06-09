//
//  Storge.cpp
//  nullatest01
//
//  Created by soeasyright on 2014/6/6.
//
//

#include "Storge.h"

bool EZSaveFile(const char *fileName,std::vector<char> *buffer)
{
    const char *localFileName=LocalFileName(fileName);
    FILE *fp = fopen(localFileName, "wb");
	if (!fp)
	{
		CCLOG("can not create file %s",localFileName);
		return false;
	}
    size_t olen = buffer->size();
	size_t len =  fwrite(&(buffer->front()), 1, olen, fp);
	fclose(fp);
    
    if( len != olen )
    {
        remove(localFileName);
        return false;
    }
    return true;
}