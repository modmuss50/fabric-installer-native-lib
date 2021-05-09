#include "MojangLauncherHelper.h"

#include <windows.h>

constexpr LPCSTR MinecraftLauncherMutexName = "MojangLauncher";

JNIEXPORT jboolean JNICALL Java_net_fabricmc_installer_launcher_MojangLauncherHelper_isMojangLauncherOpen(JNIEnv *, jclass) {
    HANDLE handle = CreateMutexA(nullptr, false, MinecraftLauncherMutexName);

    if (GetLastError() == ERROR_ALREADY_EXISTS)
    {
        // Already exists so must be open.
        return 1;
    }

    CloseHandle(handle);
    return 0;
}