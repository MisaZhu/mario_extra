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

console.ln(expr.toString());
console.ln(expr.test("https://www.rokid.com"));

expr = regex.reset().find("name");
console.ln(expr.toString());
console.ln(expr.replace("Hello, name.", "master Yoda"));
