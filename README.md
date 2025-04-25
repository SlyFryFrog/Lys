# Lys

## Features

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
git@github.com:SlyFryFrog/Lys.git```

2. **Run CMake Preset**

The template has 2 presets, Debug and Release.

```
cmake --preset Debug
```

```
cmake --preset Release
```

