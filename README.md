# NDK Secret Storage Demo (Kotlin + C++)

This project demonstrates how to store an API key inside native C++ code (NDK) instead of placing it
directly in Kotlin. The goal is not to achieve perfect security, but to make sensitive values harder
to extract than they would be in plain `.dex` files.

The app loads an API key from a native `.so` library, decrypts it in C++, and exposes it to Kotlin
through JNI.

---

## Features

- Store an encrypted API key in native code
- Decrypt the key inside C++
- Access the decrypted value in Kotlin via JNI
- Uses:
    - Kotlin
    - C++ (NDK)
    - CMake
    - JNI

---

## Project Structure

```
app/
├── src/main/java/com/example/ndkstore/
│ ├── MainActivity.kt
│ └── NativeLib.kt
├── src/main/cpp/
│ └── native-lib.cpp
├── CMakeLists.txt
└── build.gradle
```

---

### File Overview

**NativeLib.kt**  
Loads the native library and defines the `external` function used to fetch the API key.

**native-lib.cpp**  
Stores the encrypted key as a byte array, decrypts it using XOR, and returns it as a `jstring`.

**CMakeLists.txt**  
Defines how the C++ source is compiled into a shared library.

**MainActivity.kt**  
Calls the native method and shows the resulting key on the screen.

---

## How It Works

1. The API key is stored as XOR-encrypted bytes in `native-lib.cpp`.
2. C++ decrypts the bytes back into a readable string at runtime.
3. JNI sends the decrypted value back to Kotlin.
4. Kotlin loads the native library using `System.loadLibrary("native-lib")`.
5. The app displays the key to confirm everything works.

This technique does not fully secure secrets, but it raises the difficulty for anyone trying to read
or modify them.

---

## Changing the API Key

1. Choose your new key, for example: MY_NEW_SECRET_123
2. Generate encrypted bytes using Python:

```python
plaintext = "MY_NEW_SECRET_123"
xor = 0x5A
encrypted = [ord(c) ^ xor for c in plaintext]
print(encrypted)
```

3. Update the C++ array:

```
static const unsigned char encrypted[] = {
    /* paste generated values here */
};
```

4. Rebuild the project.
   Your new key is now embedded in the native library.

## What Else Can Be Stored in the NDK?

Aside from API keys, developers often store:

- Feature unlock flags
- Hidden developer options
- Internal configuration strings
- Small anti-tamper checks
- Root or signature detection logic
- Proprietary formulas or lookup tables
- Lightweight license validation data

These are not impossible to extract, but placing them in native code makes reverse engineering
significantly harder.

## Security Notes

- The NDK improves obfuscation, not absolute protection.
- Any client-side secret can be extracted with enough effort.
- For sensitive production keys, always use a backend server that issues short-lived tokens.

