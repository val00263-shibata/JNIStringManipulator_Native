#include <jni.h>
#include <stdio.h>
#include <string.h>
#include "com_example_jni_ReferenceCall.h"

// 1. Stringを処理する関数
JNIEXPORT jstring JNICALL Java_com_example_jni_ReferenceCall_processString(JNIEnv *env, jobject obj, jstring input) {
    // JavaのString (jstring) を Cの文字列 (const char*) に変換
    const char *nativeString = (*env)->GetStringUTFChars(env, input, 0);
    if (nativeString == NULL) {
        return NULL; // メモリ確保失敗
    }

    // 新しい文字列を格納するためのバッファ
    char newString[256];
    // 受け取った文字列とCで追加する文字列を結合
    sprintf(newString, "%s (processed in C)", nativeString);

    // Cの文字列 (char*) を JavaのString (jstring) に変換
    jstring result = (*env)->NewStringUTF(env, newString);

    // GetStringUTFCharsで確保したメモリを解放
    (*env)->ReleaseStringUTFChars(env, input, nativeString);

    // Javaに結果を返す
    return result;
}


// 2. UserDataオブジェクトを処理する関数
JNIEXPORT void JNICALL Java_com_example_jni_ReferenceCall_processUserData(JNIEnv *env, jobject obj, jobject userData) {
    // UserDataクラスへの参照を取得
    jclass userDataClass = (*env)->GetObjectClass(env, userData);
    if (userDataClass == NULL) {
        return;
    }

    // --- userIdフィールドを操作 ---
    // userIdフィールドのIDを取得
    jfieldID userIdField = (*env)->GetFieldID(env, userDataClass, "userId", "I"); // "I" はint型を示す
    if (userIdField == NULL) {
        return;
    }
    // 現在のuserIdの値を取得
    jint currentId = (*env)->GetIntField(env, userData, userIdField);
    // userIdの値を変更 (現在の値 + 500)
    (*env)->SetIntField(env, userData, userIdField, currentId + 500);


    // --- userNameフィールドを操作 ---
    // userNameフィールドのIDを取得
    jfieldID userNameField = (*env)->GetFieldID(env, userDataClass, "userName", "Ljava/lang/String;");
    if (userNameField == NULL) {
        return;
    }
    // 現在のuserName (jstring) を取得
    jstring currentName = (jstring)(*env)->GetObjectField(env, userData, userNameField);
    // jstringをCの文字列に変換
    const char *nativeName = (*env)->GetStringUTFChars(env, currentName, 0);

    // 新しい名前を作成
    char newName[256];
    sprintf(newName, "%s (updated by C!)", nativeName);

    // Cの文字列を新しいjstringに変換
    jstring newJniName = (*env)->NewStringUTF(env, newName);

    // userNameフィールドの値を新しいjstringで更新
    (*env)->SetObjectField(env, userData, userNameField, newJniName);

    // メモリ解放
    (*env)->ReleaseStringUTFChars(env, currentName, nativeName);
}

