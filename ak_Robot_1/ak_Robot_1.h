// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the AK_ROBOT_1_EXPORTS
// symbol defined on the command line. This symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// AK_ROBOT_1_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.


//__cdecl
#ifdef AK_ROBOT_1_EXPORTS
#define AK_ROBOT_1_API __declspec(dllexport)
//#define CAK_ROBOT_1_API __cdecl(dllexport)
#else
#define AK_ROBOT_1_API __declspec(dllimport)
//#define CAK_ROBOT_1_API __cdecl(dllimport)
#endif
/*
  int __stdcall fnak_addKZ_Robot(wchar_t *kz, int_list nodes) {
        if (empty == nodes) {
            ...
        } else {
            ...
        }
    }
}
*/
// 
typedef struct node *int_list;
struct node {
    int head;
    int_list tail;
};
const int_list empty = (int_list) 1;
//

typedef struct {
	int number;
	double x;
	double y;
	double z;
} POINT;

typedef struct {
	int numbFEA;
	POINT p1;
	POINT p2;
	POINT p3;
	double As1;
	double As2;
	double As3;
	double As4;
} SHELL3;

typedef struct {
	int numbPoint; // 3 or 4
	int numbFEA;
	POINT p1;
	POINT p2;
	POINT p3;
	POINT p4;
	double As1;
	double As2;
	double As3;
	double As4;
} SHELL4;


/*
typedef struct  {
	unsigned char func;
	union {
		SHELL3 feaSh3;
		SHELL4 feaSh4;
	} shell;
} shellDDOM;
*/
/*
typedef struct node {
	 unsigned char func ; // тип
	 int val;
	 struct node *next;
} int_list;
*/

// This class is exported from the ak_Robot_1.dll
//class AK_ROBOT_1_API Cak_Robot_1 {
//public:
	//Cak_Robot_1(void);
	// TODO: add your methods here.
//};

//extern AK_ROBOT_1_API int nak_Robot_1;

//AK_ROBOT_1_API int fnak_Robot_1(void);
extern    AK_ROBOT_1_API int fnak_ini_Robot();
extern  /*"C"*/ AK_ROBOT_1_API int fnak_unIni_Robot();

extern   AK_ROBOT_1_API void fnak_visible_Robot();
extern   AK_ROBOT_1_API void fnak_hide_Robot();



extern    AK_ROBOT_1_API int fnak_addNod_Robot(int nod ,double x,double y,double z);
extern AK_ROBOT_1_API int fnak_getNodCountRobot();
extern AK_ROBOT_1_API int fnak_getNod_Robot(int nodNumb ,double *x,double *y,double *z);

extern  AK_ROBOT_1_API int fnak_addKZ_Robot(wchar_t *kz ,int_list nodes);
extern   AK_ROBOT_1_API int fnak_freeNod_Robot();
