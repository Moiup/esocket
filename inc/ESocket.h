#pragma once

#if _WIN32
	#include "windows/ESocket_windows.h"
#else
	#include "linux/ESocket_linux.h" 
#endif