#include "mario_vm.h"
#include "fs/native_fs.h"
#include "dir/native_dir.h"
#include "socket/native_socket.h"
#include "system/native_system.h"
#include "dns/native_dns.h"
#include "timer/native_timer.h"
#include "thread/native_thread.h"


#ifdef __cplusplus /* __cplusplus */
extern "C" {
#endif

void reg_natives(vm_t* vm) {
	reg_native_fs(vm);
	reg_native_dir(vm);
	reg_native_socket(vm);
	reg_native_system(vm);
	reg_native_dns(vm);
	reg_native_timer(vm);
	reg_native_thread(vm);
}

#ifdef __cplusplus /* __cplusplus */
}
#endif
