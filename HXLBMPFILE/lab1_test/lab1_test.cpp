#include"..\\HXLBMPFILE\HXLBMPFILE.h"
#pragma comment (lib, "..\\Debug\\HXLBMPFILE.lib")
int main(int argc, char* argv[])
{
	HXLBMPFILE bmpfile; int i, j, v;
	if (!bmpfile.LoadBMPFILE("C:\\Users\\楠\\Desktop\\temp\\lesson\\计算机图像处理\\TY_I.bmp")) return 1;
	// do other processing with the imagedata//
	HXLBMPFILE bf;
	bf.imagew = bmpfile.imagew;
	bf.imageh = bmpfile.imageh;
	//bf.iYRGBnum = bmpfile.iYRGBnum;
	//bf.iYRGBnum = 3;
	bf.iYRGBnum = 1;
	if (!bf.AllocateMem()) return 1;
	for (i = 0;i < bmpfile.imageh - 1;i++)
	{
		for (j = 0;j < bmpfile.imagew - 1;j++)
		{
			//bf.pDataAt(i)[j] = bmpfile.palette[bmpfile.pDataAt(i)[j]].rgbBlue;
			//bf.pDataAt(i,1)[j] = bmpfile.palette[bmpfile.pDataAt(i)[j]].rgbGreen;
			//bf.pDataAt(i, 2)[j] = bmpfile.palette[bmpfile.pDataAt(i)[j]].rgbRed;
			//bf.palette[]
			bf.pDataAt(i)[j] = BYTE(0.114*bmpfile.pDataAt(i)[j] + 0.587*bmpfile.pDataAt(i, 1)[j] + 0.299*bmpfile.pDataAt(i, 2)[j]);


		}
	}
	bf.SaveBMPFILE("C:\\Users\\楠\\Desktop\\temp\\lesson\\计算机图像处理\\TYtest.bmp");
	printf("program ends!\n");
	return 0;
}