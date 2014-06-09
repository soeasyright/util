//
//  Storge.h
//  nullatest01
//
//  Created by soeasyright on 2014/6/6.
//
//

#ifndef __nullatest01__Storge__
#define __nullatest01__Storge__

#include "Macro.h"
#include "cocos2d.h"
bool EZSaveFile(const char *fileName,std::vector<char> *buffer);

#define EZSaveKey(key,valType,val) CCUserDefault::sharedUserDefault()->set##valType##ForKey(key, val)
#define EZSaveFlush() CCUserDefault::sharedUserDefault()->flush()
#define EZGetKey(key,valType) CCUserDefault::sharedUserDefault()->get##valType##ForKey(key);
#endif /* defined(__nullatest01__Storge__) */
