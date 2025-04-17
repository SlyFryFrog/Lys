# CMake-Template

A template for C/C++ projects using CMake 20 with Ninja as the default generator. This setup includes predefined configurations for consistent clang tooling and base CMake presets for streamlined builds.

## Features

- **CMake 20**: Uses modern CMake for enhanced project configuration.
- **Ninja Build System**: Default build generator for fast and efficient compilation.
- **Clang Tooling**: Includes `.clang-format`, `.clang-tidy`, and `.clangd` for consistent code formatting and static analysis (they are configured to my personal style).
- **CMake Presets**: Provides `CMakePresets.json` for easy build configuration management.

## Getting Started

### Prerequisites

- **CMake 20** or higher.
- **Ninja** (ensure it's installed and accessible in your system's PATH).
- **Clang** (for code formatting and static analysis).

### Building the Project

1. **Clone the Repository**:

```
git clone https://github.com/SlyFryFrog/CMake-Template.git
```

2. **Run CMake Preset**

The template has 2 presets, Debug and Release.

```
cmake --preset Debug
```

```
cmake --preset Release
```# Lys
