## 빌드 방법
* g++ -o result.exe widget_test.cpp -L/usr/X11R6/lib -lXt -lX11
* 현재 주어진 -L 경로 대신 /usr/amd64 경로로 떨어지므로 -l만 추가해줘도 됨
