//
//  Singleton.h
//  
//
//  Created by soeasyright on 2014/6/5.
//
//

#ifndef ____Singleton__
#define ____Singleton__


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

#endif /* defined(____Singleton__) */
