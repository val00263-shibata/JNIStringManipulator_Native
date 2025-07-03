#include "com_example_jni_MultipleValuesReturnByHash.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

// +++ 整数をIntegerオブジェクトとしてputするヘルパー関数 +++
void put_integer(JNIEnv *env, jobject map, jmethodID put_method, const char* key, int value) {
    // 1. Integerクラスを探す
    jclass intClass = (*env)->FindClass(env, "java/lang/Integer");
    if (intClass == NULL) return;
    // 2. intを引数に取るコンストラクタのIDを取得
    jmethodID intConstructor = (*env)->GetMethodID(env, intClass, "<init>", "(I)V");
    if (intConstructor == NULL) return;
    // 3. Cのint値からIntegerオブジェクトを生成
    jobject intObject = (*env)->NewObject(env, intClass, intConstructor, value);

    // 4. putメソッドを呼び出す
    jstring jKey = (*env)->NewStringUTF(env, key);
    (*env)->CallObjectMethod(env, map, put_method, jKey, intObject);
    (*env)->DeleteLocalRef(env, jKey);
    (*env)->DeleteLocalRef(env, intObject);
}

// putメソッドを呼び出すヘルパー関数
void put_string(JNIEnv *env, jobject map, jmethodID put_method, const char* key, const char* value) {
    jstring jKey = (*env)->NewStringUTF(env, key);
    jstring jValue = (*env)->NewStringUTF(env, value);
    (*env)->CallObjectMethod(env, map, put_method, jKey, jValue);
    // CallObjectMethodはローカル参照を返すことがあるので解放する
    (*env)->DeleteLocalRef(env, jKey);
    (*env)->DeleteLocalRef(env, jValue);
}

// +++ ユーザー定義クラスをputするヘルパー関数 +++
void put_custom_data(JNIEnv *env, jobject map, jmethodID put_method, const char* key, const char* info, int value) {
    // 1. MyCustomDataクラスを探す (パッケージにあれば "com/example/MyCustomData"のように指定)
    jclass customClass = (*env)->FindClass(env, "com/example/jni/MyCustomData");
    if (customClass == NULL) return;

    // 2. コンストラクタIDを取得 (Stringとintを引数に取る)
    jmethodID customConstructor = (*env)->GetMethodID(env, customClass, "<init>", "(Ljava/lang/String;I)V");
    if (customConstructor == NULL) return;

    // 3. コンストラクタに渡す引数(jstring)を用意
    jstring jInfo = (*env)->NewStringUTF(env, info);

    // 4. MyCustomDataオブジェクトを生成
    jobject customObject = (*env)->NewObject(env, customClass, customConstructor, jInfo, value);

    // 5. putメソッドでHashMapに追加
    jstring jKey = (*env)->NewStringUTF(env, key);
    (*env)->CallObjectMethod(env, map, put_method, jKey, customObject);

    // ローカル参照を解放
    (*env)->DeleteLocalRef(env, jInfo);
    (*env)->DeleteLocalRef(env, customObject);
    (*env)->DeleteLocalRef(env, jKey);
}

JNIEXPORT jobject JNICALL Java_com_example_jni_MultipleValuesReturnByHash_getInfoAsMap(JNIEnv *env, jobject obj) {

    // 1. HashMapクラスを探す
    jclass mapClass = (*env)->FindClass(env, "java/util/HashMap");
    if (mapClass == NULL) {
        return NULL;
    }

    // 2. HashMapのコンストラクタIDを取得する
    jmethodID mapConstructor = (*env)->GetMethodID(env, mapClass, "<init>", "()V");
    if (mapConstructor == NULL) {
        return NULL;
    }

    // 3. 新しいHashMapオブジェクトを生成する
    jobject mapObject = (*env)->NewObject(env, mapClass, mapConstructor);
    if (mapObject == NULL) {
        return NULL;
    }

    // 4. putメソッドのIDを取得する
    // シグネチャ: (Ljava/lang/Object;Ljava/lang/Object;)Ljava/lang/Object;
    jmethodID putMethod = (*env)->GetMethodID(env, mapClass, "put", "(Ljava/lang/Object;Ljava/lang/Object;)Ljava/lang/Object;");
    if (putMethod == NULL) {
        return NULL;
    }

    // 5. putメソッドを呼び出してキーと値を追加する
    put_string(env, mapObject, putMethod, "name", "Taro Yamada (from C)");
    put_string(env, mapObject, putMethod, "language", "C");
    put_string(env, mapObject, putMethod, "year", "2025");

    // --- キーと値を追加 ---
    put_string(env, mapObject, putMethod, "status", "OK");
    put_integer(env, mapObject, putMethod, "code", 200);
    // ユーザー定義オブジェクトを追加
    put_custom_data(env, mapObject, putMethod, "custom", "This is custom data", 999);

    // 6. 作成したHashMapオブジェクトをJavaに返す
    return mapObject;
}

JNIEXPORT jobject JNICALL Java_com_example_jni_MultipleValuesReturnByHash_getNumberAsMap(JNIEnv *env, jobject obj) {
    // 1. HashMapクラスを探す
    jclass mapClass = (*env)->FindClass(env, "java/util/HashMap");
    if (mapClass == NULL) {
        return NULL;
    }

    // 2. HashMapのコンストラクタIDを取得する
    jmethodID mapConstructor = (*env)->GetMethodID(env, mapClass, "<init>", "()V");
    if (mapConstructor == NULL) {
        return NULL;
    }

    // 3. 新しいHashMapオブジェクトを生成する
    jobject mapObject = (*env)->NewObject(env, mapClass, mapConstructor);
    if (mapObject == NULL) {
        return NULL;
    }

    // 4. putメソッドのIDを取得する
    // シグネチャ: (Ljava/lang/Object;Ljava/lang/Object;)Ljava/lang/Object;
    jmethodID putMethod = (*env)->GetMethodID(env, mapClass, "put", "(Ljava/lang/Object;Ljava/lang/Object;)Ljava/lang/Object;");
    if (putMethod == NULL) {
        return NULL;
    }

    // 5. putメソッドを呼び出してキーと値を追加する
    put_integer(env, mapObject, putMethod, "codeA", 100);
    put_integer(env, mapObject, putMethod, "codeB", 200);
    put_integer(env, mapObject, putMethod, "codeC", 300);

    // 6. 作成したHashMapオブジェクトをJavaに返す
    return mapObject;
}
