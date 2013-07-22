#ifndef __ImagePicker__ImagePicker__
#define __ImagePicker__ImagePicker__

#include "cocos2d.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#include "ObjCCalls.h"
#endif

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "platform/android/jni/GalleryJNI.h"
#include "platform/android/jni/JniHelper.h"
#endif

using namespace cocos2d;


class ImagePickerDelegate {
    
public:
    virtual void didFinishPickingWithResult(bool result) = 0;
    
};

class ImagePicker : public CCNode {
    
public:
    static bool pickImage(CCNode *target, CCPoint position, ImagePickerDelegate *delegate);
    
    static CCSprite* getLastSprite();
    static void dismissed();
    static void setReady();
    
private:
    CCNode *_target;
    CCPoint _position;
    CCSprite *last;
    
    static ImagePicker *sharedPicker;
    
    ImagePickerDelegate *_delegate;
    bool ready;
    static bool working;
    
    ImagePicker() {};
    
    void start();
    void finished();
};

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)

#ifdef __cplusplus
extern "C" {
#endif
    void Java_org_cocos2dx_lib_Cocos2dxActivity_informNative(JNIEnv *env, jobject thiz);
    void Java_org_cocos2dx_lib_Cocos2dxActivity_informNativeCancel(JNIEnv *env, jobject thiz);
#ifdef __cplusplus
}
#endif

#endif /* if CC_PLATFORM_ANDROID) */

#endif /* defined(__ImagePicker__ImagePicker__) */
