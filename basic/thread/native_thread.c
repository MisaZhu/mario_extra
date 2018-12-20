#include "native_thread.h"

#include <unistd.h>
#include <pthread.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#ifdef MARIO_THREAD

void* threadThread(void* p) {
	vm_t* vm = (vm_t*)p;
	pthread_detach(pthread_self());

	vm_run(vm);
	vm_close(vm);
	_free(vm);
	return NULL;
}

#define CLS_THREAD "MarioThread"

var_t* native_thread_run(vm_t* vm, var_t* env, void* data) {
	const char* s = get_str(env, "s");
	if(s[0] == 0)
		return NULL;
	
	vm_t* vm_thread = vm_from(vm);
	if(!vm_load(vm_thread, s)) {
		vm_close(vm_thread);
		_free(vm_thread);
		return NULL;
	}

	var_t* vmain = var_new_obj(vm_thread, vm, _free_none);
  var_instance_from(vmain, get_obj(env, THIS));
	var_add(vm_thread->root, "_fatherThread", vmain);

	pthread_t pid;
	pthread_create(&pid, NULL, threadThread, vm_thread);

	var_t* vthread = var_new_obj(vm, vm_thread, _free_none);
  var_instance_from(vthread, get_obj(env, THIS));
	return vthread;
}

var_t* native_thread_current(vm_t* vm, var_t* env, void* data) {
	return get_obj(vm->root, "_thread");
}

var_t* native_thread_father(vm_t* vm, var_t* env, void* data) {
	return get_obj(vm->root, "_fatherThread");
}

var_t* native_thread_send_message(vm_t* vm, var_t* env, void* data) {
	vm_t* vm_thread = (vm_t*)get_raw(env, THIS);
	if(vm_thread == NULL)
		return NULL;
	
	const char* s = get_str(env, "s");
	var_t* thread_obj = get_obj(vm_thread->root, "_thread");
	if(thread_obj == NULL) {
		return NULL;
	}
	interrupt_by_name(vm_thread, thread_obj, "onMessage", s);
	return NULL;
}

void reg_native_thread(vm_t* vm) {
	vm_reg_static(vm, CLS_THREAD, "run(s)", native_thread_run, NULL);
	vm_reg_native(vm, CLS_THREAD, "sendMessage(s)", native_thread_send_message, NULL);
	vm_reg_static(vm, CLS_THREAD, "current()", native_thread_current, NULL);
	vm_reg_static(vm, CLS_THREAD, "father()", native_thread_father, NULL);

	//add current thread object.
	var_t* vthread = new_obj(vm, CLS_THREAD, 0);
	vthread->value = vm;
	vthread->free_func = _free_none;
	var_add(vm->root, "_thread", vthread);
}

#else
void reg_native_thread(vm_t* vm) {
}
#endif

#ifdef __cplusplus
}
#endif /* __cplusplus */

