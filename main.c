#include "miniaudio.h"
#include <stdio.h>
#include <math.h>

// Callback function for audio data
void data_callback(ma_device* pDevice, void* pOutput, const void* pInput, ma_uint32 frameCount) {
    float* fOutput = (float*)pOutput;

    static float phase = 0.0f;
    const float amplitude = 0.2f;
    const float frequency = 440.0f; // A4 note

    for (ma_uint32 i = 0; i < frameCount * 2; i += 2) {
        float sample = amplitude * sinf(phase);

        fOutput[i + 0] = sample;     // Left channel
        fOutput[i + 1] = sample;     // Right channel

        phase += 2.0f * 3.14159265359f * frequency / pDevice->sampleRate;
        if (phase >= 2.0f * 3.14159265359f) {
            phase -= 2.0f * 3.14159265359f;
        }
    }

    (void)pInput;
}

int main() {
    ma_device_config deviceConfig;
    ma_device device;

    deviceConfig = ma_device_config_init(ma_device_type_playback);
    deviceConfig.playback.format = ma_format_f32;
    deviceConfig.playback.channels = 2;
    deviceConfig.sampleRate = 44100;
    deviceConfig.dataCallback = data_callback;

    if (ma_device_init(NULL, &deviceConfig, &device) != MA_SUCCESS) {
        printf("Failed to initialize audio device.\n");
        return -1;
    }

    if (ma_device_start(&device) != MA_SUCCESS) {
        printf("Failed to start audio device.\n");
        ma_device_uninit(&device);
        return -1;
    }

    printf("Playing a sine wave. Press Enter to quit...\n");
    getchar();

    ma_device_uninit(&device);

    return 0;
}