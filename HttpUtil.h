//
//  HttpUtil.h
//  nullatest01
//
//  Created by soeasyright on 2014/6/5.
//
//

#ifndef __nullatest01__HttpUtil__
#define __nullatest01__HttpUtil__

#include "Singleton.h"
#include "cocos2d.h"
#include "cocos-ext.h"
#include "Macro.h"
USING_NS_CC;
USING_NS_CC_EXT;
using namespace std;

//typedef void (CCObject::*SEL_HTTPOKCALLBACK)(CCDictionary*);
typedef void (CCObject::*SEL_HTTPOKCALLBACK)(const char* ,CCObject * );
typedef void (CCObject::*SEL_HTTPERRORCALLBACK)(const char* );


#define httpOk_selector(_selector) (SEL_HTTPOKCALLBACK)(&_selector)
#define httpError_selector(_selector) (SEL_HTTPERRORCALLBACK)(&_selector)


struct selectorParam {
    CCObject *target;
    SEL_HTTPOKCALLBACK ok;
    SEL_HTTPERRORCALLBACK error;
    CCObject *callbackTarget;
};

class HttpReq :  public CCHttpRequest
{
public:
    HttpReq():
    _target(NULL),
    _ok(NULL),
    _error(NULL),
    _callbackTarget(NULL){};
    ~HttpReq(){memset(_downloadFileName, '\0', FILE_NAME_MAX_SIZE);};
    
    RW_Property(CCObject *, _target, Target);
    RW_Property(SEL_HTTPOKCALLBACK, _ok, OKCallBack);
    RW_Property(SEL_HTTPERRORCALLBACK, _error, ErrorCallBack);
    RW_Property(CCObject *, _callbackTarget, CallbackTarget);
    
protected:
    enum{   FILE_NAME_MAX_SIZE=64 };
    char   _downloadFileName[FILE_NAME_MAX_SIZE];
public:
    inline void setDownloadFileName(const char *fileName)
    {
        CCAssert(fileName != NULL, "");
        strcpy(_downloadFileName, fileName);
    }
    
    inline const char*  getDownloadFileName()
    {
        return _downloadFileName ;
    }
    
};

class HttpUtil : public CCObject, public Singleton<HttpUtil>
{
public:
    HttpUtil(){};
    ~HttpUtil(){
        CCHttpClient::destroyInstance();
    };

    void EZreq(CCHttpRequest::HttpRequestType type,const char *url,const char *sendparam,const char *filename,selectorParam *p,bool enableJson);
    
    inline void getReq(const char *url,const char *sendparam,selectorParam *p=NULL,bool enableJson=false){
        EZreq(CCHttpRequest::kHttpGet,url,sendparam,NULL,p,enableJson);
    };
    inline void postReq(const char *url,const char *sendparam,selectorParam *p=NULL,bool enableJson=false){
        EZreq(CCHttpRequest::kHttpPost,url,sendparam,NULL,p,enableJson);
    }
    inline void download(const char *url,const char *sendparam,const char *filename,selectorParam *p=NULL,bool enableJson=false){
        EZreq(CCHttpRequest::kHttpGet,url,sendparam,filename,p,enableJson);
    }

    
private:
    void onHttpRequestCompleted(CCHttpClient *sender, CCHttpResponse *response);
    void onDownloadCompleted(CCHttpClient *sender, CCHttpResponse *response);


   
};

#endif /* defined(__nullatest01__HttpUtil__) */
