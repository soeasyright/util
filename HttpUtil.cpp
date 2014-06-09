//
//  HttpUtil.cpp
//  
//
//  Created by soeasyright on 2014/6/5.
//
//

#include "HttpUtil.h"
#include "Storge.h"
Delcear_Singleton_Instance(HttpUtil);

void HttpUtil::EZreq(CCHttpRequest::HttpRequestType type,const char *url,const char *sendparam,const char *filename,selectorParam *p,bool enableJson)
{
    CCAssert(url != NULL, "");
    HttpReq* httpReq = new HttpReq();
    httpReq->setUrl(url);
    httpReq->setRequestType(type);
   
    if (sendparam && *sendparam)
    {
        CCLog("sendparam exist");
        httpReq->setRequestData(sendparam, strlen(sendparam));
    }
    if(enableJson)
    {
        std::vector<std::string> headers;
        headers.push_back("Content-Type: application/json; charset=utf-8");
        httpReq->setHeaders(headers);
    }
    if(p)
    {
        CCLog("p exist");
        httpReq->setTarget(p->target);
        httpReq->setOKCallBack(p->ok);
        httpReq->setErrorCallBack(p->error);
        httpReq->setCallbackTarget(p->callbackTarget);
    }
    if (filename && *filename) {
         CCLog("filename exist %s",filename);
        httpReq->setDownloadFileName(filename);
        httpReq->setResponseCallback(this, httpresponse_selector(HttpUtil::onDownloadCompleted));
    }
    else
    {
        httpReq->setResponseCallback(this, httpresponse_selector(HttpUtil::onHttpRequestCompleted));
    }
    CCHttpClient::getInstance()->send(httpReq);
    httpReq->release();
}

void HttpUtil::onHttpRequestCompleted(CCHttpClient *sender, CCHttpResponse *response)
{
    CCLog("%s", __PRETTY_FUNCTION__);
    if (!response ) {
		CCLog("response failed");
        return;
    }
    HttpReq* httpReq=(HttpReq*)response->getHttpRequest();
    CCObject *target=httpReq->getTarget();
    SEL_HTTPOKCALLBACK ok=httpReq->getOKCallBack();
    SEL_HTTPERRORCALLBACK error=httpReq->getErrorCallBack();
    CCObject *callbackTarget=httpReq->getCallbackTarget();


    if (!response->isSucceed())
    {
        CCLog("error buffer: %s %d", response->getErrorBuffer(), response->getResponseCode());
        if(target && error) (target->*error)(response->getErrorBuffer());
        return;
    }
    
    int statusCode = response->getResponseCode();
    CCLog("response code: %d", statusCode);
    
	vector<char> *buffer = response->getResponseData();
    
    string json;
    json.assign(buffer->begin(),buffer->end());
    CCLog("response code: %s", json.c_str());
    if(target && ok)
    {
        (target->*ok)(json.c_str(),callbackTarget);
    }

    
	return;
}


void HttpUtil::onDownloadCompleted(CCHttpClient *sender, CCHttpResponse *response)
{
    CCLog("%s", __PRETTY_FUNCTION__);
    if (!response ) {
		CCLog("response failed");
        return;
    }
    HttpReq* httpReq=(HttpReq*)response->getHttpRequest();
    CCObject *target=httpReq->getTarget();

    if (!response->isSucceed())
    {
        CCLog("error buffer: %s %d", response->getErrorBuffer(), response->getResponseCode());
        SEL_HTTPERRORCALLBACK error=httpReq->getErrorCallBack();
        if(target && error) (target->*error)(response->getErrorBuffer());
        return;
    }
    int statusCode = response->getResponseCode();
    CCLog("response code: %d", statusCode);
    
    const char *fileName=httpReq->getDownloadFileName();
    vector<char> *buffer = response->getResponseData();
    bool isSave=EZSaveFile(fileName,buffer);

    CCObject *callbackTarget=httpReq->getCallbackTarget();
    if(isSave)
    {
        SEL_HTTPOKCALLBACK ok=httpReq->getOKCallBack();
        if(target && ok)
            (target->*ok)(fileName,callbackTarget);
    }
    else
    {
        SEL_HTTPERRORCALLBACK error=httpReq->getErrorCallBack();
        if(target && error)
            (target->*error)("Save file error");
    }
	
}