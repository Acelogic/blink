#ifndef BLINK_BLINK_H_
#define BLINK_BLINK_H_

#ifdef __cplusplus
extern "C" {
#endif

int BlinkMain(int argc, char *argv[]);

// Returns 0 when generated ARM64 code executed successfully, 77 when the
// process lacks JIT permission, and a negative value for an internal failure.
int BlinkJitSelfTest(void);

#ifdef __cplusplus
}
#endif

#endif /* BLINK_BLINK_H_ */
