// src/my_calculator.c
#include "com_example_jni_Calculator.h" // �������ꂽJNI�w�b�_�[���C���N���[�h
#include <stdio.h>       // printf�p

// JNIEXPORT �� JNICALL ��JNI�̋K��ŕK�v
// jint: Java��int�^�ɑΉ�����JNI�̌^
// JNIEnv*: JNI���|�C���^ (Java�I�u�W�F�N�g�ւ̃A�N�Z�X�ȂǂɎg�p)
// jobject: ���\�b�h���Ăяo���ꂽJava�I�u�W�F�N�g�̎Q�� (static���\�b�h�̏ꍇ��jclass)
// jint num1, jint num2: Java����n��������
JNIEXPORT jint JNICALL Java_com_example_jni_Calculator_addNumbers
  (JNIEnv *env, jobject obj, jint num1, jint num2) {

    // Java����󂯎����������C���ŕ\��
    printf("C native method received: num1 = %d, num2 = %d\n", (int)num1, (int)num2);

    // 2�̐��l�����Z
    jint result = num1 + num2;

    // ���Z���ʂ�C���ŕ\��
    printf("C native method calculated result: %d\n", (int)result);

    // ���Z���ʂ�Java�ɕԋp
    return result;
}
