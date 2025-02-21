#pragma once

#if _WIN32
	#include "windows/EStream_windows.h"
#else
	#include "linux/EStream_linux.h" 
#endif