#include "lib/tray/CrossPlatformTrayIconProvider.h"
#include "lib/tray/CrossPlatformTrayIcon.h"
#include "lib/microphone/AMixer/AMixerMicrophoneStateProvider.h"
#include "lib/microphone/AMixer/AMixerMicrophoneController.h"
#include "lib/BashCodeExecutor.h"

#include "tray_icon.h"

int main(int argc, char *argv[])
{
    GUI::CrossPlatformTrayIconProvider provider;
    GUI::CrossPlatformTrayIcon trayIcon(provider);

    BashCodeExecutor codeExecutor;

    AMixerMicrophoneStateProvider microphoneStateProvider(codeExecutor);
    AMixerMicrophoneController microphoneController(codeExecutor);

    auto trayIconContext = std::unique_ptr<Muted::TrayIconContext>(
        Muted::newTrayIcon(
            &trayIcon,
            (MicrophoneController *) &microphoneController,
            (MicrophoneStateProvider *) &microphoneStateProvider
        )
    );

    while (trayIcon.loop(1) == 0);
}