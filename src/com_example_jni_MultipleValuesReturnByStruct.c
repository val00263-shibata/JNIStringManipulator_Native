#include "com_example_jni_MultipleValuesReturnByStruct.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

JNIEXPORT jobject JNICALL Java_com_example_jni_MultipleValuesReturnByStruct_getMultipleValues(JNIEnv *env, jobject obj) {

    // 1. �ԋp�l�p��Java�N���X��T��
    jclass resultDataClass = (*env)->FindClass(env, "com/example/jni/ResultData");
    if (resultDataClass == NULL) {
        return NULL; // �N���X��������Ȃ�
    }

    // 2. �R���X�g���N�^�̃��\�b�hID���擾���� (<init>�̓R���X�g���N�^���w��)
    jmethodID constructor = (*env)->GetMethodID(env, resultDataClass, "<init>", "()V");
    if (constructor == NULL) {
        return NULL; // �R���X�g���N�^��������Ȃ�
    }

    // 3. �V����ResultData�I�u�W�F�N�g�𐶐�����
    jobject resultObject = (*env)->NewObject(env, resultDataClass, constructor);
    if (resultObject == NULL) {
        return NULL; // �I�u�W�F�N�g�������s
    }

    // 4. �ݒ肵�����t�B�[���h��ID���擾����
    // �����̃t�B�[���hID
    jfieldID intField = (*env)->GetFieldID(env, resultDataClass, "intValue", "I");
    // ������̃t�B�[���hID
    jfieldID stringField = (*env)->GetFieldID(env, resultDataClass, "stringValue", "Ljava/lang/String;");

    if (intField == NULL || stringField == NULL) {
        return NULL; // �t�B�[���h��������Ȃ�
    }

    // 5. �t�B�[���h�ɒl��ݒ肷��
    // �����l��ݒ�
    (*env)->SetIntField(env, resultObject, intField, 2025);

    // ������l��ݒ�
    const char* c_str = "Hello from C!";
    jstring javaString = (*env)->NewStringUTF(env, c_str);
    (*env)->SetObjectField(env, resultObject, stringField, javaString);

    // 6. �쐬�����I�u�W�F�N�g��Java�ɕԂ�
    return resultObject;
}
