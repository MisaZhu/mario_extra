SDL.init();
mode = SDL.getDisplayMode();

Font.init();
font = Font.open("wqy.ttc", 22);

win = SDL.createWindow("hello", 10, 10, mode.w-100, mode.h-100, false);
canvas = win.getCanvas();

texImage = Image.loadTexture(canvas, "test.png");

function draw(text) {
	canvas.setColor(0x0);
	canvas.clear();
	let w = texImage.w/3;
	let h = texImage.h/3;

	canvas.filledRoundedRectangle(4, h-h/3, win.w-4, h, 6, 0xFFFFFF00);

	canvas.copyTexture(texImage, 
			new Rect(0, 0, texImage.w, texImage.h), 
			new Rect(0, 0, texImage.w/3, texImage.h/3));

	canvas.drawText(":>" + text, 4, win.h - 30, font, 0xFF00FF00);
	canvas.refresh();
}

let text = "";

Event.setTextInputRect(new Rect(20, win.h-50, 200, 200));
while(true) {
	ev = Event.pollEvent();
	if(ev.type == Event.NONE)
		continue;

	if(ev.type == Event.QUIT) {
		break;
	}
	else if(ev.type == Event.KEY_UP) {
		if(ev.keyboard.code == 27) {
			break;
		}
		else if(ev.keyboard.code == 13) {
			if(text == "exit")
				break;
			text = "";
		}
	}
	else if(ev.type == Event.KEY_DOWN) {
		if(ev.keyboard.code == 8) {
			let utf8 = new UTF8(text);
			let len = utf8.length();
			if(len > 0) {
				utf8 = utf8.substr(0, len-1);
				text = utf8.toString();
			}
		}
	}
	else if(ev.type == Event.TEXT_INPUT) {
		text = text + ev.text.text;
	}

	draw(text);
}

font.close();
texImage.destroy();
canvas.destroy();
win.destroy();

Font.quit();
SDL.quit();
