#include"..\\HXLBMPFILE\HXLBMPFILE.h"
#pragma comment (lib, "..\\Debug\\HXLBMPFILE.lib")
int main(int argc, char* argv[])
{
	HXLBMPFILE f;
	if (!f.LoadBMPFILE("C:\\Users\\�\\Desktop\\temp\\lesson\\�����ͼ����\\���ӽ�.bmp"))
		return 1;
	float H[256], T[256];
	memset(H, 0, 256 * 4);
	int i, j;
	int total = f.imagew*f.imageh;
	FILE *fp = NULL;
	fopen_s(&fp, "C:\\Users\\�\\Desktop\\temp\\lesson\\�����ͼ����\\ԭͼֱ��ͼ.txt", "w+");
	for (i = 0;i < f.imageh;i++)
	{
		for (j = 0;j < f.imagew;j++)
		{
			H[f.pDataAt(i)[j]] += 1.0;
		}
	}


	for (i = 0;i < 256;i++)
	{
		H[i] /= (float)total;
		fprintf(fp, "%f ", H[i]);
	}

	fclose(fp);
	fopen_s(&fp, "C:\\Users\\�\\Desktop\\temp\\lesson\\�����ͼ����\\����ת��ͼ.txt", "w+t");
	for (i = 0;i < 256;i++)
	{
		if (i == 0)
		{
			T[i] = H[i];
			fprintf(fp, "%f ", T[i]);
		}
		else
		{
			T[i] = T[i - 1] + H[i];
			fprintf(fp, "%f ", T[i]);
		}
	}
	fclose(fp);
	//fopen_s(&fp, "C:\\Users\\�\\Desktop\\temp\\lesson\\�����ͼ����\\���⻯ת��ͼtest.txt", "w+t");
	for (i = 0;i < 256;i++)
	{
		T[i] = int(255 * T[i] + 0.5);
		//fprintf(fp, "%f ", T[i]/total);
	}

	//fclose(fp);

	for (i = 0;i < f.imageh;i++)
		for (j = 0;j < f.imagew;j++)
			f.pDataAt(i)[j] = T[f.pDataAt(i)[j]];

	f.SaveBMPFILE("C:\\Users\\�\\Desktop\\temp\\lesson\\�����ͼ����\\���ӽ����⻯.bmp");
	fopen_s(&fp, "C:\\Users\\�\\Desktop\\temp\\lesson\\�����ͼ����\\���⻯ת��ͼ.txt", "w+t");
	memset(H, 0, 256 * 4);
	for (i = 0;i < f.imageh;i++)
	{
		for (j = 0;j < f.imagew;j++)
		{
			H[f.pDataAt(i)[j]] += 1.0;
		}
	}


	for (i = 0;i < 256;i++)
	{
		H[i] /= (float)total;
		fprintf(fp, "%f ", H[i]);
	}
	printf("program ends!\n");
	return 0;
}