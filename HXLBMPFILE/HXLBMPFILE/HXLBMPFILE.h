// ���� ifdef ���Ǵ���ʹ�� DLL �������򵥵�
// ��ı�׼�������� DLL �е������ļ��������������϶���� HXLBMPFILE_EXPORTS
// ���ű���ġ���ʹ�ô� DLL ��
// �κ�������Ŀ�ϲ�Ӧ����˷��š�������Դ�ļ��а������ļ����κ�������Ŀ���Ὣ
// HXLBMPFILE_API ������Ϊ�Ǵ� DLL ����ģ����� DLL ���ô˺궨���
// ������Ϊ�Ǳ������ġ�
#ifdef HXLBMPFILE_EXPORTS
#define HXLBMPFILE_API __declspec(dllexport)
#else
#define HXLBMPFILE_API __declspec(dllimport)
#endif

#include <stdio.h>
#include<math.h>
#include<windows.h>

// �����Ǵ� HXLBMPFILE.dll ������
//class HXLBMPFILE CHXLBMPFILE {
//public:
//	CHXLBMPFILE(void);
//	// TODO:  �ڴ�������ķ�����
//};

class HXLBMPFILE_API HXLBMPFILE
{
	BYTE *Imagedata;
public:
	int imagew, imageh;
	int iYRGBnum;

	RGBQUAD palette[256];

	BYTE* pDataAt(int h, int Y0R0G1B2 = 0);
	BOOL AllocateMem();

	BOOL LoadBMPFILE(char *fname);
	BOOL SaveBMPFILE(char *fname);

	HXLBMPFILE();
	~HXLBMPFILE();
};

//extern HXLBMPFILE int nHXLBMPFILE;
//
//HXLBMPFILE int fnHXLBMPFILE(void);
//HXLBMPFILE HXLBMPFILE(void);

