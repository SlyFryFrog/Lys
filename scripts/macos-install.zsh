#!/bin/zsh

echo "Updating submodules"
git submodule update --init --recursive

echo "Installing vcpkg dependencies"
vcpkg install