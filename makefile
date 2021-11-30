CC=g++
CFLAGS=-c -static
FOLDER=src/

I_GLEW=-I dependencies\GLEW\include
I_GLFW=-I dependencies\GLFW\include
L_GLEW=-L dependencies\GLEW\lib\Release\Win32 -lglew32s
L_GLFW=-L dependencies\GLFW\lib-mingw-w64 -lglfw3
L_EXTRA=-lOpenGL32 -lgdi32 -lmingw32
KOSTILS=-Wl,-u,___mingw_vsnprintf -Wl,--defsym,___ms_vsnprintf=___mingw_vsnprintf

IL_ALL=$(IL_GLFW) $(IL_GLEW)

I_ALL=$(I_GLEW) $(I_GLFW)
L_ALL=$(L_GLEW) $(L_GLFW) $(L_EXTRA) $(KOSTILS)

build: app.o errorHandling.o Triangle.o
	$(CC) -static app.o errorHandling.o Triangle.o -o $(FOLDER)app.exe $(L_ALL)
	$(FOLDER)./app

app.o: $(FOLDER)app.cpp
	$(CC) $(CFLAGS) $(FOLDER)app.cpp $(I_ALL)

errorHandling.o: $(FOLDER)errorHandling.cpp
	$(CC) $(CFLAGS) $(FOLDER)errorHandling.cpp $(I_GLEW)

Triangle.o: $(FOLDER)Triangle.cpp
	$(CC) $(CFLAGS) $(FOLDER)Triangle.cpp $(I_GLEW)


debug: app.d errorHandling.d Triangle.d
	$(CC) -g -static app.d errorHandling.d Triangle.d -o $(FOLDER)app.exe $(L_ALL)

app.d: $(FOLDER)app.cpp
	$(CC) $(CFLAGS) -g $(FOLDER)app.cpp $(I_ALL) -o app.d

errorHandling.d: $(FOLDER)errorHandling.cpp
	$(CC) $(CFLAGS) -g $(FOLDER)errorHandling.cpp $(I_GLEW) -o errorHandling.d

Triangle.d: $(FOLDER)Triangle.cpp
	$(CC) $(CFLAGS) -g $(FOLDER)Triangle.cpp $(I_GLEW) -o Triangle.d