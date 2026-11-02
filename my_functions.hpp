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

void my_sobel (Mat , Mat );
void my_median (Mat, Mat, int );
/**
 * Renvoie le nom du modèle du cpu présent sur la machine Linux qui exécute ce code
 */
string get_cpu_model();
/**
 * Prend en paramètre une liste de ligne à écrire dans un fichier CSV créé par la fonction, et les ajoute
 * @param data Liste contenant les lignes à ajouter dans le fichier CSV. Chaque élément de chaque ligne correspond au contenu d'une cellule du fichier CSV
 */
void storeDataInCSV(const vector<vector<string>>& data, int n, int nbOfThreads, string resolution);

/**
 * Vérifie que les deux matrices passées en paramètre sont bien égale.
 * @return 0 si les matrices sont égales, un nombre > 0 indiquant le nombre de pixels qui diffèrent sinon.
 */
int checkMatrix(Mat im_out_ref, Mat im_out_mycode);

/**
 * Vérifie que les deux matrices passées en paramètre sont bien égale.
 * @param max_abs_diff stocke l'écart de valeur absolu et maximal entre les pixels des 2 matrices passées en paramètre
 * @return 0 si les matrices sont égales, un nombre > 0 indiquant le nombre de pixels qui diffèrent sinon.
 */
int checkMatrix(Mat im_out_ref, Mat im_out_mycode, double& max_abs_diff);