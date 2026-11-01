#include "my_functions.hpp"
#include <math.h>


void my_sobel (Mat im_in, Mat im_out)
{

 int rows = im_in.rows; // height
 int cols = im_in.cols; // width
 
 
    for (int i = 1; i< cols-1; i++)
 	for (int j = 1; j< rows-1; j++){
 		int n = im_in.at<uchar>(j-1,i);
 		int s = im_in.at<uchar>(j+1,i);
 		int e = im_in.at<uchar>(j,i+1);
 		int w = im_in.at<uchar>(j,i-1);
 		int ne = im_in.at<uchar>(j-1,i+1);
 		int nw = im_in.at<uchar>(j-1,i-1);
 		int se = im_in.at<uchar>(j+1,i+1);
 		int sw = im_in.at<uchar>(j+1,i-1);
 		int c = im_in.at<uchar>(j,i);
 	
 	 	int gx = 2*e + ne + se - 2*w - sw - nw + 0*n + 0*c + 0*s;
 	 	int gy = 2*n + ne + nw - 2*s - sw - se + 0*w + 0*c + 0*e;
 	 	
 	 	float g = abs(gx) + abs(gy);
 	 	
 	 	if (g>255)
 	 		g=255;
 	 	
 	 	im_out.at<uchar>(j,i) = (uchar) (g);
 	 	
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

std::string get_cpu_model() {
    std::string model;
    
    auto deleter = [](FILE* p) { if (p) pclose(p); };
    std::unique_ptr<FILE, decltype(deleter)> pipe(
        popen("grep 'model name' /proc/cpuinfo | head -n 1 | cut -d: -f2 | sed 's/^[ \t]*//'", "r"),
        deleter
    );
    
    if (!pipe) {
        throw std::runtime_error("popen() failed!");
    }
    
    char buffer[256];
    while (fgets(buffer, sizeof(buffer), pipe.get()) != nullptr) {
        model += buffer;
    }
    
    if (!model.empty() && model.back() == '\n') {
        model.pop_back();
    }
    
    return model;
}

void storeDataInCSV(const std::vector<std::vector<std::string>>& data, int n, int nbOfThreads, string resolution) {
    // 1. Génération de la date et de l'heure courante au format JJ_MM_AAAA_HH_MM_SS
    std::time_t now = std::time(nullptr);
    std::tm* localTime = std::localtime(&now);

    std::ostringstream filenameStream;
    filenameStream << "mesures/stats_"
                   << std::setfill('0')
                   << std::setw(2) << localTime->tm_mday << "_"
                   << std::setw(2) << (localTime->tm_mon + 1) << "_"
                   << (localTime->tm_year + 1900) << "_"
                   << std::setw(2) << localTime->tm_hour << "_"
                   << std::setw(2) << localTime->tm_min << "_"
                   << std::setw(2) << localTime->tm_sec << ".csv";

    std::string filename = filenameStream.str();

    // 2. Ouverture / création du fichier CSV
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Erreur : Impossible de créer le fichier " << filename << std::endl;
        return;
    }

    // 3. Ligne 1 : Information concernant les paramètres d'exécution
    file << get_cpu_model() + ";" + "n : " + to_string(n) + ";" + "Resolution : " + resolution + ";" + "Threads : " + to_string(nbOfThreads) << "\n";

    // 4. Ligne 2 : En-tête CSV
    file << "Type;Nom;Moyenne (ms);Mediane (ms);Min (ms);Max (ms)\n";

    // 5. Parcours de data et écriture de chaque ligne dans le CSV
    for (const auto& row : data) {
        for (size_t i = 0; i < row.size(); ++i) {
            file << row[i];
            if (i < row.size() - 1) {
                file << ";";
            }
        }
        file << "\n";
    }

    file.close();
    std::cout << "Fichier " << filename << " sauvegardé avec succès." << std::endl;
}