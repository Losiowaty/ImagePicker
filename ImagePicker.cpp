//
//  ImagePicker.cpp
//  ImagePicker
//
//  Created by Festina Lente on 17.07.2013.
//
//

#include "ImagePicker.h"

bool ImagePicker::working = false;
ImagePicker* ImagePicker::sharedPicker = NULL;

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)

#ifdef __cplusplus
extern "C" {
#endif
    void Java_org_cocos2dx_lib_Cocos2dxActivity_informNative(JNIEnv *env, jobject thiz)
    {
        ImagePicker::setReady();
    }
    
    void Java_org_cocos2dx_lib_Cocos2dxActivity_informNativeCancel(JNIEnv *env, jobject thiz) {
        ImagePicker::dismissed();
    }
#ifdef __cplusplus
}
#endif

#endif

bool ImagePicker::pickImage(CCNode *target, CCPoint position, ImagePickerDelegate *delegate) {
    
    if (!working) {
        
        if (sharedPicker) {
            if (sharedPicker->getParent())
                sharedPicker->removeFromParentAndCleanup(true);
            delete sharedPicker;
        }
        
        sharedPicker = new ImagePicker();
        sharedPicker->_target = target;
        sharedPicker->_position = position;
        sharedPicker->_delegate = delegate;
        sharedPicker->last = NULL;
        
        sharedPicker->ready = false;
        sharedPicker->working = true;
        
        sharedPicker->retain();
        sharedPicker->schedule(schedule_selector(ImagePicker::finished), 1);
        
        sharedPicker->start();
        
        target->addChild(sharedPicker);
        
        return true;
        
    }
    
    return false;
    
}

CCSprite* ImagePicker::getLastSprite() {
    return sharedPicker->last;
}

void ImagePicker::start() {
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    openImageJNI();
#endif
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    ObjCCalls::openImage();
#endif
    
}

void ImagePicker::finished() {
    
    if (ready) {
        
        unscheduleAllSelectors();
        
        CCSprite *result;
        
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
        std::string path = getImagePathJNI();
        result = CCSprite::create(path.c_str());
        
#endif
        
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
        result =  ObjCCalls::image();
#endif
        
        result->setPosition(_position);
        
        if (_target)
            _target->addChild(result);
        
        last = result;
        
        working = false;
        
        if (_delegate)
            _delegate->didFinishPickingWithResult(true);
    }
    
}

void ImagePicker::setReady() {
    sharedPicker->ready = true;
}

void ImagePicker::dismissed() {
    
    sharedPicker->unscheduleAllSelectors();
    working = false;
    
    if (sharedPicker->_delegate)
        sharedPicker->_delegate->didFinishPickingWithResult(false);
}
