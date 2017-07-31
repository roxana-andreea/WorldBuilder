#include "Framework/DrawingWindow.h"
#include "Framework/Visual2D.h"
#include "Framework/Transform2D.h"
#include "Framework/Transform3D.h"
#include "Framework/Line2D.h"
#include "Framework/Rectangle2D.h"
#include "Framework/Circle2D.h"
#include "Framework/Polygon2D.h"
#include <iostream>
#include <windows.h>


#define PI 3.14159265358979323846
#define inf 1000000
using namespace std;

Visual2D *v2d1;
Object3D *cube11, *casa, *piata;
Object3D *mat[50][50]; //matricea in care retin grila

Color color_aux = Color(0.93, 0.9 ,0.66); //culoarea grilei

float n=1;

//Pozitia curenta pe care ma aflu

int pos_initX = 0;
int pos_initY = 0;

//Dimensiunile ferestrei cu care fac scroll-ul grilei

int x_min = -3; 
int x_max = 7;
int y_min = -1;
int y_max = 9;

vector <Point3D*> vertices;
vector <Face*> faces;

//Functia care permite adaugarea de obiecte

void DrawingWindow::init()
{
	
	v2d1 = new Visual2D(-3,-1,7,9,0,0,DrawingWindow::width,DrawingWindow::height); 
	v2d1->tipTran(true);
	addVisual2D(v2d1);
	
	//Desenare grila

	for(int i = 0; i <= 10; i++) 
	{
		for(int j = 0; j <= 10; j++) 
		{
			vertices.clear();
			//varfurile de jos
			vertices.push_back(new Point3D(0,0,0));
			vertices.push_back(new Point3D(n,0,0));
			vertices.push_back(new Point3D(n,0,n));
			vertices.push_back(new Point3D(0,0,n));
			//varfurile de sus
			vertices.push_back(new Point3D(0,n/10,0));
			vertices.push_back(new Point3D(n,n/10,0));
			vertices.push_back(new Point3D(n,n/10,n));
			vertices.push_back(new Point3D(0,n/10,n));
	
			//cele 6 fete
			vector <int> contour;
			//fata jos
			contour.clear();
			contour.push_back(0);
			contour.push_back(1);
			contour.push_back(2);
			contour.push_back(3);
			faces.push_back(new Face(contour));
			//fata sus
			contour.clear();
			contour.push_back(4);
			contour.push_back(5);
			contour.push_back(6);
			contour.push_back(7);
			faces.push_back(new Face(contour));
			//fata fata
			contour.clear();
			contour.push_back(0);
			contour.push_back(1);
			contour.push_back(5);
			contour.push_back(4);
			faces.push_back(new Face(contour));
			//fata dreapta
			contour.clear();
			contour.push_back(1);
			contour.push_back(2);
			contour.push_back(6);
			contour.push_back(5);
			faces.push_back(new Face(contour));
			//fata spate
			contour.clear();
			contour.push_back(2);
			contour.push_back(3);
			contour.push_back(7);
			contour.push_back(6);
			faces.push_back(new Face(contour));
			//fata stanga
			contour.clear();
			contour.push_back(3);
			contour.push_back(0);
			contour.push_back(4);
			contour.push_back(7);
			faces.push_back(new Face(contour));
	
			cube11 = new Object3D(vertices,faces,Color(0.93, 0.9 ,0.66),true);
			addObject3D_to_Visual2D(cube11,v2d1);

			Transform3D::loadIdentityModelMatrix();
			Transform3D::translateMatrix(i,0,j);
			Transform3D::applyTransform(cube11);
			mat[i][j] = cube11;	//retin intr-o matrice grila
			mat[pos_initX][pos_initY]->color=Color(0.4, 0.2, 0.4); //colorare pozitie curenta
		}
	}
}


//Functia care permite animatia

void DrawingWindow::onIdle()
{
	static float pas = 0;
	static float scale = 1;
	static int iter = 0;
	static float ty = 0;
	iter++;

	if (iter <= 100)
	{
		scale *= 1.01;
		ty += 0.01;
	}
	else
		if (iter <=200)
		{
			scale *= 1/1.01;
			ty-=0.01;
		}
		else
			iter = 0;
	
	pas+=0.01;
}

//Functia care se apeleaza la redimensionarea ferestrei

void DrawingWindow::onReshape(int width,int height)
{
		v2d1->poarta(0,0,width,height); 
}

//Functia care defineste ce se intampla cand se apasa pe tastatura

void DrawingWindow::onKey(unsigned char key)
{
	if(key == KEY_DOWN && pos_initX < 10)   // miscare pozitie curenta in jos
	{
		mat[pos_initX][pos_initY]->color=color_aux;
		color_aux = mat[pos_initX + 1][pos_initY]->color;
		mat[pos_initX + 1][pos_initY]->color=Color(0.4, 0.2, 0.4);
		pos_initX++;
	}
	if(key == KEY_UP && pos_initX > 0) // miscare pozitie curenta in sus
	{
		mat[pos_initX][pos_initY]->color=color_aux;
		color_aux = mat[pos_initX - 1][pos_initY]->color;
		mat[pos_initX - 1][pos_initY]->color=Color(0.4, 0.2, 0.4);
		pos_initX--;
	}
	if(key == KEY_LEFT && pos_initY < 10) // miscare pozitie curenta in stanga
	{
		mat[pos_initX][pos_initY]->color=color_aux;
		color_aux = mat[pos_initX ][pos_initY + 1]->color;
		mat[pos_initX ][pos_initY+ 1]->color=Color(0.4, 0.2, 0.4);
		pos_initY++;
	}
	if(key == KEY_RIGHT && pos_initY > 0) // miscare pozitie curenta in dreapta
	{
		mat[pos_initX][pos_initY]->color=color_aux;
		color_aux = mat[pos_initX ][pos_initY - 1]->color;
		mat[pos_initX ][pos_initY- 1]->color=Color(0.4, 0.2, 0.4);
		pos_initY--;
	}
	if(key == 't') //pune teren
	{
		mat[pos_initX][pos_initY]->color=Color(0.2, 0.4, 0);
		color_aux = mat[pos_initX][pos_initY]->color;
	}
	if(key == 'a') //pune apa
	{
		mat[pos_initX][pos_initY]->color=Color(0, 0.8 ,0.81);
		color_aux = mat[pos_initX][pos_initY]->color;
	}
	if(key == '1') //pune drum 
	{
		mat[pos_initX][pos_initY]->color=Color(0.5, 0.5 ,0.5);
		color_aux = mat[pos_initX][pos_initY]->color;
	}
	if(key == 'b') //reface pozitia curenta de culoare initiala
	{
		mat[pos_initX][pos_initY]->color=Color(0.93, 0.9 ,0.66);
		color_aux = mat[pos_initX][pos_initY]->color;
	}
	if(key == '8') //scroll sus
	{
		y_max += 2;
		y_min += 2 ;
		v2d1->fereastra(x_min,y_min,x_max,y_max);
	}
	if(key == '2') //scroll jos
	{
		y_max -= 2;
		y_min -= 2 ;
		v2d1->fereastra(x_min,y_min,x_max,y_max);
	}
	if(key == '6') //scroll dreapta
	{
		x_max += 2;
		x_min += 2 ;
		v2d1->fereastra(x_min,y_min,x_max,y_max);
	}
	if(key == '4') //scroll stanga
	{
		x_max -= 2;
		x_min -= 2 ;
		v2d1->fereastra(x_min,y_min,x_max,y_max);
	}
	if(key == 'p') //pune piata
	{
		//construire piata
		for (int i = pos_initX - 1; i <= pos_initX + 1; i++)
		{
			for(int j = pos_initY - 1; j <= pos_initY + 1; j++)
			{
				if(i >= 0 && i <=10 && j >= 0 && j <= 10)
				{
					mat[i][j]->color = Color(0.6, 0.2, 0.0);
				}

			}
		}
	
		mat[pos_initX][pos_initY]->color=Color(0.6, 0.2, 0.0);
		color_aux = mat[pos_initX][pos_initY]->color;		
	}
	if(key == 'c') //pune casa
	{
		//construire casa
		vertices.clear();
		//varfurile de jos
		vertices.push_back(new Point3D(0,0,0));//0
		vertices.push_back(new Point3D(n,0,0));//1
		vertices.push_back(new Point3D(n,0,n));//2
		vertices.push_back(new Point3D(0,0,n));//3

		vertices.push_back(new Point3D(n/2,0,0));//4
		vertices.push_back(new Point3D(n,0,n/2));//5
		vertices.push_back(new Point3D(n/2,0,n));//6
		vertices.push_back(new Point3D(0,0,n/2));//7
		vertices.push_back(new Point3D(n/2,0,n/2));//8
		//varfurile de sus
		vertices.push_back(new Point3D(0,n,0));//9
		vertices.push_back(new Point3D(n,n,0));//10
		vertices.push_back(new Point3D(n,n,n));//11
		vertices.push_back(new Point3D(0,n,n));//12

		vertices.push_back(new Point3D(n/2,n,0));//13
		vertices.push_back(new Point3D(n,n,n/2));//14
		vertices.push_back(new Point3D(n/2,n,n));//15
		vertices.push_back(new Point3D(0,n,n/2));//16
		vertices.push_back(new Point3D(n/2,n,n/2));//17
		//varfurile de mijloc
		vertices.push_back(new Point3D(0,n/2,0));//18
		vertices.push_back(new Point3D(n,n/2,0));//19
		vertices.push_back(new Point3D(n,n/2,n));//20
		vertices.push_back(new Point3D(0,n/2,n));//21

		vertices.push_back(new Point3D(n/2,n/2,0));//22
		vertices.push_back(new Point3D(n,n/2,n/2));//23
		vertices.push_back(new Point3D(n/2,n/2,n));//24
		vertices.push_back(new Point3D(0,n/2,n/2));//25
		vertices.push_back(new Point3D(n/2,n/2,n/2));//26
		
		//cele 6 fete
		vector <int> contour;
		//fata jos
		contour.clear();
		faces.clear();
		contour.push_back(0);
		contour.push_back(1);
		contour.push_back(2);
		contour.push_back(3);
		faces.push_back(new Face(contour));
		//fata sus
		contour.clear();
		contour.push_back(12);
		contour.push_back(16);
		contour.push_back(17);
		contour.push_back(15);
		faces.push_back(new Face(contour));

		contour.clear();
		contour.push_back(16);
		contour.push_back(9);
		contour.push_back(13);
		contour.push_back(17);
		faces.push_back(new Face(contour));

		contour.clear();
		contour.push_back(17);
		contour.push_back(13);
		contour.push_back(10);
		contour.push_back(14);
		faces.push_back(new Face(contour));
		//fata mijloc
		contour.clear();
		contour.push_back(18);
		contour.push_back(19);
		contour.push_back(20);
		contour.push_back(21);
		faces.push_back(new Face(contour));
		//fata spate
		contour.clear();
		contour.push_back(9);
		contour.push_back(10);
		contour.push_back(1);
		contour.push_back(0);
		faces.push_back(new Face(contour));
		//fata stanga
		contour.clear();
		contour.push_back(9);
		contour.push_back(12);
		contour.push_back(3);
		contour.push_back(0);
		faces.push_back(new Face(contour));
		//fata dreapta
		contour.clear();
		contour.push_back(20);
		contour.push_back(19);
		contour.push_back(1);
		contour.push_back(2);
		faces.push_back(new Face(contour));

		contour.clear();
		contour.push_back(14);
		contour.push_back(10);
		contour.push_back(19);
		contour.push_back(23);
		faces.push_back(new Face(contour));
		//fata fata

		contour.clear();
		contour.push_back(21);
		contour.push_back(20);
		contour.push_back(2);
		contour.push_back(3);
		faces.push_back(new Face(contour));

		contour.clear();
		contour.push_back(21);
		contour.push_back(24);
		contour.push_back(15);
		contour.push_back(12);
		faces.push_back(new Face(contour));
		//fata stanga mijloc
		contour.clear();
		contour.push_back(24);
		contour.push_back(26);
		contour.push_back(17);
		contour.push_back(15);
		faces.push_back(new Face(contour));
		//fata spate mijloc
		contour.clear();
		contour.push_back(17);
		contour.push_back(14);
		contour.push_back(23);
		contour.push_back(26);
		faces.push_back(new Face(contour));
			
		casa = new Object3D(vertices,faces,Color(0.9, 0.4, 0.31),true);
		
		Transform3D::loadIdentityModelMatrix();
		Transform3D::loadIdentityProjectionMatrix();
		Transform3D::translateMatrix(pos_initX,0,pos_initY);
		Transform3D::applyTransform(casa);
	
		mat[pos_initX][pos_initY] = casa;
		addObject3D_to_Visual2D(mat[pos_initX][pos_initY],v2d1);
		color_aux = mat[pos_initX][pos_initY]->color;
		
	}		
}
			
//Functia care defineste ce se intampla cand se da click pe mouse

void DrawingWindow::onMouse(int button,int state,int x, int y)
{
	
}


int main(int argc, char** argv)
{
	//creare fereastra
	DrawingWindow dw(argc, argv, 600, 600, 200, 50, "World Building");
	//se apeleaza functia init() - in care s-au adaugat obiecte
	dw.init();
	//se intra in bucla principala de desenare - care face posibila desenarea, animatia si procesarea evenimentelor
	dw.run();
	return 0;

}