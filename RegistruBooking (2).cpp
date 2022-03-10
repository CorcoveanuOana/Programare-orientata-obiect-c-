#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<cstring>
#include<fstream>
#include<string>
using namespace std;

class Client {
private:
	string nume;
	string prenume;
	char telefon[11];
	string email;
	char* adresa;
	int varsta;

public:
	//constructor default
	Client() {
		this->nume = "";
		this->prenume = "";
		strcpy(this->telefon, "0712345678");
		this->email = "";
		this->adresa = NULL;
		this->varsta = 0;
	}

	//constructori cu parametrii
	Client(string nume, string prenume, char telefon[11], string email, const char* adresa, int varsta) {
		this->nume = nume;
		this->prenume = prenume;
		strcpy(this->telefon, telefon);

		this->email = email;

		this->adresa = new char[strlen(adresa) + 1];
		strcpy(this->adresa, adresa);

		this->varsta = varsta;
	}

	Client(string nume, string prenume) {
		this->nume = nume;
		this->prenume = prenume;
		strcpy(this->telefon, "0000000000");
		this->email = "";
		this->adresa = NULL;
		this->varsta = 0;
	}

	//constructor de copiere
	Client(const Client& c) {
		this->nume = c.nume;
		this->prenume = c.prenume;
		strcpy(this->telefon, c.telefon);

		this->email = c.email;

		if (c.adresa)
		{
			this->adresa = new char[strlen(c.adresa) + 1];
			strcpy(this->adresa, c.adresa);
		}
		else
			this->adresa = NULL;

		this->varsta = c.varsta;
	}

	//operator =
	Client& operator=(const Client& c) {
		if (this == &c)
			return *this;

		if (this->adresa != NULL) {
			delete[]this->adresa;
		}

		if (c.adresa)
		{
			this->adresa = new char[strlen(c.adresa) + 1];
			strcpy(this->adresa, c.adresa);
		}
		else
		{
			this->adresa = NULL;
		}

		this->nume = c.nume;
		this->prenume = c.prenume;

		strcpy(this->telefon, c.telefon);

		this->email = c.email;
		this->varsta = c.varsta;

		return *this;
	}

	//getteri si setteri
	string getNume() {
		return this->nume;
	}
	void setNume(string nume) {
		if (nume.length() < 1) {
			throw "nu ati introdus numele";
		}
		this->nume = nume;
	}

	string getPrenume() {
		return this->prenume;
	}
	void setPrenume(string prenume) {
		if (prenume.length() < 1) {
			throw "nu ati introdus prenumele";
		}
		this->prenume = prenume;
	}

	const char* getTelefon() {
		return this->telefon;
	}
	void setTelefon(char telefon[11]) {
		if (strlen(telefon) < 10) {
			throw "Numar incorect";
		}
		else
		{
			strcpy(this->telefon, telefon);
		}
	}
	void setTelString(string telefon) {
		if (telefon.size() < 10) {
			throw "Numar incorect";
		}
		else
		{
			strcpy(this->telefon, telefon.c_str());
		}
	}

	string getEmail() {
		return this->email;
	}
	void setEmail(string email) {
		if (email.length() < 1) {
			throw "nu ati introdus adresa de email";
		}
		this->email = email;
	}

	char* getAdresa() {
		return this->adresa;
	}
	void setAdresa(const char* adresa) {

		if (strlen(adresa) < 1) {
			throw "nu ati introdus adresa";
		}

		if (this->adresa != NULL)
		{
			delete[]this->adresa;
		}

		this->adresa = new char[strlen(adresa) + 1];
		strcpy(this->adresa, adresa);

	}

	int getVarsta() {
		return this->varsta;
	}
	void setVarsta(int varsta) {
		if (varsta < 0) {
			throw "varsta incorecta";
		}
		this->varsta = varsta;
	}

	//operatori >> si <<
	friend istream& operator >> (istream& intrare, Client& c) {
		cout << "Nume:";
		intrare >> c.nume;
		cout << "prenume:";
		intrare >> c.prenume;
		cout << "telefon:";

		for (int i = 0; i < 10; i++)
			intrare >> c.telefon[i];
		c.telefon[10] = '\0';

		cout << "adresa:";
		if (c.adresa) {
			delete[]c.adresa;
		}
		char buffer[100];
		intrare >> buffer;
		c.adresa = new char[strlen(buffer) + 1];
		strcpy(c.adresa, buffer);
		cout << "varsta:";
		intrare >> c.varsta;
		intrare.get();
		cout << "email:";
		intrare >> c.email;
		return intrare;
	}

	friend ostream& operator <<(ostream& iesire, Client& c) {
		cout << "Nume:";
		iesire << c.nume;
		cout << endl;
		cout << "Prenume:";
		iesire << c.prenume;
		cout << endl;
		cout << "Telefon:";
		for (int i = 0; i < 10; i++)
			iesire << c.telefon[i];
		cout << endl;
		cout << "email:";
		iesire << c.email;
		cout << endl;
		if (c.adresa) 
		{
			cout << "Adresa:";
			iesire << c.adresa;
			cout << endl;
		}
		cout << "Varsta:";
		iesire << c.varsta;
		return iesire;
	}

	//operatorul == (verificam 2 adrese: daca sunt din aceeasi zona oferim transport gratis)
	bool operator ==(Client c) {
		return this->adresa == c.adresa;
	}

	///operatorul != (comparam adrese de email)
	bool operator !=(Client c) {
		return this->email != c.email;
	}

	//verificam ca varsta clentului sa fie peste 18 ani
	bool minori() {
		return varsta > 18;

	}

	//peste o anumita varsta clentii pot beneficia de un discount
	bool reducere(int x) {
		return varsta > x;
	}

	//destructor
	~Client() {
		if (this->adresa)
			delete[]adresa;
	}

	//scriere in txt
	void scrieTxt(fstream& fisier) {

		fisier << nume << "\n";

		fisier << prenume << "\n";

		fisier << telefon << "\n";

		fisier << email << "\n";

		if (adresa)
		{
			fisier << adresa << "\n";
		}
		else
		{
			cout << "\n";
		}

		fisier << varsta << "\n";
	}

	//citire din txt
	void citesteTxt(fstream& fisier) {
		char buffer[100]{};

		getline(fisier, nume);

		getline(fisier, prenume);

		string tel;
		getline(fisier, tel);
		strcpy(telefon, tel.c_str());

		getline(fisier, email);

		string adr;
		getline(fisier, adr);
		if (adr.empty())
			adresa = NULL;
		else {
			adresa = new char[adr.size() + 1];
			strcpy(adresa, adr.c_str());
		}

		fisier >> varsta;
		fisier.get();
	}

	//scriere in fisier binar
	void scrieInBinar(std::fstream& fisier) {
		int lungimeSir = nume.size() + 1;
		fisier.write((const char*)&lungimeSir, sizeof(int));
		fisier.write((const char*)nume.c_str(), sizeof(char) * lungimeSir);

		lungimeSir = prenume.size() + 1;
		fisier.write((const char*)&lungimeSir, sizeof(int));
		fisier.write((const char*)prenume.c_str(), sizeof(char) * lungimeSir);

		fisier.write((const char*)telefon, sizeof(char) * 11);

		lungimeSir = email.size() + 1;
		fisier.write((const char*)&lungimeSir, sizeof(int));
		fisier.write((const char*)email.c_str(), sizeof(char) * lungimeSir);

		if (adresa)
		{
			lungimeSir = strlen(adresa) + 1;
			fisier.write((const char*)&lungimeSir, sizeof(int));
			fisier.write((const char*)adresa, sizeof(char) * lungimeSir);
		}
		else
		{
			lungimeSir = 0;
			fisier.write((const char*)&lungimeSir, sizeof(int));
		}

		fisier.write((const char*)&varsta, sizeof(int));
	}

	//citire din fisier binar
	void citesteDinBinar(std::fstream& fisier)
	{
		int lungimeSir = 0;
		char buffer[100]{};

		fisier.read((char*)&lungimeSir, sizeof(int));
		fisier.read((char*)buffer, sizeof(char) * lungimeSir);
		nume = buffer;

		fisier.read((char*)&lungimeSir, sizeof(int));
		fisier.read((char*)buffer, sizeof(char) * lungimeSir);
		prenume = buffer;

		fisier.read((char*)telefon, sizeof(char) * 11);

		fisier.read((char*)&lungimeSir, sizeof(int));
		fisier.read((char*)buffer, sizeof(char) * lungimeSir);
		email = buffer;

		if (adresa)
			delete[] adresa;

		fisier.read((char*)&lungimeSir, sizeof(int));

		if (lungimeSir == 0)
			adresa = NULL;
		else
		{
			fisier.read((char*)buffer, sizeof(char) * lungimeSir);
			adresa = new char[strlen(buffer) + 1];
			strcpy(adresa, buffer);
		}

		fisier.read((char*)&varsta, sizeof(int));
	}
};

class RegistruClienti {
private:
	Client* client;
	int nrClienti;

public:
	//constructor default
	RegistruClienti() {
		this->client = NULL;
		this->nrClienti = 0;
	}

	//constructori cu parametrii
	RegistruClienti(Client* client, int nrClienti) {
		this->nrClienti = nrClienti;
		this->client = new Client[nrClienti];
		for (int i = 0; i < nrClienti; i++) {
			this->client[i] = client[i];
		}
	}

	//constructor de copiere
	RegistruClienti(const RegistruClienti& c) {
		this->nrClienti = c.nrClienti;
		this->client = new Client[c.nrClienti];
		for (int i = 0; i < c.nrClienti; i++) {
			this->client[i] = c.client[i];
		}
	}

	//operator =
	RegistruClienti& operator=(const RegistruClienti& c) {
		this->nrClienti = c.nrClienti;
		this->client = new Client[c.nrClienti];
		for (int i = 0; i < c.nrClienti; i++) {
			this->client[i] = c.client[i];
		}
		return *this;
	}

	//getteri si setteri
	int getNrClienti() {
		return this->nrClienti;
	}

	void setNrClienti(int nrClienti) {
		if (nrClienti < 1) {
			throw "Nr clienti invalid.";
		}
		this->nrClienti = nrClienti;
	}

	//operatori >> si <<
	friend istream& operator >> (istream& intrare, RegistruClienti& c) {
		cout << "Introduceti nr de clienti : ";
		intrare >> c.nrClienti;
		cout << endl;
		return intrare;
	}

	friend ostream& operator <<(ostream& iesire, RegistruClienti& c) {
		cout << "Nr de clienti : ";
		iesire << c.nrClienti;
		cout << endl;
		for (int i = 0; i < c.nrClienti; i++) {
			cout << "Clientul cu nr " << i << " : \n";
			iesire << c.client[i] << endl;
		}
		return iesire;
	}

	//functie adaugare client
	void adaugareClient(Client C) {
		Client* aux = new Client[this->nrClienti + 1];
		for (int i = 0; i < this->nrClienti; i++)
			aux[i] = this->client[i];

		aux[this->nrClienti] = C;
		this->nrClienti++;

		if (this->client != NULL)
			delete[] this->client;

		this->client = aux;
	}

	//scriere in fisier txt
	void scrieInFisier() {
		fstream f("registru_clienti.txt", ios::out);

		f << this->nrClienti << '\n';
		for (int i = 0; i < this->nrClienti; i++)
			this->client[i].scrieTxt(f);

		f.close();
	}

	//citire din fisier txt
	void citesteDinFisier() {
		fstream f("registru_clienti.txt", ios::in);

		f >> this->nrClienti;
		f.get();
		this->client = new Client[this->nrClienti];
		for (int i = 0; i < this->nrClienti; i++)
			this->client[i].citesteTxt(f);

		f.close();
	}

	//functie de stergere client
	void stergeClient(string numeClient) {
		if (this->nrClienti == 0)
			throw "Nu exista clienti";

		int index = -1;
		for (int i = 0; i < this->nrClienti; i++)
			if (this->client[i].getNume() == numeClient)
			{
				index = i;
				break;
			}

		if (index == -1)
			throw "Clientul nu exista";

		Client* clientiNoi = new Client[this->nrClienti - 1];
		for (int i = 0; i < index; i++)
			clientiNoi[i] = this->client[i];

		for (int i = index + 1; i < this->nrClienti; i++)
			clientiNoi[i - 1] = this->client[i];

		this->nrClienti--;
		delete[] this->client;
		this->client = clientiNoi;
	}

	//functie de actualizare a datelor unui client ales dupa nume
	void actualizeazaClient(string numeClient) {
		int index = -1;
		for (int i = 0; i < this->nrClienti; i++)
			if (this->client[i].getNume() == numeClient) {
				index = i;
				break;
			}

		if (index == -1)
			throw "Clientul nu exista";

		//meniu de comenzi pentru actualizarea datelor
		cout << "Introduceti de la tastatura : " << endl;
		cout << "~ Numarul '7' pentru a accesa meniul de comenzi." << endl;
		cout << "~ Numarul '1' pentru a actualiza numele." << endl;
		cout << "~ Numarul '2' pentru a actualiza prenumele." << endl;
		cout << "~ Numarul '3' pentru a actualiza varsta." << endl;
		cout << "~ Numarul '4' pentru a actualiza nr de telefon." << endl;
		cout << "~ Numarul '5' pentru a actualiza adresa." << endl;
		cout << "~ Numarul '6' pentru a actualiza email-ul." << endl;
		cout << "~ Numarul '0' pentru a iesi din optiunea de actualizare." << endl;

		int n;
		cin >> n;
		while (n != 0) {
			if (n < 0 || n>7) {
				cout << "Numar comanda invalid." << endl;
			}

			if (n == 7) {
				cout << "Introduceti de la tastatura : " << endl;
				cout << "~ Numarul '7' pentru a accesa meniul de comenzi." << endl;
				cout << "~ Numarul '1' pentru a actualiza numele." << endl;
				cout << "~ Numarul '2' pentru a actualiza prenumele." << endl;
				cout << "~ Numarul '3' pentru a actualiza varsta." << endl;
				cout << "~ Numarul '4' pentru a actualiza nr de telefon." << endl;
				cout << "~ Numarul '5' pentru a actualiza adresa." << endl;
				cout << "~ Numarul '0' pentru a iesi din optiunea de actualizare." << endl;
				cout << endl;
				cout << "Ce doriti sa faceti in continuare?" << endl;
			}
			if (n == 1){
				string numeNou;
				cout << "Introduceti nume nou: ";
				cin.get();
				getline(cin, numeNou);
				this->client[index].setNume(numeNou);
				cout << "Numele a fost actualizat." << endl;
				cout << endl;
				cout << "Ce doriti sa faceti in continuare?" << endl;
			}
			else if (n == 2){
				string prenumeNou;
				cout << "Introduceti prenume nou: ";
				cin.get();
				getline(cin, prenumeNou);
				this->client[index].setPrenume(prenumeNou);
				cout << "Prenumele a fost actualizat." << endl;
				cout << endl;
				cout << "Ce doriti sa faceti in continuare?" << endl;
			}
			else if (n == 3){
				int varstaNoua;
				cout << "Introduceti varsta noua: ";
				cin >> varstaNoua;
				this->client[index].setVarsta(varstaNoua);
				cout << "Varsta a fost actualizata." << endl;
				cout << endl;
				cout << "Ce doriti sa faceti in continuare?" << endl;
			}
			else if (n == 4){
				string telefonNou;
				cout << "Introduceti telefon nou: ";
				cin.get();
				getline(cin, telefonNou);
				this->client[index].setTelString(telefonNou);
				cout << "Nr de telefon a fost actualizat." << endl;
				cout << endl;
				cout << "Ce doriti sa faceti in continuare?" << endl;
			}
			else if (n == 5){
				string adresaNoua;
				cout << "Introduceti adresa noua: ";
				cin.get();
				getline(cin, adresaNoua);
				this->client[index].setAdresa(adresaNoua.c_str());
				cout << "Adresa a fost actualizata." << endl;
				cout << endl;
				cout << "Ce doriti sa faceti in continuare?" << endl;
			}
			else if (n == 6) {
				string emailNou;
				cout << "Introduceti email nou: ";
				cin.get();
				getline(cin, emailNou);
				this->client[index].setEmail(emailNou);
				cout << "Email-ul a fost actualizat." << endl;
				cout << endl;
				cout << "Ce doriti sa faceti in continuare?" << endl;
			}
			cin >> n;
		}
		
	}
};

class Hotel {
private:
	string denumire;
	string adresa;
	string telefon;
	int nrStele;
	char* servicii;
	static float discountDeSezon;
	float costCamera[5];

public:
	// constructor default
	Hotel() {
		this->denumire = "";
		this->adresa = "";
		this->telefon = "";
		this->nrStele = 0;
		this->servicii = NULL;
		for (int i = 0; i < 5; ++i)
			costCamera[i] = 0;
	}

	// constructori cu parametri
	Hotel(string denumire, string adresa, string telefon, int nrStele, const char* servicii, float costCamera[5]) {
		this->denumire = denumire;
		this->adresa = adresa;
		this->telefon = telefon;
		this->nrStele = nrStele;
		this->servicii = new char[strlen(servicii) + 1];
		strcpy(this->servicii, servicii);
		for (int i = 0; i < 5; i++) {
			this->costCamera[i] = costCamera[i];
		}
	}

	Hotel(string denumire, string adresa, string telefon, const char* servicii, float costCamera[5]) {
		this->denumire = denumire;
		this->adresa = adresa;
		this->telefon = telefon;
		this->nrStele = 4;
		this->servicii = new char[strlen(servicii) + 1];
		strcpy(this->servicii, servicii);
		for (int i = 0; i < 5; i++) {
			this->costCamera[i] = costCamera[i];
		}
	}

	// constructor de copiere
	Hotel(const Hotel& c) {
		this->denumire = c.denumire;
		this->adresa = c.adresa;
		this->telefon = c.telefon;
		this->nrStele = c.nrStele;
		if (c.servicii)
		{
			this->servicii = new char[strlen(c.servicii) + 1];
			strcpy(this->servicii, c.servicii);
		}
		else
			this->servicii = NULL;

		for (int i = 0; i < 5; i++) {
			this->costCamera[i] = c.costCamera[i];
		}
	}

	// operator =
	Hotel& operator=(const Hotel& c) {
		this->denumire = c.denumire;
		this->adresa = c.adresa;
		this->telefon = c.telefon;
		this->nrStele = c.nrStele;
		if (this->servicii != NULL) {
			delete[] this->servicii;
		}
		if (c.servicii)
		{
			this->servicii = new char[strlen(c.servicii) + 1];
			strcpy(this->servicii, c.servicii);
		}
		else
			this->servicii = NULL;
		for (int i = 0; i < 5; i++) {
			this->costCamera[i] = c.costCamera[i];
		}
		return *this;
	}

	// getteri si setteri (+ exceptii)
	string getDenumire() {
		return denumire;
	}
	string getAdresa() {
		return adresa;
	}
	string getTelefon() {
		return telefon;
	}
	int getNrStele() {
		return nrStele;
	}
	char* getServicii() {
		return servicii;
	}
	float getCostCamera(int i) {
		return costCamera[i];
	}

	void setDenumire(string denumire) {
		if (denumire.length() < 1)
			throw "Denumire invalida.";
		else
			this->denumire = denumire;
	}
	void setAdresa(string adresa) {
		if (adresa.length() < 1)
			throw "Adresa invalida.";
		else
			this->adresa = adresa;
	}
	void setTelefon(string telefon) {
		if (telefon.length() < 1)
			throw "Nr Telefon invalid.";
		else
			this->telefon = telefon;
	}
	void setNrStele(int nrStele) {
		if (nrStele < 1)
			throw "Nr stele invalid.";
		else
			this->nrStele = nrStele;
	}
	void setServicii(const char* servicii) {
		if (this->servicii != NULL)
		{
			delete[]this->servicii;
		}
		if (strlen(servicii) < 1) {
			throw "Servicii invalide.";
		}
		this->servicii = new char[strlen(servicii) + 1];
		strcpy(this->servicii, servicii);

	}
	void setCostCamera(float costCamera[5]) {
		for (int i = 0; i < 5; i++) {
			this->costCamera[i] = costCamera[i];
		}
	}

	// destructor
	~Hotel() {
		if (this->servicii)
			delete[] this->servicii;
	}

	//supraincarcare << si >>
	friend istream& operator>>(istream& input, Hotel& H) {
		cout << "Introduceti denumirea hotelului " << endl;
		input >> H.denumire;
		cout << "Introduceti adresa hotelului " << endl;
		input >> H.adresa;
		cout << "Introduceti numarul de contact al hotelului " << endl;
		input >> H.telefon;
		cout << "Introduceti numarul de stele al hotelului " << endl;
		input >> H.nrStele;
		cout << "Introduceti serviciile " << endl;
		if (H.servicii) {
			delete[]H.servicii;
		}
		char buffer[100];
		input >> buffer;
		H.servicii = new char[strlen(buffer) + 1];
		strcpy(H.servicii, buffer);
		for (int i = 0; i < 5; i++) {
			cout << "Introduceti costul camerei " << i << endl;
			input >> H.costCamera[i];
		}
		return input;
	}

	friend ostream& operator<<(ostream& output, const Hotel& H) {
		output << "Hotelul se numeste " << H.denumire << ".";
		output << "Este situat in " << H.adresa << "." << endl;
		output << "Numarul de contact al hotelului este " << H.telefon << "." << endl;
		output << "Hotelul are " << H.nrStele << " stele." << endl;
		if (H.servicii)
		{
			output << "Hotelul dispune de urmatoarele servicii: " << H.servicii << "." << endl;
		}
		for (int i = 0; i < 5; i++)
			output << "Costul camerei " << i << " este " << H.costCamera[i] << " lei/noapte." << endl;
		return output;
	}

	// operatorul + (adauga stele)
	Hotel operator+(float nrStele) {
		Hotel copie(*this);
		copie.nrStele = copie.nrStele + nrStele;
		return copie;
	}

	// operatorul - (scade stele)
	Hotel operator-(float nrStele) {
		Hotel copie(*this);
		copie.nrStele = copie.nrStele - nrStele;
		return copie;
	}

	// operatorul == (compara numarul de stele a doua hoteluri)
	bool operator==(float nrStele) {
		return this->nrStele = nrStele;
	}

	//operatorul ==
	bool operator ==(Hotel h) {
		return this->denumire == h.denumire;
	}

	//functie de afisare
	void show() {
		cout << "Hotelul se numeste " << denumire << "." << endl;
		cout << "Este situat in " << adresa << "." << endl;
		cout << "Numarul de contact al hotelului este " << telefon << "." << endl;
		cout << "Hotelul are " << nrStele << " stele." << endl;
		cout << "Hotelul dispune de urmatoarele servicii: " << servicii << "." << endl;
		for (int i = 0; i < 5; i++) {
			cout << "Costul camerei " << i << " este " << costCamera[i] << " lei/noapte." << endl;
		}
		cout << endl;
	}

	//functie de calculare a mediei preturilor camerelor
	float pretMediuCamere() {
		float suma = 0;
		for (int i = 0; i < 5; i++)
			suma = suma + this->costCamera[i];
		return suma / 5;
	}

	//scriere in txt
	void scrieTxt(fstream& fisier) {
		fisier << denumire << "\n";
		fisier << adresa << "\n";
		fisier << telefon << "\n";
		fisier << nrStele << "\n";

		if (servicii)
		{
			fisier << servicii << "\n";
		}
		else
		{
			cout << "\n";
		}
		for (int i = 0; i < 5; i++)
			fisier << costCamera[i] << "\n";
	}

	//citire din txt
	void citesteTxt(fstream& fisier) {
		getline(fisier, denumire);
		getline(fisier, adresa);
		getline(fisier, telefon);
		fisier >> nrStele;
		fisier.get();

		string ser;
		getline(fisier, ser);
		if (ser.empty())
			servicii = NULL;
		else {
			servicii = new char[ser.size() + 1];
			strcpy(servicii, ser.c_str());
		}

		for (int i = 0; i < 5; i++)
			fisier >> costCamera[i];
		fisier.get();
	}

	//scriere in fisier binar
	void scrieInBinar(fstream& fisier) {
		int lungimeSir = denumire.size() + 1;
		fisier.write((const char*)&lungimeSir, sizeof(int));
		fisier.write((const char*)denumire.c_str(), sizeof(char) * lungimeSir);

		lungimeSir = adresa.size() + 1;
		fisier.write((const char*)&lungimeSir, sizeof(int));
		fisier.write((const char*)adresa.c_str(), sizeof(char) * lungimeSir);


		lungimeSir = telefon.size() + 1;
		fisier.write((const char*)&lungimeSir, sizeof(int));
		fisier.write((const char*)telefon.c_str(), sizeof(char) * lungimeSir);

		if (servicii)
		{
			lungimeSir = strlen(servicii) + 1;
			fisier.write((const char*)&lungimeSir, sizeof(int));
			fisier.write((const char*)servicii, sizeof(char) * lungimeSir);
		}
		else
		{
			lungimeSir = 0;
			fisier.write((const char*)&lungimeSir, sizeof(int));
		}

		fisier.write((const char*)&nrStele, sizeof(int));

		fisier.write((const char*)costCamera, sizeof(int) * 5);

	}

	//citire in fisier binar
	void citesteDinBinar(fstream& fisier) {
		int lungimeSir = 0;
		char buffer[100]{};

		fisier.read((char*)&lungimeSir, sizeof(int));
		fisier.read((char*)buffer, sizeof(char) * lungimeSir);
		denumire = buffer;

		fisier.read((char*)&lungimeSir, sizeof(int));
		fisier.read((char*)buffer, sizeof(char) * lungimeSir);
		adresa = buffer;


		fisier.read((char*)&lungimeSir, sizeof(int));
		fisier.read((char*)buffer, sizeof(char) * lungimeSir);
		telefon = buffer;

		if (servicii)
			delete[] servicii;

		fisier.read((char*)&lungimeSir, sizeof(int));

		if (lungimeSir == 0)
			servicii = NULL;
		else
		{
			fisier.read((char*)buffer, sizeof(char) * lungimeSir);
			servicii = new char[strlen(buffer) + 1];
			strcpy(servicii, buffer);
		}

		fisier.read((char*)&nrStele, sizeof(int));

		fisier.read((char*)&costCamera, sizeof(float) * 5);
	}
};
float Hotel::discountDeSezon = 15.45;

class RegistruHoteluri {
private:
	Hotel* hotel;
	int nrHoteluri;

public:
	//constructor default
	RegistruHoteluri() {
		this->hotel = NULL;
		this->nrHoteluri = 0;
	}

	//constructori cu parametrii
	RegistruHoteluri(Hotel* hotel, int nrHoteluri) {
		this->nrHoteluri = nrHoteluri;
		this->hotel = new Hotel[nrHoteluri];
		for (int i = 0; i < nrHoteluri; i++) {
			this->hotel[i] = hotel[i];
		}
	}

	//constructor de copiere
	RegistruHoteluri(const RegistruHoteluri& c) {
		this->nrHoteluri = c.nrHoteluri;
		this->hotel = new Hotel[c.nrHoteluri];
		for (int i = 0; i < c.nrHoteluri; i++) {
			this->hotel[i] = c.hotel[i];
		}
	}

	//operator =
	RegistruHoteluri& operator=(const RegistruHoteluri& c) {
		this->nrHoteluri = c.nrHoteluri;
		this->hotel = new Hotel[c.nrHoteluri];
		for (int i = 0; i < c.nrHoteluri; i++) {
			this->hotel[i] = c.hotel[i];
		}
		return *this;
	}

	//getteri si setteri
	int getNrHoteluri() {
		return this->nrHoteluri;
	}

	void setNrHoteluri(int nrHoteluri) {
		if (nrHoteluri < 1) {
			throw "Nr hoteluri invalid.";
		}
		this->nrHoteluri = nrHoteluri;
	}

	//operatorii >> si <<
	friend istream& operator >> (istream& intrare, RegistruHoteluri& c) {
		cout << "Introduceti nr de hoteluri : ";
		intrare >> c.nrHoteluri;
		cout << endl;
	}

	friend ostream& operator <<(ostream& iesire, RegistruHoteluri& c) {
		cout << "Nr de hoteluri : ";
		iesire << c.nrHoteluri;
		cout << endl;
		for (int i = 0; i < c.nrHoteluri; i++) {
			cout << "Hotelul cu nr " << i << " : ";
			iesire << c.hotel[i] << endl;
		}
		return iesire;
	}
	
	//functie de adaugare hotel
	void adaugareHotel(Hotel H) {
		Hotel* aux = new Hotel[this->nrHoteluri + 1];
		for (int i = 0; i < this->nrHoteluri; ++i)
			aux[i] = this->hotel[i];

		aux[this->nrHoteluri] = H;
		this->nrHoteluri++;

		if (this->hotel != NULL)
			delete[] this->hotel;

		this->hotel = aux;
	}

	//functie de scriere in fisier txt
	void scrieInFisier()
	{
		fstream f("registru_hoteluri.txt", ios::out);

		f << this->nrHoteluri << '\n';
		for (int i = 0; i < this->nrHoteluri; ++i)
			this->hotel[i].scrieTxt(f);

		f.close();
	}

	//functie de citire din fisier txt
	void citesteDinFisier() {
		fstream f("registru_hoteluri.txt", ios::in);

		f >> this->nrHoteluri;
		f.get();
		this->hotel = new Hotel[this->nrHoteluri];
		for (int i = 0; i < this->nrHoteluri; ++i)
			this->hotel[i].citesteTxt(f);

		f.close();
	}

	//functie de stergere a unui hotel cautat dupa denumire
	void stergeHotel(string numeHotel) {
		if (this->nrHoteluri == 0)
			throw "Nu exista hoteluri.";

		int index = -1;
		for (int i = 0; i < this->nrHoteluri; ++i)
			if (this->hotel[i].getDenumire() == numeHotel)
			{
				index = i;
				break;
			}

		if (index == -1)
			throw "Hotelul nu exista";

		Hotel* hotelNou = new Hotel[this->nrHoteluri - 1];
		for (int i = 0; i < index; ++i)
			hotelNou[i] = this->hotel[i];

		for (int i = index + 1; i < this->nrHoteluri; ++i)
			hotelNou[i - 1] = this->hotel[i];

		this->nrHoteluri--;
		delete[] this->hotel;
		this->hotel = hotelNou;
	}

	//functie de actualizare a informatiilor unui hotel cautat dupa denumire
		void actualizeazaHotel(string numeHotel)
		{
			int index = -1;
			for (int i = 0; i < this->nrHoteluri; ++i)
				if (this->hotel[i].getDenumire() == numeHotel)
				{
					index = i;
					break;
				}

			if (index == -1)
				throw "Hotelul nu exista";

			//meniu de comenzi pentru actualizarea informatiilor hotelului
			cout << "Introduceti de la tastatura : " << endl;
			cout << "~ Numarul '7' pentru a accesa meniul de comenzi." << endl;
			cout << "~ Numarul '1' pentru a actualiza denumire." << endl;
			cout << "~ Numarul '2' pentru a actualiza adresa." << endl;
			cout << "~ Numarul '3' pentru a actualiza nr de telefon." << endl;
			cout << "~ Numarul '4' pentru a actualiza nr de stele." << endl;
			cout << "~ Numarul '5' pentru a actualiza serviciile." << endl;
			cout << "~ Numarul '6' pentru a actualiza costul camerelor." << endl;
			cout << "~ Numarul '0' pentru a iesi din optiunea de actualizare." << endl;

			cout << endl;
			cout << "Alegeti o optiune." << endl;

			int n;
			cin >> n;
			while (n != 0) {
				if (n < 0 || n>7) {
					cout << "Numar comanda invalid." << endl;
				}

				if (n == 7) {
					cout << "Introduceti de la tastatura : " << endl;
					cout << "~ Numarul '7' pentru a accesa meniul de comenzi." << endl;
					cout << "~ Numarul '1' pentru a actualiza denumire." << endl;
					cout << "~ Numarul '2' pentru a actualiza adresa." << endl;
					cout << "~ Numarul '3' pentru a actualiza nr de telefon." << endl;
					cout << "~ Numarul '4' pentru a actualiza nr de stele." << endl;
					cout << "~ Numarul '5' pentru a actualiza serviciile." << endl;
					cout << "~ Numarul '6' pentru a actualiza costul camerelor." << endl;
					cout << "~ Numarul '0' pentru a iesi din optiunea de actualizare." << endl;

					cout << endl;
					cout << "Ce doriti sa faceti in continuare?" << endl;
				}
				if (n == 1) {
					string denumireNoua;
					cout << "Introduceti o noua denumire: ";
					cin.get();
					getline(cin, denumireNoua);
					this->hotel[index].setDenumire(denumireNoua);
					cout << "Denumirea a fost actualizata." << endl;
					cout << endl;
					cout << "Ce doriti sa faceti in continuare?" << endl;
				}
				else if (n == 2) {
					string adresaNoua;
					cout << "Introduceti o noua adresa: ";
					cin.get();
					getline(cin, adresaNoua);
					this->hotel[index].setAdresa(adresaNoua);
					cout << "Adresa a fost actualizata." << endl;
					cout << endl;
					cout << "Ce doriti sa faceti in continuare?" << endl;
				}
				else if (n == 3) {
					string telefonNou;
					cout << "Introduceti un nr nou de telefon: ";
					cin.get();
					getline(cin, telefonNou);
					this->hotel[index].setTelefon(telefonNou);
					cout << "Nr de telefon a fost actualizat." << endl;
					cout << endl;
					cout << "Ce doriti sa faceti in continuare?" << endl;
				}
				else if (n == 4) {
					int nrSteleNou;
					cout << "Introduceti un nou nr de stele: ";
					cin >> nrSteleNou;
					this->hotel[index].setNrStele(nrSteleNou);
					cout << "Nr de stele a fost actualizat." << endl;
					cout << endl;
					cout << "Ce doriti sa faceti in continuare?" << endl;
				}
				else if (n == 5) {
					string serviciiNoi;
					cout << "Introduceti servicii noi: ";
					cin.get();
					getline(cin, serviciiNoi);
					this->hotel[index].setServicii(serviciiNoi.c_str());
					cout << "Serviciile au fost actualizate." << endl;
					cout << endl;
					cout << "Ce doriti sa faceti in continuare?" << endl;
				}
				else if (n == 6) {
					float costCameraNou[5];
					for (int i = 0; i < 5; i++) {
						cout << "Introduceti un nou cost pentru camera cu nr " << i << " : ";
						cin >> costCameraNou[i];
						cout << endl;
					}
					this->hotel[index].setCostCamera(costCameraNou);

					cout << "Costul camerelor a fost actualizat." << endl;
					cout << endl;
					cout << "Ce doriti sa faceti in continuare?" << endl;
				}
				cin >> n;
			}
	}
};


class ObiectiveTuristice {
private:
	char* denumire;
	string localizare;
	string oraDeschidere;
	string oraInchidere;
	float pretBilet; 
	
public:
	// constructor default
	ObiectiveTuristice() {
		this->denumire = NULL;
		this->localizare = "";
		this->oraDeschidere = "";
		this->oraInchidere = " ";
		this->pretBilet = 0;
	}

	// constructori cu parametri
	ObiectiveTuristice(const char* denumire, string localizare, string oraDeschidere, string oraInchidere, float pretBilet) {
		this->denumire = new char[strlen(denumire) + 1];
		strcpy(this->denumire, denumire);
		this->localizare = localizare;
		this->oraDeschidere = oraDeschidere;
		this->oraInchidere = oraInchidere;
		this->pretBilet = pretBilet;
	}

	ObiectiveTuristice(string oraDeschidere, string oraInchidere) {
		this->oraDeschidere = oraDeschidere;
		this->oraInchidere = oraInchidere;
		this->denumire = NULL;
		this->localizare = "";
		this->pretBilet = 0;
	}

	// constructor de copiere
	ObiectiveTuristice(const ObiectiveTuristice& c) {
		if (c.denumire) {
			this->denumire = new char[strlen(c.denumire) + 1];
			strcpy(this->denumire, c.denumire);
		}
		else
			this->denumire = NULL;

		this->localizare = c.localizare;
		this->oraDeschidere = c.oraDeschidere;
		this->oraInchidere = c.oraInchidere;
		this->pretBilet = c.pretBilet;
	}

	// operatorul =
	ObiectiveTuristice& operator = (const ObiectiveTuristice& c) {
		if (this == &c)
			return *this;
		if (this->denumire != NULL) {
			delete[]this->denumire;
		}
		if (c.denumire) {
			this->denumire = new char[strlen(c.denumire) + 1];
			strcpy(this->denumire, c.denumire);
		}
		else {
			this->denumire = NULL;
		}

		this->localizare = c.localizare;
		this->oraDeschidere = c.oraDeschidere;
		this->oraInchidere = c.oraInchidere;
		this->pretBilet = c.pretBilet;
		return *this;
	}

	// operatorii >> si <<
	friend istream& operator >> (istream& intrare, ObiectiveTuristice& s) {
		cout << "Localizare:";
		intrare >> s.localizare;
		cout << "Ora Deschidere:";
		intrare >> s.oraDeschidere;
		cout << "Ora inchidere:";
		intrare >> s.oraInchidere;
		cout << "Pret bilet:";
		intrare >> s.pretBilet;
		cout << "Denumire obiectiv:";
		if (s.denumire) {
			delete[]s.denumire;
		}
		intrare.get();
		char buffer[100];
		intrare >> buffer;
		s.denumire = new char[strlen(buffer) + 1];
		strcpy(s.denumire, buffer);
		return intrare;
	}

	friend ostream& operator << (ostream& iesire, ObiectiveTuristice& s) {
		cout << "Denumire obiectiv:";
		if (s.denumire)
			iesire << s.denumire << endl;
		cout << "Localizare:";
		iesire << s.localizare << endl;
		cout << "Ora deschidere:";
		iesire << s.oraDeschidere << endl;
		cout << "Ora inchidere:";
		iesire << s.oraInchidere << endl;
		cout << "Pret bilet:";
		iesire << s.pretBilet << endl;
		return iesire;
	}

	// getteri si setteri
	const char* getDenumire() {

		return this->denumire;
	}
	void setDenumire(const char* denumire) {
		if (strlen(denumire) < 1) {
			throw "nu ati introdus denumirea";
		}
		if (this->denumire != NULL) {
			delete[]this->denumire;
		}
		this->denumire = new char[strlen(denumire) + 1];
		strcpy(this->denumire, denumire);
	}
	string getLocalizare() {

		return this->localizare;
	}
	void setLocalizare(string localizare) {
		if (localizare.length() < 1) {
			throw "nu ati introdus locatia";
		}
		else
			this->localizare = localizare;
	}
	string getOraDeschidere() {

		return this->oraDeschidere;
	}
	void setOraDeschidere(string oraDeschidere) {
		if (oraDeschidere.length() < 1) {
			throw "nu ati introdus ora deschiderii";
		}
		else
			this->oraDeschidere = oraDeschidere;
	}
	string getOraInchidere() {

		return this->oraInchidere;
	}
	void setOraInchidere(string oraInchidere) {
		if (oraInchidere.length() < 1) {
			throw "nu ati introdus ora inchiderii";
		}
		else
			this->oraInchidere = oraInchidere;
	}
	float getPretBilet() {

		return this->pretBilet;
	}
	void setPretBilet(float pretBilet) {
		if (pretBilet < 0) {
			throw "nu ati introdus o valoare valida";
		}
		else
			this->pretBilet = pretBilet;
	}

	// destructor
	~ObiectiveTuristice() {
		if (this->denumire) {
			delete[]this->denumire;
		}
	}

	// operatorul + (crestem pretul biletului)
	ObiectiveTuristice operator +(float pretBilet) {
		ObiectiveTuristice copie(*this);
		copie.pretBilet = copie.pretBilet + pretBilet;
		return copie;
	}

	// operatorul - (reducem pretul biletului)
	ObiectiveTuristice operator-(float pretBilet) {
		ObiectiveTuristice copie(*this);
		copie.pretBilet = copie.pretBilet - pretBilet;
		return copie;
	}

	//operatorul >= (comparam preturile a doua bilete)
	bool operator >=(ObiectiveTuristice c) {
		return this->pretBilet >= c.pretBilet;
	}

	float majorare(float x) {
		pretBilet = pretBilet + pretBilet * x;
		return pretBilet;
	}

	float reducere(float y) {
		pretBilet = pretBilet - pretBilet * y;
		return pretBilet;
	}

	//scriere in fisier binar
	void scrieInBinar(std::fstream& fisier)
	{


		int lungimeSir = localizare.size() + 1;
		fisier.write((const char*)&lungimeSir, sizeof(int));
		fisier.write((const char*)localizare.c_str(), sizeof(char) * lungimeSir);

		lungimeSir = oraDeschidere.size() + 1;
		fisier.write((const char*)&lungimeSir, sizeof(int));
		fisier.write((const char*)oraDeschidere.c_str(), sizeof(char) * lungimeSir);


		lungimeSir = oraInchidere.size() + 1;
		fisier.write((const char*)&lungimeSir, sizeof(int));
		fisier.write((const char*)oraInchidere.c_str(), sizeof(char) * lungimeSir);

		if (denumire)
		{
			lungimeSir = strlen(denumire) + 1;
			fisier.write((const char*)&lungimeSir, sizeof(int));
			fisier.write((const char*)denumire, sizeof(char) * lungimeSir);
		}
		else
		{
			lungimeSir = 0;
			fisier.write((const char*)&lungimeSir, sizeof(int));
		}


		fisier.write((const char*)&pretBilet, sizeof(float));


	}

	//citire din fisier binar
	void citesteInBinar(std::fstream& fisier)
	{
		int lungimeSir = 0;
		char buffer[100]{};

		fisier.read((char*)&lungimeSir, sizeof(int));
		fisier.read((char*)buffer, sizeof(char) * lungimeSir);
		localizare = buffer;

		fisier.read((char*)&lungimeSir, sizeof(int));
		fisier.read((char*)buffer, sizeof(char) * lungimeSir);
		oraDeschidere = buffer;


		fisier.read((char*)&lungimeSir, sizeof(int));
		fisier.read((char*)buffer, sizeof(char) * lungimeSir);
		oraInchidere = buffer;

		if (denumire)
			delete[] denumire;

		fisier.read((char*)&lungimeSir, sizeof(int));

		if (lungimeSir == 0)
			denumire = NULL;
		else
		{
			fisier.read((char*)buffer, sizeof(char) * lungimeSir);
			denumire = new char[strlen(buffer) + 1];
			strcpy(denumire, buffer);
		}

		fisier.read((char*)&pretBilet, sizeof(float));

	}
};

class Rezervare {
private:
	string zonaGeografica;
	int perioada;
	int nrPersoane;
	string regimCazare;
	Hotel* hotel;
	Client* client;
	int nrObiective;
	ObiectiveTuristice* obiectiveTuristice;
	int nrCamereRezervate;
	int camereRezervate[100];
public:
	// constructor default
	Rezervare() {
		this->zonaGeografica = "";
		this->perioada = 0;
		this->nrPersoane = 0;
		this->regimCazare = "";
		this->hotel = NULL;
		this->client = NULL;
		this->nrObiective = 0;
		this->obiectiveTuristice = NULL;
		this->nrCamereRezervate = 0;
		for (int i = 0; i < 100; i++)
			this->camereRezervate[i] = 0;
	}

	// constructor cu toti parametrii + cu x parametrii
	Rezervare(string zonaGeografica, int perioada, int nrPersoane, string regimCazare, Hotel* hotel, Client* client, int nrObiective,
		ObiectiveTuristice* obiectiveTuristice, int nrCamereRezervate, int camereRezervate[100]) {

		this->zonaGeografica = zonaGeografica;
		this->perioada = perioada;
		this->nrPersoane = nrPersoane;
		this->regimCazare = regimCazare;
		this->hotel = hotel;
		this->client = client;
		this->nrObiective = nrObiective;
		this->obiectiveTuristice = new ObiectiveTuristice[nrObiective];
		for (int i = 0; i < nrObiective; i++) {
			this->obiectiveTuristice[i] = obiectiveTuristice[i];
		}
		this->nrCamereRezervate = nrCamereRezervate;
		for (int i = 0; i < 100; i++)
			this->camereRezervate[i] = camereRezervate[i];
	}

	Rezervare(int perioada, int nrPersoane, string regimCazare, Hotel* hotel, Client* client, int nrObiective,
		ObiectiveTuristice* obiectiveTuristice, int nrCamereRezervate, int camereRezervate[100]) {

		this->zonaGeografica = "Sud";
		this->perioada = perioada;
		this->nrPersoane = nrPersoane;
		this->regimCazare = regimCazare;
		this->hotel = hotel;
		this->client = client;
		this->nrObiective = nrObiective;
		this->obiectiveTuristice = new ObiectiveTuristice[nrObiective];
		for (int i = 0; i < nrObiective; i++) {
			this->obiectiveTuristice[i] = obiectiveTuristice[i];
		}
		this->nrCamereRezervate = nrCamereRezervate;
		for (int i = 0; i < 100; i++)
			this->camereRezervate[i] = camereRezervate[i];
	}

	// constructor de copiere
	Rezervare(const Rezervare& c) {
		this->zonaGeografica = c.zonaGeografica;
		this->perioada = c.perioada;
		this->nrPersoane = c.nrPersoane;
		this->regimCazare = c.regimCazare;
		this->hotel = new Hotel;
		this->client = new Client;
		this->nrObiective = c.nrObiective;
		this->obiectiveTuristice = new ObiectiveTuristice[c.nrObiective];
		for (int i = 0; i < c.nrObiective; i++) {
			this->obiectiveTuristice[i] = c.obiectiveTuristice[i];
		}
		this->nrCamereRezervate = c.nrCamereRezervate;
		for (int i = 0; i < c.nrCamereRezervate; i++)
			this->camereRezervate[i] = c.camereRezervate[i];
	}

	// operator =
	Rezervare& operator=(const Rezervare& c) {
		this->zonaGeografica = c.zonaGeografica;
		this->perioada = c.perioada;
		this->nrPersoane = c.nrPersoane;
		this->regimCazare = c.regimCazare;
		this->hotel = new Hotel;
		this->client = new Client;
		this->nrObiective = c.nrObiective;
		this->obiectiveTuristice = new ObiectiveTuristice[c.nrObiective];
		for (int i = 0; i < c.nrObiective; i++) {
			this->obiectiveTuristice[i] = c.obiectiveTuristice[i];
		}
		this->nrCamereRezervate = c.nrCamereRezervate;
		for (int i = 0; i < c.nrCamereRezervate; i++)
			this->camereRezervate[i] = c.camereRezervate[i];
		return *this;
	}

	// getteri si setteri (+ exceptii)
	string getZonaGeografica() {
		return zonaGeografica;
	}
	int getPerioada() {
		return perioada;
	}
	int getNrPersoane() {
		return nrPersoane;
	}
	string getRegimCazare() {
		return regimCazare;
	}
	int getNrObiectiveTuristice() {
		return nrObiective;
	}
	int getNrCamereRezervate() {
		return nrCamereRezervate;
	}
	int getCamereRezervate(int i) {
		if (i >= 0 && i < 100)
			return camereRezervate[i];
		else
			throw "Index invalid.";
	}

	void setZonaGeografica(string zonaGeografica) {
		if (zonaGeografica.length() < 1)
			throw "Zona Geografica invalida";
		else
			this->zonaGeografica = zonaGeografica;
	}
	void setPerioada(int perioada) {
		if (perioada < 1)
			throw "Prioada invalida";
		else
			this->perioada = perioada;
	}
	void setNrPersoane(int nrPersoane) {
		if (nrPersoane < 1)
			throw "Nr Persoane invalid";
		else
			this->nrPersoane = nrPersoane;
	}
	void setRegimCazare(string regimCazare) {
		if (regimCazare.length() < 1)
			throw "Regim Cazare invalid";
		else
			this->regimCazare = regimCazare;
	}
	void setNrObiective(int nrObiective) {
		if (nrObiective < 1)
			throw "Nr Obiective invalid";
		else
			this->nrObiective = nrObiective;
	}
	void setNrCamereRezervate(int nrCamereRezervate) {
		if (nrCamereRezervate < 1)
			throw "Nr Camere Rezervate invalid";
		else
			this->nrCamereRezervate = nrCamereRezervate;
	}
	void setCamereRezervate(int camereRezervate[100]) {
		for (int i = 0; i < 100; i++)
			this->camereRezervate[i] = camereRezervate[i];
	}

	// operatori >> si <<
	friend istream& operator >> (istream& intrare, Rezervare& r) {
		cout << "Introduceti zona geografica." << endl;
		intrare >> r.zonaGeografica;
		cout << "Introduceti perioada." << endl;
		intrare >> r.perioada;
		cout << "Introduceti numarul de persoane." << endl;
		intrare >> r.nrPersoane;
		cout << "Introduceti regimul de cazare." << endl;
		intrare >> r.regimCazare;
		cout << "Introduceti numarul de obiective turistice." << endl;
		intrare >> r.nrObiective;
		cout << "Introduceti numarul de camere rezervate." << endl;
		intrare >> r.nrCamereRezervate;
		for (int i = 0; i < r.nrCamereRezervate; i++) {
			cout << "Introduceti numarul camerei rezervate." << endl;
			intrare >> r.camereRezervate[i];
		}
		return intrare;
	}
	friend ostream& operator<<(ostream& output, const Rezervare& r) {
		cout << "Zona geografica : ";
		output << r.zonaGeografica;
		cout << endl;
		cout << "Perioada : ";
		output << r.perioada;
		cout << endl;
		cout << "Nr persoane : ";
		output << r.nrPersoane;
		cout << endl;
		cout << "Regim cazare : ";
		output << r.regimCazare;
		cout << endl;
		cout << "Hotel : ";
		output << *r.hotel;
		cout << endl;
		cout << "Client : ";
		output << *r.client;
		cout << endl;
		cout << "Nr obiective : ";
		output << r.nrObiective;
		cout << endl;
		for (int i = 0; i < r.nrObiective; i++) {
			cout << "Obiectivul turistic nr " << i << ": ";
			output << r.obiectiveTuristice << endl;
		}
		cout << "Nr camere rezervate : ";
		output << r.nrCamereRezervate;
		cout << endl;
		for (int i = 0; i < r.nrCamereRezervate; i++) {
			cout << "Este rezervata camera cu nr ";
			output << r.camereRezervate[i];
			cout << endl;
		}
		return output;
	}

	// operatorul + (adauga persoane la nrPersoane)
	Rezervare operator+(int nrPersoane) {
		Rezervare copie(*this);
		copie.nrPersoane = copie.nrPersoane + nrPersoane;
		return copie;
	}

	// operatorul - (reduce nrPersoane)
	Rezervare operator-(int nrPersoane) {
		Rezervare copie(*this);
		copie.nrPersoane = copie.nrPersoane - nrPersoane;
		return copie;
	}

	//// operatorul []
	//Rezervare operator[](int index) {
	//	if (index < this->nrObiective) {
	//		return this->obiectiveTuristice[index];
	//	}
	//}

	//scriere in fisier binar
	void scrieInBinar(std::fstream& fisier) {


		int lungimeSir = zonaGeografica.size() + 1;
		fisier.write((const char*)&lungimeSir, sizeof(int));
		fisier.write((const char*)zonaGeografica.c_str(), sizeof(char) * lungimeSir);

		lungimeSir = regimCazare.size() + 1;
		fisier.write((const char*)&lungimeSir, sizeof(int));
		fisier.write((const char*)regimCazare.c_str(), sizeof(char) * lungimeSir);

		fisier.write((const char*)&perioada, sizeof(int));
		fisier.write((const char*)&nrPersoane, sizeof(int));
		fisier.write((const char*)&nrObiective, sizeof(float));
		fisier.write((const char*)&nrCamereRezervate, sizeof(int));
		fisier.write((const char*)&camereRezervate, sizeof(float));

	}

	//citire din fisier binar
	void citesteDinBinar(std::fstream& fisier)
	{
		int lungimeSir = 0;
		char buffer[100]{};

		fisier.read((char*)&lungimeSir, sizeof(int));
		fisier.read((char*)buffer, sizeof(char) * lungimeSir);
		zonaGeografica = buffer;

		fisier.read((char*)&lungimeSir, sizeof(int));
		fisier.read((char*)buffer, sizeof(char) * lungimeSir);
		regimCazare = buffer;

		fisier.read((char*)&perioada, sizeof(int));
		fisier.read((char*)&nrPersoane, sizeof(int));
		fisier.read((char*)&nrObiective, sizeof(int));
		fisier.read((char*)&nrCamereRezervate, sizeof(int));
		fisier.read((char*)&camereRezervate, sizeof(int) * 100);
	}
};

int main() {
	//IMPLEMENTARE METODE FAZA FINALA
	cout << "Acest program reprezinta o baza de date a unui site de booking." << endl;
	cout << "Introduceti de la tastatura : " << endl;

	cout << "~ Numarul '9' pentru a accesa meniul de comenzi." << endl;

	cout << "~ Numarul '1' pentru a adauga un nou client." << endl;
	cout << "~ Numarul '2' pentru a adauga un nou hotel." << endl;

	cout << "~ Numarul '3' pentru a actualiza informatiile unui client." << endl;
	cout << "~ Numarul '4' pentru a actualiza informatiile unui hotel." << endl;

	cout << "~ Numarul '5' pentru a sterge un client." << endl;
	cout << "~ Numarul '6' pentru a sterge un hotel." << endl;

	cout << "~ Numarul '7' pentru a afisa un raport al tuturor clientilor existenti." << endl;
	cout << "~ Numarul '8' pentru a afisa un raport al tuturor hotelurilor existente." << endl;

	cout << "~ Numarul '0' pentru a iesi din meniu." << endl;

	cout << endl;
	cout << "Alegeti o optiune." << endl;

	RegistruClienti rc;
	rc.citesteDinFisier();

	RegistruHoteluri rh;
	rh.citesteDinFisier();
	string nume;
	int n;
	cin >> n;
	while (n != 0) {
		if (n == 9) {
			cout << "Acest program reprezinta o baza de date a unui site de booking." << endl;
			cout << "Introduceti de la tastatura : " << endl;

			cout << "~ Numarul '9' pentru a accesa meniul de comenzi." << endl;

			cout << "~ Numarul '1' pentru a adauga un nou client." << endl;
			cout << "~ Numarul '2' pentru a adauga un nou hotel." << endl;

			cout << "~ Numarul '3' pentru a actualiza informatiile unui client." << endl;
			cout << "~ Numarul '4' pentru a actualiza informatiile unui hotel." << endl;

			cout << "~ Numarul '5' pentru a sterge un client." << endl;
			cout << "~ Numarul '6' pentru a sterge un hotel." << endl;

			cout << "~ Numarul '7' pentru a afisa un raport al tuturor clientilor existenti." << endl;

			cout << "~ Numarul '8' pentru a afisa un raport al tuturor hotelurilor existente." << endl;

			cout << "~ Numarul '0' pentru a iesi din meniu." << endl;
		
			cout << endl;
			cout << "Alegeti o alta optiune." << endl;
			cout << endl;
		}

		if (n == 1) {
			cout << "Ati ales sa adaugati un nou client." << endl;
			Client C;
			cout << "Introduceti datele clientului." << endl;
			cin >> C;

			rc.adaugareClient(C);
			rc.scrieInFisier();
			cout << endl;
			cout << "Client adaugat." << endl;

			cout << endl;
			cout << "Alegeti o alta optiune." << endl;
			cout << endl;
		}

		if (n == 2) {
			cout << "Ati ales sa adaugati un nou hotel." << endl;
			Hotel H;
			cout << endl;
			cout << "Introduceti datele hotelului." << endl;
			cin >> H;
			cout << endl;

			rh.adaugareHotel(H);
			rh.scrieInFisier();
			cout << "Hotel adaugat";

			cout << endl;
			cout << "Alegeti o alta optiune." << endl;
			cout << endl;
		}

		if (n == 3) {
			cout << "Ati ales sa actualizati un client." << endl;
			cout << endl;
			cout << "Introduceti numele dupa care vreti sa efectuati cautarea." << endl;
			cout << endl;
			string nume;
			cin >> nume;
			rc.actualizeazaClient(nume);
			rc.scrieInFisier();
			cout << "Actualizare efectuata." << endl;
			cout << endl;
			cout << "Alegeti o alta optiune." << endl;
			cout << endl;
		}
		if (n == 4) {
			cout << "Ati ales sa actualizati un hotel." << endl;
			cout << endl;
			cout << "Introduceti denumirea hotelului dupa care vreti sa efectuati cautarea." << endl;
			string denumire;
			cin >> denumire;
			cout << endl;
			rh.actualizeazaHotel(denumire);
			rh.scrieInFisier();
			cout << "Actualizare efectuata." << endl;
			cout << endl;
			cout << "Alegeti o alta optiune." << endl;
			cout << endl;
		}
		if (n == 5) {
			cout << "Ati ales sa stergeti un client." << endl;
			cout << endl;
			cout << "Introduceti numele clientului pe care doriti sa-l stergeti." << endl;
			cout << endl;
			string nume;
			cin >> nume;
			rc.stergeClient(nume);
			rc.scrieInFisier();
			cout << "Client sters." << endl;
			cout << endl;
			cout << "Alegeti o alta optiune." << endl;
			cout << endl;
		}
		if (n == 6) {
			cout << "Ati ales sa stergeti un hotel." << endl;
			cout << endl;
			cout << "Introduceti denumirea hotelului pe care doriti sa-l stergeti." << endl;
			cout << endl;
			string denumire;
			cin >> denumire;
			rh.stergeHotel(denumire);
			rh.scrieInFisier();
			cout << "Hotel sters." << endl;
			cout << endl;
			cout << "Alegeti o alta optiune." << endl;
			cout << endl;
		}
		if (n == 7) {
			cout << "Ati ales sa afisati raportul tuturor clientilor inregistrati." << endl;
			RegistruClienti rc;
			rc.citesteDinFisier();
			cout << rc << '\n';
			system("pause");

			cout << endl;
			cout << "Alegeti o alta optiune." << endl;
			cout << endl;
		}
		if (n == 8) {
			cout << "Ati ales sa afisati raportul tuturor hotelurilor inregistrate." << endl;
			cout << endl;
			RegistruHoteluri rh;
			rh.citesteDinFisier();
			cout << rh << '\n';
			system("pause");

			cout << endl;
			cout << "Alegeti o alta optiune." << endl;
			cout << endl;
		}
		if (n < 0 || n>9) {
			cout << "Numar comanda invalid." << endl;
			cout << endl;
		}
		cin >> n;
	}
	cout << "Sfarsitul programului.";

	//TESTARE METODE FAZA ANTERIOARA
	////testare clasa client
	//char telefon[11] = "0720484545";
	//Client c1("Popescu", "Mihai", telefon, "p.mihai@yahoo.com", "Bucuresti", 14);
	//cout << c1;
	//cout << endl;
	//if (c1.minori()) {
	//	cout << "clentul are peste 18 ani";
	//}
	//else {

	//	cout << "clentul are sub 18 ani";
	//}

	//cout << endl;
	//if (c1.reducere(60)) {
	//	cout << "clentul poate beneficia de reducere";
	//}
	//else
	//{
	//	cout << "clentul nu poate beneficia de reducere";
	//}
	//cout << endl;

	//cout << "numele este:";
	//cout << c1.getNume() << endl;
	//cout << "prenumele este:";
	//cout << c1.getPrenume() << endl;
	//cout << "telefonul este:";
	//cout << c1.getTelefon() << endl;
	//cout << "Emailul este:";
	//cout << c1.getEmail() << endl;
	//cout << "adresa este:";
	//cout << c1.getAdresa() << endl;
	//cout << "varsta este:";
	//cout << c1.getVarsta() << endl;
	//cout << "introduceti datele personale:\n";

	//Client c2;
	//cin >> c2;
	//cout << c2;
	//try {
	//	c1.setNume("Dumitrescu");
	//}
	//catch (const char* exceptie) {
	//	cout << exceptie;
	//}
	//try {
	//	c1.setPrenume("Ion");
	//}
	//catch (const char* exceptie) {
	//	cout << exceptie;
	//}
	//char telefon1[11] = "0720484545";
	//try {
	//	c1.setTelefon(telefon1);
	//}
	//catch (const char* exceptie) {
	//	cout << exceptie;
	//}
	//try {
	//	c1.setEmail("dumitescui@yahoo.com");
	//}
	//catch (const char* exceptie) {
	//	cout << exceptie;
	//}
	//try {
	//	c1.setAdresa("Timisoara");
	//}
	//catch (const char* exceptie) {
	//	cout << exceptie;
	//}
	//try {
	//	c1.setVarsta(32);
	//}
	//catch (const char* exceptie) {
	//	cout << exceptie;
	//}
	//cout << c1;
	//Client c3 = c1;
	//cout << c3;
	//c2 = c1;
	//cout << c2;

	//if (c2 == c3) {
	//	cout << "clientul are 2 rezervari";
	//}
	//if (c2 != c3) {
	//	cout << "clientul nu are 2 rezervari";
	//}

	////testare clasa hotel
	//Hotel H1();

	//float v[] = { 100, 200, 300, 400, 500 };
	//Hotel H2("Phoenicia", "Constanta", "0735699796", 3, "piscina", v);
	//cout << "Hotelul se numeste " << H2.getDenumire() << "." << endl;
	//cout << "Este situat in " << H2.getAdresa() << "." << endl;
	//cout << "Numarul de contact al hotelului este " << H2.getTelefon() << "." << endl;
	//cout << "Hotelul are " << H2.getNrStele() << " stele." << endl;
	//cout << "Hotelul dispune de urmatoarele servicii: " << H2.getServicii() << "." << endl;
	//for (int i = 0; i < 5; i++)
	//	cout << "Costul camerei " << i << " este " << H2.getCostCamera(i) << " lei/noapte." << endl;
	//cout << endl;

	//try {
	//	H2.setDenumire("Aurelius");
	//}
	//catch (const char* exceptie) {
	//	cout << exceptie;
	//}
	//try {
	//	H2.setAdresa("Brasov");
	//}
	//catch (const char* exceptie) {
	//	cout << exceptie;
	//}
	//try {
	//	H2.setTelefon("0725446528");
	//}
	//catch (const char* exceptie) {
	//	cout << exceptie;
	//}
	//try {
	//	H2.setNrStele(4);
	//}
	//catch (const char* exceptie) {
	//	cout << exceptie;
	//}
	//try {
	//	H2.setServicii("mese incluse");
	//}
	//catch (const char* exceptie) {
	//	cout << exceptie;
	//}
	//float v2[] = { 50, 60, 70, 80, 90 };
	//try {
	//	H2.setCostCamera(v2);
	//}
	//catch (const char* exceptie) {
	//	cout << exceptie;
	//}

	//float v3[] = { 50, 100, 150, 600, 1000 };
	//Hotel H3("Bran", "Predeal", "0756442342", 4, "permis animale", v3);

	//H2.getNrStele() + 1;
	//cout << "Noul numar de stele este : " << H2.getNrStele() << endl;
	//cout << endl;

	//H3.getNrStele() - 2;
	//cout << "Noul numar de stele este : " << H3.getNrStele() << endl;
	//cout << endl;

	//if (H2.getNrStele() == H3.getNrStele())
	//	cout << "Numarul de stele ale celor doua hoteluri este egal." << endl;
	//else cout << "Numarul de stele ale celor doua hoteluri NU este egal." << endl;
	//cout << endl;

	//Hotel H4 = H2;
	//H4 = H3;
	//cout << "Hotelul cu nr 4 : " << endl;
	//cout << H4;
	//cout << endl;

	//Hotel H5;
	//cout << "Introduceti date pentru hotelul cu nr 5." << endl;
	//cin >> H5;
	//cout << H5;
	//cout << endl;

	////testare clasa obiective turistice
	//ObiectiveTuristice O1;
	//cout << O1 << endl;
	//ObiectiveTuristice O2("Statuie", "Bucuresti", "14:00", "18:00", 12);
	//cout << O2 << endl;
	//ObiectiveTuristice O3 = O2;
	//cout << O3 << endl;
	//ObiectiveTuristice O4;
	//cin >> O4;
	//cout << O4 << endl;
	//O2 = O4;
	//cout << O2;
	//cout << endl;
	//cout << O2.getDenumire() << endl;
	//cout << O2.getLocalizare() << endl;
	//cout << O2.getOraDeschidere() << endl;
	//cout << O2.getOraInchidere() << endl;
	//cout << O2.getPretBilet() << endl;

	//try {
	//	O2.setDenumire("Muzeu");
	//}
	//catch (const char* exceptie) {
	//	cout << exceptie << endl;;
	//}
	//try {
	//	O2.setLocalizare("Brasov");
	//}
	//catch (const char* exceptie) {
	//	cout << exceptie << endl;;
	//}
	//try {
	//	O2.setOraDeschidere("10:00");
	//}
	//catch (const char* exceptie) {
	//	cout << exceptie << endl;;
	//}
	//try {
	//	O2.setOraInchidere("16:00");
	//}
	//catch (const char* exceptie) {
	//	cout << exceptie << endl;;
	//}
	//try {
	//	O2.setPretBilet(5);
	//}
	//catch (const char* exceptie) {
	//	cout << exceptie << endl;;
	//}
	//cout << O2;
	//cout << "Pret majorat" << endl;
	//O2.majorare(0.2);
	//cout << O2.getPretBilet() << endl;
	//cout << "Pret redus" << endl;
	//O2.reducere(0.2);
	//cout << O2.getPretBilet() << endl;
	//O2 = O2 + 3;
	//cout << O2;
	//O4 = O4 - 5;
	//cout << O4;
	//if (O3 >= O4) {
	//	cout << "Obiectivul O2 are un pret mai mare" << endl;
	//}
	//else cout << "Obiectivul O4 are un pret mai mare" << endl;

	////testare clasa rezervare
	//Rezervare R1();

	//Hotel hotel[] = { H2 };
	//Client client[] = { c1 };
	//ObiectiveTuristice obiective[] = { O2, O4 };
	//int cr[] = { 1, 2, 3, 5 };
	//Rezervare R2("Nord", 5, 20, "hotelier", hotel, client, 2, obiective, 4, cr);
	//cout << R2;
	////i=0; afisare
	//Rezervare R4;
	//cin >> R4;
	//cout << R4;

	//cout << R2.getZonaGeografica() << endl;
	//cout << R2.getPerioada() << endl;
	//cout << R2.getNrPersoane() << endl;
	//cout << R2.getRegimCazare() << endl;
	//cout << R2.getNrObiectiveTuristice() << endl;
	//cout << R2.getNrCamereRezervate() << endl;
	//cout << R2.getCamereRezervate(2) << endl;

	//try {
	//	R2.setZonaGeografica("Nord");
	//}
	//catch (const char* exceptie) {
	//	cout << exceptie;
	//}
	//try {
	//	R2.setPerioada(4);
	//}
	//catch (const char* exceptie) {
	//	cout << exceptie;
	//}
	//try {
	//	R2.setNrPersoane(8);
	//}
	//catch (const char* exceptie) {
	//	cout << exceptie;
	//}
	//try {
	//	R2.setRegimCazare("hotelier");
	//}
	//catch (const char* exceptie) {
	//	cout << exceptie;
	//}
	//try {
	//	R2.setNrObiective(1);
	//}
	//catch (const char* exceptie) {
	//	cout << exceptie;
	//}
	//try {
	//	R2.setNrCamereRezervate(2);
	//}
	//catch (const char* exceptie) {
	//	cout << exceptie;
	//}
	//int cr2[] = { 10, 14 };
	//try {
	//	R2.setCamereRezervate(cr2);
	//}
	//catch (const char* exceptie) {
	//	cout << exceptie;
	//}

	//R2 = R2 + 3;
	//cout << "Dupa supraincarcarea operatorului + se va afisa :" << R2.getNrPersoane() << endl;

	//R2 = R2 - 1;
	//cout << "Dupa supraincarcarea operatorului - se va afisa :" << R2.getNrPersoane() << endl;

	////R2[4];
}