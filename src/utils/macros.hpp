#pragma once

#include <cstdlib>
#include <cxxabi.h>
#include <memory>

#define CLASS_NAME(somePointer) ((const char*)cpp_demangle(typeid(*somePointer).name()).get())

std::shared_ptr<char> cpp_demangle(const char* abiName);
