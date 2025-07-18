#include "com_example_jni_MultipleValuesReturnByArray.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

JNIEXPORT void JNICALL Java_com_example_jni_MultipleValuesReturnByArray_getIntsIntoArray(JNIEnv *env, jobject obj, jintArray outputArray) {

    // �z��̗v�f�����`�F�b�N (�C�ӂł����A���S�̂���)
    jsize len = (*env)->GetArrayLength(env, outputArray);
    if (len < 2) {
        // �z��̃T�C�Y������Ȃ��ꍇ�͉������Ȃ�
        return;
    }

    // Java��int�z���C�ő��삷�邽�߂̃|�C���^���擾
    // isCopy��NULL�łȂ���΁AJava�̃q�[�v����C�̃������ɃR�s�[�����
    //// java�̔z���c�ƈ���ă������A�h���X���A�����Ă��Ȃ���������Ȃ��@GetIntArrayElements�Ń|�C���^�����ƘA�����ĂȂ��ꍇ�͍Ĕz�u���Ă����
    jboolean isCopy;
    jint *body = (*env)->GetIntArrayElements(env, outputArray, &isCopy);
    if (body == NULL) {
        return; // �������m�ێ��s
    }

    // C�̃|�C���^�o�R�Œl��ݒ肷��
    body[0] = 123;
    body[1] = 456;

    // �ύX��Java���̔z��ɔ��f������
    // 0: �ύX���R�s�[���AC���̃o�b�t�@���������
    (*env)->ReleaseIntArrayElements(env, outputArray, body, 0);
}

JNIEXPORT jintArray JNICALL Java_com_example_jni_MultipleValuesReturnByArray_getNewIntArray(JNIEnv *env, jobject obj) {

    // 1. �ԋp�p��Java int�z��𐶐� (���̗�ł̓T�C�Y2)
    jintArray javaArray = (*env)->NewIntArray(env, 2);
    if (javaArray == NULL) {
        return NULL; // �������m�ێ��s
    }

    // 2. Java�̔z��ɐݒ肵�����f�[�^��C�̔z��(�o�b�t�@)�ŗp�ӂ���
    jint c_buffer[2];
    c_buffer[0] = 999;
    c_buffer[1] = 888;

    // 3. C�̃o�b�t�@�̓��e���AJava�̔z��ɃR�s�[����
    // (*env)->Set<Type>ArrayRegion(env, javaArray, startIndex, copyLength, c_buffer);
    //// SetIntArrayRegion�֐���C�̃�������ɂ���A�������f�[�^�u���b�N�i�z��j��Java�̔z��ɃR�s�[���邽�߂̂��̂Ȃ̂ŁAC�̔z��i�o�b�t�@�j���o�R����K�v������܂��B
    (*env)->SetIntArrayRegion(env, javaArray, 0, 2, c_buffer);

    // 4. ��������Java�z��̎Q�Ƃ�Ԃ�
    return javaArray;
}
