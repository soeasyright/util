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
char *table_queryprintf(const char *fmt, ...) {
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
    {
        CCLog("open database failed ");
        return false;
    }
    int result=sqlite3_open(LocalFileName(fileName),&pdb);
    if(result!=SQLITE_OK)
    {
        CCLog("open database failed,  number%d",result);
        return false;
    }
    return true;
}
void EZsqlite3::CommandLine(const char *table,const char *fields,const char *values)
{
   if(sqlite3_exec(pdb,table_queryprintf(EZsqlite3_insert,table,fields,values) ,NULL,NULL,NULL)!=SQLITE_OK)
   {
       CCLog("EZsqlite3 failed, "EZsqlite3_insert,table,fields,values);
   }
}

void EZsqlite3::destroyInstance(void)
{
    if(pdb)
    {
        sqlite3_close(pdb);
        pdb=NULL;
    }
}