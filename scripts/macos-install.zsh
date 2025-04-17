#!/bin/zsh

echo "Installing dependencies"
brew install glfw glew glm

echo "Updating submodules"
git submodule update --init --recursive