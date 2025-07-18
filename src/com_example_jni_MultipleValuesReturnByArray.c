#include "com_example_jni_MultipleValuesReturnByArray.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

JNIEXPORT void JNICALL Java_com_example_jni_MultipleValuesReturnByArray_getIntsIntoArray(JNIEnv *env, jobject obj, jintArray outputArray) {

    // 配列の要素数をチェック (任意ですが、安全のため)
    jsize len = (*env)->GetArrayLength(env, outputArray);
    if (len < 2) {
        // 配列のサイズが足りない場合は何もしない
        return;
    }

    // Javaのint配列をCで操作するためのポインタを取得
    // isCopyがNULLでなければ、JavaのヒープからCのメモリにコピーされる
    //// javaの配列はcと違ってメモリアドレスが連続していないかもしれない　GetIntArrayElementsでポインタを取ると連続してない場合は再配置してくれる
    jboolean isCopy;
    jint *body = (*env)->GetIntArrayElements(env, outputArray, &isCopy);
    if (body == NULL) {
        return; // メモリ確保失敗
    }

    // Cのポインタ経由で値を設定する
    body[0] = 123;
    body[1] = 456;

    // 変更をJava側の配列に反映させる
    // 0: 変更をコピーし、C側のバッファを解放する
    (*env)->ReleaseIntArrayElements(env, outputArray, body, 0);
}

JNIEXPORT jintArray JNICALL Java_com_example_jni_MultipleValuesReturnByArray_getNewIntArray(JNIEnv *env, jobject obj) {

    // 1. 返却用のJava int配列を生成 (この例ではサイズ2)
    jintArray javaArray = (*env)->NewIntArray(env, 2);
    if (javaArray == NULL) {
        return NULL; // メモリ確保失敗
    }

    // 2. Javaの配列に設定したいデータをCの配列(バッファ)で用意する
    jint c_buffer[2];
    c_buffer[0] = 999;
    c_buffer[1] = 888;

    // 3. Cのバッファの内容を、Javaの配列にコピーする
    // (*env)->Set<Type>ArrayRegion(env, javaArray, startIndex, copyLength, c_buffer);
    //// SetIntArrayRegion関数はCのメモリ上にある連続したデータブロック（配列）をJavaの配列にコピーするためのものなので、Cの配列（バッファ）を経由する必要があります。
    (*env)->SetIntArrayRegion(env, javaArray, 0, 2, c_buffer);

    // 4. 生成したJava配列の参照を返す
    return javaArray;
}
