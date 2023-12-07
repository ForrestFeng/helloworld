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