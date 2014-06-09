//
//  Storge.h
//  
//
//  Created by soeasyright on 2014/6/6.
//
//

#ifndef ____Storge__
#define ____Storge__


#include "cocos2d.h"
bool EZSaveFile(const char *fileName,std::vector<char> *buffer);

#define EZSaveKey(key,valType,val) CCUserDefault::sharedUserDefault()->set##valType##ForKey(key, val)
#define EZSaveFlush() CCUserDefault::sharedUserDefault()->flush()
#define EZGetKey(key,valType) CCUserDefault::sharedUserDefault()->get##valType##ForKey(key);
#endif /* defined(____Storge__) */
