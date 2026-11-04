#include "my_functions.hpp"
#include <math.h>


void my_sobel (Mat im_in, Mat im_out)
{

 int rows = im_in.rows; // height
 int cols = im_in.cols; // width
 
 
    for (int i = 0; i < cols; i++)
 	for (int j = 0; j < rows; j++){
 		// --- GESTION DU BORD VERTICAL (Lignes) ---
		int r_m1, r_p1;
		
		if (j == 0) {
			r_m1 = 1; // Miroir haut
		} else {
			r_m1 = j - 1;
		}

		if (j == rows - 1) {
			r_p1 = rows - 2; // Miroir bas
		} else {
			r_p1 = j + 1;
		}

		// --- GESTION DU BORD HORIZONTAL (Colonnes) ---
		int c_m1, c_p1;

		if (i == 0) {
			c_m1 = 1; // Miroir gauche
		} else {
			c_m1 = i - 1;
		}

		if (i == cols - 1) {
			c_p1 = cols - 2; // Miroir droite
		} else {
			c_p1 = i + 1;
		}

		// --- LECTURE DES 9 PIXELS DE LA FENÊTRE ---
		int nw = im_in.at<uchar>(r_m1, c_m1);
		int n  = im_in.at<uchar>(r_m1, i);
		int ne = im_in.at<uchar>(r_m1, c_p1);
		int w  = im_in.at<uchar>(j, c_m1);
		int c  = im_in.at<uchar>(j, i);
		int e  = im_in.at<uchar>(j, c_p1);
		int sw = im_in.at<uchar>(r_p1, c_m1);
		int s  = im_in.at<uchar>(r_p1, i);
		int se = im_in.at<uchar>(r_p1, c_p1);
 	
 	 	int gx = 2*e + ne + se - 2*w - sw - nw + 0*n + 0*c + 0*s;
 	 	int gy = 2*n + ne + nw - 2*s - sw - se + 0*w + 0*c + 0*e;
 	 	
 	 	// Saturation individuelle à 255 (comme convertScaleAbs d'OpenCV)
		int abs_gx = abs(gx);
		if (abs_gx > 255) abs_gx = 255;

		int abs_gy = abs(gy);
		if (abs_gy > 255) abs_gy = 255;
		
		float g = 0.5f * abs_gx + 0.5f * abs_gy;

		if (g>255.0f)
			g=255.0f;
		
		im_out.at<uchar>(j,i) = (uchar)(g);
 	 	
 	 	}

};

void my_median (Mat im_in, Mat im_out, int n)
{

 int k = n*n;
 int rows = im_in.rows; // height
 int cols = im_in.cols; // width
 int r, c, rr, cc, p;
 vector<uchar> v (k);
 
    for (r = 0; r < rows; r++)
	{
      for (c = 0; c < cols; c++)
	  {
         p = 0;
         for (rr = (r-(n/2)); rr < (r-(n/2)+n); rr++)
		 {
            for (cc = (c-(n/2)); cc < (c-(n/2)+n); cc++)
			{
				// si le pixel courant de la fenêtre de taille n² est compris dans l'image, on prend la valeur du pixel aux coordonnées (cc, rr)
                if ((rr >= 0) && (rr < rows) && (cc >= 0) && (cc < cols))
			    {
                	v[p] = im_in.at<uchar>(rr,cc);
			   	}
				// sinon c'est que l'on se trouve en dehors de l'image : on applique la méthode du remplissage (padding) par miroir
				else if (rr < 0 && cc < 0)
				{
					v[p] = im_in.at<uchar>(-rr - 1, -cc - 1);
				}
				else if (rr < 0 && cc >= 0 && cc < cols)
				{
					v[p] = im_in.at<uchar>(-rr - 1, cc);
				}
				else if (rr < 0 && cc >= cols)
				{
					v[p] = im_in.at<uchar>(-rr - 1, cols - (cc - cols) - 1);
				}
				else if (rr >= 0 && rr < rows && cc < 0)
				{
					v[p] = im_in.at<uchar>(rr, -cc - 1);
				}
				else if (rr >= rows && cc < 0)
				{
					v[p] = im_in.at<uchar>(rows - (rr - rows) - 1, -cc - 1);
				}
				else if (rr >= rows && cc >= cols)
				{
					v[p] = im_in.at<uchar>(rows - (rr - rows) - 1, cols - (cc - cols) - 1);
				}
				else if (rr >= rows && cc < cols && cc >= 0)
				{
					v[p] = im_in.at<uchar>(rows - (rr - rows) - 1, cc);
				}
				else if (rr >= 0 && rr < rows && cc >= cols)
				{
					v[p] = im_in.at<uchar>(rr, cols - (cc - cols) - 1);
				}
				p++;
            }
         }
        
         sort (v.begin(), v.end());
         im_out.at<uchar>(r,c) = v[k/2];
      }

	}
};

