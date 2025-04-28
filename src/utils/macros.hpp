#pragma once

#include <cstdlib>
#include <cxxabi.h>
#include <memory>

#define CLASS_NAME(somePointer) ((const char*)cpp_demangle(typeid(*somePointer).name()).get())

std::shared_ptr<char> cpp_demangle(const char* abiName)
{
	int status;
	char* ret = abi::__cxa_demangle(abiName, 0, 0, &status);

	/* NOTE: must free() the returned char when done with it! */
	std::shared_ptr<char> retval;
	retval.reset((char*)ret,
				 [](const char* mem)
				 {
					 if (mem)
					 {
						 free((void*)mem);
					 }
				 });
	return retval;
}
