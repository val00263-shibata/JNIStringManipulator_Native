#include <jni.h>
#include <stdio.h>
#include <string.h>
#include "com_example_jni_ReferenceCall.h"

// 1. String����������֐�
JNIEXPORT jstring JNICALL Java_com_example_jni_ReferenceCall_processString(JNIEnv *env, jobject obj, jstring input) {
    // Java��String (jstring) �� C�̕����� (const char*) �ɕϊ�
    const char *nativeString = (*env)->GetStringUTFChars(env, input, 0);
    if (nativeString == NULL) {
        return NULL; // �������m�ێ��s
    }

    // �V������������i�[���邽�߂̃o�b�t�@
    char newString[256];
    // �󂯎�����������C�Œǉ����镶���������
    sprintf(newString, "%s (processed in C)", nativeString);

    // C�̕����� (char*) �� Java��String (jstring) �ɕϊ�
    jstring result = (*env)->NewStringUTF(env, newString);

    // GetStringUTFChars�Ŋm�ۂ��������������
    (*env)->ReleaseStringUTFChars(env, input, nativeString);

    // Java�Ɍ��ʂ�Ԃ�
    return result;
}


// 2. UserData�I�u�W�F�N�g����������֐�
JNIEXPORT void JNICALL Java_com_example_jni_ReferenceCall_processUserData(JNIEnv *env, jobject obj, jobject userData) {
    // UserData�N���X�ւ̎Q�Ƃ��擾
    jclass userDataClass = (*env)->GetObjectClass(env, userData);
    if (userDataClass == NULL) {
        return;
    }

    // --- userId�t�B�[���h�𑀍� ---
    // userId�t�B�[���h��ID���擾
    jfieldID userIdField = (*env)->GetFieldID(env, userDataClass, "userId", "I"); // "I" ��int�^������
    if (userIdField == NULL) {
        return;
    }
    // ���݂�userId�̒l���擾
    jint currentId = (*env)->GetIntField(env, userData, userIdField);
    // userId�̒l��ύX (���݂̒l + 500)
    (*env)->SetIntField(env, userData, userIdField, currentId + 500);


    // --- userName�t�B�[���h�𑀍� ---
    // userName�t�B�[���h��ID���擾
    jfieldID userNameField = (*env)->GetFieldID(env, userDataClass, "userName", "Ljava/lang/String;");
    if (userNameField == NULL) {
        return;
    }
    // ���݂�userName (jstring) ���擾
    jstring currentName = (jstring)(*env)->GetObjectField(env, userData, userNameField);
    // jstring��C�̕�����ɕϊ�
    const char *nativeName = (*env)->GetStringUTFChars(env, currentName, 0);

    // �V�������O���쐬
    char newName[256];
    sprintf(newName, "%s (updated by C!)", nativeName);

    // C�̕������V����jstring�ɕϊ�
    jstring newJniName = (*env)->NewStringUTF(env, newName);

    // userName�t�B�[���h�̒l��V����jstring�ōX�V
    (*env)->SetObjectField(env, userData, userNameField, newJniName);

    // ���������
    (*env)->ReleaseStringUTFChars(env, currentName, nativeName);
}

