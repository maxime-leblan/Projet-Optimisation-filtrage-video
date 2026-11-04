#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <cstdio>
#include <string>
#include <memory>
#include <fstream>
#include <vector>
#include <ctime>
#include <iomanip>
#include <sstream>

/*INCLUDES pour version 4.1*/
#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"

using namespace std;
using namespace cv;

// Version naïve et de base des programmes

void my_sobel (Mat , Mat );
void my_median (Mat, Mat, int );

/**
 * Applique le filtre de sobel sur le pixel de coordonnées (i, j) en gérant le cas où le pixel se trouve sur le bord de l'image
 * @param i coordonnée de la ligne
 * @param j coordonnée de la colonne
 */
void sobel_pixel_border_v1_stg0(Mat im_in, Mat im_out, int i, int j, int rows, int cols);

void my_sobel_opti_v1_stg0 (Mat , Mat );
void my_median_opti_v3_stg0 (Mat, Mat, int );