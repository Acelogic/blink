#include "blink/blink.h"

static int (*volatile blink_entry)(int, char **) = BlinkMain;

int main(void) {
  return blink_entry == 0;
}
