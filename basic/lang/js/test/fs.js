if(_args.length < 3) {
	console.log("Error: filename missed.");
	return;
}

fd = FS.open(_args[2], FS.RDONLY);

b = new Bytes(100);
FS.read(fd, b, 100);

console.log(b.toString());

FS.close(fd);
