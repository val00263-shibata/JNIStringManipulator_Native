#include "com_example_jni_MultipleValuesReturnByGlobal.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

// --- �������댯�ȃO���[�o���ϐ� ---
// �����̃X���b�h���瓯���ɃA�N�Z�X�����Ɣj�]����
static int g_int_value;
static char g_string_buffer[256];
// ---

// �O���[�o���ϐ��ɒl��ݒ肷��֐�
JNIEXPORT void JNICALL Java_com_example_jni_MultipleValuesReturnByGlobal_setValuesToGlobals(JNIEnv *env, jobject obj, jint val1, jstring val2) {
    // �O���[�o���ϐ��ɐ����l��ݒ�
    g_int_value = val1;

    // �O���[�o���o�b�t�@�ɕ�������R�s�[
    //// strncpy�Ŏg����悤��jstring��char*�ɕϊ�����
    const char *nativeString = (*env)->GetStringUTFChars(env, val2, 0);
    strncpy(g_string_buffer, nativeString, sizeof(g_string_buffer) - 1);
    g_string_buffer[sizeof(g_string_buffer) - 1] = '\0'; // �O�̂��ߏI�[����
    (*env)->ReleaseStringUTFChars(env, val2, nativeString);
}

// �O���[�o���ϐ�����l���擾����֐�
JNIEXPORT jintArray JNICALL Java_com_example_jni_MultipleValuesReturnByGlobal_getValuesFromGlobals(JNIEnv *env, jobject obj) {
    // �ԋp�p��Java int�z��𐶐� (�T�C�Y2)
    jintArray resultArray = (*env)->NewIntArray(env, 2);
    if (resultArray == NULL) {
        return NULL; // �������m�ێ��s
    }

    jint fill[2];
    fill[0] = g_int_value;
    // ������₷�����邽�߁A������̍ŏ���1������ASCII�R�[�h������
    fill[1] = (int)g_string_buffer[0];

    // C�̔z��(fill)�̓��e��Java�̔z��(resultArray)�ɃR�s�[
    (*env)->SetIntArrayRegion(env, resultArray, 0, 2, fill);

    return resultArray;
}

JNIEXPORT void JNICALL Java_com_example_jni_MultipleValuesReturnByGlobal_setJavaStaticFields(JNIEnv *env, jobject obj, jint val1, jstring val2) {
    // 1. �N���X�̎Q�Ƃ��擾
	//// �N���X���̓t���p�X�Œ����Ȃ�̂Ń��e�����萔�ɐ؂���������������
    jclass cls = (*env)->FindClass(env, "com/example/jni/MultipleValuesReturnByGlobal");
    if (cls == NULL) return;

    // 2. �ÓI�t�B�[���h��ID���擾
    //// c����java�̃O���[�o���ϐ���G��(GET)
    jfieldID intFieldID = (*env)->GetStaticFieldID(env, cls, "staticIntValue", "I");
    jfieldID stringFieldID = (*env)->GetStaticFieldID(env, cls, "staticStringValue", "Ljava/lang/String;");
    if (intFieldID == NULL || stringFieldID == NULL) return;

    // 3. �ÓI�t�B�[���h�ɒl��ݒ�
    //// c����java�̃O���[�o���ϐ���G��(SET)
    (*env)->SetStaticIntField(env, cls, intFieldID, val1 + 100);
    (*env)->SetStaticObjectField(env, cls, stringFieldID, val2);
}


JNIEXPORT jstring JNICALL Java_com_example_jni_MultipleValuesReturnByGlobal_getJavaStaticFieldsAsString(JNIEnv *env, jobject obj) {
    // 1. �N���X�̎Q�Ƃ��擾
    jclass cls = (*env)->FindClass(env, "com/example/jni/MultipleValuesReturnByGlobal");
    if (cls == NULL) return NULL;

    // 2. �ÓI�t�B�[���h��ID���擾
    jfieldID intFieldID = (*env)->GetStaticFieldID(env, cls, "staticIntValue", "I");
    jfieldID stringFieldID = (*env)->GetStaticFieldID(env, cls, "staticStringValue", "Ljava/lang/String;");
    if (intFieldID == NULL || stringFieldID == NULL) return NULL;

    // 3. �ÓI�t�B�[���h����l���擾
    jint i_val = (*env)->GetStaticIntField(env, cls, intFieldID) + 100;
    jstring s_val = (jstring)(*env)->GetStaticObjectField(env, cls, stringFieldID);

    const char *s_val_native = (*env)->GetStringUTFChars(env, s_val, 0);

    // 4. ���ʂ𐮌`���ĕ�����Ƃ��ĕԂ�
    char buffer[256];
    sprintf(buffer, "int=%d, string=\"%s\"", i_val, s_val_native);

    (*env)->ReleaseStringUTFChars(env, s_val, s_val_native);

    return (*env)->NewStringUTF(env, buffer);
}

// C���̍\���̂ŕԂ�
// java����long�^�Ƀ|�C���^���󂯂�
// �\���̂���̃����o�ϐ��̑����C���̃l�C�e�B�u���\�b�h��p�ӂ���
// �t�@�C�i���C�Y�̏����@�|�C���^�̊J��
