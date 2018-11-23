let regex = new Regex();
let expr = regex
				.searchLine(true)
				.startOfLine(true)
				.then("http")
				.maybe("s")
				.then("://")
				.maybe("www.")
				.anythingBut(" ")
				.endOfLine(true);

console.log(expr.toString());
console.log(expr.test("https://www.rokid.com"));

expr = regex.reset().find("name");
console.log(expr.toString());
console.log(expr.replace("Hello, name.", "master Yoda"));
