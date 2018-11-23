if(_args.length < 3) {
	console.log("Error: dirname missed.\n");
	return;
}

let dir = new Dir(_args[2]);
let count = 0;
let s = "";
while(true) {
	s = dir.read();

	if(s.length == 0)
		break;

	console.log("[" + s + "]\n");
	count++;
}
dir.close();

console.log("--------\nTotal: " + count + "\n");
