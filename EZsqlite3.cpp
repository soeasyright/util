//
//  EZsqlite3.cpp
//  
//
//  Created by soeasyright on 2014/6/9.
//
//

#include "EZsqlite3.h"
#include "Macro.h"
#define QUERY_SIZE (1 << 8)
char *table_queryprintf(char *fmt, ...) {
	static char q[QUERY_SIZE];
	va_list ap;
	va_start(ap, fmt);
	sqlite3_vsnprintf(QUERY_SIZE - 1, q, fmt, ap);
	va_end(ap);
	return q;
}

sqlite3* EZsqlite3::pdb=NULL;

bool EZsqlite3::GetOrCreate(const char *fileName)
{
    if(pdb)
        return false;
    
    int result=sqlite3_open(LocalFileName(fileName),&pdb);
    if(result!=SQLITE_OK)
        CCLog("open database failed,  number%d",result);
        return false;
    return true;
}