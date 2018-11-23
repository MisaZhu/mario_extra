let promise = new Promise(function(resolve, reject) {
	setTimeout(function() { 
		resolve("ok."); 
		//reject("error!"); 
	}, 1000);
});


promise.then(function(value) {
		console.log("resolve: " + value);
		marioQuit();
	}, 
	function(value) {
		console.log("reject: " + value);
		marioQuit();
	});

console.log("main task going.");

marioLoop();
