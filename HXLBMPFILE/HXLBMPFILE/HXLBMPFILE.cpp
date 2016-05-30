// HXLBMPFILE.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"
#include "HXLBMPFILE.h"
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4996)

// 这是导出变量的一个示例
//HXLBMPFILE_API int nHXLBMPFILE=0;
//
//// 这是导出函数的一个示例。
//HXLBMPFILE_API int fnHXLBMPFILE(void)
//{
//    return 42;
//}

// 这是已导出类的构造函数。
// 有关类定义的信息，请参阅 HXLBMPFILE.h
HXLBMPFILE::HXLBMPFILE()
{
	Imagedata = NULL;
	for (int i = 0;i < 256;i++)
	{
		palette[i].rgbBlue = palette[i].rgbGreen = palette[i].rgbRed = i;
		palette[i].rgbReserved = 0;
	}
	iYRGBnum = 0;
	imagew = imageh = 0;
}

HXLBMPFILE::~HXLBMPFILE()
{
	if (Imagedata)
		delete Imagedata;
}

BYTE *HXLBMPFILE::pDataAt(int h, int Y0R0G1B2)
{
	if (iYRGBnum <= Y0R0G1B2)
		return NULL;
	int w = imagew*h + Y0R0G1B2*imagew*imageh;
	return Imagedata + w;
}

BOOL HXLBMPFILE::AllocateMem()
{
	int w = imagew*imageh*iYRGBnum;
	if (Imagedata)
	{
		delete Imagedata;
		Imagedata = NULL;
	}
	Imagedata = new BYTE[w];
	if (Imagedata)
		memset(Imagedata, 0, w);
	return (Imagedata != NULL);
}

BOOL HXLBMPFILE::LoadBMPFILE(char *cFilename)
{
	FILE *f;
	if (strlen(cFilename) < 1)
		return FALSE;

	f = fopen(cFilename, "r+b");
	if (f == NULL)
		return FALSE;
	BITMAPFILEHEADER fh;
	BITMAPINFOHEADER ih;
	fread(&fh, sizeof(BITMAPFILEHEADER), 1, f);
	if (fh.bfType != 0x4d42)
	{
		fclose(f);
		return FALSE;
	}//"BM"
	fread(&ih, sizeof(BITMAPINFOHEADER), 1, f);
	if ((ih.biBitCount != 8) && (ih.biBitCount != 24))
	{
		fclose(f);
		return FALSE;
	}
	iYRGBnum = ih.biBitCount / 8;
	imagew = ih.biWidth;
	imageh = ih.biHeight;
	if (!AllocateMem())
	{
		fclose(f);
		return FALSE;
	}
	if (iYRGBnum == 1)
		fread(palette, sizeof(RGBQUAD), 256, f);
	fseek(f, fh.bfOffBits, SEEK_SET);
	int w4b = (imagew * iYRGBnum + 3) / 4 * 4, i, j;
	BYTE *ptr;
	if (iYRGBnum == 1)
	{
		w4b -= imagew;
		for (i = imageh - 1; i >= 0; i--)
		{
			fread(pDataAt(i), imagew, 1, f);
			if (w4b > 0) fseek(f, w4b, SEEK_CUR);
		}
	}
	if (iYRGBnum == 3)
	{
		ptr = new BYTE[w4b];
		for (i = imageh - 1; i >= 0; i--)
		{
			fread(ptr, w4b, 1, f);
			for (j = 0; j < imagew; j++)
			{
				*(pDataAt(i, 0) + j) = *(ptr + j * 3 + 0);
				*(pDataAt(i, 1) + j) = *(ptr + j * 3 + 1);
				*(pDataAt(i, 2) + j) = *(ptr + j * 3 + 2);

			}
		}
		delete ptr;
	}
	fclose(f);
	return TRUE;
}

BOOL HXLBMPFILE::SaveBMPFILE(char *cFilename)
{
	if (!Imagedata)
		return FALSE;
	FILE *f;
	if (strlen(cFilename)<1)
		return FALSE;
	f = fopen(cFilename, "w+b");
	if (f == NULL)
		return FALSE;
	BITMAPFILEHEADER fh;
	BITMAPINFOHEADER ih;
	memset(&ih, 0, sizeof(BITMAPINFOHEADER));
	fh.bfType = 0x4d42;
	fh.bfReserved1 = fh.bfReserved2 = 0;
	fh.bfOffBits = sizeof(BITMAPFILEHEADER) +
		sizeof(BITMAPINFOHEADER) +
		((iYRGBnum == 1) ? 256 * sizeof(RGBQUAD) : 0);
	ih.biSize = 40;
	ih.biPlanes = 1;
	ih.biWidth = imagew;
	ih.biHeight = imageh;
	ih.biBitCount = 8 * iYRGBnum;
	int w4b = (imagew*iYRGBnum + 3) / 4 * 4;
	ih.biSizeImage = ih.biHeight *w4b;
	fh.bfSize = fh.bfOffBits + ih.biSizeImage;
	fwrite(&fh, sizeof(BITMAPFILEHEADER), 1, f);
	fwrite(&ih, sizeof(BITMAPINFOHEADER), 1, f);
	if (iYRGBnum == 1)
		fwrite(palette, sizeof(RGBQUAD), 256, f);
	BYTE* ptr; int i, j;
	if (iYRGBnum == 1)
	{
		ptr = new BYTE[10];
		memset(ptr, 0, 10);
		w4b -= ih.biWidth;
		for (i = ih.biHeight - 1;i >= 0;i--)
		{
			fwrite(pDataAt(i), ih.biWidth, 1, f);
			if (w4b>0) fwrite(ptr, w4b, 1, f);
		}
		delete ptr;
	}
	if (iYRGBnum == 3)
	{
		ptr = new BYTE[w4b];
		memset(ptr, 0, w4b);
		for (i = ih.biHeight - 1;i >= 0;i--)
		{
			for (j = 0; j < ih.biWidth; j++)
			{
				*(ptr + j * 3 + 0) = *(pDataAt(i, 0) + j);
				*(ptr + j * 3 + 1) = *(pDataAt(i, 1) + j);
				*(ptr + j * 3 + 2) = *(pDataAt(i, 2) + j);
			}
			fwrite(ptr, w4b, 1, f);
		}
		delete ptr;
	}
	fclose(f);
	return TRUE;
}
