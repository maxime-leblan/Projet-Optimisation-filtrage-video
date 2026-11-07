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

void my_sobel_opti_v3_stg1(Mat im_in, Mat im_out)
{
	int rows = im_in.rows;
    int cols = im_in.cols;

    // 1. BOUCLE EXTERNE SOUR LES LIGNES y (j)
    for (int j = 1; j < rows - 1; j++)
    {
        // ROW POINTERS : Extraction des pointeurs directs sur les 3 lignes (supprime 100% des calls at<uchar>)
        const uchar* r_top = im_in.ptr<uchar>(j - 1);
        const uchar* r_mid = im_in.ptr<uchar>(j);
        const uchar* r_bot = im_in.ptr<uchar>(j + 1);
        uchar*       r_out = im_out.ptr<uchar>(j);

        int i = 1;

        // 2. BOUCLE INTERNE DÉROULÉE SUR LE PARCOURS HORIZONTAL x (i) PAR d = 4
        for (; i <= cols - 5; i += 4)
        {
            // --- PHASE 1 : LOADS FIRST ---
            // Chargement unique des 6 colonnes (i-1 à i+4) couvrant les 4 pixels contigus le long de x
            int t_m1 = r_top[i - 1], t_0 = r_top[i], t_1 = r_top[i + 1], t_2 = r_top[i + 2], t_3 = r_top[i + 3], t_4 = r_top[i + 4];
            int m_m1 = r_mid[i - 1], m_0 = r_mid[i], m_1 = r_mid[i + 1], m_2 = r_mid[i + 2], m_3 = r_mid[i + 3], m_4 = r_mid[i + 4];
            int b_m1 = r_bot[i - 1], b_0 = r_bot[i], b_1 = r_bot[i + 1], b_2 = r_bot[i + 2], b_3 = r_bot[i + 3], b_4 = r_bot[i + 4];

            // --- PHASE 2 : INDEPENDENT OPERATIONS (A, B, C, D) WITH RENAMING ---
            // Aucune valeur n'est utilisée immédiatement après son chargement (évite les load-use stalls)
            int A0 = b_1 - t_m1, B0 = t_1 - b_m1, C0 = m_1 - m_m1, D0 = b_0 - t_0;
            int A1 = b_2 - t_0,  B1 = t_2 - b_0,  C1 = m_2 - m_0,  D1 = b_1 - t_1;
            int A2 = b_3 - t_1,  B2 = t_3 - b_1,  C2 = m_3 - m_1,  D2 = b_2 - t_2;
            int A3 = b_4 - t_2,  B3 = t_4 - b_2,  C3 = m_4 - m_2,  D3 = b_3 - t_3;

            // --- PHASE 3 : SEVERAL ACCUMULATORS (gx0..3, gy0..3) ---
            // Casse la chaîne RAW de dépendances de boucle
            int gx0 = A0 + B0 + (C0 << 1), gy0 = A0 - B0 + (D0 << 1);
            int gx1 = A1 + B1 + (C1 << 1), gy1 = A1 - B1 + (D1 << 1);
            int gx2 = A2 + B2 + (C2 << 1), gy2 = A2 - B2 + (D2 << 1);
            int gx3 = A3 + B3 + (C3 << 1), gy3 = A3 - B3 + (D3 << 1);

            // --- PHASE 4 : BRANCH-FREE COMPARE-EXCHANGE / SATURATION ---
            // Dépendances de contrôle converties en dépendances de données sans misprediction
            int g0 = std::min((std::min(std::abs(gx0), 255) + std::min(std::abs(gy0), 255)) >> 1, 255);
            int g1 = std::min((std::min(std::abs(gx1), 255) + std::min(std::abs(gy1), 255)) >> 1, 255);
            int g2 = std::min((std::min(std::abs(gx2), 255) + std::min(std::abs(gy2), 255)) >> 1, 255);
            int g3 = std::min((std::min(std::abs(gx3), 255) + std::min(std::abs(gy3), 255)) >> 1, 255);

            // --- PHASE 5 : STORES ---
            r_out[i]     = (uchar)g0;
            r_out[i + 1] = (uchar)g1;
            r_out[i + 2] = (uchar)g2;
            r_out[i + 3] = (uchar)g3;
        }

        // 3. REMAINDER LOOP (Pour les derniers W mod d pixels en bout de ligne)
        for (; i < cols - 1; i++)
        {
            int t_m1 = r_top[i - 1], t_0 = r_top[i], t_1 = r_top[i + 1];
            int m_m1 = r_mid[i - 1],               m_1 = r_mid[i + 1];
            int b_m1 = r_bot[i - 1], b_0 = r_bot[i], b_1 = r_bot[i + 1];

            int A = b_1 - t_m1, B = t_1 - b_m1, C = m_1 - m_m1, D = b_0 - t_0;

            int gx = A + B + (C << 1);
            int gy = A - B + (D << 1);

            int g = std::min((std::min(std::abs(gx), 255) + std::min(std::abs(gy), 255)) >> 1, 255);
            r_out[i] = (uchar)g;
        }
    }

    // 4. GESTION DES BORDS
    for (int i = 0; i < cols; i++) {
        sobel_pixel_border_v3_stg0(im_in, im_out, 0, i, rows, cols);
        sobel_pixel_border_v3_stg0(im_in, im_out, rows - 1, i, rows, cols);
    }
    for (int j = 1; j < rows - 1; j++) {
        sobel_pixel_border_v3_stg0(im_in, im_out, j, 0, rows, cols);
        sobel_pixel_border_v3_stg0(im_in, im_out, j, cols - 1, rows, cols);
    }
}

void my_sobel_opti_v3_stg2(Mat im_in, Mat im_out)
{
    int rows = im_in.rows;
    int cols = im_in.cols;

    // 1. CŒUR DE L'IMAGE - PARCOURS ROW-MAJOR SUR LES LIGNES y (j)
    for (int j = 1; j < rows - 1; j++)
    {
        // ROW POINTERS : Accès direct à la mémoire (0 appel at<uchar>)
        const uchar* r_top = im_in.ptr<uchar>(j - 1);
        const uchar* r_mid = im_in.ptr<uchar>(j);
        const uchar* r_bot = im_in.ptr<uchar>(j + 1);
        uchar*       r_out = im_out.ptr<uchar>(j);

        // AMORÇAGE (PRIMING) : Chargement initial des colonnes 0 et 1 en registres CPU
        int t_m1 = r_top[0], m_m1 = r_mid[0], b_m1 = r_bot[0]; // Colonne (i - 1) pour i = 1
        int t_0  = r_top[1], m_0  = r_mid[1], b_0  = r_bot[1]; // Colonne (i)     pour i = 1

        int i = 1;

        // 2. BOUCLE PRINCIPALE DÉROULÉE PAR d = 4 AVEC FENÊTRE GLISSANTE EN REGISTRES
        for (; i <= cols - 5; i += 4)
        {
            // --- LOADS MINIMISÉS : Chargement de seulement 4 nouvelles colonnes (12 octets au lieu de 18) ---
            // Les colonnes i-1 (t_m1, m_m1, b_m1) et i (t_0, m_0, b_0) sont DÉJÀ dans les registres CPU !
            int t_1 = r_top[i + 1], m_1 = r_mid[i + 1], b_1 = r_bot[i + 1];
            int t_2 = r_top[i + 2], m_2 = r_mid[i + 2], b_2 = r_bot[i + 2];
            int t_3 = r_top[i + 3], m_3 = r_mid[i + 3], b_3 = r_bot[i + 3];
            int t_4 = r_top[i + 4], m_4 = r_mid[i + 4], b_4 = r_bot[i + 4];

            // --- CALCUL SOBEL V3 RENAMED (Pixel 0 : col i) ---
            int A0 = b_1 - t_m1, B0 = t_1 - b_m1, C0 = m_1 - m_m1, D0 = b_0 - t_0;
            // --- CALCUL SOBEL V3 RENAMED (Pixel 1 : col i+1) ---
            int A1 = b_2 - t_0,  B1 = t_2 - b_0,  C1 = m_2 - m_0,  D1 = b_1 - t_1;
            // --- CALCUL SOBEL V3 RENAMED (Pixel 2 : col i+2) ---
            int A2 = b_3 - t_1,  B2 = t_3 - b_1,  C2 = m_3 - m_1,  D2 = b_2 - t_2;
            // --- CALCUL SOBEL V3 RENAMED (Pixel 3 : col i+3) ---
            int A3 = b_4 - t_2,  B3 = t_4 - b_2,  C3 = m_4 - m_2,  D3 = b_3 - t_3;

            // --- ACCUMULATEURS SÉPARÉS (Rupture des chaînes RAW) ---
            int gx0 = A0 + B0 + (C0 << 1), gy0 = A0 - B0 + (D0 << 1);
            int gx1 = A1 + B1 + (C1 << 1), gy1 = A1 - B1 + (D1 << 1);
            int gx2 = A2 + B2 + (C2 << 1), gy2 = A2 - B2 + (D2 << 1);
            int gx3 = A3 + B3 + (C3 << 1), gy3 = A3 - B3 + (D3 << 1);

            // --- SATURATION BRANCH-FREE ---
            int g0 = std::min((std::min(std::abs(gx0), 255) + std::min(std::abs(gy0), 255)) >> 1, 255);
            int g1 = std::min((std::min(std::abs(gx1), 255) + std::min(std::abs(gy1), 255)) >> 1, 255);
            int g2 = std::min((std::min(std::abs(gx2), 255) + std::min(std::abs(gy2), 255)) >> 1, 255);
            int g3 = std::min((std::min(std::abs(gx3), 255) + std::min(std::abs(gy3), 255)) >> 1, 255);

            // --- ÉCRITURE DES 4 RÉSULTATS (Stores contigus en mémoire) ---
            r_out[i]     = (uchar)g0;
            r_out[i + 1] = (uchar)g1;
            r_out[i + 2] = (uchar)g2;
            r_out[i + 3] = (uchar)g3;

            // --- RÉUTILISATION DE LA FENÊTRE DANS LES REGISTRES POUR L'ITÉRATION SUIVANTE ---
            // Les colonnes i+3 et i+4 deviennent les colonnes i-1 et i pour le bloc suivant
            t_m1 = t_3; m_m1 = m_3; b_m1 = b_3;
            t_0  = t_4; m_0  = m_4; b_0  = b_4;
        }

        // 3. REMAINDER LOOP AVEC FENÊTRE GLISSANTE (Chaque itération ne charge qu'UNE seule nouvelle colonne)
        for (; i < cols - 1; i++)
        {
            int t_1 = r_top[i + 1], m_1 = r_mid[i + 1], b_1 = r_bot[i + 1];

            int A = b_1 - t_m1, B = t_1 - b_m1, C = m_1 - m_m1, D = b_0 - t_0;

            int gx = A + B + (C << 1);
            int gy = A - B + (D << 1);

            int g = std::min((std::min(std::abs(gx), 255) + std::min(std::abs(gy), 255)) >> 1, 255);
            r_out[i] = (uchar)g;

            // Glissement de la fenêtre d'une colonne vers la droite
            t_m1 = t_0; m_m1 = m_0; b_m1 = b_0;
            t_0  = t_1; m_0  = m_1; b_0  = b_1;
        }
    }

    // 4. GESTION DES BORDS
    for (int i = 0; i < cols; i++) {
        sobel_pixel_border_v3_stg0(im_in, im_out, 0, i, rows, cols);
        sobel_pixel_border_v3_stg0(im_in, im_out, rows - 1, i, rows, cols);
    }
    for (int j = 1; j < rows - 1; j++) {
        sobel_pixel_border_v3_stg0(im_in, im_out, j, 0, rows, cols);
        sobel_pixel_border_v3_stg0(im_in, im_out, j, cols - 1, rows, cols);
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

void CE_BF(uchar &a, uchar &b) {               
    uchar _min = std::min(a, b);    
    uchar _max = std::max(a, b);    
    a = _min;                       
    b = _max;                       
}

void sort3(uchar &a, uchar &b, uchar &c) {
    CE(a, b);
    CE(b, c);
    CE(a, b);
}

void sort3_bf(uchar &a, uchar &b, uchar &c) {
    CE_BF(a, b);
    CE_BF(b, c);
    CE_BF(a, b);
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

void median_pixel_border_m3_stg0(Mat im_in, Mat im_out, int row, int col, int rows, int cols)
{
    // --- GESTION DU BORD VERTICAL (Lignes) ---
    int r_m1, r_p1;

    if (row == 0) {
        r_m1 = 0; // Ligne haut dupliquée (BORDER_REPLICATE)
    } else {
        r_m1 = row - 1;
    }

    if (row == rows - 1) {
        r_p1 = rows - 1; // Ligne bas dupliquée
    } else {
        r_p1 = row + 1;
    }

    // --- GESTION DU BORD HORIZONTAL (Colonnes) ---
    int c_m1, c_p1;

    if (col == 0) {
        c_m1 = 0; // Colonne gauche dupliquée (BORDER_REPLICATE)
    } else {
        c_m1 = col - 1;
    }

    if (col == cols - 1) {
        c_p1 = cols - 1; // Colonne droite dupliquée
    } else {
        c_p1 = col + 1;
    }

    // --- LECTURE DES 9 PIXELS DE LA FENÊTRE ---
    uchar c0_0 = im_in.at<uchar>(r_m1, c_m1);
    uchar c0_1 = im_in.at<uchar>(row,  c_m1);
    uchar c0_2 = im_in.at<uchar>(r_p1, c_m1);

    uchar c1_0 = im_in.at<uchar>(r_m1, col);
    uchar c1_1 = im_in.at<uchar>(row,  col);
    uchar c1_2 = im_in.at<uchar>(r_p1, col);

    uchar c2_0 = im_in.at<uchar>(r_m1, c_p1);
    uchar c2_1 = im_in.at<uchar>(row,  c_p1);
    uchar c2_2 = im_in.at<uchar>(r_p1, c_p1);

    // --- RÉSEAU DE TRI M3 (15 CE) ---
    sort3(c0_0, c0_1, c0_2);
    sort3(c1_0, c1_1, c1_2);
    sort3(c2_0, c2_1, c2_2);

    sort3(c0_0, c1_0, c2_0);
    sort3(c0_1, c1_1, c2_1);
    sort3(c0_2, c1_2, c2_2);

    uchar med = c1_1;
    sort3(c0_2, med, c2_0);

    // Écriture du résultat
    im_out.at<uchar>(row, col) = med;
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

void my_median_opti_m3_stg0(Mat im_in, Mat im_out)
{
    int rows = im_in.rows;
    int cols = im_in.cols;

    // 1. CŒUR DE L'IMAGE - BALAYAGE PAR FENÊTRE GLISSANTE (M3)
    for (int j = 1; j < rows - 1; j++)
    {
        // Amorçage (Priming) : Tri des colonnes 0 et 1 (6 CE, 6 loads)
        uchar c0_0 = im_in.at<uchar>(j - 1, 0);
        uchar c0_1 = im_in.at<uchar>(j,     0);
        uchar c0_2 = im_in.at<uchar>(j + 1, 0);
        sort3(c0_0, c0_1, c0_2);

        uchar c1_0 = im_in.at<uchar>(j - 1, 1);
        uchar c1_1 = im_in.at<uchar>(j,     1);
        uchar c1_2 = im_in.at<uchar>(j + 1, 1);
        sort3(c1_0, c1_1, c1_2);

        // Boucle principale le long de la ligne
        for (int i = 1; i < cols - 1; i++)
        {
            // Lecture et tri de la seule NOUVELLE colonne entrante (i + 1) : 3 CE + 3 loads
            uchar c2_0 = im_in.at<uchar>(j - 1, i + 1);
            uchar c2_1 = im_in.at<uchar>(j,     i + 1);
            uchar c2_2 = im_in.at<uchar>(j + 1, i + 1);
            sort3(c2_0, c2_1, c2_2);

            // Tri des 3 lignes (Min, Med, Max des colonnes c0, c1, c2) : 9 CE
            uchar r1_0 = c0_0, r1_1 = c1_0, r1_2 = c2_0;
            sort3(r1_0, r1_1, r1_2);

            uchar r2_0 = c0_1, r2_1 = c1_1, r2_2 = c2_1;
            sort3(r2_0, r2_1, r2_2);

            uchar r3_0 = c0_2, r3_1 = c1_2, r3_2 = c2_2;
            sort3(r3_0, r3_1, r3_2);

            // Tri de la diagonale secondaire : 3 CE
            uchar med = r2_1;
            sort3(r1_2, med, r3_0);

            im_out.at<uchar>(j, i) = med;

            // Décalage de la fenêtre dans les registres (0 accès mémoire)
            c0_0 = c1_0; c0_1 = c1_1; c0_2 = c1_2;
            c1_0 = c2_0; c1_1 = c2_1; c1_2 = c2_2;
        }
    }

    // 2. GESTION DES BORDS
    for (int i = 0; i < cols; i++) {
        median_pixel_border_m3_stg0(im_in, im_out, 0, i, rows, cols);
        median_pixel_border_m3_stg0(im_in, im_out, rows - 1, i, rows, cols);
    }
    for (int j = 1; j < rows - 1; j++) {
        median_pixel_border_m3_stg0(im_in, im_out, j, 0, rows, cols);
        median_pixel_border_m3_stg0(im_in, im_out, j, cols - 1, rows, cols);
    }
}

void my_median_opti_m3_stg1(Mat im_in, Mat im_out)
{
    int rows = im_in.rows;
    int cols = im_in.cols;

    // 1. CŒUR DE L'IMAGE - BALAYAGE PAR FENÊTRE GLISSANTE ET DÉROULAGE PAR d = 4 SUR LE LONG DE x (i)
    for (int j = 1; j < rows - 1; j++)
    {
        // ROW POINTERS : Suppression de 100% des appels im_in.at<uchar>()
        const uchar* r_top = im_in.ptr<uchar>(j - 1);
        const uchar* r_mid = im_in.ptr<uchar>(j);
        const uchar* r_bot = im_in.ptr<uchar>(j + 1);
        uchar*       r_out = im_out.ptr<uchar>(j);

        // Amorçage (Priming) : Tri des colonnes 0 et 1 conservées en registres
        uchar c0_0 = r_top[0], c0_1 = r_mid[0], c0_2 = r_bot[0];
        sort3_bf(c0_0, c0_1, c0_2);

        uchar c1_0 = r_top[1], c1_1 = r_mid[1], c1_2 = r_bot[1];
        sort3_bf(c1_0, c1_1, c1_2);

        int i = 1;

        // Boucle principale déroulée par d = 4 pixels (i, i+1, i+2, i+3)
        for (; i <= cols - 5; i += 4)
        {
            // --- PHASE 1 : LOADS FIRST ---
            // Chargement des 4 nouvelles colonnes entrantes (i+1, i+2, i+3, i+4)
            uchar c2_0 = r_top[i + 1], c2_1 = r_mid[i + 1], c2_2 = r_bot[i + 1];
            uchar c3_0 = r_top[i + 2], c3_1 = r_mid[i + 2], c3_2 = r_bot[i + 2];
            uchar c4_0 = r_top[i + 3], c4_1 = r_mid[i + 3], c4_2 = r_bot[i + 3];
            uchar c5_0 = r_top[i + 4], c5_1 = r_mid[i + 4], c5_2 = r_bot[i + 4];

            // --- PHASE 2 : INTERLEAVED SORTING OF NEW COLUMNS (c2, c3, c4, c5) ---
            // Entrelacement des réseaux de tri des 4 colonnes pour masquer les latences
            CE_BF(c2_0, c2_1); CE_BF(c3_0, c3_1); CE_BF(c4_0, c4_1); CE_BF(c5_0, c5_1);
            CE_BF(c2_1, c2_2); CE_BF(c3_1, c3_2); CE_BF(c4_1, c4_2); CE_BF(c5_1, c5_2);
            CE_BF(c2_0, c2_1); CE_BF(c3_0, c3_1); CE_BF(c4_0, c4_1); CE_BF(c5_0, c5_1);

            // --- PHASE 3 : RENAMING & INITIALISATION DES 4 FENÊTRES ---
            // Ligne 1 des 4 pixels
            uchar r1_0_0 = c0_0, r1_1_0 = c1_0, r1_2_0 = c2_0; // Pixel 0 (i)
            uchar r1_0_1 = c1_0, r1_1_1 = c2_0, r1_2_1 = c3_0; // Pixel 1 (i+1)
            uchar r1_0_2 = c2_0, r1_1_2 = c3_0, r1_2_2 = c4_0; // Pixel 2 (i+2)
            uchar r1_0_3 = c3_0, r1_1_3 = c4_0, r1_2_3 = c5_0; // Pixel 3 (i+3)

            // Ligne 2 des 4 pixels
            uchar r2_0_0 = c0_1, r2_1_0 = c1_1, r2_2_0 = c2_1;
            uchar r2_0_1 = c1_1, r2_1_1 = c2_1, r2_2_1 = c3_1;
            uchar r2_0_2 = c2_1, r2_1_2 = c3_1, r2_2_2 = c4_1;
            uchar r2_0_3 = c3_1, r2_1_3 = c4_1, r2_2_3 = c5_1;

            // Ligne 3 des 4 pixels
            uchar r3_0_0 = c0_2, r3_1_0 = c1_2, r3_2_0 = c2_2;
            uchar r3_0_1 = c1_2, r3_1_1 = c2_2, r3_2_1 = c3_2;
            uchar r3_0_2 = c2_2, r3_1_2 = c3_2, r3_2_2 = c4_2;
            uchar r3_0_3 = c3_2, r3_1_3 = c4_2, r3_2_3 = c5_2;

            // --- PHASE 4 : INTERLEAVED ROW SORTING NETWORKS (P0, P1, P2, P3) ---
            // Passe 1 (Comparaison éléments 0 et 1)
            CE_BF(r1_0_0, r1_1_0); CE_BF(r1_0_1, r1_1_1); CE_BF(r1_0_2, r1_1_2); CE_BF(r1_0_3, r1_1_3);
            CE_BF(r2_0_0, r2_1_0); CE_BF(r2_0_1, r2_1_1); CE_BF(r2_0_2, r2_1_2); CE_BF(r2_0_3, r2_1_3);
            CE_BF(r3_0_0, r3_1_0); CE_BF(r3_0_1, r3_1_1); CE_BF(r3_0_2, r3_1_2); CE_BF(r3_0_3, r3_1_3);

            // Passe 2 (Comparaison éléments 1 et 2)
            CE_BF(r1_1_0, r1_2_0); CE_BF(r1_1_1, r1_2_1); CE_BF(r1_1_2, r1_2_2); CE_BF(r1_1_3, r1_2_3);
            CE_BF(r2_1_0, r2_2_0); CE_BF(r2_1_1, r2_2_1); CE_BF(r2_1_2, r2_2_2); CE_BF(r2_1_3, r2_2_3);
            CE_BF(r3_1_0, r3_2_0); CE_BF(r3_1_1, r3_2_1); CE_BF(r3_1_2, r3_2_2); CE_BF(r3_1_3, r3_2_3);

            // Passe 3 (Comparaison éléments 0 et 1)
            CE_BF(r1_0_0, r1_1_0); CE_BF(r1_0_1, r1_1_1); CE_BF(r1_0_2, r1_1_2); CE_BF(r1_0_3, r1_1_3);
            CE_BF(r2_0_0, r2_1_0); CE_BF(r2_0_1, r2_1_1); CE_BF(r2_0_2, r2_1_2); CE_BF(r2_0_3, r2_1_3);
            CE_BF(r3_0_0, r3_1_0); CE_BF(r3_0_1, r3_1_1); CE_BF(r3_0_2, r3_1_2); CE_BF(r3_0_3, r3_1_3);

            // --- PHASE 5 : INTERLEAVED ANTI-DIAGONAL SORTING ---
            uchar med0 = r2_1_0;
            uchar med1 = r2_1_1;
            uchar med2 = r2_1_2;
            uchar med3 = r2_1_3;

            CE_BF(r1_2_0, med0); CE_BF(r1_2_1, med1); CE_BF(r1_2_2, med2); CE_BF(r1_2_3, med3);
            CE_BF(med0, r3_0_0); CE_BF(med1, r3_0_1); CE_BF(med2, r3_0_2); CE_BF(med3, r3_0_3);
            CE_BF(r1_2_0, med0); CE_BF(r1_2_1, med1); CE_BF(r1_2_2, med2); CE_BF(r1_2_3, med3);

            // --- PHASE 6 : STORES ---
            r_out[i]     = med0;
            r_out[i + 1] = med1;
            r_out[i + 2] = med2;
            r_out[i + 3] = med3;

            // Décalage de la fenêtre dans les registres pour l'itération suivante
            c0_0 = c4_0; c0_1 = c4_1; c0_2 = c4_2;
            c1_0 = c5_0; c1_1 = c5_1; c1_2 = c5_2;
        }

        // 2. REMAINDER LOOP (Pour les pixels restants en fin de ligne : W mod d)
        for (; i < cols - 1; i++)
        {
            uchar c2_0 = r_top[i + 1], c2_1 = r_mid[i + 1], c2_2 = r_bot[i + 1];
            sort3_bf(c2_0, c2_1, c2_2);

            uchar r1_0 = c0_0, r1_1 = c1_0, r1_2 = c2_0;
            sort3_bf(r1_0, r1_1, r1_2);

            uchar r2_0 = c0_1, r2_1 = c1_1, r2_2 = c2_1;
            sort3_bf(r2_0, r2_1, r2_2);

            uchar r3_0 = c0_2, r3_1 = c1_2, r3_2 = c2_2;
            sort3_bf(r3_0, r3_1, r3_2);

            uchar med = r2_1;
            sort3_bf(r1_2, med, r3_0);

            r_out[i] = med;

            c0_0 = c1_0; c0_1 = c1_1; c0_2 = c1_2;
            c1_0 = c2_0; c1_1 = c2_1; c1_2 = c2_2;
        }
    }

    // 3. GESTION DES BORDS
    for (int i = 0; i < cols; i++) {
        median_pixel_border_m3_stg0(im_in, im_out, 0, i, rows, cols);
        median_pixel_border_m3_stg0(im_in, im_out, rows - 1, i, rows, cols);
    }
    for (int j = 1; j < rows - 1; j++) {
        median_pixel_border_m3_stg0(im_in, im_out, j, 0, rows, cols);
        median_pixel_border_m3_stg0(im_in, im_out, j, cols - 1, rows, cols);
    }
}

void my_median_opti_m3_stg2(Mat im_in, Mat im_out)
{
    int rows = im_in.rows;
    int cols = im_in.cols;

    // 1. CŒUR DE L'IMAGE - PARCOURS ROW-MAJOR SUR LES LIGNES y (j)
    for (int j = 1; j < rows - 1; j++)
    {
        // ROW POINTERS : Accès mémoire direct (0 appel at<uchar>)
        const uchar* r_top = im_in.ptr<uchar>(j - 1);
        const uchar* r_mid = im_in.ptr<uchar>(j);
        const uchar* r_bot = im_in.ptr<uchar>(j + 1);
        uchar*       r_out = im_out.ptr<uchar>(j);

        // AMORÇAGE (PRIMING) : Chargement et tri des colonnes 0 et 1 en registres CPU
        uchar c0_0 = r_top[0], c0_1 = r_mid[0], c0_2 = r_bot[0];
        sort3_bf(c0_0, c0_1, c0_2);

        uchar c1_0 = r_top[1], c1_1 = r_mid[1], c1_2 = r_bot[1];
        sort3_bf(c1_0, c1_1, c1_2);

        int i = 1;

        // 2. BOUCLE PRINCIPALE DÉROULÉE PAR d = 4 AVEC FENÊTRE GLISSANTE
        for (; i <= cols - 5; i += 4)
        {
            // --- LOADS FIRST : Chargement unique des 4 nouvelles colonnes entrantes (i+1..i+4) ---
            // c0 et c1 sont DÉJÀ triées et conservées en registres depuis l'itération précédente !
            uchar c2_0 = r_top[i + 1], c2_1 = r_mid[i + 1], c2_2 = r_bot[i + 1];
            uchar c3_0 = r_top[i + 2], c3_1 = r_mid[i + 2], c3_2 = r_bot[i + 2];
            uchar c4_0 = r_top[i + 3], c4_1 = r_mid[i + 3], c4_2 = r_bot[i + 3];
            uchar c5_0 = r_top[i + 4], c5_1 = r_mid[i + 4], c5_2 = r_bot[i + 4];

            // --- TRI ENTRELACÉ DES 4 NOUVELLES COLONNES ---
            CE_BF(c2_0, c2_1); CE_BF(c3_0, c3_1); CE_BF(c4_0, c4_1); CE_BF(c5_0, c5_1);
            CE_BF(c2_1, c2_2); CE_BF(c3_1, c3_2); CE_BF(c4_1, c4_2); CE_BF(c5_1, c5_2);
            CE_BF(c2_0, c2_1); CE_BF(c3_0, c3_1); CE_BF(c4_0, c4_1); CE_BF(c5_0, c5_1);

            // --- INITIALISATION DES 4 FENÊTRES (Renaming) ---
            uchar r1_0_0 = c0_0, r1_1_0 = c1_0, r1_2_0 = c2_0; // Pixel 0 (col i)
            uchar r1_0_1 = c1_0, r1_1_1 = c2_0, r1_2_1 = c3_0; // Pixel 1 (col i+1)
            uchar r1_0_2 = c2_0, r1_1_2 = c3_0, r1_2_2 = c4_0; // Pixel 2 (col i+2)
            uchar r1_0_3 = c3_0, r1_1_3 = c4_0, r1_2_3 = c5_0; // Pixel 3 (col i+3)

            uchar r2_0_0 = c0_1, r2_1_0 = c1_1, r2_2_0 = c2_1;
            uchar r2_0_1 = c1_1, r2_1_1 = c2_1, r2_2_1 = c3_1;
            uchar r2_0_2 = c2_1, r2_1_2 = c3_1, r2_2_2 = c4_1;
            uchar r2_0_3 = c3_1, r2_1_3 = c4_1, r2_2_3 = c5_1;

            uchar r3_0_0 = c0_2, r3_1_0 = c1_2, r3_2_0 = c2_2;
            uchar r3_0_1 = c1_2, r3_1_1 = c2_2, r3_2_1 = c3_2;
            uchar r3_0_2 = c2_2, r3_1_2 = c3_2, r3_2_2 = c4_2;
            uchar r3_0_3 = c3_2, r3_1_3 = c4_2, r3_2_3 = c5_2;

            // --- RÉSEAUX DE TRI DES LIGNES (ENTRELACÉS) ---
            CE_BF(r1_0_0, r1_1_0); CE_BF(r1_0_1, r1_1_1); CE_BF(r1_0_2, r1_1_2); CE_BF(r1_0_3, r1_1_3);
            CE_BF(r2_0_0, r2_1_0); CE_BF(r2_0_1, r2_1_1); CE_BF(r2_0_2, r2_1_2); CE_BF(r2_0_3, r2_1_3);
            CE_BF(r3_0_0, r3_1_0); CE_BF(r3_0_1, r3_1_1); CE_BF(r3_0_2, r3_1_2); CE_BF(r3_0_3, r3_1_3);

            CE_BF(r1_1_0, r1_2_0); CE_BF(r1_1_1, r1_2_1); CE_BF(r1_1_2, r1_2_2); CE_BF(r1_1_3, r1_2_3);
            CE_BF(r2_1_0, r2_2_0); CE_BF(r2_1_1, r2_2_1); CE_BF(r2_1_2, r2_2_2); CE_BF(r2_1_3, r2_2_3);
            CE_BF(r3_1_0, r3_2_0); CE_BF(r3_1_1, r3_2_1); CE_BF(r3_1_2, r3_2_2); CE_BF(r3_1_3, r3_2_3);

            CE_BF(r1_0_0, r1_1_0); CE_BF(r1_0_1, r1_1_1); CE_BF(r1_0_2, r1_1_2); CE_BF(r1_0_3, r1_1_3);
            CE_BF(r2_0_0, r2_1_0); CE_BF(r2_0_1, r2_1_1); CE_BF(r2_0_2, r2_1_2); CE_BF(r2_0_3, r2_1_3);
            CE_BF(r3_0_0, r3_1_0); CE_BF(r3_0_1, r3_1_1); CE_BF(r3_0_2, r3_1_2); CE_BF(r3_0_3, r3_1_3);

            // --- TRI ANTI-DIAGONALE ET EXTRACTION MÉDIANE ---
            uchar med0 = r2_1_0, med1 = r2_1_1, med2 = r2_1_2, med3 = r2_1_3;

            CE_BF(r1_2_0, med0); CE_BF(r1_2_1, med1); CE_BF(r1_2_2, med2); CE_BF(r1_2_3, med3);
            CE_BF(med0, r3_0_0); CE_BF(med1, r3_0_1); CE_BF(med2, r3_0_2); CE_BF(med3, r3_0_3);
            CE_BF(r1_2_0, med0); CE_BF(r1_2_1, med1); CE_BF(r1_2_2, med2); CE_BF(r1_2_3, med3);

            // --- STORES ---
            r_out[i]     = med0;
            r_out[i + 1] = med1;
            r_out[i + 2] = med2;
            r_out[i + 3] = med3;

            // --- RÉUTILISATION DE LA FENÊTRE EN REGISTRES ---
            // c4 et c5 (déjà triées) deviennent c0 et c1 pour le bloc suivant
            c0_0 = c4_0; c0_1 = c4_1; c0_2 = c4_2;
            c1_0 = c5_0; c1_1 = c5_1; c1_2 = c5_2;
        }

        // 3. REMAINDER LOOP
        for (; i < cols - 1; i++)
        {
            uchar c2_0 = r_top[i + 1], c2_1 = r_mid[i + 1], c2_2 = r_bot[i + 1];
            sort3_bf(c2_0, c2_1, c2_2);

            uchar r1_0 = c0_0, r1_1 = c1_0, r1_2 = c2_0; sort3_bf(r1_0, r1_1, r1_2);
            uchar r2_0 = c0_1, r2_1 = c1_1, r2_2 = c2_1; sort3_bf(r2_0, r2_1, r2_2);
            uchar r3_0 = c0_2, r3_1 = c1_2, r3_2 = c2_2; sort3_bf(r3_0, r3_1, r3_2);

            uchar med = r2_1;
            sort3_bf(r1_2, med, r3_0);
            r_out[i] = med;

            c0_0 = c1_0; c0_1 = c1_1; c0_2 = c1_2;
            c1_0 = c2_0; c1_1 = c2_1; c1_2 = c2_2;
        }
    }

    // 4. BORDS
    for (int i = 0; i < cols; i++) {
        median_pixel_border_m3_stg0(im_in, im_out, 0, i, rows, cols);
        median_pixel_border_m3_stg0(im_in, im_out, rows - 1, i, rows, cols);
    }
    for (int j = 1; j < rows - 1; j++) {
        median_pixel_border_m3_stg0(im_in, im_out, j, 0, rows, cols);
        median_pixel_border_m3_stg0(im_in, im_out, j, cols - 1, rows, cols);
    }
}

int clamp_coord(int val, int max_val) {
    if (val < 0) {
        return 0;
    }
    if (val >= max_val) {
        return max_val - 1;
    }
    return val;
}

void my_median_opti_huang_stg0(Mat im_in, Mat im_out, int n)
{
    // Implémentation de l'histogramme glissant de Huang (R4) pour n >= 5

    int rows = im_in.rows;
    int cols = im_in.cols;
    int r = n / 2;
    int L = n * n;
    int h = (L + 1) / 2; // Rang de la médiane (ex: 13 pour n=5, 25 pour n=7)

    for (int y = 0; y < rows; y++)
    {
        // 1. Initialisation de l'histogramme au début de chaque ligne (pixel x = 0)
        int hist[256] = {0};

        for (int i = -r; i <= r; i++)
        {
            int rr = clamp_coord(y + i, rows);
            for (int j = -r; j <= r; j++)
            {
                int cc = clamp_coord(j, cols);
                uchar val = im_in.at<uchar>(rr, cc);
                hist[val]++;
            }
        }

        // Recherche de la première valeur 'med' dont le cumul atteint au moins h
        int count_sum = 0;
        int med = 0;
        for (int v = 0; v < 256; v++)
        {
            count_sum += hist[v];
            if (count_sum >= h)
            {
                med = v;
                break;
            }
        }

        // Compte 'lt' des pixels strictement inférieurs à 'med' dans la fenêtre
        int lt = 0;
        for (int v = 0; v < med; v++)
        {
            lt += hist[v];
        }

        im_out.at<uchar>(y, 0) = (uchar)med;

        // 2. Fenêtre glissante le long de la ligne (x = 1 jusqu'à cols - 1)
        for (int x = 1; x < cols; x++)
        {
            // Retrait de la colonne sortante à gauche (x - r - 1)
            int col_out = clamp_coord(x - r - 1, cols);
            for (int i = -r; i <= r; i++)
            {
                int rr = clamp_coord(y + i, rows);
                uchar v_out = im_in.at<uchar>(rr, col_out);
                hist[v_out]--;
                if (v_out < med)
                {
                    lt--;
                }
            }

            // Ajout de la colonne entrante à droite (x + r)
            int col_in = clamp_coord(x + r, cols);
            for (int i = -r; i <= r; i++)
            {
                int rr = clamp_coord(y + i, rows);
                uchar v_in = im_in.at<uchar>(rr, col_in);
                hist[v_in]++;
                if (v_in < med)
                {
                    lt++;
                }
            }

            // Ajustement dynamique de la valeur médiane 'med'
            while (lt >= h)
            {
                med--;
                lt -= hist[med];
            }

            while (lt + hist[med] < h)
            {
                lt += hist[med];
                med++;
            }

            im_out.at<uchar>(y, x) = (uchar)med;
        }
    }
}

void my_median_opti_stg0(Mat im_in, Mat im_out, int n)
{
	if (n == 3)
	{
		my_median_opti_m3_stg0(im_in, im_out);
		return;
	}
    else
    {
        my_median_opti_huang_stg0(im_in, im_out, n);
    }
}

void my_median_opti_stg1(Mat im_in, Mat im_out, int n)
{
    if (n == 3)
    {
        my_median_opti_m3_stg1(im_in, im_out);
    }
    else
    {
        my_median_opti_huang_stg0(im_in, im_out, n);
    }
}

void my_median_opti_stg2(Mat im_in, Mat im_out, int n)
{
    if (n == 3)
    {
        my_median_opti_m3_stg2(im_in, im_out);
    }
    else
    {
        my_median_opti_huang_stg0(im_in, im_out, n);
    }
}