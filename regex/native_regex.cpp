#include "mario.h"
#include "verbalexpressions.h"

static void _destroyRegex(void* p) {
	verex::verex* m = (verex::verex*)p;
	if(m == NULL)
		return;
	delete m;
}

#define GET_REGEX verex::verex* regex = (verex::verex*)get_raw(env, THIS); \
	if(regex == NULL)\
		return NULL;

var_t* native_regex_constructor(vm_t* vm, var_t* env, void* data) {
	verex::verex *m = new verex::verex();
	var_t* thisV = var_new_obj(vm, m, _destroyRegex);
  var_instance_from(thisV, get_obj(env, THIS));
	return thisV;
}

var_t* native_regex_toString(vm_t* vm, var_t* env, void* data) {
	(void)vm; (void)data;
	GET_REGEX

	const std::string& pattern = regex->get_pattern();
	return var_new_str(vm, pattern.c_str());
}

var_t* native_regex_replace(vm_t* vm, var_t* env, void* data) {
	(void)vm; (void)data;
	const char* src = get_str(env, "src");
	const char* value = get_str(env, "value");
	GET_REGEX

	std::string res = regex->replace(src, value);
	return var_new_str(vm, res.c_str());
}

var_t* native_regex_find(vm_t* vm, var_t* env, void* data) {
	(void)vm; (void)data;
	const char* str = get_str(env, "str");
	var_t* thisV = get_obj(env, THIS);
	GET_REGEX

	regex->find(str);
	return thisV;
}

var_t* native_regex_maybe(vm_t* vm, var_t* env, void* data) {
	(void)vm; (void)data;
	const char* str = get_str(env, "str");
	var_t* thisV = get_obj(env, THIS);
	GET_REGEX

	regex->maybe(str);
	return thisV;
}

var_t* native_regex_then(vm_t* vm, var_t* env, void* data) {
	(void)vm; (void)data;
	const char* str = get_str(env, "str");
	var_t* thisV = get_obj(env, THIS);
	GET_REGEX

	regex->then(str);
	return thisV;
}

var_t* native_regex_anythingBut(vm_t* vm, var_t* env, void* data) {
	(void)vm; (void)data;
	const char* str = get_str(env, "str");
	var_t* thisV = get_obj(env, THIS);
	GET_REGEX

	regex->anything_but(str);
	return thisV;
}

var_t* native_regex_anything(vm_t* vm, var_t* env, void* data) {
	(void)vm; (void)data;
	var_t* thisV = get_obj(env, THIS);
	GET_REGEX

	regex->anything();
	return thisV;
}

var_t* native_regex_somethingBut(vm_t* vm, var_t* env, void* data) {
	(void)vm; (void)data;
	const char* str = get_str(env, "str");
	var_t* thisV = get_obj(env, THIS);
	GET_REGEX

	regex->something_but(str);
	return thisV;
}

var_t* native_regex_something(vm_t* vm, var_t* env, void* data) {
	(void)vm; (void)data;
	var_t* thisV = get_obj(env, THIS);
	GET_REGEX

	regex->something();
	return thisV;
}

var_t* native_regex_add(vm_t* vm, var_t* env, void* data) {
	(void)vm; (void)data;
	const char* str = get_str(env, "str");
	var_t* thisV = get_obj(env, THIS);
	GET_REGEX

	regex->add(str);
	return thisV;
}

var_t* native_regex_alt(vm_t* vm, var_t* env, void* data) {
	(void)vm; (void)data;
	const char* str = get_str(env, "str");
	var_t* thisV = get_obj(env, THIS);
	GET_REGEX

	regex->alt(str);
	return thisV;
}

var_t* native_regex_anyOf(vm_t* vm, var_t* env, void* data) {
	(void)vm; (void)data;
	const char* str = get_str(env, "str");
	var_t* thisV = get_obj(env, THIS);
	GET_REGEX

	regex->any_of(str);
	return thisV;
}

var_t* native_regex_any(vm_t* vm, var_t* env, void* data) {
	(void)vm; (void)data;
	const char* str = get_str(env, "str");
	var_t* thisV = get_obj(env, THIS);
	GET_REGEX

	regex->any(str);
	return thisV;
}

var_t* native_regex_test(vm_t* vm, var_t* env, void* data) {
	(void)vm; (void)data;
	const char* str = get_str(env, "str");
	GET_REGEX

	return var_new_bool(vm, regex->test(str));
}

var_t* native_regex_linebr(vm_t* vm, var_t* env, void* data) {
	(void)vm; (void)data;
	var_t* thisV = get_obj(env, THIS);
	GET_REGEX

	regex->linebreak();
	return thisV;
}

var_t* native_regex_br(vm_t* vm, var_t* env, void* data) {
	(void)vm; (void)data;
	var_t* thisV = get_obj(env, THIS);
	GET_REGEX

	regex->br();
	return thisV;
}

var_t* native_regex_tab(vm_t* vm, var_t* env, void* data) {
	(void)vm; (void)data;
	var_t* thisV = get_obj(env, THIS);
	GET_REGEX

	regex->tab();
	return thisV;
}

var_t* native_regex_word(vm_t* vm, var_t* env, void* data) {
	(void)vm; (void)data;
	var_t* thisV = get_obj(env, THIS);
	GET_REGEX

	regex->word();
	return thisV;
}

var_t* native_regex_startOfLine(vm_t* vm, var_t* env, void* data) {
	(void)vm; (void)data;
	var_t* thisV = get_obj(env, THIS);
	bool en = get_bool(env, "enable");
	GET_REGEX

	regex->start_of_line(en);
	return thisV;
}

var_t* native_regex_endOfLine(vm_t* vm, var_t* env, void* data) {
	(void)vm; (void)data;
	var_t* thisV = get_obj(env, THIS);
	bool en = get_bool(env, "enable");
	GET_REGEX

	regex->end_of_line(en);
	return thisV;
}

var_t* native_regex_withAnyCase(vm_t* vm, var_t* env, void* data) {
	(void)vm; (void)data;
	var_t* thisV = get_obj(env, THIS);
	bool en = get_bool(env, "enable");
	GET_REGEX

	regex->with_any_case(en);
	return thisV;
}

var_t* native_regex_multi(vm_t* vm, var_t* env, void* data) {
	(void)vm; (void)data;
	var_t* thisV = get_obj(env, THIS);
	const char* str = get_str(env, "str");
	GET_REGEX

	regex->multiple(str);
	return thisV;
}

var_t* native_regex_addModifier(vm_t* vm, var_t* env, void* data) {
	(void)vm; (void)data;
	var_t* thisV = get_obj(env, THIS);
	const char* str = get_str(env, "str");
	GET_REGEX

	regex->add_modifier(str[0]);
	return thisV;
}

var_t* native_regex_removeModifier(vm_t* vm, var_t* env, void* data) {
	(void)vm; (void)data;
	var_t* thisV = get_obj(env, THIS);
	const char* str = get_str(env, "str");
	GET_REGEX

	regex->remove_modifier(str[0]);
	return thisV;
}

var_t* native_regex_range(vm_t* vm, var_t* env, void* data) {
	(void)vm; (void)data;
	var_t* thisV = get_obj(env, THIS);
	const char* a = get_str(env, "a");
	const char* b = get_str(env, "b");
	GET_REGEX

	regex->range(a, b);
	return thisV;
}

var_t* native_regex_searchGlobal(vm_t* vm, var_t* env, void* data) {
	(void)vm; (void)data;
	var_t* thisV = get_obj(env, THIS);
	bool en = get_bool(env, "enable");
	GET_REGEX

	regex->search_global(en);
	return thisV;
}

var_t* native_regex_searchLine(vm_t* vm, var_t* env, void* data) {
	(void)vm; (void)data;
	var_t* thisV = get_obj(env, THIS);
	bool en = get_bool(env, "enable");
	GET_REGEX

	regex->search_one_line(en);
	return thisV;
}

var_t* native_regex_reset(vm_t* vm, var_t* env, void* data) {
	(void)vm; (void)data;
	var_t* thisV = get_obj(env, THIS);
	GET_REGEX

	regex->reset();
	return thisV;
}

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#define CLS_REGEX "Regex"

void reg_natives(vm_t* vm) {
	var_t *cls = vm_new_class(vm, CLS_REGEX);
	vm_reg_native(vm, cls, "constructor()", native_regex_constructor, NULL);
	vm_reg_native(vm, cls, "reset()", native_regex_reset, NULL);
	vm_reg_native(vm, cls, "toString()", native_regex_toString, NULL);
	vm_reg_native(vm, cls, "find(str)", native_regex_find, NULL);
	vm_reg_native(vm, cls, "maybe(str)", native_regex_maybe, NULL);
	vm_reg_native(vm, cls, "then(str)", native_regex_then, NULL);
	vm_reg_native(vm, cls, "anythingBut(str)", native_regex_anythingBut, NULL);
	vm_reg_native(vm, cls, "anyOf(str)", native_regex_anyOf, NULL);
	vm_reg_native(vm, cls, "any(str)", native_regex_any, NULL);
	vm_reg_native(vm, cls, "anything()", native_regex_anything, NULL);
	vm_reg_native(vm, cls, "somethingBut(str)", native_regex_somethingBut, NULL);
	vm_reg_native(vm, cls, "something()", native_regex_something, NULL);
	vm_reg_native(vm, cls, "add(str)", native_regex_add, NULL);
	vm_reg_native(vm, cls, "alt(str)", native_regex_alt, NULL);
	vm_reg_native(vm, cls, "linebr()", native_regex_linebr, NULL);
	vm_reg_native(vm, cls, "br()", native_regex_br, NULL);
	vm_reg_native(vm, cls, "tab()", native_regex_tab, NULL);
	vm_reg_native(vm, cls, "word()", native_regex_word, NULL);
	vm_reg_native(vm, cls, "startOfLine(enable)", native_regex_startOfLine, NULL);
	vm_reg_native(vm, cls, "endOfLine(enable)", native_regex_endOfLine, NULL);
	vm_reg_native(vm, cls, "withAnyCase(enable)", native_regex_withAnyCase, NULL);
	vm_reg_native(vm, cls, "searchGlobal(enable)", native_regex_searchGlobal, NULL);
	vm_reg_native(vm, cls, "searchLine(enable)", native_regex_searchLine, NULL);
	vm_reg_native(vm, cls, "multi(str)", native_regex_multi, NULL);
	vm_reg_native(vm, cls, "test(str)", native_regex_test, NULL);
	vm_reg_native(vm, cls, "addModifier(str)", native_regex_addModifier, NULL);
	vm_reg_native(vm, cls, "removeModifier(str)", native_regex_removeModifier, NULL);
	vm_reg_native(vm, cls, "range(a, b)", native_regex_range, NULL);
	vm_reg_native(vm, cls, "replace(src, value)", native_regex_replace, NULL);
}

#ifdef __cplusplus
}
#endif /* __cplusplus */

