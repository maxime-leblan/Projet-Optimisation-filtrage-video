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

void sobel_pixel_border_v1_stg0(Mat im_in, Mat im_out, int i, int j, int rows, int cols)
{
	// --- GESTION DU BORD VERTICAL (Lignes) ---
	int r_m1, r_p1;
	
	if (i == 0) {
		r_m1 = 1; // Miroir haut
	} else {
		r_m1 = i - 1;
	}

	if (i == rows - 1) {
		r_p1 = rows - 2; // Miroir bas
	} else {
		r_p1 = i + 1;
	}

	// --- GESTION DU BORD HORIZONTAL (Colonnes) ---
	int c_m1, c_p1;

	if (j == 0) {
		c_m1 = 1; // Miroir gauche
	} else {
		c_m1 = j - 1;
	}

	if (j == cols - 1) {
		c_p1 = cols - 2; // Miroir droite
	} else {
		c_p1 = j + 1;
	}

	// --- LECTURE DES 9 PIXELS DE LA FENÊTRE ---
	int nw = im_in.at<uchar>(r_m1, c_m1);
	int n  = im_in.at<uchar>(r_m1, j);
	int ne = im_in.at<uchar>(r_m1, c_p1);
	int w  = im_in.at<uchar>(i, c_m1);
	int e  = im_in.at<uchar>(i, c_p1);
	int sw = im_in.at<uchar>(r_p1, c_m1);
	int s  = im_in.at<uchar>(r_p1, j);
	int se = im_in.at<uchar>(r_p1, c_p1);

	int gx = (e << 1) + ne + se - (w << 1) - sw - nw;
	int gy = (n << 1) + ne + nw - (s << 1) - sw - se;

	int abs_gx = abs(gx);
	if (abs_gx > 255) abs_gx = 255;

	int abs_gy = abs(gy);
	if (abs_gy > 255) abs_gy = 255;

	int g = (abs_gx + abs_gy) >> 1;
	if (g > 255) g = 255;
	
	im_out.at<uchar>(i,j) = (uchar)(g);
}

void sobel_pixel_border_v3_stg0(Mat im_in, Mat im_out, int i, int j, int rows, int cols)
{
	// --- GESTION DU BORD VERTICAL (Lignes) ---
	int r_m1, r_p1;
	
	if (i == 0) {
		r_m1 = 1; // Miroir haut
	} else {
		r_m1 = i - 1;
	}

	if (i == rows - 1) {
		r_p1 = rows - 2; // Miroir bas
	} else {
		r_p1 = i + 1;
	}

	// --- GESTION DU BORD HORIZONTAL (Colonnes) ---
	int c_m1, c_p1;

	if (j == 0) {
		c_m1 = 1; // Miroir gauche
	} else {
		c_m1 = j - 1;
	}

	if (j == cols - 1) {
		c_p1 = cols - 2; // Miroir droite
	} else {
		c_p1 = j + 1;
	}

	// --- LECTURE DES 9 PIXELS DE LA FENÊTRE ---
	int nw = im_in.at<uchar>(r_m1, c_m1);
	int n  = im_in.at<uchar>(r_m1, j);
	int ne = im_in.at<uchar>(r_m1, c_p1);
	int w  = im_in.at<uchar>(i, c_m1);
	int e  = im_in.at<uchar>(i, c_p1);
	int sw = im_in.at<uchar>(r_p1, c_m1);
	int s  = im_in.at<uchar>(r_p1, j);
	int se = im_in.at<uchar>(r_p1, c_p1);

	int A = se - nw;
	int B = ne - sw;
	int C = e - w;
	int D = s - n;

	int gx = A + B + (C << 1);
	int gy = A - B + (D << 1);

	int abs_gx = abs(gx);
	if (abs_gx > 255) abs_gx = 255;

	int abs_gy = abs(gy);
	if (abs_gy > 255) abs_gy = 255;

	int g = (abs_gx + abs_gy) >> 1;
	if (g > 255) g = 255;
	
	im_out.at<uchar>(i,j) = (uchar)(g);
}

void my_sobel_opti_v1_stg0(Mat im_in, Mat im_out)
{
	int rows = im_in.rows; // height
 	int cols = im_in.cols; // width
 
    // 1. CŒUR DE L'IMAGE (99% des pixels) - AUCUN TEST 'IF'
    for (int i = 1; i < cols - 1; i++)
    {
        for (int j = 1; j < rows - 1; j++)
        {
            // Directement j-1, j, j+1 et i-1, i, i+1 sans variables intermédiaires
            int nw = im_in.at<uchar>(j - 1, i - 1);
            int n  = im_in.at<uchar>(j - 1, i);
            int ne = im_in.at<uchar>(j - 1, i + 1);
            int w  = im_in.at<uchar>(j, i - 1);
            int e  = im_in.at<uchar>(j, i + 1);
            int sw = im_in.at<uchar>(j + 1, i - 1);
            int s  = im_in.at<uchar>(j + 1, i);
            int se = im_in.at<uchar>(j + 1, i + 1);

            int gx = (e << 1) + ne + se - (w << 1) - sw - nw;
            int gy = (n << 1) + ne + nw - (s << 1) - sw - se;

            int abs_gx = abs(gx);
            if (abs_gx > 255) abs_gx = 255;

            int abs_gy = abs(gy);
            if (abs_gy > 255) abs_gy = 255;

            int g = (abs_gx + abs_gy) >> 1;
            if (g > 255) g = 255;

            im_out.at<uchar>(j, i) = (uchar)g;
        }
    }

	// GESTION SEPARÉE DES BORDS (Seulement si nécessaire)
    // Bords Haut & Bas
    for (int i = 0; i < cols; i++) {
        sobel_pixel_border_v1_stg0(im_in, im_out, 0, i, rows, cols);        // Ligne haut
        sobel_pixel_border_v1_stg0(im_in, im_out, rows - 1, i, rows, cols); // Ligne bas
    }
    // Bords Gauche & Droite
    for (int j = 1; j < rows - 1; j++) {
        sobel_pixel_border_v1_stg0(im_in, im_out, j, 0, rows, cols);        // Colonne gauche
        sobel_pixel_border_v1_stg0(im_in, im_out, j, cols - 1, rows, cols); // Colonne droite
    }
}

void my_sobel_opti_v3_stg0(Mat im_in, Mat im_out)
{
	int rows = im_in.rows; // height
 	int cols = im_in.cols; // width
 
    // 1. CŒUR DE L'IMAGE (99% des pixels) - AUCUN TEST 'IF'
    for (int i = 1; i < cols - 1; i++)
    {
        for (int j = 1; j < rows - 1; j++)
        {
            // Directement j-1, j, j+1 et i-1, i, i+1 sans variables intermédiaires
            int nw = im_in.at<uchar>(j - 1, i - 1);
            int n  = im_in.at<uchar>(j - 1, i);
            int ne = im_in.at<uchar>(j - 1, i + 1);
            int w  = im_in.at<uchar>(j, i - 1);
            int e  = im_in.at<uchar>(j, i + 1);
            int sw = im_in.at<uchar>(j + 1, i - 1);
            int s  = im_in.at<uchar>(j + 1, i);
            int se = im_in.at<uchar>(j + 1, i + 1);

			int A = se - nw;
			int B = ne - sw;
			int C = e - w;
			int D = s - n;

            int gx = A + B + (C << 1);
            int gy = A - B + (D << 1);

            int abs_gx = abs(gx);
            if (abs_gx > 255) abs_gx = 255;

            int abs_gy = abs(gy);
            if (abs_gy > 255) abs_gy = 255;

            int g = (abs_gx + abs_gy) >> 1;
            if (g > 255) g = 255;

            im_out.at<uchar>(j, i) = (uchar)g;
        }
    }

	// GESTION SEPARÉE DES BORDS (Seulement si nécessaire)
    // Bords Haut & Bas
    for (int i = 0; i < cols; i++) {
        sobel_pixel_border_v3_stg0(im_in, im_out, 0, i, rows, cols);        // Ligne haut
        sobel_pixel_border_v3_stg0(im_in, im_out, rows - 1, i, rows, cols); // Ligne bas
    }
    // Bords Gauche & Droite
    for (int j = 1; j < rows - 1; j++) {
        sobel_pixel_border_v3_stg0(im_in, im_out, j, 0, rows, cols);        // Colonne gauche
        sobel_pixel_border_v3_stg0(im_in, im_out, j, cols - 1, rows, cols); // Colonne droite
    }
}

void my_sobel_opti_v4_stg0(Mat im_in, Mat im_out)
{
    int rows = im_in.rows;
    int cols = im_in.cols;

    // Allocation des deux tampons temporaires 16 bits (short signés)
    Mat S(rows, cols, CV_16S);
    Mat T(rows, cols, CV_16S);

    // Calcul des tampons de lissage S (vertical) et T (horizontal)
    for (int i = 1; i < cols - 1; i++)
    {
        for (int j = 1; j < rows - 1; j++)
        {
            // S[j][i] = Lissage vertical de la colonne i
            int val_S = im_in.at<uchar>(j - 1, i) + (im_in.at<uchar>(j, i) << 1) + im_in.at<uchar>(j + 1, i);
            S.at<short>(j, i) = (short)val_S;

            // T[j][i] = Lissage horizontal de la ligne j
            int val_T = im_in.at<uchar>(j, i - 1) + (im_in.at<uchar>(j, i) << 1) + im_in.at<uchar>(j, i + 1);
            T.at<short>(j, i) = (short)val_T;
        }
    }

    // Calcul des dérivées (gx, gy) et de la norme sur im_out
    for (int i = 1; i < cols - 1; i++)
    {
        for (int j = 1; j < rows - 1; j++)
        {
            // Gx = différence horizontale sur le tampon S
            int gx = S.at<short>(j, i + 1) - S.at<short>(j, i - 1);

            // Gy = différence verticale sur le tampon T
            int gy = T.at<short>(j + 1, i) - T.at<short>(j - 1, i);

            // Saturation individuelle et calcul de la norme entière
            int abs_gx = abs(gx);
            if (abs_gx > 255) abs_gx = 255;

            int abs_gy = abs(gy);
            if (abs_gy > 255) abs_gy = 255;

            int g = (abs_gx + abs_gy) >> 1;
            if (g > 255) g = 255;

            im_out.at<uchar>(j, i) = (uchar)g;
        }
    }

    // Gestion des bords de l'image
    for (int i = 0; i < cols; i++) {
        sobel_pixel_border_v1_stg0(im_in, im_out, 0, i, rows, cols);
        sobel_pixel_border_v1_stg0(im_in, im_out, rows - 1, i, rows, cols);
    }
    for (int j = 1; j < rows - 1; j++) {
        sobel_pixel_border_v1_stg0(im_in, im_out, j, 0, rows, cols);
        sobel_pixel_border_v1_stg0(im_in, im_out, j, cols - 1, rows, cols);
    }
}

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

void CE(uchar &a, uchar &b) {
    if (a > b) {
        uchar tmp = a;
        a = b;
        b = tmp;
    }
}

void sort3(uchar &a, uchar &b, uchar &c) {
    CE(a, b);
    CE(b, c);
    CE(a, b);
}

void median_pixel_border_m2_3t3_stg0(Mat im_in, Mat im_out, int row, int col, int rows, int cols)
{
    // --- GESTION DU BORD VERTICAL (Conforme à OpenCV BORDER_REPLICATE) ---
    int r_m1, r_p1;

    if (row == 0) {
        r_m1 = 0; // Ligne haut dupliquée (0 au lieu de 1)
    } else {
        r_m1 = row - 1;
    }

    if (row == rows - 1) {
        r_p1 = rows - 1; // Ligne bas dupliquée
    } else {
        r_p1 = row + 1;
    }

    // --- GESTION DU BORD HORIZONTAL (Conforme à OpenCV BORDER_REPLICATE) ---
    int c_m1, c_p1;

    if (col == 0) {
        c_m1 = 0; // Colonne gauche dupliquée (0 au lieu de 1)
    } else {
        c_m1 = col - 1;
    }

    if (col == cols - 1) {
        c_p1 = cols - 1; // Colonne droite dupliquée
    } else {
        c_p1 = col + 1;
    }

    // --- LECTURE DES 9 PIXELS DE LA FENÊTRE ---
    uchar w1 = im_in.at<uchar>(r_m1, c_m1);
    uchar w2 = im_in.at<uchar>(r_m1, col);
    uchar w3 = im_in.at<uchar>(r_m1, c_p1);
    uchar w4 = im_in.at<uchar>(row,  c_m1);
    uchar w5 = im_in.at<uchar>(row,  col);
    uchar w6 = im_in.at<uchar>(row,  c_p1);
    uchar w7 = im_in.at<uchar>(r_p1, c_m1);
    uchar w8 = im_in.at<uchar>(r_p1, col);
    uchar w9 = im_in.at<uchar>(r_p1, c_p1);

    // Étape 1 : Tri des 3 lignes (9 CE)
    sort3(w1, w2, w3);
    sort3(w4, w5, w6);
    sort3(w7, w8, w9);

    // Étape 2 : Tri des 3 colonnes (9 CE)
    sort3(w1, w4, w7);
    sort3(w2, w5, w8);
    sort3(w3, w6, w9);

    // Étape 3 : Tri de l'anti-diagonale (3 CE)
    sort3(w3, w5, w7);

    // Écriture de la médiane au centre (w5)
    im_out.at<uchar>(row, col) = w5;
}

void my_median_opti_m2_3t3_stg0(Mat im_in, Mat im_out)
{
    int rows = im_in.rows;
    int cols = im_in.cols;

    // 1. CŒUR DE L'IMAGE (99% des pixels) - AUCUN TEST 'IF'
    for (int i = 1; i < cols - 1; i++)
    {
        for (int j = 1; j < rows - 1; j++)
        {
            // Lecture des 9 pixels de la fenêtre 3x3
            uchar w1 = im_in.at<uchar>(j - 1, i - 1);
            uchar w2 = im_in.at<uchar>(j - 1, i);
            uchar w3 = im_in.at<uchar>(j - 1, i + 1);
            uchar w4 = im_in.at<uchar>(j,     i - 1);
            uchar w5 = im_in.at<uchar>(j,     i);
            uchar w6 = im_in.at<uchar>(j,     i + 1);
            uchar w7 = im_in.at<uchar>(j + 1, i - 1);
            uchar w8 = im_in.at<uchar>(j + 1, i);
            uchar w9 = im_in.at<uchar>(j + 1, i + 1);

            // Étape 1 : Tri des 3 lignes (9 CE)
            sort3(w1, w2, w3);
            sort3(w4, w5, w6);
            sort3(w7, w8, w9);

            // Étape 2 : Tri des 3 colonnes (9 CE)
            sort3(w1, w4, w7);
            sort3(w2, w5, w8);
            sort3(w3, w6, w9);

            // Étape 3 : Tri de l'anti-diagonale (3 CE)
            sort3(w3, w5, w7);

            // La valeur médiane se trouve au centre w5
            im_out.at<uchar>(j, i) = w5;
        }
    }

    // 2. GESTION SEPARÉE DES BORDS DE L'IMAGE
    // Bords Haut & Bas (ligne 0 et rows-1)
    for (int i = 0; i < cols; i++) {
        median_pixel_border_m2_3t3_stg0(im_in, im_out, 0, i, rows, cols);
        median_pixel_border_m2_3t3_stg0(im_in, im_out, rows - 1, i, rows, cols);
    }
    // Bords Gauche & Droite (colonne 0 et cols-1)
    for (int j = 1; j < rows - 1; j++) {
        median_pixel_border_m2_3t3_stg0(im_in, im_out, j, 0, rows, cols);
        median_pixel_border_m2_3t3_stg0(im_in, im_out, j, cols - 1, rows, cols);
    }
}