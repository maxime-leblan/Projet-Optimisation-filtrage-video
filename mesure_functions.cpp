#include "mesure_functions.hpp"

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

int checkMatrix(Mat im_out_ref, Mat im_out_mycode) {
    // Vérification que les deux images ont les mêmes dimensions et le même type
    if (im_out_ref.rows != im_out_mycode.rows || 
        im_out_ref.cols != im_out_mycode.cols || 
        im_out_ref.type() != im_out_mycode.type()) {
        cerr << "Erreur : Les deux matrices doivent avoir les mêmes dimensions et le même type." << endl;
        return -1;
    }

    int diff_count = 0;
    int rows = im_out_ref.rows;
    int cols = im_out_ref.cols;

    // Parcours pixel par pixel
    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            if (im_out_ref.at<uchar>(r, c) != im_out_mycode.at<uchar>(r, c)) {
                diff_count++;
            }
        }
    }

    return diff_count;
}

int checkMatrix(Mat im_out_ref, Mat im_out_mycode, double& max_abs_diff)
{
	// Vérification que les deux images ont les mêmes dimensions et le même type
    if (im_out_ref.rows != im_out_mycode.rows || 
        im_out_ref.cols != im_out_mycode.cols || 
        im_out_ref.type() != im_out_mycode.type()) {
        cerr << "Erreur : Les deux matrices doivent avoir les mêmes dimensions et le même type." << endl;
        return -1;
    }

	int rows = im_out_ref.rows;
    int cols = im_out_ref.cols;
	int diff_sobel = 0;
	int max_abs_diff_sobel = 0;

	for (int r = 0; r < rows; r++) {
		for (int c = 0; c < cols; c++) {
			int diff = std::abs((int)im_out_ref.at<uchar>(r, c) - (int)im_out_mycode.at<uchar>(r, c));
			if (diff > 0) {
				diff_sobel++;
				if (diff > max_abs_diff_sobel) {
					max_abs_diff_sobel = diff;
				}
			}
		}
	}

	max_abs_diff = max_abs_diff_sobel;
	return diff_sobel;
}