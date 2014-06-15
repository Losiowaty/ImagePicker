#include "JniHelper.h"
#include <jni.h>

#include "GalleryJNI.h"

using namespace cocos2d;

void openImageJNI() {
    
	JniMethodInfo t;
	if (JniHelper::getStaticMethodInfo(t, "org/cocos2dx/lib/Cocos2dxActivity", "openImage", "()V")) {
        	t.env->CallStaticVoidMethod(t.classID, t.methodID);
        
	        t.env->DeleteLocalRef(t.classID);
	}
}

std::string getImagePathJNI() {

    	std::string ret;
	JniMethodInfo t;
	if (JniHelper::getStaticMethodInfo(t, "org/cocos2dx/lib/Cocos2dxActivity", "getImageString", "()Ljava/lang/String;")) {
        
        
        	jstring retFromJava = (jstring)t.env->CallStaticObjectMethod(t.classID, t.methodID);
        
        	const char* str = t.env->GetStringUTFChars(retFromJava, 0);
        
	        ret = str;
        
        	t.env->ReleaseStringUTFChars(retFromJava, str);
        	t.env->DeleteLocalRef(t.classID);
	}
    
    return ret;

}
