//
//  Singleton.h
//  nullatest01
//
//  Created by soeasyright on 2014/6/5.
//
//

#ifndef __nullatest01__Singleton__
#define __nullatest01__Singleton__

#include "Macro.h"
#include "cocos2d.h"
using namespace cocos2d;


template <class T>
class Singleton
{
public:
    static inline T* getInstance();
    static inline void destroyInstance();
protected:
    static T* _instance;
    Singleton(){};
    ~Singleton(){};
};


template <class T>
inline T* Singleton<T>::getInstance()
{
    CCLog("%s", __PRETTY_FUNCTION__);
    if (!_instance) {
        _instance=new T();
    }
    return _instance;
}

template <class T>
inline void Singleton<T>::destroyInstance()
{
    CCLog("%s", __PRETTY_FUNCTION__);
    CC_SAFE_DELETE(_instance);
}

#define Delcear_Singleton_Instance(_Ti) \
    template<> _Ti* Singleton<_Ti>::_instance = NULL

#endif /* defined(__nullatest01__Singleton__) */
