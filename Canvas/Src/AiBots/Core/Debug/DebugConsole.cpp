#include "DebugConsole.h"
#include <iterator>

// initialize static variable
std::vector<std::string> DebugConsole::debugConsoleBuffer;
bool DebugConsole::isBufferFlushed = true;
bool DebugConsole::isDebugWindowDestroyed = false;
bool DebugConsole::isDebugConsoleActive = true;

// TODO to implement
//std::ofstream DebugConsole::logOutFile;

int DebugConsole::debugWindowPositionLeft;
int DebugConsole::debugWindowPositionTop;

bool DebugConsole::createDebugWindow()
{
	debugWindowPositionLeft = 0;
	debugWindowPositionTop = 0;
	isBufferFlushed = true;

	// open log file
	// TODO to implement
	//logOutFile.open("DebugLog.txt");

	// it is fixed size text box
	// with dimensions
	// DEBUG_WINDOW_WIDTH
	// DEBUG_WINDOW_HEIGHT

	return true;
}

DebugConsole& DebugConsole::Instance()
{
	static DebugConsole instance;
	static bool created = false;
	if (!created)
	{
		createDebugWindow();
		created = true;
	}

	return instance;
}

void DebugConsole::writeAndResetBuffer()
{
	debugWindowPositionLeft = 0;
	debugWindowPositionTop = 0;
	isBufferFlushed = true;

	// write out the contents of the buffer to a file
	for (std::string str : debugConsoleBuffer)
	{
		// TODO to implement
		//logOutFile << str << std::endl;
	}

	debugConsoleBuffer.clear();
}

void DebugConsole::outputText()
{
	//SetBkMode(ps.hdc, TRANSPARENT);
	//SetTextColor(ps.hdc, RGB(255, 255, 255));

	//if (debugConsoleBuffer.size() > 1)
	//{

	//	// Get vertical scroll bar position
	//	si.cbSize = sizeof(si);
	//	si.fMask = SIF_POS;
	//	GetScrollInfo(hwnd, SB_VERT, &si);
	//	iVertPos = si.nPos;

	//	//number of lines we can fit on this page
	//	int PageSize = (int)(cyClient / cyChar) - 1;

	//	int StartIndex = 0;

	//	if (iVertPos > PageSize)
	//	{
	//		StartIndex = iVertPos - PageSize;
	//	}

	//	std::vector<std::string>::iterator beg = debugConsoleBuffer.begin() + StartIndex;
	//	std::vector<std::string>::iterator end = beg;

	//	//advance end
	//	for (int i = 0; i < PageSize + 1; ++i)
	//	{
	//		++end;
	//		if (end == debugConsoleBuffer.end()) break;
	//	}

	//	int line = 0;

	//	for (beg; (beg != end) && (beg != debugConsoleBuffer.end()); ++beg)
	//	{
	//		TextOut(ps.hdc, 0, cyChar*line++, (*beg).c_str(), (*beg).size());
	//	}
	//}
}

void DebugConsole::clearText()
{

}

DebugConsole::~DebugConsole()
{
	writeAndResetBuffer();
}

void DebugConsole::clearDebugBuffer()
{
	debugConsoleBuffer.clear();
	flush();
}

void DebugConsole::flush()
{
	if (!isDebugWindowDestroyed)
	{
		isBufferFlushed = true;
	}
}

void DebugConsole::setDebugConsoleOff()
{
	isDebugConsoleActive = false;
}

void DebugConsole::setDebugConsoleOn()
{
	isDebugConsoleActive = true;
}

bool DebugConsole::getIsDebugWindowDestroyed() const
{
	return isDebugWindowDestroyed;
}

void DebugConsole::writeToDebugConsole(std::string messageToWrite)
{
	if (!isDebugConsoleActive || isDebugWindowDestroyed)
	{
		return;
	}
	else
	{
		// reset buffer and scroll info if it overflows. Write the excess to file
		if (debugConsoleBuffer.size() > MaxBufferSize)
		{
			writeAndResetBuffer();
		}

		if (messageToWrite == "")
		{
			flush();
			return;
		}

		if (!isBufferFlushed)
		{
			debugConsoleBuffer.back() += messageToWrite;
		}
		else
		{
			debugConsoleBuffer.push_back(messageToWrite);
			isBufferFlushed = false;
		}
	}
}
