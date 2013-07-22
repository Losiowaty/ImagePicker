ImagePicker
===========

ImagePicker utility for cocos2d-x (Android and iOS[iPad] only).

This utility lets you load images from device gallery and load it to your application as a CCSprite.
At the moment it supports only Android and iOS platforms, if I find more time I will add support for other.

Guide
=====
Installation
------------

For Android :

1. [ANDROID] Copy GalleryJNI.cpp and GalleryJNI.h to COCOS2DX_ROOT/cocos2dx/platform/android/jni

2. [ANDROID] Add <pre>platform/android/jni/GalleryJNI.cpp \ </pre> to Android.mk in COCOS2DX_ROOT/cocos2dx

3. [ANDROID] Copy & paste the contents of ImagePickerAndroid.java to Cocos2dxActivity.java, then rebuild cocos2dx library

4. [iOS] Add ObjCCalls folder to your iOS project

5. [GENERAL] Add ImagePicker.cpp and ImagePicker.h to your project

Usage
-----

Usage is really simple - you basically call a static method
  <pre>ImagePicker::pickImage(CCNode *target, CCPoint position, ImagePickerDelegate *delegate);</pre>
  
and after the user picks the image it will be added as a child to 'target' node at specified position.
If you want to get a pointer to added CCSprite you can call
  <pre>ImagePicker::getLastSprite();</pre>
  
but remember that it is not safe to make any assumptions about if the user actually did pick the image or not.

Because of that, if you want to get the pointer to created CCSprite, you should subclass ImagePickerDelegate and
implement the
  <pre>virutal void didFinishPickingWithResult(bool result);</pre>
  
It will be called when the user picked the image or cancelled.
