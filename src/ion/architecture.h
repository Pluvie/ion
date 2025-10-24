/* ⚡️ION⚡️ Hardware architectures mapping.  */

#ifndef ARCHITECTURE
#error "ION: Specify a target architecture."
#endif

#define X86       0
#define X64       1
#define ARM32     2
#define ARM64     3
#define RISCV32   4
#define RISCV64   5

#define architecture(name) (ARCHITECTURE == name)

#if   architecture(X86)
  #include "architecture/x86.h"

#elif architecture(X64)
  #include "architecture/x64.h"

#else
#error "ION: Unsupported architecture -- contributions to support it are most welcome."
#endif
