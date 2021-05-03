#ifndef MUTED_MICROPHONESTATEPROVIDER_H
#define MUTED_MICROPHONESTATEPROVIDER_H

enum class MicrophoneState {
    MUTED, LIVE
};

class MicrophoneStateProvider {
private:
    const char* microphoneStateQuery = "amixer get Capture | grep off";
public:
    virtual MicrophoneState getState() = 0;
};

#endif
