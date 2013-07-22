#include "ObjCCalls.h" 
#include "ObjCCalls_objc.h" 
#import "../cocos2dx/platform/ios/EAGLView.h" 
#import "ImagePickerIOS.h"

ImagePickerIOS *sharedPicker = nil;

void ObjCCalls::openImage() {
    
    if (sharedPicker == nil) {
        sharedPicker = [[ImagePickerIOS alloc] init];
        [sharedPicker retain];
    }
    [sharedPicker takePicture];
}

CCSprite* ObjCCalls::image() {
    
    CCImage *imf =new CCImage();
    NSData *imgData = UIImagePNGRepresentation([sharedPicker getImage]);
    NSUInteger len = [imgData length];
    Byte *byteData = (Byte*)malloc(len);
    memcpy(byteData, [imgData bytes], len);
    imf->initWithImageData(byteData,imgData.length);
    imf->autorelease();
    
    
    CCTexture2D* pTexture = new CCTexture2D();
    pTexture->initWithImage(imf);
    pTexture->autorelease();
    
    CCSprite *sprit = CCSprite::createWithTexture(pTexture);
    
    return sprit;
}