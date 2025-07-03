#include "com_example_jni_MultipleValuesReturnByHash.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

// +++ ������Integer�I�u�W�F�N�g�Ƃ���put����w���p�[�֐� +++
void put_integer(JNIEnv *env, jobject map, jmethodID put_method, const char* key, int value) {
    // 1. Integer�N���X��T��
    jclass intClass = (*env)->FindClass(env, "java/lang/Integer");
    if (intClass == NULL) return;
    // 2. int�������Ɏ��R���X�g���N�^��ID���擾
    jmethodID intConstructor = (*env)->GetMethodID(env, intClass, "<init>", "(I)V");
    if (intConstructor == NULL) return;
    // 3. C��int�l����Integer�I�u�W�F�N�g�𐶐�
    jobject intObject = (*env)->NewObject(env, intClass, intConstructor, value);

    // 4. put���\�b�h���Ăяo��
    jstring jKey = (*env)->NewStringUTF(env, key);
    (*env)->CallObjectMethod(env, map, put_method, jKey, intObject);
    (*env)->DeleteLocalRef(env, jKey);
    (*env)->DeleteLocalRef(env, intObject);
}

// put���\�b�h���Ăяo���w���p�[�֐�
void put_string(JNIEnv *env, jobject map, jmethodID put_method, const char* key, const char* value) {
    jstring jKey = (*env)->NewStringUTF(env, key);
    jstring jValue = (*env)->NewStringUTF(env, value);
    (*env)->CallObjectMethod(env, map, put_method, jKey, jValue);
    // CallObjectMethod�̓��[�J���Q�Ƃ�Ԃ����Ƃ�����̂ŉ������
    (*env)->DeleteLocalRef(env, jKey);
    (*env)->DeleteLocalRef(env, jValue);
}

// +++ ���[�U�[��`�N���X��put����w���p�[�֐� +++
void put_custom_data(JNIEnv *env, jobject map, jmethodID put_method, const char* key, const char* info, int value) {
    // 1. MyCustomData�N���X��T�� (�p�b�P�[�W�ɂ���� "com/example/MyCustomData"�̂悤�Ɏw��)
    jclass customClass = (*env)->FindClass(env, "com/example/jni/MyCustomData");
    if (customClass == NULL) return;

    // 2. �R���X�g���N�^ID���擾 (String��int�������Ɏ��)
    jmethodID customConstructor = (*env)->GetMethodID(env, customClass, "<init>", "(Ljava/lang/String;I)V");
    if (customConstructor == NULL) return;

    // 3. �R���X�g���N�^�ɓn������(jstring)��p��
    jstring jInfo = (*env)->NewStringUTF(env, info);

    // 4. MyCustomData�I�u�W�F�N�g�𐶐�
    jobject customObject = (*env)->NewObject(env, customClass, customConstructor, jInfo, value);

    // 5. put���\�b�h��HashMap�ɒǉ�
    jstring jKey = (*env)->NewStringUTF(env, key);
    (*env)->CallObjectMethod(env, map, put_method, jKey, customObject);

    // ���[�J���Q�Ƃ����
    (*env)->DeleteLocalRef(env, jInfo);
    (*env)->DeleteLocalRef(env, customObject);
    (*env)->DeleteLocalRef(env, jKey);
}

JNIEXPORT jobject JNICALL Java_com_example_jni_MultipleValuesReturnByHash_getInfoAsMap(JNIEnv *env, jobject obj) {

    // 1. HashMap�N���X��T��
    jclass mapClass = (*env)->FindClass(env, "java/util/HashMap");
    if (mapClass == NULL) {
        return NULL;
    }

    // 2. HashMap�̃R���X�g���N�^ID���擾����
    jmethodID mapConstructor = (*env)->GetMethodID(env, mapClass, "<init>", "()V");
    if (mapConstructor == NULL) {
        return NULL;
    }

    // 3. �V����HashMap�I�u�W�F�N�g�𐶐�����
    jobject mapObject = (*env)->NewObject(env, mapClass, mapConstructor);
    if (mapObject == NULL) {
        return NULL;
    }

    // 4. put���\�b�h��ID���擾����
    // �V�O�l�`��: (Ljava/lang/Object;Ljava/lang/Object;)Ljava/lang/Object;
    jmethodID putMethod = (*env)->GetMethodID(env, mapClass, "put", "(Ljava/lang/Object;Ljava/lang/Object;)Ljava/lang/Object;");
    if (putMethod == NULL) {
        return NULL;
    }

    // 5. put���\�b�h���Ăяo���ăL�[�ƒl��ǉ�����
    put_string(env, mapObject, putMethod, "name", "Taro Yamada (from C)");
    put_string(env, mapObject, putMethod, "language", "C");
    put_string(env, mapObject, putMethod, "year", "2025");

    // --- �L�[�ƒl��ǉ� ---
    put_string(env, mapObject, putMethod, "status", "OK");
    put_integer(env, mapObject, putMethod, "code", 200);
    // ���[�U�[��`�I�u�W�F�N�g��ǉ�
    put_custom_data(env, mapObject, putMethod, "custom", "This is custom data", 999);

    // 6. �쐬����HashMap�I�u�W�F�N�g��Java�ɕԂ�
    return mapObject;
}

JNIEXPORT jobject JNICALL Java_com_example_jni_MultipleValuesReturnByHash_getNumberAsMap(JNIEnv *env, jobject obj) {
    // 1. HashMap�N���X��T��
    jclass mapClass = (*env)->FindClass(env, "java/util/HashMap");
    if (mapClass == NULL) {
        return NULL;
    }

    // 2. HashMap�̃R���X�g���N�^ID���擾����
    jmethodID mapConstructor = (*env)->GetMethodID(env, mapClass, "<init>", "()V");
    if (mapConstructor == NULL) {
        return NULL;
    }

    // 3. �V����HashMap�I�u�W�F�N�g�𐶐�����
    jobject mapObject = (*env)->NewObject(env, mapClass, mapConstructor);
    if (mapObject == NULL) {
        return NULL;
    }

    // 4. put���\�b�h��ID���擾����
    // �V�O�l�`��: (Ljava/lang/Object;Ljava/lang/Object;)Ljava/lang/Object;
    jmethodID putMethod = (*env)->GetMethodID(env, mapClass, "put", "(Ljava/lang/Object;Ljava/lang/Object;)Ljava/lang/Object;");
    if (putMethod == NULL) {
        return NULL;
    }

    // 5. put���\�b�h���Ăяo���ăL�[�ƒl��ǉ�����
    put_integer(env, mapObject, putMethod, "codeA", 100);
    put_integer(env, mapObject, putMethod, "codeB", 200);
    put_integer(env, mapObject, putMethod, "codeC", 300);

    // 6. �쐬����HashMap�I�u�W�F�N�g��Java�ɕԂ�
    return mapObject;
}
