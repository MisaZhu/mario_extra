#include "native_dns.h"
#include "dnsc.h"
#include <string>

using namespace std;

var_t* native_dns_resolv(vm_t* vm, var_t* env, void *data) {
	string domain = get_str(env, "domain");
	string type = get_str(env, "type");
	
	int t = DNS_A_RECORD;
	
	if(type == "MX") {
		t = DNS_MX_RECORD;
	}
	else if(type == "CNAME") {
		t = DNS_CNAME_RECORD;
	}
	else if(type == "NS") {
		t = DNS_NS_RECORD;
	}
	
	vector<DNSRes> res;
	DNSC::resolv(domain.c_str(), t, res);

	var_t *ret = var_new_array(vm);
	size_t sz = res.size();
	for(size_t i=0; i<sz; ++i) {
		var_array_add(ret, var_new_str(vm, res[i].res.c_str()));
	}

	return ret;
}


#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#define CLS_DNS "DNS"

void reg_native_dns(vm_t* vm) {
	vm_reg_var(vm, CLS_DNS, "A", var_new_str(vm, "A"), true);
	vm_reg_var(vm, CLS_DNS, "MX", var_new_str(vm, "MX"), true);
	vm_reg_var(vm, CLS_DNS, "NS", var_new_str(vm, "NS"), true);
	vm_reg_var(vm, CLS_DNS, "CNAME", var_new_str(vm, "CNAME"), true);
	vm_reg_static(vm, CLS_DNS, "resolv(domain, type)", native_dns_resolv, NULL);
}

#ifdef __cplusplus
}
#endif /* __cplusplus */
