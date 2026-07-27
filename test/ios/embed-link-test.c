#include "blink/blink.h"

static int (*volatile blink_entry)(int, char **) = BlinkMain;
static int (*volatile blink_jit_test)(void) = BlinkJitSelfTest;

int main(void) {
  return blink_entry == 0 || blink_jit_test == 0;
}
