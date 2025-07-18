#include "com_example_jni_MultipleValuesReturnByList.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

JNIEXPORT jobject JNICALL Java_com_example_jni_MultipleValuesReturnByList_getList(JNIEnv *env, jobject obj) {
    // 1. ArrayListのクラスとメソッドIDを取得
    jclass listClass = (*env)->FindClass(env, "java/util/ArrayList");
    if (listClass == NULL) return NULL;
    jmethodID listConstructor = (*env)->GetMethodID(env, listClass, "<init>", "()V");
    if (listConstructor == NULL) return NULL;
    jmethodID addMethod = (*env)->GetMethodID(env, listClass, "add", "(Ljava/lang/Object;)Z");
    if (addMethod == NULL) return NULL;

    // 2. 新しいArrayListオブジェクトを生成
    jobject listObject = (*env)->NewObject(env, listClass, listConstructor);
    if (listObject == NULL) return NULL;

    // --- 要素2: Integerオブジェクトを追加 ---
    jclass intClass = (*env)->FindClass(env, "java/lang/Integer");
    if (intClass == NULL) return NULL;
    jmethodID intConstructor = (*env)->GetMethodID(env, intClass, "<init>", "(I)V");
    if (intConstructor == NULL) return NULL;
    jobject intObject = (*env)->NewObject(env, intClass, intConstructor, 12345);
    (*env)->CallBooleanMethod(env, listObject, addMethod, intObject);
    (*env)->DeleteLocalRef(env, intObject);

    intObject = (*env)->NewObject(env, intClass, intConstructor, 67890);
    (*env)->CallBooleanMethod(env, listObject, addMethod, intObject);
    (*env)->DeleteLocalRef(env, intObject);

    return listObject;
}

JNIEXPORT jobject JNICALL Java_com_example_jni_MultipleValuesReturnByList_getMixedList(JNIEnv *env, jobject obj) {

    // 1. ArrayListのクラスとメソッドIDを取得
    jclass listClass = (*env)->FindClass(env, "java/util/ArrayList");
    if (listClass == NULL) return NULL;
    jmethodID listConstructor = (*env)->GetMethodID(env, listClass, "<init>", "()V");
    if (listConstructor == NULL) return NULL;
    jmethodID addMethod = (*env)->GetMethodID(env, listClass, "add", "(Ljava/lang/Object;)Z");
    if (addMethod == NULL) return NULL;

    // 2. 新しいArrayListオブジェクトを生成
    jobject listObject = (*env)->NewObject(env, listClass, listConstructor);
    if (listObject == NULL) return NULL;

    // --- 要素1: Stringオブジェクトを追加 ---
    jstring stringItem = (*env)->NewStringUTF(env, "A string from C");
    (*env)->CallBooleanMethod(env, listObject, addMethod, stringItem);
    (*env)->DeleteLocalRef(env, stringItem);

    // --- 要素2: Integerオブジェクトを追加 ---
    jclass intClass = (*env)->FindClass(env, "java/lang/Integer");
    if (intClass == NULL) return NULL;
    jmethodID intConstructor = (*env)->GetMethodID(env, intClass, "<init>", "(I)V");
    if (intConstructor == NULL) return NULL;
    jobject intObject = (*env)->NewObject(env, intClass, intConstructor, 12345);
    (*env)->CallBooleanMethod(env, listObject, addMethod, intObject);
    (*env)->DeleteLocalRef(env, intObject);

    // --- 要素3: MyCustomDataオブジェクトを追加 ---
    jclass customClass = (*env)->FindClass(env, "com/example/jni/ListCustomData");
    if (customClass == NULL) return NULL;
    jmethodID customConstructor = (*env)->GetMethodID(env, customClass, "<init>", "(Ljava/lang/String;)V");
    if (customConstructor == NULL) return NULL;
    jstring customStringArg = (*env)->NewStringUTF(env, "This is custom data!");
    jobject customObject = (*env)->NewObject(env, customClass, customConstructor, customStringArg);
    (*env)->CallBooleanMethod(env, listObject, addMethod, customObject);
    (*env)->DeleteLocalRef(env, customStringArg);
    (*env)->DeleteLocalRef(env, customObject);

    // 3. 作成したListオブジェクトを返す
    return listObject;
}
