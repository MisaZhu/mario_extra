#include "native_timer.h"

#include <unistd.h>
#include <pthread.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#ifdef MARIO_THREAD

typedef struct st_timer {
	uint32_t msec;
	uint32_t counter;
	bool repeat;
	var_t* env;
	var_t* callback;
} m_timer_t;

#define TIMER_MAX 32
#define TIMER_STEP 1

typedef struct st_js_timer {
	m_timer_t timers[TIMER_MAX];
	pthread_mutex_t timerLocker;
	uint32_t isignalNum;
} js_timer_t;

js_timer_t* new_js_timer(vm_t* vm) {
	js_timer_t* ret =  (js_timer_t*)_malloc(sizeof(js_timer_t));
	memset(ret, 0, sizeof(js_timer_t));
	var_t* v = var_new_obj(ret, NULL);
	var_add(vm->root, "__timer", v);
	return ret;
}

js_timer_t* get_js_timer(vm_t* vm) {
	var_t* v = var_find_var(vm->root, "__timer");
	return (js_timer_t*)v->value;
}

int setTimer(js_timer_t* js_timer, uint32_t msec, bool repeat, var_t* env, var_t* callback) {
	pthread_mutex_lock(&js_timer->timerLocker);
	int i;
	for(i=0; i<TIMER_MAX; i++) {
		if(js_timer->timers[i].msec == 0) {
			js_timer->timers[i].msec = msec;
			js_timer->timers[i].counter = 0;
			js_timer->timers[i].repeat = repeat;
			js_timer->timers[i].env = var_ref(env);
			js_timer->timers[i].callback = var_ref(callback);
			pthread_mutex_unlock(&js_timer->timerLocker);
			return i;
		}
	}
	_debug("Set timer failed, Too many timers!\n");
	pthread_mutex_unlock(&js_timer->timerLocker);
	return -1;
}

void cancelTimer(vm_t* vm, int id) {
	if(id < 0 || id >= TIMER_MAX)
		return;

	js_timer_t* js_timer = get_js_timer(vm);
	pthread_mutex_lock(&js_timer->timerLocker);
	if(js_timer->timers[id].msec == 0) {
		js_timer->timers[id].msec = 0;
		var_unref(js_timer->timers[id].env, true);
		var_unref(js_timer->timers[id].callback, true);
	}
	pthread_mutex_unlock(&js_timer->timerLocker);
}

void tryTimers(vm_t* vm) {
	js_timer_t* js_timer = get_js_timer(vm);
	int i;
	for(i=0; i<TIMER_MAX; i++) {
		if(js_timer->timers[i].msec == 0) 
			continue;

		js_timer->timers[i].counter += TIMER_STEP;
		if(js_timer->timers[i].counter >= js_timer->timers[i].msec) {
			js_timer->timers[i].counter = 0;
			
			interrupt(vm, js_timer->timers[i].env, js_timer->timers[i].callback, NULL);

			if(!js_timer->timers[i].repeat) {
				js_timer->timers[i].msec = 0;
				var_unref(js_timer->timers[i].callback, true);
				var_unref(js_timer->timers[i].env, true);
			}
		}
	}

	usleep(TIMER_STEP*1000);
}

void* timerThread(void* p) {
	vm_t* vm = (vm_t*)p;
	pthread_detach(pthread_self());

	js_timer_t* js_timer = get_js_timer(vm);

	while(!vm->terminated) {
		pthread_mutex_lock(&js_timer->timerLocker);
		tryTimers(vm);
		pthread_mutex_unlock(&js_timer->timerLocker);
	}

	pthread_mutex_destroy(&js_timer->timerLocker);
	return NULL;
}

/*=====timer native functions=========*/
var_t* native_timer_set(vm_t* vm, var_t* env, void* data) {
	(void)data;
	uint32_t msec = (uint32_t)get_int(env, "msec");
	bool repeat = get_int(env, "repeat");
	var_t* callback = get_obj(env, "callback");

	js_timer_t* js_timer = get_js_timer(vm);
	vm_mark_func_scopes(vm, callback);
	int id = setTimer(js_timer, msec, repeat, env, callback);
	return var_new_int(id);
}

var_t* native_timer_cancel(vm_t* vm, var_t* env, void* data) {
	(void)data;
	int id = get_int(env, "id");
	cancelTimer(vm, id);
	return NULL;
}

void native_timer_init(void* data) {
	vm_t* vm = (vm_t*)data;
	js_timer_t* js_timer = new_js_timer(vm);
	pthread_mutex_init(&js_timer->timerLocker, NULL);
	pthread_t pid;
	pthread_create(&pid, NULL, timerThread, vm);
}

void native_timer_close(void* data) {
	vm_t* vm = (vm_t*)data;
	js_timer_t* js_timer = get_js_timer(vm);
	pthread_mutex_destroy(&js_timer->timerLocker);
}

#define CLS_TIMER "MarioTimer"
void reg_native_timer(vm_t* vm) {
	vm_reg_init(vm, native_timer_init, vm);
	vm_reg_static(vm, CLS_TIMER, "setTimer(msec, repeat, callback)", native_timer_set, NULL);
	vm_reg_static(vm, CLS_TIMER, "cancelTimer(id)", native_timer_cancel, NULL);
	vm_reg_close(vm, native_timer_close, vm);
}

#else
void reg_native_timer(vm_t* vm) {
}
#endif


#ifdef __cplusplus
}
#endif /* __cplusplus */

