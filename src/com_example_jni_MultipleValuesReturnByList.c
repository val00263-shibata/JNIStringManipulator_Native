#include "com_example_jni_MultipleValuesReturnByList.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

JNIEXPORT jobject JNICALL Java_com_example_jni_MultipleValuesReturnByList_getList(JNIEnv *env, jobject obj) {
    // 1. ArrayList�̃N���X�ƃ��\�b�hID���擾
    jclass listClass = (*env)->FindClass(env, "java/util/ArrayList");
    if (listClass == NULL) return NULL;
    jmethodID listConstructor = (*env)->GetMethodID(env, listClass, "<init>", "()V");
    if (listConstructor == NULL) return NULL;
    jmethodID addMethod = (*env)->GetMethodID(env, listClass, "add", "(Ljava/lang/Object;)Z");
    if (addMethod == NULL) return NULL;

    // 2. �V����ArrayList�I�u�W�F�N�g�𐶐�
    jobject listObject = (*env)->NewObject(env, listClass, listConstructor);
    if (listObject == NULL) return NULL;

    // --- �v�f2: Integer�I�u�W�F�N�g��ǉ� ---
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

    // 1. ArrayList�̃N���X�ƃ��\�b�hID���擾
    jclass listClass = (*env)->FindClass(env, "java/util/ArrayList");
    if (listClass == NULL) return NULL;
    jmethodID listConstructor = (*env)->GetMethodID(env, listClass, "<init>", "()V");
    if (listConstructor == NULL) return NULL;
    jmethodID addMethod = (*env)->GetMethodID(env, listClass, "add", "(Ljava/lang/Object;)Z");
    if (addMethod == NULL) return NULL;

    // 2. �V����ArrayList�I�u�W�F�N�g�𐶐�
    jobject listObject = (*env)->NewObject(env, listClass, listConstructor);
    if (listObject == NULL) return NULL;

    // --- �v�f1: String�I�u�W�F�N�g��ǉ� ---
    jstring stringItem = (*env)->NewStringUTF(env, "A string from C");
    (*env)->CallBooleanMethod(env, listObject, addMethod, stringItem);
    (*env)->DeleteLocalRef(env, stringItem);

    // --- �v�f2: Integer�I�u�W�F�N�g��ǉ� ---
    jclass intClass = (*env)->FindClass(env, "java/lang/Integer");
    if (intClass == NULL) return NULL;
    jmethodID intConstructor = (*env)->GetMethodID(env, intClass, "<init>", "(I)V");
    if (intConstructor == NULL) return NULL;
    jobject intObject = (*env)->NewObject(env, intClass, intConstructor, 12345);
    (*env)->CallBooleanMethod(env, listObject, addMethod, intObject);
    (*env)->DeleteLocalRef(env, intObject);

    // --- �v�f3: MyCustomData�I�u�W�F�N�g��ǉ� ---
    jclass customClass = (*env)->FindClass(env, "com/example/jni/ListCustomData");
    if (customClass == NULL) return NULL;
    jmethodID customConstructor = (*env)->GetMethodID(env, customClass, "<init>", "(Ljava/lang/String;)V");
    if (customConstructor == NULL) return NULL;
    jstring customStringArg = (*env)->NewStringUTF(env, "This is custom data!");
    jobject customObject = (*env)->NewObject(env, customClass, customConstructor, customStringArg);
    (*env)->CallBooleanMethod(env, listObject, addMethod, customObject);
    (*env)->DeleteLocalRef(env, customStringArg);
    (*env)->DeleteLocalRef(env, customObject);

    // 3. �쐬����List�I�u�W�F�N�g��Ԃ�
    return listObject;
}
