let js = "
	MarioThread.current().onMessage = function(s) {
		console.log('from main msg: '+ s); 
		MarioThread.father().sendMessage('reply ' + s);
	};
	while(true) { 
		yield();
	}
";

let th = MarioThread.run(js);
let x = 1000;

MarioThread.current().onMessage = function(s) {
	console.log('from sub msg: '+ s);
};


while(true) {
	th.sendMessage("" + (x++));
	yield();
}
