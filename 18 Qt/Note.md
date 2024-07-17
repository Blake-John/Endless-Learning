---
annotation-target: "[[906264+Qt6C+++开发指南.pdf]]"
---



>%%
>```annotation-json
>{"created":"2024-06-29T12:16:56.764Z","text":"# What is a event","updated":"2024-06-29T12:16:56.764Z","document":{"title":"","link":[{"href":"urn:x-pdf:4bbfd6590e0562d469c92cac14ad6974"},{"href":"vault:/18 Qt/906264+Qt6C+++%E5%BC%80%E5%8F%91%E6%8C%87%E5%8D%97.pdf"}],"documentFingerprint":"4bbfd6590e0562d469c92cac14ad6974"},"uri":"vault:/18 Qt/906264+Qt6C+++%E5%BC%80%E5%8F%91%E6%8C%87%E5%8D%97.pdf","target":[{"source":"vault:/18 Qt/906264+Qt6C+++%E5%BC%80%E5%8F%91%E6%8C%87%E5%8D%97.pdf","selector":[{"type":"TextPositionSelector","start":365178,"end":365322},{"type":"TextQuoteSelector","exact":"事件表示应用程序中发生的操作或变化，如移动鼠标、点击鼠标、按下按键等。在Qt 中，事件是对象，是 QEvent 类或其派生类的实例，例如 QKeyEvent 是按键事件类，QMouseEvent 是鼠标事件类，QPaintEvent 是绘制事件类，QTimerEvent 是定时器事件类。","prefix":"理等内容。 6.1.1    事件的产生和派发 1．事件的产生 ","suffix":" 按事件的来源，可以将事件划分为3 类。 • 自生事件（spon"}]}]}
>```
>%%
>*%%PREFIX%%理等内容。 6.1.1    事件的产生和派发 1．事件的产生%%HIGHLIGHT%% ==事件表示应用程序中发生的操作或变化，如移动鼠标、点击鼠标、按下按键等。在Qt 中，事件是对象，是 QEvent 类或其派生类的实例，例如 QKeyEvent 是按键事件类，QMouseEvent 是鼠标事件类，QPaintEvent 是绘制事件类，QTimerEvent 是定时器事件类。== %%POSTFIX%%按事件的来源，可以将事件划分为3 类。 • 自生事件（spon*
>%%LINK%%[[#^667ovc7egw7|show annotation]]
>%%COMMENT%%
># What is a event
>%%TAGS%%
>
^667ovc7egw7


>%%
>```annotation-json
>{"created":"2024-06-29T12:17:47.457Z","text":"* 自生事件 (spontaneous event)","updated":"2024-06-29T12:17:47.457Z","document":{"title":"","link":[{"href":"urn:x-pdf:4bbfd6590e0562d469c92cac14ad6974"},{"href":"vault:/18 Qt/906264+Qt6C+++%E5%BC%80%E5%8F%91%E6%8C%87%E5%8D%97.pdf"}],"documentFingerprint":"4bbfd6590e0562d469c92cac14ad6974"},"uri":"vault:/18 Qt/906264+Qt6C+++%E5%BC%80%E5%8F%91%E6%8C%87%E5%8D%97.pdf","target":[{"source":"vault:/18 Qt/906264+Qt6C+++%E5%BC%80%E5%8F%91%E6%8C%87%E5%8D%97.pdf","selector":[{"type":"TextPositionSelector","start":365369,"end":365440},{"type":"TextQuoteSelector","exact":"是由窗口系统产生的事件。例如，QKeyEvent 事件、QMouseEvent事件。自生事件会进入系统队列，然后被应用程序的事件循环逐个处理。","prefix":"为3 类。 • 自生事件（spontaneous event）：","suffix":" • 发布事件（posted event）：是由 Qt 或应用程"}]}]}
>```
>%%
>*%%PREFIX%%为3 类。 • 自生事件（spontaneous event）：%%HIGHLIGHT%% ==是由窗口系统产生的事件。例如，QKeyEvent 事件、QMouseEvent事件。自生事件会进入系统队列，然后被应用程序的事件循环逐个处理。== %%POSTFIX%%• 发布事件（posted event）：是由 Qt 或应用程*
>%%LINK%%[[#^moqcavup9ok|show annotation]]
>%%COMMENT%%
>* 自生事件 (spontaneous event)
>%%TAGS%%
>
^moqcavup9ok


>%%
>```annotation-json
>{"created":"2024-06-29T12:18:30.461Z","text":"* 发布事件 (posted event)","updated":"2024-06-29T12:18:30.461Z","document":{"title":"","link":[{"href":"urn:x-pdf:4bbfd6590e0562d469c92cac14ad6974"},{"href":"vault:/18 Qt/906264+Qt6C+++%E5%BC%80%E5%8F%91%E6%8C%87%E5%8D%97.pdf"}],"documentFingerprint":"4bbfd6590e0562d469c92cac14ad6974"},"uri":"vault:/18 Qt/906264+Qt6C+++%E5%BC%80%E5%8F%91%E6%8C%87%E5%8D%97.pdf","target":[{"source":"vault:/18 Qt/906264+Qt6C+++%E5%BC%80%E5%8F%91%E6%8C%87%E5%8D%97.pdf","selector":[{"type":"TextPositionSelector","start":365462,"end":365600},{"type":"TextQuoteSelector","exact":"是由 Qt 或应用程序产生的事件。例如，QTimer 定时器发生定时溢出时Qt 会自动发布QTimerEvent 事件。应用程序使用静态函数QCoreApplication::postEvent()产生发布事件。发布事件会进入Qt 事件队列，然后由应用程序的事件循环进行处理。","prefix":"的事件循环逐个处理。 • 发布事件（posted event）：","suffix":" • 发送事件（sent  event）：是由Qt 或应用程序定"}]}]}
>```
>%%
>*%%PREFIX%%的事件循环逐个处理。 • 发布事件（posted event）：%%HIGHLIGHT%% ==是由 Qt 或应用程序产生的事件。例如，QTimer 定时器发生定时溢出时Qt 会自动发布QTimerEvent 事件。应用程序使用静态函数QCoreApplication::postEvent()产生发布事件。发布事件会进入Qt 事件队列，然后由应用程序的事件循环进行处理。== %%POSTFIX%%• 发送事件（sent  event）：是由Qt 或应用程序定*
>%%LINK%%[[#^87v5or9gkpt|show annotation]]
>%%COMMENT%%
>* 发布事件 (posted event)
>%%TAGS%%
>
^87v5or9gkpt


>%%
>```annotation-json
>{"created":"2024-06-29T12:18:53.958Z","text":"* 发送事件 (sent event)","updated":"2024-06-29T12:18:53.958Z","document":{"title":"","link":[{"href":"urn:x-pdf:4bbfd6590e0562d469c92cac14ad6974"},{"href":"vault:/18 Qt/906264+Qt6C+++%E5%BC%80%E5%8F%91%E6%8C%87%E5%8D%97.pdf"}],"documentFingerprint":"4bbfd6590e0562d469c92cac14ad6974"},"uri":"vault:/18 Qt/906264+Qt6C+++%E5%BC%80%E5%8F%91%E6%8C%87%E5%8D%97.pdf","target":[{"source":"vault:/18 Qt/906264+Qt6C+++%E5%BC%80%E5%8F%91%E6%8C%87%E5%8D%97.pdf","selector":[{"type":"TextPositionSelector","start":365621,"end":365708},{"type":"TextQuoteSelector","exact":"是由Qt 或应用程序定向发送给某个对象的事件。应用程序使用静态函数QCoreApplication::sendEvent()产生发送事件，由对象的event()函数直接处理。","prefix":"序的事件循环进行处理。 • 发送事件（sent  event）：","suffix":" 窗口系统产生的自生事件自动进入系统队列，应用程序发布的事件进入"}]}]}
>```
>%%
>*%%PREFIX%%序的事件循环进行处理。 • 发送事件（sent  event）：%%HIGHLIGHT%% ==是由Qt 或应用程序定向发送给某个对象的事件。应用程序使用静态函数QCoreApplication::sendEvent()产生发送事件，由对象的event()函数直接处理。== %%POSTFIX%%窗口系统产生的自生事件自动进入系统队列，应用程序发布的事件进入*
>%%LINK%%[[#^1p804d3jzk1|show annotation]]
>%%COMMENT%%
>* 发送事件 (sent event)
>%%TAGS%%
>
^1p804d3jzk1


>%%
>```annotation-json
>{"created":"2024-06-29T12:22:09.698Z","text":"```C++\nint main (int argc, char* argv[])\n{\n    QApplication a (argc, argv);\n    Widget w;\n    w.show ();\n    return a.exec ();\n}\n```\n\n代码一般就是这样。","updated":"2024-06-29T12:22:09.698Z","document":{"title":"","link":[{"href":"urn:x-pdf:4bbfd6590e0562d469c92cac14ad6974"},{"href":"vault:/18 Qt/906264+Qt6C+++%E5%BC%80%E5%8F%91%E6%8C%87%E5%8D%97.pdf"}],"documentFingerprint":"4bbfd6590e0562d469c92cac14ad6974"},"uri":"vault:/18 Qt/906264+Qt6C+++%E5%BC%80%E5%8F%91%E6%8C%87%E5%8D%97.pdf"}
>```
>%%
>*%%PREFIX%%%%HIGHLIGHT%% ==== %%POSTFIX%%*
>%%LINK%%[[#^xwzjtp64pq|show annotation]]
>%%COMMENT%%
>```C++
>int main (int argc, char* argv[])
>{
>    QApplication a (argc, argv);
>    Widget w;
>    w.show ();
>    return a.exec ();
>}
>```
>
>代码一般就是这样。
>%%TAGS%%
>
^xwzjtp64pq
