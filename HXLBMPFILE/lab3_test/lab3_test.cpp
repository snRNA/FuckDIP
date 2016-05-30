#include"..\\HXLBMPFILE\HXLBMPFILE.h"
#pragma comment (lib, "..\\Debug\\HXLBMPFILE.lib")
#include <math.h>
#include "Histogram.h"
#define pi 3.14159265

int main(int argc,char* argv[])
{
	HXLBMPFILE f;
	FILE *fp = NULL;
	float H[256];
	if (!f.LoadBMPFILE("C:\\Users\\楠\\Desktop\\temp\\lesson\\计算机图像处理\\柿子椒.bmp"))
		return 1;
	double *src = (double*)malloc(sizeof(double)*f.imageh*f.imagew);
	double *dst = (double*)malloc(sizeof(double)*f.imageh*f.imagew);
	//memset(src, 0, 256 * sizeof(double));
	for (int i = 0;i < f.imageh;i++)
		for (int j = 0;j < f.imagew;j++)
			src[i*f.imagew + j] = f.pDataAt(i)[j];
	int *hist = (int*)malloc(sizeof(double) * 256);
	fopen_s(&fp, "C:\\Users\\楠\\Desktop\\temp\\lesson\\计算机图像处理\\规定化d直方图.txt", "w+t");
	for (int i = 0;i < 256;i++)
	{
		int a = (int)(sin(pi*(double)i / 256) * 1000);
		hist[i] = a;
		fprintf(fp, "%d ", hist[i]);
	}
	fclose(fp);
	HistogramSpecification(src, dst, hist, f.imagew, f.imageh);
	for (int i = 0;i < f.imageh;i++)
		for (int j = 0;j < f.imagew;j++)
			f.pDataAt(i)[j] = dst[i*f.imagew + j];
	f.SaveBMPFILE("C:\\Users\\楠\\Desktop\\temp\\lesson\\计算机图像处理\\柿子椒规定化.bmp");

	fopen_s(&fp, "C:\\Users\\楠\\Desktop\\temp\\lesson\\计算机图像处理\\规定化转化图.txt", "w+t");
	memset(H, 0, 256 * 4);
	for (int i = 0;i < f.imageh;i++)
	{
		for (int j = 0;j < f.imagew;j++)
		{
			H[f.pDataAt(i)[j]] += 1.0;
		}
	}


	for (int i = 0;i < 256;i++)
	{
		fprintf(fp, "%f ", H[i]);
	}
	fclose(fp);
	printf("program ends!\n");
	return 0;
}

void InitMappingTable(void * arry, int size, int Data_type) {
	if (Data_type == TABLE_INT)
		for (int i = 0;i<size;i++)
			((int*)arry)[i] = 0;
	else if (Data_type == TABLE_CHAR)
		for (int i = 0;i<size;i++)
			((char*)arry)[i] = 0;
	else if (Data_type == TABLE_DOUBLE)
		for (int i = 0;i<size;i++)
			((double*)arry)[i] = 0;

}
void InitHistogram(int *hist) {
	for (int i = 0;i<GRAY_LEVEL;i++)
		hist[i] = 0;
}

void setHistogram(double *src, int *hist, int width, int height) {
	InitHistogram(hist);
	for (int j = 0;j<height;j++)
		for (int i = 0;i<width;i++) {
			int tempv = src[j*width + i];
			hist[tempv]++;
		}
}
int findHistogramMax(int *hist) {
	for (int i = GRAY_LEVEL - 1;i >= 0;i--) {
		if (hist[i] != 0)
			return i;
	}
	return -1;

}
int findHistogramMin(int *hist) {
	for (int i = 0;i<GRAY_LEVEL;i++) {
		if (hist[i] != 0)
			return i;
	}
	return -1;
}
void fillMaptable(double * map) {

	for (int i = 1;i<GRAY_LEVEL;i++) {
		if (map[i] == 0)
			map[i] = map[i - 1];

	}

}
/**********************************
直方图均衡
**********************************/
//均衡直方图，将原图直方图，经过公式得到目标直方图
void EqualizationHist(int *src_hist, double *dst_map) {
	int temphist[GRAY_LEVEL];
	InitHistogram(temphist);
	int max = findHistogramMax(src_hist);
	int min = findHistogramMin(src_hist);
	temphist[min] = src_hist[min];
	for (int i = min + 1;i <= max;i++)
		temphist[i] = temphist[i - 1] + src_hist[i];
	for (int i = min;i <= max;i++)
		temphist[i] -= temphist[min];
	int total = temphist[max];
	for (int i = min;i <= max;i++) {
		dst_map[i] = ((double)GRAY_LEVEL - 1.0)*temphist[i] / total;
	}

}
//直方图均很，用输入图像得到输出图像
void HistogramEqualization(double *src, double *dst, int width, int height) {
	int hist[GRAY_LEVEL];
	setHistogram(src, hist, width, height);
	double GrayMappingTable[GRAY_LEVEL];
	InitMappingTable(GrayMappingTable, GRAY_LEVEL, TABLE_DOUBLE);
	EqualizationHist(hist, GrayMappingTable);
	for (int i = 0;i<width;i++)
		for (int j = 0;j<height;j++)
			dst[j*width + i] = GrayMappingTable[(int)src[j*width + i]];

}
/******************************
直方图归一化
******************************/
void HistogramSpecification(double *src, double *dst, int* hist, int width, int height) {
	int src_hist[GRAY_LEVEL];
	setHistogram(src, src_hist, width, height);
	double srcMap[GRAY_LEVEL];
	double histMap[GRAY_LEVEL];
	InitMappingTable(srcMap, GRAY_LEVEL, TABLE_DOUBLE);
	EqualizationHist(src_hist, srcMap);
	EqualizationHist(hist, histMap);
	int histMap_[GRAY_LEVEL];
	InitHistogram(histMap_);
	for (int i = 0;i<GRAY_LEVEL;i++)
		histMap_[(int)histMap[i]] = i;
	double dstMap[GRAY_LEVEL];
	for (int i = 0;i<GRAY_LEVEL;i++) {
		dstMap[i] = histMap_[(int)srcMap[i]];
	}

	fillMaptable(dstMap);
	for (int i = 0;i<width;i++)
		for (int j = 0;j<height;j++)
			dst[j*width + i] = dstMap[(int)src[j*width + i]];
}