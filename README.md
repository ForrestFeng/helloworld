# helloworld

How to use the vcpkg and cmake with VS 2022

## Tutorial: Install and use packages with vcpkg(https://learn.microsoft.com/en-us/vcpkg/get_started/get-started?pivots=shell-powershell)


## Fix error of error: Failed to download from mirror set
```
Downloading https://repo.msys2.org/mingw/i686/mingw-w64-i686-libwinpthread-git-9.0.0.6373.5be8fcd83-1-any.pkg.tar.zst
Downloading https://repo.msys2.org/mingw/i686/mingw-w64-i686-libwinpthread-git-9.0.0.6373.5be8fcd83-1-any.pkg.tar.zst
Downloading https://repo.msys2.org/mingw/i686/mingw-w64-i686-libwinpthread-git-9.0.0.6373.5be8fcd83-1-any.pkg.tar.zst
Downloading https://repo.msys2.org/mingw/i686/mingw-w64-i686-libwinpthread-git-9.0.0.6373.5be8fcd83-1-any.pkg.tar.zst
Downloading https://repo.msys2.org/mingw/i686/mingw-w64-i686-libwinpthread-git-9.0.0.6373.5be8fcd83-1-any.pkg.tar.zst
error: Failed to download from mirror set
error: https://mirror.msys2.org/mingw/i686/mingw-w64-i686-libwinpthread-git-9.0.0.6373.5be8fcd83-1-any.pkg.tar.zst: failed: status code 404
error: https://repo.msys2.org/mingw/i686/mingw-w64-i686-libwinpthread-git-9.0.0.6373.5be8fcd83-1-any.pkg.tar.zst: failed: status code 404
error: https://repo.msys2.org/mingw/i686/mingw-w64-i686-libwinpthread-git-9.0.0.6373.5be8fcd83-1-any.pkg.tar.zst: failed: status code 404
error: https://repo.msys2.org/mingw/i686/mingw-w64-i686-libwinpthread-git-9.0.0.6373.5be8fcd83-1-any.pkg.tar.zst: failed: status code 404
error: https://repo.msys2.org/mingw/i686/mingw-w64-i686-libwinpthread-git-9.0.0.6373.5be8fcd83-1-any.pkg.tar.zst: failed: status code 404
error: https://repo.msys2.org/mingw/i686/mingw-w64-i686-libwinpthread-git-9.0.0.6373.5be8fcd83-1-any.pkg.tar.zst: failed: status code 404
[DEBUG] D:\a\_work\1\s\src\vcpkg\base\downloads.cpp(1003):
[DEBUG] Time in subprocesses: 0us
[DEBUG] Time in parsing JSON: 15us
[DEBUG] Time in JSON reader: 0us
[DEBUG] Time in filesystem: 4781us
[DEBUG] Time in loading ports: 0us
[DEBUG] Exiting after 7.4 s (7444995us)

CMake Error at scripts/cmake/vcpkg_download_distfile.cmake:32 (message):

      Failed to download file with error: 1
      If you are using a proxy, please check your proxy setting. Possible causes are:

      1. You are actually using an HTTP proxy, but setting HTTPS_PROXY variable
         to `https://address:port`. This is not correct, because `https://` prefix
         claims the proxy is an HTTPS proxy, while your proxy (v2ray, shadowsocksr
         , etc..) is an HTTP proxy. Try setting `http://address:port` to both
         HTTP_PROXY and HTTPS_PROXY instead.

      2. If you are using Windows, vcpkg will automatically use your Windows IE Proxy Settings
         set by your proxy software. See https://github.com/microsoft/vcpkg-tool/pull/77
         The value set by your proxy might be wrong, or have same `https://` prefix issue.

      3. Your proxy's remote server is out of service.

      If you've tried directly download the link, and believe this is not a temporary
      download server failure, please submit an issue at https://github.com/Microsoft/vcpkg/issues
      to report this upstream download server failure.
```
 
The vcpkg integrated with VS2022 is located in this dir
```
C:\Program Files\Microsoft Visual Studio\2022\Enterprise\VC\vcpkg
```

This version is old, updated with latest version from github to solve the issue.
```
git clone https://github.com/microsoft/vcpkg.git
cd vcpkg
git pull
```

Copy the contenst from you local repo to C:\Program Files\Microsoft Visual Studio\2022\Enterprise\VC\vcpkg
The problem will be fixed.


## How to write CMakeLists(https://stackoverflow.com/questions/39598323/how-to-properly-link-libraries-with-cmake)

```
207

My recommendation is to start simple, and then complicate your project further.

Let me try to explain how linking works in CMake. The idea is that you build modules in CMake, and link them together. Let's ignore header files for now, as they can be all included in your source files.

Say you have file1.cpp, file2.cpp, main.cpp. You add them to your project with:

ADD_LIBRARY(LibsModule 
    file1.cpp
    file2.cpp
)
Now you added them to a module called LibsModule. Keep that in mind. Say you want to link to pthread for example that's already in the system. You can combine it with LibsModule using the command:

target_link_libraries(LibsModule -lpthread)
And if you want to link a static library to that too, you do this:

target_link_libraries(LibsModule liblapack.a)
And if you want to add a directory where any of these libraries are located, you do this:

target_link_libraries(LibsModule -L/home/user/libs/somelibpath/)
Now you add an executable, and you link it with your main file:

ADD_EXECUTABLE(MyProgramExecBlaBla main.cpp)
(I added BlaBla just to make it clear that the name is custom). And then you link LibsModule with your executable module MyProgramExecBlaBla

target_link_libraries(MyProgramExecBlaBla LibsModule)
And this will do it.

What I see in your CMake file is a lot of redundancy. For example, why do you have texture_mapping, which is an executable module in your include directories? So you need to clean this up and follow the simple logic I explained. Hopefully it works.

In summary, it looks like this:

project (MyProgramExecBlaBla)  #not sure whether this should be the same name of the executable, but I always see that "convention"
cmake_minimum_required(VERSION 2.8)

ADD_LIBRARY(LibsModule 
    file1.cpp
    file2.cpp
)

target_link_libraries(LibsModule -lpthread)
target_link_libraries(LibsModule liblapack.a)
target_link_libraries(LibsModule -L/home/user/libs/somelibpath/)
ADD_EXECUTABLE(MyProgramExecBlaBla main.cpp)
target_link_libraries(MyProgramExecBlaBla LibsModule)
The most important thing to understand is the module structure, where you create modules and link them all together with your executable. Once this works, you can complicate your project further with more details. Good luck!

Note: Keep in mind that this is the simple way to use CMake. The better cross-platform way would be using find_package, which locates a package/library, and provides the libraries and includes in CMake variables so that you could link your program to them. Here's how to do this for boost, for example.

```