# pdf-viewer
This is an application that originaly was intended to read PDF files and present it in a nice, paged way, so that it could be viewed as a presentation. At it's current shape, application supports only ASCII TXT files. Slides may be changed either with arrow keys or buttons. The application was written using Visual Studio C++ 2017 and Win32 API (low level C API) and may be run only on Windows platform. There is few things that might be improved. Gtest/gmock was used in order to unit-test the code.
Things that could be added:
- UNICODE files support
- PDF files support
- changing the font size/style

Bugs to be fixed:
- arrow keys should be registered globally
- better algorithm for determining how much text goes into one page
