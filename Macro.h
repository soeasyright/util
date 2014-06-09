//
//  Macro.h
//  
//
//  Created by soeasyright on 2014/6/5.
//
//

#ifndef ____Macro_h
#define ____Macro_h


#define RW_Property(varType, varName, funName)\
protected: varType varName;\
public: inline varType get##funName(void){return varName;};\
public: inline void set##funName(varType var){varName=var;};

#define LocalFileName(_NAME_) cocos2d::CCFileUtils::sharedFileUtils()->getWritablePath().append(_NAME_).c_str()

#endif
