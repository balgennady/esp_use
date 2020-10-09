# ESp8266 clock with Oled display

## Описание
Простые часы на ESp8266 + Oled display 
 
Для сборки потребуется : 
* Плата NodeMcu v3
* 0.96" I2C OLED Display

## Изображения

![1](/img/ESp8266(1).jpg)
![2](/img/ESp8266(2).jpg)
![3](/img/ESp8266(3).jpg)
![4](/img/ESp8266(4).jpg)


## Вопросы

```cpp
#include <Adafruit_GFX.h> 
#include <Adafruit_SSD1306.h> 
```

[Библиотека Adafruit GFX](https://github.com/adafruit/Adafruit-GFX-Library)

Это основная графическая библиотека для всех Adafruit дисплеев, предоставляющая общий набор графических примитивов (точки, линии, круги и т. Д.). 
Он должен быть соединен с аппаратной библиотекой для каждого устройства отображения, которое мы несем (для обработки функций нижнего уровня).
