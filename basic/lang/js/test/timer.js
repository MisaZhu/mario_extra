function f(s) {
	let x = 0;
	MarioTimer.setTimer(10, true, function() { console.ln(s + x); x++; });
}

f("timer count: ");

while(true) {
	yield();
}
