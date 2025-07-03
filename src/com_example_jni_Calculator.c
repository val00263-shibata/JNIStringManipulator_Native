// src/my_calculator.c
#include "com_example_jni_Calculator.h" // 生成されたJNIヘッダーをインクルード
#include <stdio.h>       // printf用

// JNIEXPORT と JNICALL はJNIの規約で必要
// jint: Javaのint型に対応するJNIの型
// JNIEnv*: JNI環境ポインタ (Javaオブジェクトへのアクセスなどに使用)
// jobject: メソッドが呼び出されたJavaオブジェクトの参照 (staticメソッドの場合はjclass)
// jint num1, jint num2: Javaから渡される引数
JNIEXPORT jint JNICALL Java_com_example_jni_Calculator_addNumbers
  (JNIEnv *env, jobject obj, jint num1, jint num2) {

    // Javaから受け取った引数をC側で表示
    printf("C native method received: num1 = %d, num2 = %d\n", (int)num1, (int)num2);

    // 2つの数値を加算
    jint result = num1 + num2;

    // 加算結果をC側で表示
    printf("C native method calculated result: %d\n", (int)result);

    // 加算結果をJavaに返却
    return result;
}
