if(_args.length < 3) {
	console.log("Error: filename missed.\n");
	return;
}

fd = FS.open(_args[2], FS.RDONLY);

b = new Bytes(100);
FS.read(fd, b, 100);

console.ln(b.toString());

FS.close(fd);
