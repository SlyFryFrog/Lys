# Lys

## Tooling

- **CMake 3.30**: Uses modern CMake for enhanced project configuration.
- **Ninja Build System**: Default build generator for fast and efficient compilation.
- **Clang Tooling**: Includes `.clang-format`, `.clang-tidy`, and `.clangd` for consistent code formatting and static analysis (they are configured to my personal style).
- **Clang 20**: Uses modern C++ and modules and possible.
- **CMake Presets**: Provides `CMakePresets.json` for easy build configuration management.

## Getting Started

### Prerequisites

- **CMake 3.30**
- **Ninja**
- **Clang 20**

### Building the Project

1. **Clone the Repository**:

```
git clone git@github.com:SlyFryFrog/Lys.git
```

2. **Run CMake Preset**

Before running the preset, it is necessary to configure the `CMakeUserPresets.json`. An example of what this may look like on linux is as follows.

```json
{
  "version": 8,
  "configurePresets": [
    {
      "name": "config",
      "inherits": "abstract",
      "hidden": true,
      "environment": {
        "VCPKG_ROOT": "PATH"
      },
      "cacheVariables": {
        "CMAKE_C_COMPILER": "/usr/bin/clang",
        "CMAKE_CXX_COMPILER": "/usr/bin/clang++",
        "CMAKE_C_FLAGS": "-stdlib=libc++",
        "CMAKE_CXX_FLAGS": "-stdlib=libc++"
      }
    },
    {
      "name": "DebugLinux",
      "inherits": ["config", "Debug"]
    },
    {
      "name": "ReleaseLinux",
      "inherits": ["config", "Release"]
    }
  ]
}
```

The template has 2 presets, Debug and Release.

```
cmake --preset Debug
```

```
cmake --preset Release
```


