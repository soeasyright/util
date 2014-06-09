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

class EZsqlite3
{
public:
    static sqlite3 *pdb;
    static bool GetOrCreate(const char *fileName);
};

#endif /* defined(____EZsqlite3__) */
