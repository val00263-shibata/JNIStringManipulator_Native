// src/my_string_manipulator.c
#include "com_example_jni_StringManipulator.h" // �������ꂽJNI�w�b�_�[���C���N���[�h
#include <stdio.h>   // printf�p
#include <string.h>  // strcat, strlen�p
#include <stdlib.h>  // malloc, free�p

// Java_�p�b�P�[�W��_�N���X��_���\�b�h�� �̖����K���ɏ]��
JNIEXPORT jstring JNICALL Java_com_example_jni_StringManipulator_concatenateStrings
  (JNIEnv *env, jobject obj, jstring javaStr1, jstring javaStr2) {

    // Java��jstring��C��char*�ɕϊ�
    const char *cStr1 = (*env)->GetStringUTFChars(env, javaStr1, NULL);
    const char *cStr2 = (*env)->GetStringUTFChars(env, javaStr2, NULL);

    if (cStr1 == NULL || cStr2 == NULL) {
        // �������s���܂��͕�����ϊ��G���[
        // ������Java���ɗ�O���X���[���邱�Ƃ��\�ł����A����̓V���v����NULL��Ԃ��܂�
        if (cStr1 != NULL) (*env)->ReleaseStringUTFChars(env, javaStr1, cStr1);
        if (cStr2 != NULL) (*env)->ReleaseStringUTFChars(env, javaStr2, cStr2);
        return NULL;
    }

    // ������̕�����ɕK�v�ȃ��������m��
    // +1 �̓k���I�[�����̂���
    size_t len1 = strlen(cStr1);
    size_t len2 = strlen(cStr2);
    size_t totalLen = len1 + len2;
    char *resultCStr = (char *)malloc(totalLen + 1);

    if (resultCStr == NULL) {
        // �������m�ێ��s
        (*env)->ReleaseStringUTFChars(env, javaStr1, cStr1);
        (*env)->ReleaseStringUTFChars(env, javaStr2, cStr2);
        // Java���ɗ�O���X���[�����:
        // (*env)->ThrowNew(env, (*env)->FindClass(env, "java/lang/OutOfMemoryError"), "Failed to allocate memory in native code");
        return NULL;
    }

    // �����������
    strcpy(resultCStr, cStr1);
    strcat(resultCStr, cStr2);

    // �f�o�b�O�p�o��
    printf("C native method received: \"%s\" and \"%s\"\n", cStr1, cStr2);
    printf("C native method concatenated result: \"%s\"\n", resultCStr);

    // C��char*��Java��jstring�ɕϊ�
    jstring javaResult = (*env)->NewStringUTF(env, resultCStr);

    // �m�ۂ���C�̃����������
    free(resultCStr);

    // GetStringUTFChars�Ŏ擾����C���������� (�d�v!)
    (*env)->ReleaseStringUTFChars(env, javaStr1, cStr1);
    (*env)->ReleaseStringUTFChars(env, javaStr2, cStr2);

    // Java�Ɍ��ʂ�Ԃ�
    return javaResult;
}
