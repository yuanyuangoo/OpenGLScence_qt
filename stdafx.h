// stdafx.h : ��׼ϵͳ�����ļ��İ����ļ���
// ���Ǿ���ʹ�õ��������ĵ�
// �ض�����Ŀ�İ����ļ�
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
#define RENDERMODE_VBO		0	//	1��ȾģʽVBO, 0��Ⱦģʽ����
#define RENDERMODE_POINT	0	//	1��Ⱦ��,  0��Ⱦ��

#define RENDERMODE_MOVING	0	//  1 ����
#define ENABLE_LIGHTING         0   //����
#define ENABLE_CONSOLE_WINDOW	0	// 1 ����һ������̨����
#define ENABLE_TIMER		0		// 1 ��ʱ
#define ENABLE_FPS_COUNT	0		// 1 ֡��

#define COUNT_MODEL						1		// ģ����Ŀ
#define COUNT_MODEL_SIMULATE		4				// ģ���ģ�ͣ�43����1M������  1012134������

#define ENABLE_DRAW_REPEAT	1	//1		�ظ���Ⱦ1��ģ��
#define ENABLE_DRAW			1	//1		��Ⱦ����

#define ENABLE_OPTIMIZE	1 //�Ż�

#define ENABLE_OPENMP	1 //OpenMP

#define ENABLE_CROSSARRAY	1 //��������

#if ENABLE_CROSSARRAY
#define ELEMENT_COUNT_POINT		8
#define STRIDE_POINT			5
#else
#define ELEMENT_COUNT_POINT		3
#define STRIDE_POINT			0
#endif

#define ELEMENT_COUNT_LINE		4

#define ELEMENT_COUNT_MATIRX	(ELEMENT_COUNT_LINE*4)


// TODO:  �ڴ˴����ó�����Ҫ������ͷ�ļ�
