# mpy-qrencode

A micropython binding to qr code generation.

Add `#define MODULE_QRENCODE_ENABLED (1)` in your `mpconfigport.h`.

Example:

```py
import m5stack
from m5stack import LCD, fonts, color565
import qrencode

lcd = LCD()
lcd.set_color(color565(0,50,250), color565(255,255,255)) # text color, background color
lcd.erase()

def run(x0=0, y0=0, data="some text here"):
	s = qrencode.make(data).decode('utf-8')
	arr = s.split('\n')
	y = y0
	color = color565(0,0,0)
	for l in arr:
		y = y + 1
		x = x0
		for b in l:
			x = x + 1
			if b == '\x01':
				lcd.pixel(x,y,color)
```