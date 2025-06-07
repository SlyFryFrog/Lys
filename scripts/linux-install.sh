#!/bin/bash

echo "Installing dependencies"
sudo apt install libglfw3-dev libglew-dev libglm-dev

echo "Updating submodules"
git submodule update --init --recursive

vcpkg install