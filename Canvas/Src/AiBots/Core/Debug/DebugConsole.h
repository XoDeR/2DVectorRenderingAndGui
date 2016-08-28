#pragma once
//------------------------------------------------------------------------
// resizable console window for recording and displaying debug info.
// Flush the buffer using "" or the flush macro. 
// DebugConsole::Instance().writeToDebugConsole("Message to Write");
//------------------------------------------------------------------------
#include <vector>

#include "Core/Math/MathFn.h"

// need to define a custom message

// maximum number of lines shown in console before the buffer is flushed to a file
const int MaxBufferSize = 500;

// initial dimensions of the console window
const int DEBUG_WINDOW_WIDTH = 1024;
const int DEBUG_WINDOW_HEIGHT = 148;

#define DEBUG

class DebugConsole
{
public:
	~DebugConsole();
	static DebugConsole& Instance();
	void clearDebugBuffer();
	static void flush();

	// writes the contents of the buffer to the file "debug_log.txt", clears
	// the buffer and resets the appropriate scroll info
	void writeAndResetBuffer();

	// use to activate deactivate
	static void setDebugConsoleOff();
	static void setDebugConsoleOn();
	bool getIsDebugWindowDestroyed() const;
	void writeToDebugConsole(std::string messageToWrite);
private:
	DebugConsole(){}
	// copy ctor and assignment should be private
	DebugConsole(const DebugConsole&);
	DebugConsole& operator=(const DebugConsole&);

	// this registers the window class and creates the window(called by the ctor)
	static bool createDebugWindow();

	void outputText();
	void clearText();

	// the string buffer. All input to debug stream is stored here
	static std::vector<std::string> debugConsoleBuffer;

	// If true the next input will be pushed into the buffer
	// If false, it will be appended.
	static bool isBufferFlushed;

	// position of debug window
	static int debugWindowPositionTop;
	static int debugWindowPositionLeft;

	// set to true if the window is destroyed
	static bool isDebugWindowDestroyed;

	// if false the console will just disregard any input
	static bool isDebugConsoleActive;

	// default logging file
	// TODO to implement
	//static std::ofstream logOutFile;
};
