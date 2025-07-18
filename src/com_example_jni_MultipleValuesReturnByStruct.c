#include "com_example_jni_MultipleValuesReturnByStruct.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

JNIEXPORT jobject JNICALL Java_com_example_jni_MultipleValuesReturnByStruct_getMultipleValues(JNIEnv *env, jobject obj) {

    // 1. 返却値用のJavaクラスを探す
    jclass resultDataClass = (*env)->FindClass(env, "com/example/jni/ResultData");
    if (resultDataClass == NULL) {
        return NULL; // クラスが見つからない
    }

    // 2. コンストラクタのメソッドIDを取得する (<init>はコンストラクタを指す)
    jmethodID constructor = (*env)->GetMethodID(env, resultDataClass, "<init>", "()V");
    if (constructor == NULL) {
        return NULL; // コンストラクタが見つからない
    }

    // 3. 新しいResultDataオブジェクトを生成する
    jobject resultObject = (*env)->NewObject(env, resultDataClass, constructor);
    if (resultObject == NULL) {
        return NULL; // オブジェクト生成失敗
    }

    // 4. 設定したいフィールドのIDを取得する
    // 整数のフィールドID
    jfieldID intField = (*env)->GetFieldID(env, resultDataClass, "intValue", "I");
    // 文字列のフィールドID
    jfieldID stringField = (*env)->GetFieldID(env, resultDataClass, "stringValue", "Ljava/lang/String;");

    if (intField == NULL || stringField == NULL) {
        return NULL; // フィールドが見つからない
    }

    // 5. フィールドに値を設定する
    // 整数値を設定
    (*env)->SetIntField(env, resultObject, intField, 2025);

    // 文字列値を設定
    const char* c_str = "Hello from C!";
    jstring javaString = (*env)->NewStringUTF(env, c_str);
    (*env)->SetObjectField(env, resultObject, stringField, javaString);

    // 6. 作成したオブジェクトをJavaに返す
    return resultObject;
}
