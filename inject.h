#pragma once

/* GnUwU */
#if !defined(_GNU_SOURCE) && defined(__GNUC__)
#define _GNU_SOURCE
#endif

#define internal __attribute__((visibility("hidden")))
#define _SymbType(x) x##_t
#define _ImportedType(x) imported_##x##_t
#define _Import(x) imported_##x

#if defined(__unix__)
#include <dlfcn.h>

/* I think this is a bit hacky, but who cares? */
#if !defined(RTLD_NEXT)
#define RTLD_NEXT ((void *)-1l)
#endif

#define use(Symbol, Return, ...)                                               \
  typedef Return (*_ImportedType(Symbol))(__VA_ARGS__);                        \
  internal _ImportedType(Symbol) _Import(Symbol) = 0;

#define import(Symbol)                                                         \
  if (!_Import(Symbol))                                                        \
    _Import(Symbol) = dlsym(RTLD_NEXT, #Symbol);

#define call(Symbol, ...) _Import(Symbol)(__VA_ARGS__)
#define OnInjected                                                             \
  __attribute__((constructor(101))) void OnLibrarySetupCompleted(void)

#define OnDestructed                                                           \
  __attribute__((destructor(101))) void OnLibraryDestructed(void)

#define drop(Symbol)                                                           \
  if (_Import(Symbol))                                                         \
  dlclose(_Import(Symbol))
#endif

#if defined(_WIN32)
size_t _msize(void *memblock);
#define sizeOfBlock _msize
#elif defined(__APPLE__)
size_t malloc_size(const void *ptr);
#define sizeOfBlock _malloc_size
#elif defined(__GNUC__)
size_t malloc_usable_size(void *ptr);
#define sizeOfBlock malloc_usable_size
#endif
