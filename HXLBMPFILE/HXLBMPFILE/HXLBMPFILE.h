// 下列 ifdef 块是创建使从 DLL 导出更简单的
// 宏的标准方法。此 DLL 中的所有文件都是用命令行上定义的 HXLBMPFILE_EXPORTS
// 符号编译的。在使用此 DLL 的
// 任何其他项目上不应定义此符号。这样，源文件中包含此文件的任何其他项目都会将
// HXLBMPFILE_API 函数视为是从 DLL 导入的，而此 DLL 则将用此宏定义的
// 符号视为是被导出的。
#ifdef HXLBMPFILE_EXPORTS
#define HXLBMPFILE_API __declspec(dllexport)
#else
#define HXLBMPFILE_API __declspec(dllimport)
#endif

#include <stdio.h>
#include<math.h>
#include<windows.h>

// 此类是从 HXLBMPFILE.dll 导出的
//class HXLBMPFILE CHXLBMPFILE {
//public:
//	CHXLBMPFILE(void);
//	// TODO:  在此添加您的方法。
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

