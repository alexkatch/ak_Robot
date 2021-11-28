// ak_Robot_1.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "ak_Robot_1.h"
#include <iostream>

// #import "D:\\Program Files\\Autodesk\\Autodesk Robot Structural Analysis Professional 2017\\System\\Exe\\robotom.tlb" no_namespace
#import "c:\\Program Files\\Autodesk\\Autodesk Robot Structural Analysis Professional 2019\\System\\Exe\\robotom.tlb" no_namespace



using namespace std;




// global Var
IRobotApplicationPtr pRobot(__uuidof(RobotApplication));
//pRobot->GetProject()->New(I_PT_SHELL);
 IRobotProjectPreferencesPtr pProjectPrefs;// = pRobot->GetProject()->GetPreferences();
IRobotMeshParamsPtr pMeshParams;

IRobotStructurePtr pStr ;
IRobotNodeServerPtr pNodes;
IRobotLabelServerPtr pLabels;// = pStr->GetLabels();
bool needSave=false;

// This is an example of an exported variable
//AK_ROBOT_1_API int nak_Robot_1=0;
// This is an example of an exported function.
//AK_ROBOT_1_API int fnak_Robot_1(void){return 42;}
// This is the constructor of a class that has been exported.
// see ak_Robot_1.h for the class definition
//Cak_Robot_1::Cak_Robot_1(){return;}

//////////////////////////
// TODO: Вставьте сюда код для приложения.


AK_ROBOT_1_API void fnak_hide_Robot(void)
{
	pRobot->put_Visible(VARIANT_FALSE);
}

AK_ROBOT_1_API void fnak_visible_Robot(void)
{
	pRobot->put_Visible(VARIANT_TRUE);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////
AK_ROBOT_1_API int fnak_ini_Robot(void)
{
::CoInitialize(NULL);
//cout << " Launching Robot ..." << endl;
IRobotApplicationPtr pRobot(__uuidof(RobotApplication));
//pRobot->GetProject()->
if(pRobot->Visible==VARIANT_FALSE)
                           { MessageBox(NULL,_T("Robot.Application  start  NEW!"),_T("__") ,MB_OK); 
                                pRobot->GetProject()->New(I_PT_SHELL); 
								needSave=true;
                            }

pRobot->put_Visible(VARIANT_TRUE);
pProjectPrefs = pRobot->GetProject()->GetPreferences();
//pProjectPrefs->SetActiveCode(I_CT_RC_THEORETICAL_REINF,"EN 1992-1-1:2004 AC:2008"); // "BAEL 91");
pMeshParams = pProjectPrefs->GetMeshParams();
pMeshParams->GetSurfaceParams()->GetMethod()->PutMethod(I_MMT_DELAUNAY);
pMeshParams->GetSurfaceParams()->GetGeneration()->PutType(I_MGT_ELEMENT_SIZE);
pMeshParams->GetSurfaceParams()->GetGeneration()->PutElementSize(0.5);
pMeshParams->GetSurfaceParams()->GetDelaunay()->PutType(I_MDT_DELAUNAY);
//cout << "Structure Generation..." << endl;
 pStr = pRobot->GetProject()->GetStructure();
 pNodes = pStr->GetNodes();
 pLabels = pStr->GetLabels();
return 1;
}

AK_ROBOT_1_API int fnak_unIni_Robot(){
	if (needSave==true)
		pRobot->GetProject()->Save();// ->SaveAs(_T("Test1"));

::CoUninitialize();
return 1;
}




AK_ROBOT_1_API int fnak_addNod_Robot(int nod ,double x,double y,double z)
{
long n=pNodes->FreeNumber;
pNodes->Create(n, x, y, z);
return n;
}
/// Return number nod in contur
AK_ROBOT_1_API int fnak_getNodCountRobot(){
	 long nmax=pNodes->GetAll()->Count;
	 return nmax;
}


AK_ROBOT_1_API int fnak_getNod_Robot(int nodNumb ,double *x,double *y,double *z)
{
int n=0;

long nmax=pNodes ->GetAll()->Count;
 IRobotCollectionPtr  ssN= pNodes ->GetAll();
IRobotNodePtr nod;

if (nodNumb >0 && nodNumb <= nmax) {
//IRobotDataObjectPtr pt= pNodes->Get(nodNumb);
nod=   ssN->Get(nodNumb); //pNodes->GetAll()->Get(nodNumb);
*x=nod->GetX();
*y=nod->GetY();
*z=nod->GetZ();
n=nod->GetNumber();
}

return n;
}



/*
(defun getNodes ( rbNodes / l coll i c)
  (setq coll (vlax-invoke-method rbNodes 'GetAll))
  (setq c (vlax-get-property coll 'Count))
  (setq i 1)
  (repeat c
    (setq nod (vlax-invoke-method coll  'Get i))
  (setq l (cons (list (vlax-get-property nod 'Number) (vlax-get-property nod 'X)
                                                      (vlax-get-property nod 'Y)
                                                      (vlax-get-property nod 'Z)) l)
    )
    (setq i (1+ i))
    )
;  (reverse l)
l
  )

*/





/*
          
       				(setq pLabel (vlax-invoke-method Labels 'Create rc-I_LT_SUPPORT NameSpring))
                                (setq pSpringDataPtr (vlax-get-property  pLabel 'Data))
                                ;(vlax-put-property pSpringDataPtr 'UX 1.0); -1 (vlax-make-variant -1 vlax-vbBoolean) 
                                ;(vlax-put-property pSpringDataPtr 'UY 1.0)
                                ;(vlax-put-property pSpringDataPtr 'UZ 1.0)
                                ;(vlax-put-property pSpringDataPtr 'KZ (atof KZ))
                                ;(vlax-put-property pSpringDataPtr 'RX 1.0)
                                ;(vlax-put-property pSpringDataPtr 'RY 1.0)
                                ;(vlax-put-property pSpringDataPtr 'RZ 1.0)
                               (if (and (listp KZ) (= (length KZ) 6))
                                (putDataSupList pSpringDataPtr KZ)
                                ;(vlax-put-property pSpringDataPtr 'KZ (* 10000.0 KZ)) ;òîííû â êí
                                 )                                
                                (vlax-invoke-method Labels 'Store pLabel)
                      
*/
AK_ROBOT_1_API int fnak_addKZ_Robot(wchar_t *kz , int_list nodes)
{
//pLabel = pLabels->Create(I_LT_SUPPORT, FootName.c_str());
//IRobotNodeSupportDataPtr pFootData = pLabel->GetData();
double kzr=_wtof(kz);

IRobotLabelPtr pLabel= pLabels->Create(I_LT_SUPPORT,kz);
IRobotNodeSupportDataPtr 	pFootData=pLabel->GetData(); //Data();
pFootData->PutUX(1.);
pFootData->PutUY(1.);

pFootData->PutUZ(0.);
pFootData->PutKZ(kzr*10000.0); // т->н

//pFootData->PutRX(1.);
pFootData->PutRX(0.);
pFootData->PutHX(0.);

//pFootData->PutRY(1.);
pFootData->PutRY(0.);
pFootData->PutHY(0.);

//pFootData->PutRZ(1.);
pFootData->PutRZ(0.);
pFootData->PutHZ(0.);

pLabels->Store(pLabel);

IRobotSelectionPtr pSelectionNodes = pStr->GetSelections()->Get(I_OT_NODE);
pSelectionNodes->Clear();

int_list p=nodes;

/*
 if (empty == nodes) {
            ...
        } else {
            ...
        }
    }

	*/

while (p != empty)
{
	pSelectionNodes->AddOne(p->head);	
	p=p->tail;
	
}
pStr->GetNodes()->SetLabel(pSelectionNodes, I_LT_SUPPORT,kz);
	return 1;
}



AK_ROBOT_1_API int fnak_freeNod_Robot()
{
long n=pNodes->FreeNumber;
return n;
}

/*
Make info FEA  1 shell elemet for write im file EDF
******
(repeat n
    (setq ob (vlax-invoke-method pObjFes 'Get i))
    (setq Fetype (vlax-get-property ob 'FeType))
    
    (setq Nodes (vlax-get-property ob 'Nodes))
     (setq NumberFe (vlax-get-property ob 'Number))
     (setq j 1)
     (setq lnod nil)    
    (repeat (vlax-get-property Nodes 'Count)
      (setq lnod (cons (vlax-invoke-method Nodes 'Get j) lnod))
      (setq j (1+ j))
    );repeat
    
    (setq lnod (reverse lnod))
    (setq pts (selectPt lnod lstPt))
    (setq obj (drawShell pts)) ;
     (setq rr (vlax-invoke-method feRes 'Reinforcement NumberFe 0))
      (setq arm (list (* 10000 (vlax-get-property rr 'AX_BOTTOM)); As1
                      (* 10000 (vlax-get-property rr 'AX_TOP)) ; As2
                      (* 10000 (vlax-get-property rr 'AY_BOTTOM)) ; As3
                      (* 10000 (vlax-get-property rr 'AY_TOP)) ;  As4
                      ))
     (addArmShell  obj NumberFe arm '(0.0 0.0));armAsw)
    (vlax-release-object obj)
    (vlax-release-object rr)
    ;(print  Fetype)
    ;(print pts)
    ;(terpri)
    (setq i (1+ i))
    );repeat

*/

AK_ROBOT_1_API int fnak_getArmShellsToFileEDF_Robot(int element,wchar_t *fileNameEdf)
{
FILE*  file ;
file = _wfopen(fileNameEdf,_T("a")); //_T("w")) ;



	 fclose(file) ;
	return 1;
}