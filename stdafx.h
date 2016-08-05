// stdafx.h : 标准系统包含文件的包含文件，
// 或是经常使用但不常更改的
// 特定于项目的包含文件
//

#pragma once
#include "Dependencies/glew/glew.h"
#include "Dependencies/Freeglut/freeglut.h"
#include <glm/glm.hpp>
#include "targetver.h"
#include <time.h>
#include <conio.h>
#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <vector>
#include <stdio.h>
#include <tchar.h>
#include "math/math2.h"
#define RENDERMODE_VBO		0	//	1渲染模式VBO, 0渲染模式常规
#define RENDERMODE_POINT	0	//	1渲染点,  0渲染面

#define RENDERMODE_MOVING	0	//  1 动画
#define ENABLE_LIGHTING         0   //光照
#define ENABLE_CONSOLE_WINDOW	0	// 1 打开另一个控制台窗口
#define ENABLE_TIMER		0		// 1 计时
#define ENABLE_FPS_COUNT	0		// 1 帧速

#define COUNT_MODEL						1		// 模型数目
#define COUNT_MODEL_SIMULATE		4				// 模拟大模型，43倍共1M顶点数  1012134个顶点

#define ENABLE_DRAW_REPEAT	1	//1		重复渲染1个模型
#define ENABLE_DRAW			1	//1		渲染开启

#define ENABLE_OPTIMIZE	1 //优化

#define ENABLE_OPENMP	1 //OpenMP

#define ENABLE_CROSSARRAY	1 //交错数组

#if ENABLE_CROSSARRAY
#define ELEMENT_COUNT_POINT		8
#define STRIDE_POINT			5
#else
#define ELEMENT_COUNT_POINT		3
#define STRIDE_POINT			0
#endif

#define ELEMENT_COUNT_LINE		4

#define ELEMENT_COUNT_MATIRX	(ELEMENT_COUNT_LINE*4)


// TODO:  在此处引用程序需要的其他头文件
