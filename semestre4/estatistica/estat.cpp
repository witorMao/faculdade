#include <bits/stdc++.h>
using namespace std;

vector<int> readData(string fileName){
	vector <int> data;

	ifstream file;
	file.open(fileName);
	string buffer;

	if(file.is_open()){
		while(getline(file, buffer)) data.push_back(stoi(buffer, nullptr, 10));
		file.close();
	}

	return data;
}

void writeData(vector<int> data, string fileName){
	ofstream file;
	file.open(fileName);
	string buffer;

	for (int i = 0; i < data.size(); ++i){
		file << data[i];
		if(i != data.size()-1) file << ",";
	}

}

double media(vector<int> data){
	long int acumulador = 0;
	for (int i = 0; i < data.size(); ++i) acumulador += data[i];

	return((double)acumulador/data.size());
}	

double variancia(vector<int> data, double media){
	double acumulador = 0.0;

	for (int i = 0; i < data.size(); ++i) acumulador += pow( ((double)(data[i] - media)), 2);

	return ((double)acumulador/(data.size()-1));
}

double nQuartil(vector<int> data, int n){
	double p;
	int aux;
	switch(n){
		case 1:
			p = 0.25 * data.size();
			aux = (int)p;
			if((double)(p - aux) == 0.0)	return (double)(data[p-1] + data[p])/2;
			else return (double)data[(int)p];
		break;

		case 2:
			p = 0.5 * data.size();
			aux = (int)p;
			if((double)(p - aux) == 0.0)	return (double)(data[p-1] + data[p])/2;
			else return (double)data[(int)p];
		break;

		case 3:
			p = 0.75 * data.size();
			aux = (int)p;
			if((double)(p - aux) == 0.0)	return (double)(data[p-1] + data[p])/2;
			else return (double)data[(int)p];
		break;
	}
}

double mediana(vector<int> data){
	// return nQuartil(data, 2);

	if(data.size()%2 == 0) return (double)(data[(int)(data.size()/2 - 1)] + data[(int)(data.size()/2)])/2;
	else return data[(int)data.size()/2];
}

double amplQuartil(vector<int> data){
	return (nQuartil(data, 3) - nQuartil(data, 1));
}

map<int, int> freq(vector<int> data){
	map<int, int> mapa;
	int aux = data[0];
	int freq = 0;
	for (int i = 0; i < data.size(); ++i){
		if(aux == data[i]) freq++;
		else{
			mapa.insert(pair<int, int>(aux, freq));
			aux = data[i];
			freq = 1;
			if(i == data.size() - 1) mapa.insert(pair<int, int>(aux, freq)); 
		}

	}
	return mapa;
}

int moda(map<int, int> mapa){
	int max = mapa.begin()->second;
	int elem = mapa.begin()->first;//elemento
	for (map<int,int>::iterator it = mapa.begin(); it != mapa.end(); ++it){ 
		if(max < it->second) {
			elem = it->first;
			max = it->second;
		}
	}

	return elem;
}


double CoeVari(double desvio, double media){
	return desvio/media;
}

void printFreq(map<int, int> mapa){
	cout << "frequência amostral: " << endl;
	for ( map<int,int>::iterator it = mapa.begin(); it != mapa.end(); ++it){ 
		cout << it->first << " - " << it->second << endl;
	}


}

int main(){
	int tam = 0;
	vector <int> data = readData("Amostra 59 .txt");
	sort(data.begin(), data.end());
	cout << "média = " << media(data) << "; moda = " << moda(freq(data)) << "; mediana = " << mediana(data) << endl;
	cout << "mínimo = " << data[0] << "; máximo = " << data[data.size()-1] << "; amplitude = " << data[data.size()-1] - data[0] << endl;
	cout << "1-quartil = " << nQuartil(data, 1) << "; 2-quartil = " << nQuartil(data, 2) << "; 3-quartil = " << nQuartil(data, 3) << endl;
	cout << "amplitude interquartil = " << amplQuartil(data) << endl;
	cout << "variancia = " << variancia(data, media(data)) << endl;
	cout << "coeficiente de variação = " << CoeVari(sqrt(variancia(data, media(data))), media(data)) << endl; 

	printFreq(freq(data));

	writeData(data, "amostraOrganizada.txt");
}