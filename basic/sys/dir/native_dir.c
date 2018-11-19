#include "native_dir.h"
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>


static void destroyDir(void* data) {
	DIR* dir = (DIR*)data;
	if(dir != NULL)
		closedir(dir);
}

static DIR* getDir(var_t* env) {
	var_t* thisV = get_obj(env, THIS);
	if(thisV == NULL)
		return NULL;
	
	var_t* n = get_obj(thisV, "dir");
	if(n == NULL)
		return NULL;
	return (DIR*)(n->value);
}

static var_t* setDir(vm_t* vm, var_t* env, DIR* dir) {
	var_t* thisV = get_obj(env, THIS);
	if(thisV == NULL)
		return NULL;
	
	node_t* n = var_find_create(thisV, "dir");
	var_t* v = var_new_obj(dir, destroyDir);
	node_replace(n, v);
	return thisV;
}

var_t* native_dir_close(vm_t* vm, var_t* env, void* data) {
	setDir(vm, env, NULL);
	return NULL;
}

var_t* native_dir_read(vm_t* vm, var_t* env, void* data) {
	DIR* dir = getDir(env);
	if(dir == NULL)
		return var_new_str(vm, "");

	struct dirent* dp = readdir(dir);
	if(dp == NULL)
		return var_new_str(vm, "");
	
	return var_new_str(vm, dp->d_name);
}


var_t* native_dir_open(vm_t* vm, var_t* env, void* data) {
	const char*  name = get_str(env, "name");
	
	if(name[0] == 0)
		return var_new_int(0);

	DIR* d = opendir(name);
	if(d == NULL)
		return var_new_int(0);

	setDir(vm, env, d);
	return var_new_int(1);
}

#define CLS_DIR "Dir"

void reg_native_dir(vm_t* vm) {
	vm_reg_native(vm, CLS_DIR, "close()", native_dir_close, NULL);
	vm_reg_native(vm, CLS_DIR, "open(name)", native_dir_open, NULL);
	vm_reg_native(vm, CLS_DIR, "read()", native_dir_read, NULL);
}	
