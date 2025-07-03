// src/my_string_manipulator.c
#include "com_example_jni_StringManipulator.h" // 生成されたJNIヘッダーをインクルード
#include <stdio.h>   // printf用
#include <string.h>  // strcat, strlen用
#include <stdlib.h>  // malloc, free用

// Java_パッケージ名_クラス名_メソッド名 の命名規則に従う
JNIEXPORT jstring JNICALL Java_com_example_jni_StringManipulator_concatenateStrings
  (JNIEnv *env, jobject obj, jstring javaStr1, jstring javaStr2) {

    // JavaのjstringをCのchar*に変換
    const char *cStr1 = (*env)->GetStringUTFChars(env, javaStr1, NULL);
    const char *cStr2 = (*env)->GetStringUTFChars(env, javaStr2, NULL);

    if (cStr1 == NULL || cStr2 == NULL) {
        // メモリ不足または文字列変換エラー
        // ここでJava側に例外をスローすることも可能ですが、今回はシンプルにNULLを返します
        if (cStr1 != NULL) (*env)->ReleaseStringUTFChars(env, javaStr1, cStr1);
        if (cStr2 != NULL) (*env)->ReleaseStringUTFChars(env, javaStr2, cStr2);
        return NULL;
    }

    // 結合後の文字列に必要なメモリを確保
    // +1 はヌル終端文字のため
    size_t len1 = strlen(cStr1);
    size_t len2 = strlen(cStr2);
    size_t totalLen = len1 + len2;
    char *resultCStr = (char *)malloc(totalLen + 1);

    if (resultCStr == NULL) {
        // メモリ確保失敗
        (*env)->ReleaseStringUTFChars(env, javaStr1, cStr1);
        (*env)->ReleaseStringUTFChars(env, javaStr2, cStr2);
        // Java側に例外をスローする例:
        // (*env)->ThrowNew(env, (*env)->FindClass(env, "java/lang/OutOfMemoryError"), "Failed to allocate memory in native code");
        return NULL;
    }

    // 文字列を結合
    strcpy(resultCStr, cStr1);
    strcat(resultCStr, cStr2);

    // デバッグ用出力
    printf("C native method received: \"%s\" and \"%s\"\n", cStr1, cStr2);
    printf("C native method concatenated result: \"%s\"\n", resultCStr);

    // Cのchar*をJavaのjstringに変換
    jstring javaResult = (*env)->NewStringUTF(env, resultCStr);

    // 確保したCのメモリを解放
    free(resultCStr);

    // GetStringUTFCharsで取得したC文字列を解放 (重要!)
    (*env)->ReleaseStringUTFChars(env, javaStr1, cStr1);
    (*env)->ReleaseStringUTFChars(env, javaStr2, cStr2);

    // Javaに結果を返す
    return javaResult;
}
