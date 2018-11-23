let __mario_quit = false;


function marioQuit() {
	__mario_quit = true;
}

function marioLoop() {
	while(!__mario_quit) {
		yield();
	}
}

function setTimeout(callback, msec) {
	MarioTimer.setTimer(msec, false, callback);
}

