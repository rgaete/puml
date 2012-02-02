#include <iostream>
#include "math.h"
#define PI 3.14159
using namespace std;

class Camera
{
private:
    double cameraT[4][4];
public:
    Camera();
    void ApplyTransform(double x, double y, double z, bool TFtype, double x1, double y1, double z1);
    void MultiplyTransform(double tfM[4][4], double M1[4][4],double M2[4][4]);
    double **DefineElementaryTransform(double M[4][4], int tfCode, double tfVal);
    void BuildElementaryTransform(double tfM[4][4], int tfCode, double tfVal);
    double DefineCameraTransform(double Fx, double Fy, double Fz, double theta, double phi, double alpha, double r);
   void setCam(double M[4][4], double M1[4][4]);  
 void printM();
};

Camera::Camera()
{
}
void Camera::ApplyTransform(double x, double y, double z, bool TFtype, double x1, double y1, double z1)
{
    double vect[4]={x,y,z,1};
    double result[4]={0,0,0,0};
    double sum=0;
    for(int r=0;r<=3;r++)
    {
      for(int c=0;c<=3;c++)
      {
          sum=sum+vect[c]*cameraT[r][c];
      }
      result[r]=sum;
      sum=0;
    }
}

void Camera::MultiplyTransform(double tfM[4][4], double M1[4][4],double M2[4][4])
{
    double TempV=0;
    for(int ROW2=0;ROW2<=3;ROW2++)
    {
        for(int ROW1=0;ROW1<=3;ROW1++)
        {
            for(int COL1=0;COL1<=3;COL1++)
            {
                TempV=TempV+M1[COL1][ROW2]*M2[ROW1][COL1];
    	    }
            tfM[ROW1][ROW2]=TempV;
            TempV=0;
        }
    }
    /*for(int x=0;x<=3;x++)
        {
                 for(int y=0;y<=3;y++)
                {
                        cout<<tfM[y][x]<<"   ";
                }
	cout<<endl;
        }*/
cout<<endl<<endl;
}
void Camera::setCam(double M[4][4], double M1[4][4])
{
	for(int y=0;y<=3;y++)
	{
		 for(int x=0;x<=3;x++)
                {
                        M[x][y]=M1[x][y];
                }
	}
}
void Camera::BuildElementaryTransform(double tfM[4][4],int tfCode, double tfVal)
{
    double tempM[4][4], resultM[4][4];
    DefineElementaryTransform(tempM, tfCode, tfVal);
    MultiplyTransform(resultM,tfM,tempM);
    setCam(tfM, resultM);
}
double Camera::DefineCameraTransform(double Fx, double Fy, double Fz, double theta, double phi, double alpha, double r)
{
   enum Trans {xTrans=1, yTrans=2, zTrans=3, xRot=4, yRot=5, zRot=6, perspective=7};
  double tfM[4][4];
   DefineElementaryTransform(tfM, xTrans,Fx);
   BuildElementaryTransform(tfM, yTrans, -Fy);
  BuildElementaryTransform(tfM, zTrans, Fz);
   BuildElementaryTransform(tfM, xRot, -theta); 
  BuildElementaryTransform(tfM, yRot, phi);
   BuildElementaryTransform(tfM, zRot, -alpha);
   BuildElementaryTransform(tfM, perspective, r);
  setCam(cameraT, tfM);  
}

double **Camera::DefineElementaryTransform(double M[4][4], int tfCode, double Mval)
{
    for(int y=0;y<=3;y++)    //Build Identity Matrix
    {
        for(int x=0;x<=3;x++)
        {
            if(y==x)
            {
               M[x][y]=1;
            }
            else
            {
              M[x][y]=0;
            }
         }
    }
    if(tfCode==1)    //if XTrans matrix
    {
        M[0][3]=Mval;
    }
    else if(tfCode==2)   //if YTrans matrix
    {
        M[1][3]=Mval;
    }
    else if(tfCode==3)   //if ZTrans matrix
    {
        M[2][3]=Mval;
    }
    else if(tfCode==4)   //if XRot matrix
    {
        Mval=Mval*PI/180;
        M[0][0]=cos(Mval);
        M[2][0]=sin(Mval);
        M[0][2]=-sin(Mval);
        M[2][2]=cos(Mval);
    }
    else if(tfCode==5)   //if YRot matrix
    {
        Mval=Mval*PI/180;
        M[1][1]=cos(Mval);
        M[2][1]=-sin(Mval);
        M[1][2]=sin(Mval);
        M[2][2]=cos(Mval);
    }
    else if(tfCode==6)   //if ZRot matrix
    {
        Mval=Mval*PI/180;
        M[0][0]=cos(Mval);
        M[1][0]=-sin(Mval);
        M[0][1]=sin(Mval);
        M[1][1]=cos(Mval);
    }
    else if(tfCode==7)   //if Perspectivwe matrix
    {
        M[3][2]=-1/Mval;
    }
      for(int y=0;y<=3;y++)
        {
                 for(int x=0;x<=3;x++)
                {
                        cout<<M[x][y]<<"   ";
                }
        cout<<endl;
        }

}

void Camera::printM()
{
	for(int y=0;y<=3;y++)
	{
		for(int x=0;x<=3;x++)
		{
			cout<<cameraT[x][y]<<"  ";
		}
		cout<<endl;
	}
}
int main()
{
	Camera cam;
	cam.DefineCameraTransform(0.0,1.0,0.0,30,45,0.0,20.0);
	cam.printM();
}

