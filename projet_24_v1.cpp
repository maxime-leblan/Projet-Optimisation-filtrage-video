/*
 * Fichier source pour le projet d'unitÃ©
 *  INF-4101C
 *---------------------------------------------------------------------------------------------------
 * Pour compiler, suivez l'exemple : g++ `pkg-config --cflags opencv` projet_base.cpp `pkg-config --libs opencv` -o projet -lm
 ou 
 g++ `pkg-config --cflags opencv4` projet_base.cpp `pkg-config --libs opencv4` -o projet -lm

 Compilation perso : 
 g++ -O0 -g projet_24_v1.cpp my_functions.cpp -o projet $(pkg-config --cflags --libs opencv4) -lm

 *---------------------------------------------------------------------------------------------------
 * auteur : Eva Dokladalova 09/2015
 * modification : Eva Dokladalova 10/2021
 * modification : Eva Dokladalova 10/2023
 */


/* 
 * Libraries standardes
 *
 */ 
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <time.h>
#include <sys/time.h>
#include <algorithm>
/* 
 * Libraries OpenCV "obligatoires" 
 *
 */ 
/* INCLUDES pour version 2.4
#include "highgui.h"
#include "cv.h"
#include "opencv2/opencv.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"*/

/*INCLUDES pour version 4.1*/
#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"

#include "my_functions.hpp"
  
/* -------------------------------------------------------------------
 * Deinition des "namespace" pour raccourcir cv::, std::, ou autre
 *
 ---------------------------------------------------------------------*/  
using namespace		std;
using namespace		cv;

/**
 * Renvoie le temps en nano-seconde
 * @return un temps en nano-seconde de type long long
 */
static inline long long now_ns(void) {
	struct timespec t;
	clock_gettime(CLOCK_MONOTONIC, &t);
	return (long long)t.tv_sec * 1000000000LL + t.tv_nsec;
}
/**
 * Exécute le programme d'OpenCV et MyCode une fois sans effectuer de mesure de temps
 */
void warmUp(VideoCapture& cap, Mat3b&	im_in, Mat& im_in_gray, Mat& im_blurred, Mat& grad_x, Mat& grad_y, Mat&	abs_grad_y, Mat& abs_grad_x, Mat&	grad, int n, int rows, int cols)
{
  // variable contenant les paramÃ¨tres des images ou d'Ã©xÃ©cution  
  int	ddepth	  = CV_16S;
  int	scale	  = 1;
  int	delta	  = 0;	
  unsigned char	key = '0';
  // acquisition d'une trame video - librairie OpenCV
    cap.read(im_in);
    cvtColor(im_in, im_in_gray, COLOR_BGR2GRAY);
  // calcul de la mediane - librairie OpenCV
      medianBlur(im_in_gray, im_blurred, n);
      // calcul du gradient- librairie OpenCV
    /// Gradient Y
    Sobel( im_blurred, grad_x, ddepth, 1, 0, 3, scale, delta, BORDER_DEFAULT );
    /// absolute value
    convertScaleAbs( grad_x, abs_grad_x );
    /// Gradient Y
    Sobel( im_blurred, grad_y, ddepth, 0, 1, 3, scale, delta, BORDER_DEFAULT );
    /// absolute value
    convertScaleAbs( grad_y, abs_grad_y );
    /// Total Gradient (approximate)
    addWeighted( abs_grad_x, 0.5, abs_grad_y, 0.5, 0, grad ); 
    
    Mat	im_blurred_my_code = cv::Mat(rows, cols, CV_8UC1);		// niveau de gris (1 cannal)
    Mat grad_my_code = cv::Mat(rows, cols, CV_8UC1);
    my_median (im_in_gray, im_blurred_my_code,n);
    my_sobel (im_blurred_my_code, grad_my_code);
  
}

/*----------------------------------------------
 *
 *--------------- MAIN FUNCTION ---------------
 *
 ----------------------------------------------*/
 
 
int main (int argc, char *argv[]) {
  //----------------------------------------------
  // Video acquisition - opening
  // on ouvre ici la lecture du flux vidÃ©o
  //----------------------------------------------
  // VideoCapture		cap(0); // le numÃ©ro 0 indique le point d'accÃ¨s Ã  la camÃ©ra 0 = > /dev/video0 : LIGNE D'ORIGINE
  VideoCapture		cap(0, CAP_V4L2); // Ligne à exécuter quand on est sur WSL et non un linux natif (pour fluidifier le formatage des images)
  if(!cap.isOpened()){
    cout << "Errore"; return -1;

  }

  // Forcer le format MJPEG (nécessaire sous WSL2 / usbipd)
  cap.set(cv::CAP_PROP_FOURCC, cv::VideoWriter::fourcc('M', 'J', 'P', 'G'));

  // On peut choisir la dÃ©finition de l'image traitée - mais il faut respecter la resolution compatible avec la camera.
  // HD resolution  1 920 Ã— 1 080,
  int			rows								  = 480;	
  int			cols								  = 640;
  cap.set(CAP_PROP_FRAME_WIDTH, cols);	 
  cap.set(CAP_PROP_FRAME_HEIGHT, rows);

  // Définition de l'utilisation ou non de l'exécution mono-coeur ou bien de l'exécution parallélisée
  cv::setNumThreads(1);

  //----------------------------------------------
  // Déclaration des variables - ATTENTION, declaration n'implique pas automatiquement l'allocation de l'espace memoire pour les images !!!
  //
  // Mat - structure contenant l'image 2D niveau de gris
  // Mat3b - structure contenant l'image 2D en couleur (trois cannaux)
  // ATTENTION - une dÃ©claration ne signifie pas une allocation !!
  // 
  //
  Mat3b	im_in;			// couleur (3cannaux)
  Mat	im_in_gray;		// niveau de gris (1 cannal)
  Mat	im_blurred;		// niveau de gris (1 cannal)

  Mat 	grad_x;
  Mat	grad_y;
  Mat	abs_grad_y;
  Mat	abs_grad_x;
  Mat	grad;

  // variable contenant les paramÃ¨tres des images ou d'Ã©xÃ©cution  
  int	ddepth	  = CV_16S;
  int	scale	  = 1;
  int	delta	  = 0;	
  unsigned char	key = '0';

  //----------------------------------------------------
  // CrÃ©ation des fenÃªtres pour affichage des rÃ©sultats
  // vous pouvez ne pas les utiliser ou ajouter selon ces exemple
  // code commentÃ© pour la vesrion 2.4

  /* cvNamedWindow("Video input", WINDOW_AUTOSIZE);
  cvNamedWindow("Video gray levels", WINDOW_AUTOSIZE);
  cvNamedWindow("Video Mediane", WINDOW_AUTOSIZE);
  cvNamedWindow("Video Edge detection", WINDOW_AUTOSIZE);
  // placement arbitraire des  fenÃªtre sur Ã©cran 
  // sinon les fenÃªtres sont superposÃ©e l'une sur l'autre
  cvMoveWindow("Video input", 10, 30);
  cvMoveWindow("Video gray levels", 800, 30);
  cvMoveWindow("Video Mediane", 10, 500);
  cvMoveWindow("Video Edge detection", 800, 500);*/

  namedWindow("Video input", WINDOW_AUTOSIZE);
  namedWindow("Video gray levels", WINDOW_AUTOSIZE);
  namedWindow("Video Mediane", WINDOW_AUTOSIZE);
  namedWindow("Video Edge detection", WINDOW_AUTOSIZE);
  // placement arbitraire des  fenÃªtre sur Ã©cran 
  // sinon les fenÃªtres sont superposÃ©e l'une sur l'autre
  moveWindow("Video input", 10, 30);
  moveWindow("Video gray levels", 800, 30);
  moveWindow("Video Mediane", 10, 500);
  moveWindow("Video Edge detection", 800, 500);


  // --------------------------------------------------
  // boucle de 100 itérations
  //
  int	n;
  if (argc == 2)
  {
    n = atoi(argv[1]);	//taille de filtre médian - doit être variables !
    if ((n % 2) != 1 || n < 3)
    {
      cout << "Erreur : n doit être un nombre impair et supérieur ou égal à 3.";
      return -1;
    }
  }
  else
  {
    cout << "1 paramètre n'a pas été passé au programme. Sa valeur a été initialisée par défaut.";
    n = 3;
  }

  // déclaration des variables permettant d'effectuer nos mesures
  double iter  = 110; 
  int nbWarmIter = 10;

  long long	t0;
  long long	t1;

  // initialisation des tableaux chargés de stocker les mesures de temps pour pouvoir ensuite extraire la mediane, le min et le max
  vector<double> t_ref_median_measures;
  vector<double> t_ref_grad_measures;
  vector<double> t_mycode_median_measures;
  vector<double> t_mycode_grad_measures;

  double    fps_ref = 0.0;
  double    fps_mycode = 0.0;

  double		mean_t_ref_median = 0.0;
  double    median_t_ref_median = 0.0;
  double    min_t_ref_median = 0.0;
  double    max_t_ref_median = 0.0;

  double		mean_t_ref_grad  = 0.0;
  double		median_t_ref_grad  = 0.0;
  double		min_t_ref_grad  = 0.0;
  double		max_t_ref_grad  = 0.0;

  double		mean_t_mycode_median  = 0.0;
  double		median_t_mycode_median  = 0.0;
  double		min_t_mycode_median  = 0.0;
  double		max_t_mycode_median  = 0.0;

  double		mean_t_mycode_grad    = 0.0;
  double		median_t_mycode_grad    = 0.0;
  double		min_t_mycode_grad    = 0.0;
  double		max_t_mycode_grad    = 0.0;

  double		temp  = 0.0;
  double		no_measures = iter - nbWarmIter;

  while(iter-- !=0 ){
    // on vérifie si nous somme encore dans l'étape warm up du programme ou non
    if (iter - no_measures >= 0)
    {
      warmUp(cap, im_in, im_in_gray, im_blurred, grad_x, grad_y, abs_grad_y, abs_grad_x, grad, n, rows, cols);
      printf("On échauffe le programme %d \n", (int)(iter - no_measures));
      continue;
    }
    // mesure de temps d'exécution de cette partie :
    t0 = now_ns();
    // acquisition d'une trame video - librairie OpenCV
    cap.read(im_in);

  //conversion en niveau de gris - librairie OpenCV
  //on travaille en niveau de gris pour ce projet (simplifie la problématique)
    cvtColor(im_in, im_in_gray, COLOR_BGR2GRAY);
    t1 = now_ns();
    temp = ((double)(t1 - t0))/(1000000.0);
    fps_ref += temp;
    fps_mycode += temp;
    
  // **************************************************************************
  // CODE DE REFERENCE - avec OPENCV, aujourd'hui un standard en traitement d'image
  // --------------------------------------------------------------------------
  // mesure de temps d'exécution de cette partie :
    t0 = now_ns();
  // **********************************************************************
  // calcul de la mediane - librairie OpenCV
    medianBlur(im_in_gray, im_blurred, n);
    t1 = now_ns();
    temp  = ((double)(t1 - t0))/(1000000.0);
    t_ref_median_measures.push_back(temp);
    mean_t_ref_median  = mean_t_ref_median + temp;
    fps_ref += temp;
    printf("-------------------------------------\n");
    printf("Median Reference \t %g ms\n", temp);
      
    // mesure de temps d'exécution de cette partie :
    t0 = now_ns();
    // **********************************************************************   
      // calcul du gradient- librairie OpenCV
    /// Gradient Y
    Sobel( im_blurred, grad_x, ddepth, 1, 0, 3, scale, delta, BORDER_DEFAULT );
    /// absolute value
    convertScaleAbs( grad_x, abs_grad_x );
    /// Gradient Y
    Sobel( im_blurred, grad_y, ddepth, 0, 1, 3, scale, delta, BORDER_DEFAULT );
    /// absolute value
    convertScaleAbs( grad_y, abs_grad_y );
    /// Total Gradient (approximate)
    addWeighted( abs_grad_x, 0.5, abs_grad_y, 0.5, 0, grad ); 
    // **********************************************************************
    // mesure de temps d'exécution de cette partie :
    t1 = now_ns();
    temp  = ((double)(t1 - t0))/(1000000.0);
    t_ref_grad_measures.push_back(temp);
    mean_t_ref_grad = mean_t_ref_grad + temp;
    fps_ref += temp;
    
    printf("Sobel Reference \t %g ms\n", temp);
    // **********************************************************************



    // **************************************************************************
    // CODE A OPTIMISER 
    // --------------------------------------------------------------------------
    // mesure de temps d'exécution de cette partie :
    t0 = now_ns();
    // **********************************************************************
    // allocation des matrices contenant les images intermédiaires
    Mat	im_blurred_my_code = cv::Mat(rows, cols, CV_8UC1);		// niveau de gris (1 cannal)
    Mat grad_my_code = cv::Mat(rows, cols, CV_8UC1);
    my_median (im_in_gray, im_blurred_my_code,n);
    t1 = now_ns();
    temp  = ((double)(t1 - t0))/(1000000.0);
    t_mycode_median_measures.push_back(temp);
    mean_t_mycode_median = mean_t_mycode_median + temp;
    fps_mycode += temp;
          printf("-------------------------------------\n");
      printf("Median MyCode \t %g ms\n", temp);
    // mesure de temps d'exécution de cette partie :
    t0 = now_ns();
    // ********************************************************************** 
      my_sobel (im_blurred_my_code, grad_my_code);

    // **********************************************************************
    // mesure de temps d'exécution de cette partie :
    t1 = now_ns();
    temp  = ((double)(t1 - t0))/(1000000.0);
    t_mycode_grad_measures.push_back(temp);
    mean_t_mycode_grad  = mean_t_mycode_grad + temp;
    fps_mycode += temp;
      printf("Sobel MyCode \t %g ms\n", temp);
    // ********************************************************************** 
    t0 = now_ns();
    imshow("Video input",im_in);
    imshow("Video gray levels",im_in_gray);
    imshow("Video Mediane",im_blurred_my_code);    
    imshow("Video Edge detection",grad_my_code);
    t1 = now_ns();
    temp = ((double)(t1 - t0))/(1000000.0);
    fps_ref += temp;
    fps_mycode += temp;

    key	= waitKey(1);
  }
  printf("========================================\n");

  // On trie les valeurs mesurées pour pouvoir calculer la médiane par la suite
  sort(t_ref_median_measures.begin(), t_ref_median_measures.end());
  sort(t_ref_grad_measures.begin(), t_ref_grad_measures.end());
  sort(t_mycode_median_measures.begin(), t_mycode_median_measures.end());
  sort(t_mycode_grad_measures.begin(), t_mycode_grad_measures.end());

  // On calcule les statistiques de chaque programme
    fps_ref = no_measures / (fps_ref / 1000.0);
    fps_mycode = no_measures / (fps_mycode / 1000.0);

    mean_t_ref_median   = mean_t_ref_median / no_measures;
    median_t_ref_median = t_ref_median_measures[t_ref_median_measures.size() / 2];
    min_t_ref_median = *min_element(t_ref_median_measures.begin(), t_ref_median_measures.end());
    max_t_ref_median = *max_element(t_ref_median_measures.begin(), t_ref_median_measures.end());

    mean_t_ref_grad = mean_t_ref_grad / no_measures;
    median_t_ref_grad = t_ref_grad_measures[t_ref_grad_measures.size() / 2];
    min_t_ref_grad = *min_element(t_ref_grad_measures.begin(), t_ref_grad_measures.end());
    max_t_ref_grad = *max_element(t_ref_grad_measures.begin(), t_ref_grad_measures.end());

    mean_t_mycode_median  = mean_t_mycode_median / no_measures;
    median_t_mycode_median = t_mycode_median_measures[t_mycode_median_measures.size() / 2];
    min_t_mycode_median = *min_element(t_mycode_median_measures.begin(), t_mycode_median_measures.end());
    max_t_mycode_median = *max_element(t_mycode_median_measures.begin(), t_mycode_median_measures.end());

    mean_t_mycode_grad  = mean_t_mycode_grad / no_measures;
    median_t_mycode_grad = t_mycode_grad_measures[t_mycode_grad_measures.size() / 2];
    min_t_mycode_grad = *min_element(t_mycode_grad_measures.begin(), t_mycode_grad_measures.end());
    max_t_mycode_grad = *max_element(t_mycode_grad_measures.begin(), t_mycode_grad_measures.end());
    
    // On affiche les statistiques de chaque programme
    printf("==========================\n");
    printf("Median reference statistics :\n");
    printf(" Mean   %f ms\n",mean_t_ref_median);
    printf(" Median  %f ms\n", median_t_ref_median);
    printf(" Min  %f ms\n", min_t_ref_median);
    printf(" Max  %f ms\n", max_t_ref_median);
    printf("==========================\n");
    printf("Sobel reference statistics :\n");
    printf(" Mean   %f ms\n",mean_t_ref_grad);
    printf(" Median  %f ms\n", median_t_ref_grad);
    printf(" Min  %f ms\n", min_t_ref_grad);
    printf(" Max  %f ms\n", max_t_ref_grad);

    printf("==========================\n");
    printf("Median mycode statistics :\n");
    printf(" Mean  %f ms\n",mean_t_mycode_median);
    printf(" Median  %f ms\n", median_t_mycode_median);
    printf(" Min  %f ms\n", min_t_mycode_median);
    printf(" Max  %f ms\n", max_t_mycode_median);

    printf("==========================\n");
    printf("Sobel mycode statistics :\n");
    printf(" Mean  %f ms\n",mean_t_mycode_grad);
    printf(" Median  %f ms\n", median_t_mycode_grad);
    printf(" Min  %f ms\n", min_t_mycode_grad);
    printf(" Max  %f ms\n", max_t_mycode_grad);

    printf("==========================\n");
    printf("Other Statistics :\n");

    printf(" Reference pipeline FPS : %f\n", fps_ref);
    printf(" MyCode pipeline FPS : %f\n", fps_mycode);

    printf(" Speedup median %f\n",mean_t_ref_median/mean_t_mycode_median);
    printf(" Speedup sobel %f\n",mean_t_ref_grad/mean_t_mycode_grad);
    
    printf("------------------\n");

    int nbThreads = cv::getNumThreads();
    printf("Nombre de threads utilisés par OpenCV : %d\n", nbThreads);

    //cout << "Modèle du CPU : " << get_cpu_model() << endl;
    // ********************************************************************** 

    // Stockage des mesures dans un nouveau fichier CSV

    vector<vector<string>> data;
    vector<string> line;

    line.push_back("reference");
    line.push_back("Median");
    line.push_back(to_string(mean_t_ref_median));
    line.push_back(to_string(median_t_ref_median));
    line.push_back(to_string(min_t_ref_median));
    line.push_back(to_string(max_t_ref_median));
    data.push_back(line);
    line.clear();

    line.push_back("reference");
    line.push_back("Sobel");
    line.push_back(to_string(mean_t_ref_grad));
    line.push_back(to_string(median_t_ref_grad));
    line.push_back(to_string(min_t_ref_grad));
    line.push_back(to_string(max_t_ref_grad));
    data.push_back(line);
    line.clear();

    line.push_back("mycode");
    line.push_back("Median");
    line.push_back(to_string(mean_t_mycode_median));
    line.push_back(to_string(median_t_mycode_median));
    line.push_back(to_string(min_t_mycode_median));
    line.push_back(to_string(max_t_mycode_median));
    data.push_back(line);
    line.clear();

    line.push_back("mycode");
    line.push_back("Sobel");
    line.push_back(to_string(mean_t_mycode_grad));
    line.push_back(to_string(median_t_mycode_grad));
    line.push_back(to_string(min_t_mycode_grad));
    line.push_back(to_string(max_t_mycode_grad));
    data.push_back(line);
    line.clear();

    // on ajoute les FPS et les Speedup
    data.push_back({" "});

    line.push_back("Median Speedup");
    line.push_back("Sobel Speedup");
    data.push_back(line);
    line.clear();

    line.push_back(to_string(mean_t_ref_median/mean_t_mycode_median));
    line.push_back(to_string(mean_t_ref_grad/mean_t_mycode_grad));
    data.push_back(line);
    line.clear();

    line.push_back("Reference pipeline FPS");
    line.push_back("MyCode pipeline FPS");
    data.push_back(line);
    line.clear();

    line.push_back(to_string(fps_ref));
    line.push_back(to_string(fps_mycode));
    data.push_back(line);
    line.clear();

    storeDataInCSV(data, n, nbThreads, to_string(rows) + " * " + to_string(cols));
  }

    
