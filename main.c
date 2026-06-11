#include <psp2/kernel/modulemgr.h>
#include <taihen.h>

static SceUID hook = -1;
static tai_hook_ref_t ref_hook;

static int vshSysconReturnFalse(void) {
  return 0;
}

int module_start(SceSize argc __attribute__((unused)), const void *args __attribute__((unused))) {
  hook = taiHookFunctionImport(&ref_hook, TAI_MAIN_MODULE, TAI_ANY_LIBRARY, 0xCEC8B917, vshSysconReturnFalse);
  return SCE_KERNEL_START_SUCCESS;
}

int module_stop(SceSize argc __attribute__((unused)), const void *args __attribute__((unused))) {
  if (hook >= 0) {
    taiHookRelease(hook, ref_hook);
    hook = -1;
  }

  return SCE_KERNEL_STOP_SUCCESS;
}