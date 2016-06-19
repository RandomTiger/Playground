Unity Rendering Plugin

Source:
http://docs.unity3d.com/Manual/NativePluginInterface.html

Installs:
Unity4.5 (known working with 0b20)
android-ndk (known working with r11c)
gawk GnuWin32 (known working with gawk-3.1.6-1)

Setup
PATH += <whereever>\android-ndk-r11c
NDK_HOST_AWK="<whereever>\GnuWin32\bin\gawk.exe"

Changes already made:
Application.mk add NDK_TOOLCHAIN_VERSION := clang
Added DayDream plugin
Added basic glew files
Disabled DirectX code paths for windows

Notes:
Unity should be launched in OpenGL mode with -force-glcore, this allows you to easily use the same source for windows editor and Android.
Build editor .dll with VisualStudio2015 project
Build Android .so with cmd ndk-build

Further info:

https://developer.android.com/ndk/guides/ndk-build.html#int