if(_args.length < 3) {
	console.log("Error: domain name missed.");
	return;
}

let res = DNS.resolv(_args[2], DNS.A);
console.log(res);
