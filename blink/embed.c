#include "blink/blink.h"

#include <stdint.h>

#include "blink/jit.h"
#include "blink/map.h"

int BlinkJitSelfTest(void) {
#ifdef HAVE_JIT
  static const int64_t key = 0x4953484a4954;
  struct Jit jit;
  struct JitBlock *block;
  uintptr_t hook;
  int result = -1;

  InitMap();
  if (InitJit(&jit, 0)) {
    return -2;
  }
  if (!(block = StartJit(&jit, key))) {
    result = 77;
    goto cleanup;
  }
  if (!AppendJitSetReg(block, kJitRes0, 42) || !AppendJitRet(block) ||
      !FinishJit(&jit, block)) {
    result = -3;
    goto cleanup;
  }
  if (FlushJit(&jit) < 0) {
    result = -4;
    goto cleanup;
  }
  if (!(hook = GetJitHook(&jit, key))) {
    result = -5;
    goto cleanup;
  }
  result = ((int (*)(void))hook)() == 42 ? 0 : -6;

cleanup:
  DestroyJit(&jit);
  ShutdownJit();
  return result;
#else
  return 77;
#endif
}
