#include "com_example_jni_MultipleValuesReturnByGlobal.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

// --- ここが危険なグローバル変数 ---
// 複数のスレッドから同時にアクセスされると破綻する
static int g_int_value;
static char g_string_buffer[256];
// ---

// グローバル変数に値を設定する関数
JNIEXPORT void JNICALL Java_com_example_jni_MultipleValuesReturnByGlobal_setValuesToGlobals(JNIEnv *env, jobject obj, jint val1, jstring val2) {
    // グローバル変数に整数値を設定
    g_int_value = val1;

    // グローバルバッファに文字列をコピー
    //// strncpyで使えるようにjstringをchar*に変換する
    const char *nativeString = (*env)->GetStringUTFChars(env, val2, 0);
    strncpy(g_string_buffer, nativeString, sizeof(g_string_buffer) - 1);
    g_string_buffer[sizeof(g_string_buffer) - 1] = '\0'; // 念のため終端文字
    (*env)->ReleaseStringUTFChars(env, val2, nativeString);
}

// グローバル変数から値を取得する関数
JNIEXPORT jintArray JNICALL Java_com_example_jni_MultipleValuesReturnByGlobal_getValuesFromGlobals(JNIEnv *env, jobject obj) {
    // 返却用のJava int配列を生成 (サイズ2)
    jintArray resultArray = (*env)->NewIntArray(env, 2);
    if (resultArray == NULL) {
        return NULL; // メモリ確保失敗
    }

    jint fill[2];
    fill[0] = g_int_value;
    // 分かりやすくするため、文字列の最初の1文字のASCIIコードを入れる
    fill[1] = (int)g_string_buffer[0];

    // Cの配列(fill)の内容をJavaの配列(resultArray)にコピー
    (*env)->SetIntArrayRegion(env, resultArray, 0, 2, fill);

    return resultArray;
}

JNIEXPORT void JNICALL Java_com_example_jni_MultipleValuesReturnByGlobal_setJavaStaticFields(JNIEnv *env, jobject obj, jint val1, jstring val2) {
    // 1. クラスの参照を取得
	//// クラス名はフルパスで長くなるのでリテラル定数に切った方がいいかも
    jclass cls = (*env)->FindClass(env, "com/example/jni/MultipleValuesReturnByGlobal");
    if (cls == NULL) return;

    // 2. 静的フィールドのIDを取得
    //// cからjavaのグローバル変数を触る(GET)
    jfieldID intFieldID = (*env)->GetStaticFieldID(env, cls, "staticIntValue", "I");
    jfieldID stringFieldID = (*env)->GetStaticFieldID(env, cls, "staticStringValue", "Ljava/lang/String;");
    if (intFieldID == NULL || stringFieldID == NULL) return;

    // 3. 静的フィールドに値を設定
    //// cからjavaのグローバル変数を触る(SET)
    (*env)->SetStaticIntField(env, cls, intFieldID, val1 + 100);
    (*env)->SetStaticObjectField(env, cls, stringFieldID, val2);
}


JNIEXPORT jstring JNICALL Java_com_example_jni_MultipleValuesReturnByGlobal_getJavaStaticFieldsAsString(JNIEnv *env, jobject obj) {
    // 1. クラスの参照を取得
    jclass cls = (*env)->FindClass(env, "com/example/jni/MultipleValuesReturnByGlobal");
    if (cls == NULL) return NULL;

    // 2. 静的フィールドのIDを取得
    jfieldID intFieldID = (*env)->GetStaticFieldID(env, cls, "staticIntValue", "I");
    jfieldID stringFieldID = (*env)->GetStaticFieldID(env, cls, "staticStringValue", "Ljava/lang/String;");
    if (intFieldID == NULL || stringFieldID == NULL) return NULL;

    // 3. 静的フィールドから値を取得
    jint i_val = (*env)->GetStaticIntField(env, cls, intFieldID) + 100;
    jstring s_val = (jstring)(*env)->GetStaticObjectField(env, cls, stringFieldID);

    const char *s_val_native = (*env)->GetStringUTFChars(env, s_val, 0);

    // 4. 結果を整形して文字列として返す
    char buffer[256];
    sprintf(buffer, "int=%d, string=\"%s\"", i_val, s_val_native);

    (*env)->ReleaseStringUTFChars(env, s_val, s_val_native);

    return (*env)->NewStringUTF(env, buffer);
}

// C側の構造体で返す
// java側のlong型にポインタを受ける
// 構造体からのメンバ変数の操作はC側のネイティブメソッドを用意する
// ファイナライズの処理　ポインタの開放
