// Required JNI header - provides JNIEnv, jstring, and JNI functions
#include <jni.h>

// For std::string and basic string operations
#include <string>

extern "C"
JNIEXPORT jstring JNICALL
Java_com_example_ndkstore_NativeLib_getApiKey(JNIEnv *env, jobject) {

    // This array contains the encrypted API key.
    // The key was XOR-encrypted before storing here.
    // Example plaintext -> XOR with 0x5A -> produce these bytes.
    static const unsigned char encrypted[] = {
            9, 27, 23, 10, 22, 31, 5, 27, 10, 19,
            5, 17, 31, 3, 5, 107, 104, 105, 110, 111
    };

    // The same XOR value used during encryption.
    // Decryption simply XORs the encrypted bytes again with the same key.
    const unsigned char xorKey = 0x5A;

    // Total number of bytes in the encrypted array.
    size_t len = sizeof(encrypted);

    // std::string is used to build the decrypted API key.
    // Reserve memory ahead of time to avoid reallocations.
    std::string decrypted;
    decrypted.reserve(len);

    // Loop through each encrypted byte and decrypt it.
    for (size_t i = 0; i < len; ++i) {
        // XOR with the same key reverses the encryption.
        decrypted.push_back(encrypted[i] ^ xorKey);
    }

    // Convert the std::string into a Java jstring
    // so we can return it back to Kotlin.
    return env->NewStringUTF(decrypted.c_str());
}

