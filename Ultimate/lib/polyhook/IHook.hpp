//
// Created by steve on 4/2/17.
//

#ifndef POLYHOOK_2_0_IHOOK_HPP
#define POLYHOOK_2_0_IHOOK_HPP


#include <polyhook/ADisassembler.hpp>
#include <polyhook/Enums.hpp>

#if defined(__clang__)

#elif defined(__GNUC__) || defined(__GNUG__)
#define NOINLINE __attribute__((noinline))
#define OPTS_OFF _Pragma("GCC push_options") \
_Pragma("GCC optimize (\"O0\")")
#define OPTS_ON #pragma GCC pop_options
#elif defined(_MSC_VER)
#define NOINLINE __declspec(noinline)
#define OPTS_OFF __pragma(optimize("", off))
#define OPTS_ON __pragma(optimize("", on))
#endif

namespace PLH {
class IHook {
public:
	IHook() {
		m_debugSet = false;
	}

	IHook(IHook&& other) = default; //move
	IHook& operator=(IHook&& other) = default;//move assignment
	IHook(const IHook& other) = delete; //copy
	IHook& operator=(const IHook& other) = delete; //copy assignment
	virtual ~IHook() = default;

	virtual bool hook() = 0;

	virtual bool unHook() = 0;

	virtual HookType getType() const = 0;

	virtual void setDebug(const bool state) {
		m_debugSet = state;
	}

protected:
	bool m_debugSet;
};
}
#endif //POLYHOOK_2_0_IHOOK_HPP
