//
//  EZsqlite3.h
//  
//
//  Created by soeasyright on 2014/6/9.
//
//

#ifndef ____EZsqlite3__
#define ____EZsqlite3__

#include "cocos2d.h"
using namespace cocos2d;
#include <sqlite3.h>

#define EZsqlite3_orderbyAsc "select %s from %s ORDER BY %s ASC"
#define EZsqlite3_orderbyDesc "select %s from %s ORDER BY %s DESC"
#define EZsqlite3_insert "insert into %s(%s) VALUES(%s)"


class EZsqlite3
{
public:

    static sqlite3 *pdb;
     static bool GetOrCreate(const char *fileName);
     static void CommandLine(const char *tables,const char *fields,const char *values);
     static void destroyInstance(void);
    
};

#endif /* defined(____EZsqlite3__) */
