# miniaudio-cmake

Easy to use CMake wrapper for miniaudio - a single-file audio playback and capture library.

## Features

- Simple CMake integration
- Cross-platform support (Windows, macOS, Linux)
- Static library build
- Automatic platform-specific configuration
- Example program included

## Usage

### As a Subdirectory

1. Add this repository as a subdirectory in your project:

```cmake
add_subdirectory(miniaudio-cmake)
```

2. Link against miniaudio in your target:

```cmake
target_link_libraries(your_target PRIVATE miniaudio)

# On Windows, also link required system libraries
if(WIN32)
    target_link_libraries(your_target PRIVATE ole32 user32 winmm)
endif()
```

## Example

A simple example program is included that plays a sine wave. Build it by enabling the `MINIAUDIO_EXAMPLES` option:

```cmake
option(MINIAUDIO_EXAMPLES "Build miniaudio examples" ON)
```

## Platform-Specific Details

### Windows
- Requires linking against `ole32`, `user32`, and `winmm`
- Built as a static library (.lib)

### macOS
- Automatically links against CoreAudio and AudioToolbox frameworks
- Built as a static library (.a)

### Linux
- Automatically links against pthread, math, and dl libraries
- Built as a static library (.a)

## License

This project is licensed under the same terms as miniaudio. See the [miniaudio repository](https://github.com/mackron/miniaudio) for details.

## Dependencies

- CMake 3.10 or higher
- C11 compiler
- Platform-specific development libraries (automatically handled)

## Contributing

Contributions are welcome! Please feel free to submit a Pull Request.