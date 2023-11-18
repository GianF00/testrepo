#include <iostream>
#include <string>

class car {
private:
	int model_year = 0;
	std::string model_name;
public:
	int get_model_year();
	std::string get_model_name();
	//car(int Model_year, std::string Model_name);
	car(){}
	friend std::istream& operator>>(std::istream& is, car& obj) {
		is >> obj.model_year >> obj.model_name;
		return is;
	}
};

int car::get_model_year() {
	return model_year;
}

std::string car::get_model_name() {
	return model_name;
}

std::ostream& operator<<(std::ostream& os, car& obj) {
	os << "Modell: " << obj.get_model_name() << ", Producerad:" << obj.get_model_year();
	return os;
}



class BankAccount {
private:
	unsigned int account_no;//Unsigned si utilizza per numeri naturali 
	std::string owner_name;
	double balance = 0.0;//inizializzare il valore perche puo dare un valore enorme che e sbagliato 
public:
	BankAccount(unsigned int Account_no, std::string Owner_name) {
		account_no = Account_no;
		owner_name = Owner_name;
	}
	void deposit(double n) {
		balance += n;//si deve sommare il balance con quello che voglio depositare
	}
	double withdraw(double n) {
		if (n > balance)
		{
			std::cerr << "You do not have enough money in your bank accout!";//serve per mostrare messagi di errori
			return balance;
		}
		return balance -= n;

	}

	int get_account_no() {
		return account_no;
	}
	std::string get_owner_name() {
		return owner_name;
	}
	double get_balance() {
		return balance;
	}

	friend std::istream& operator>>(std::istream& is, BankAccount& obj) {
		is >> obj.account_no >> obj.owner_name >> obj.balance;
		return is;
	}
};
std::ostream& operator<<(std::ostream& os, BankAccount& obj) {
	os << "Account " << obj.get_account_no() << ", owned by " << obj.get_owner_name() << " has the balance " << obj.get_balance();
	return os;
}



class Persona {
private:
	std::string nome;
	std::string cognome;
	int eta = 0;
public:
	Persona(){}
	std::string get_nome() {
		return nome;
	}
	std::string get_cognome() {
		return cognome;
	}
	int get_eta() {
		return eta;
	}
	friend std::istream& operator>>(std::istream& is, Persona& obj) {
		is >> obj.nome >> obj.cognome >> obj.eta;
		return is;//returnerar objektet: obj
	}
	
};

std::ostream& operator<<(std::ostream& os, Persona& obj) {//passing by ref. the original objects 
	os << obj.get_cognome() << " " << obj.get_nome() << " " << obj.get_eta();
	return os;//returnerar objektet: obj
}

class Point {
private:
	int x, y;
public:
	Point(int x1, int y1) {//Parametriserad construcotr
		x = x1;
		y = y1;
	}
	Point(const Point& pt) {//copy constr
		x = pt.x;
		y = pt.y;//copiando los valores de los miembros del obj existente para X y Y
	}

	~Point(){}
	int getX() { return x; }
	int getY() { return y; }
};


class Cool_list {
private:
	struct node {
		double value;
		node* next;
	};

	node* head;

public:
	Cool_list() {
		head = nullptr;
	}
	Cool_list(const Cool_list& src) {
		node* Nodo = src.head;

		head = nullptr;

		while (Nodo != nullptr) {
			this->push_back(Nodo->value);
			Nodo = Nodo->next;
		}
	}
	~Cool_list() {
		node* Nodo = this->head;
		node* temp = nullptr;

		while (Nodo != nullptr)
		{
			temp = Nodo->next;
			delete Nodo;
			Nodo = temp;
		}

		this->head = nullptr;
	}
	void push_back(double v) {
		node* Nodo = new node;//allokerar nytt minne
		Nodo->value = v;//allokerar värdet i minnet
		Nodo->next = nullptr;

		if (head == nullptr)//al inicio
		{
			head = Nodo;
		}
		else//al final
		{
			node* temp = head;
			while (temp->next != nullptr)
			{
				temp = temp->next;
			}
			temp->next = Nodo;//una volta arrivati al finale aggiungiamo il Nodo al finale 
	
		}
	}
	void print_list() {
		for (node* temp = head; temp != nullptr; temp = temp->next)
		{
			std::cout << temp->value << " ";
		}
	}
	int pop_front() { 
		int v = head->value;

		node* nuvarande = head;
		node* previ = nullptr;

		while (nuvarande != nullptr)
		{
			previ = nuvarande;
			nuvarande = nuvarande->next;
			delete previ;
		}

		return v;
	}
	Cool_list& operator+=(const Cool_list& rhs) {
		if (rhs.head == nullptr)//se la lista e vuota a destrea ritorniamo la lista di sinistra(inutile copiare la lista rhs)
		{
			return (*this);
		}

		node* Nodo = rhs.head;
		while (Nodo != nullptr)
		{
			this->push_back(Nodo->value);
			Nodo = Nodo->next;
		}
		return *this; //ritorniamo la lista lhs
	}
	inline size_t size() { return 0; }
	Cool_list& operator=(const Cool_list& rhs) {
		if (this == &rhs)
		{
			return *this;
		}
		else {

			while (head != nullptr)//que hacemos con el valor que la func pop front retorna?
			{
				pop_front();
			}
			
			for (node* temp = rhs.head; temp != nullptr; temp = temp->next)
			{
				this->push_back(temp->value);
			}
			return *this;
		}
	}

};


class MyInt{
private:
	int* ptr;
public:
	MyInt(int num) {//parame. construc.
		ptr = new int(num);//allokerar minne adress och värde
	}

	MyInt(const MyInt& source) {//copy constru.
		ptr = new int;//allokerar nytt minne adress
		*ptr = *source.ptr;//kopierar och sätter värdet i *ptr
	}
	MyInt& operator+=(const MyInt& rhs) {
		*ptr += *rhs.ptr;//kopierar värdet från rhs till ptr
		return *this;
	}
	MyInt& operator-=(const MyInt& rhs) {
		*ptr -= *rhs.ptr;
		return *this;
	}

	MyInt& operator=(const MyInt& rhs) {//tilldelning operator
		if (this == &rhs)
		{
			return *this;
		}
		delete ptr;

		//djup kopia
		this->ptr = new int;//allokera minne 
		*this->ptr = *rhs.ptr;//kopierar värdet 

		return *this;
	}
	void set(int n) {
		*ptr = n;
	}
	int get() {
		return *ptr;
	}
	friend std::istream& operator>>(std::istream& is, MyInt& obj) {
		is >> *obj.ptr;
		return is;
	}
};
std::ostream& operator<<(std::ostream& COUT, MyInt& obj) {
	COUT << obj.get() << std::endl;
	return COUT;
}

struct h {
private:
	int num = 0;
	std::string ord;
public:
	
	void set_num(int n) {
		num = n;
	}
	void set_ord(std::string o) {
		ord = o;
	}
	int get_num() {
		return num;
	}
	std::string get_ord() {
		return ord;
	}

	/*h(const h& source);*/
	/*h& operator=(const h& rhs);*/
	~h(){}//det funkar att ha en destruktor i struct 

};

class Book {
private:
	std::string title;
	unsigned int pages;
	unsigned int current_page;
public:
	Book(std::string Title, unsigned int Pages) {
		title = Title;
		pages = Pages;
	}
	void change_page(unsigned int p) {
		if (p >= pages)//limite
		{
			current_page = pages;
		}
		else if (p <= 1)//limite
		{
			current_page = 1;
		}
		else
		{
			current_page = p;
		}
	}
	void next_page() {
		if (current_page < pages)
		{
			current_page++;
		}
	}
	void prev_page() {
		if (current_page > 0)
		{
			current_page--;
		}
	}
	friend std::ostream& operator<<(std::ostream& os, Book& obj) {
		os << obj.current_page;
		return os;
	}

};

void valNuevo(int&, int&);

//Template for the function 
template <typename T>
void intercambiar(T &dato1, T &dato2) {//pasar por & asi que se pueda hacer los cambios y funcionen y no por valor porque no retorna nada 
	
	T aux = dato1;
	dato1 = dato2;
	dato2 = aux;

	std::cout << "\tDespues del cambio" << std::endl;
	std::cout << "Num1: " << dato1 << std::endl;
	std::cout << "Num2: " << dato2 << std::endl;


}
template <typename T, typename T2>
T comparar2Nume(T num1, T2 num2) {
	if (num1 > num2)
	{
		return num1;
	}
	else
	{
		return num2;
	}
}

//Template for the class
template <class T>
class Materia {
private:
	std::string nomeMateria;
	int clave;
	T calificacion;
public:
	Materia(std::string NomeMateria, int Clave, T Calificacion) {
		nomeMateria = NomeMateria;
		clave = Clave;
		calificacion = Calificacion;
	}
	void setCalific(T calif) {
		calificacion = calif;
	}
	T getCalific() {//mostrar en esta caso la modificacion de la calificacion 
		return calificacion;
	}
	void MostrarResultado() {
		std::cout << "El nombre de la calificacion es: " << nomeMateria << ", la clave es: " << clave << "." << "la calific es: " << calificacion << std::endl;
	}
};

void helsnig() {
	std::cout << "Hello World";
}
int main(){
	int a = 5;
	int b = 7;
	intercambiar(a, b);
	//std::cout << comparar2Nume('C', 'F');//func con return como get o simple return se necesita un cout para ver el resultado
	/*std::cout << "\tMostrando los datos de las materia" << std::endl;
	Materia <char> obj("Matematicas", 8745, 'C');
	obj.MostrarResultado();

	Materia <int>obj2("Fisica", 6395, 19);
	obj2.MostrarResultado();

	Materia <double>obj3("Tecnologia", 1475, 16.74);
	obj3.MostrarResultado();

	obj.setCalific('E');
	std::cout << "La nueva calificacion de la materia Matematicas es: " << obj.getCalific() << std::endl;*/

	/*std::string dato1, dato2;
	std::cout << "\tAntes del cambio" << std::endl;
	std::cout << "Num1: ";
	std::cin >> dato1;
	std::cout << "Num2: ";
	std::cin >> dato2;
	intercambiar(dato1, dato2);*///prima di entrare nella funzione bisogna definire il tipo di dato e poi salvare il numero nel indi. di memoria del tipo di dato. Una volta entrata nella funz. i numeri si possono cambiare attraverso il indi. di memoria.

	/*int a;
	std::string b;
	car car;
	std::cin >> car;
	std::cout << car;*/
	/*std::cout << factorial(3) << std::endl;*/

	/*unsigned int a;
	std::string name;
	double ba, n;*/
	//std::cin >> a >> name >> ba >> n;
	//BankAccount acc(0, " ");//per dare dei valori iniziale per il construttore altrimenti si lamenta 
	/*std::cin >> acc;*///Istream
	/*std::cout << acc*;//ostream
	//acc.deposit(ba);//devo depositare 1000 prima di prelevare 300 altrimenti non funziona
	//std::cout << acc.withdraw(n);// 300

	/*Persona p;.
	std::cin >> p;
	std::cout << p.get_cognome() << " " << p.get_nome() << " " << p.get_eta() << std::endl;*/
	
	/*std::cout << p;*/
	//Persona p2;
	//std::cin >> p2;
	//std::cout << p2;
	//std::cout << p1.get_cognome() << " " << p1.get_nome() << " " << p1.get_eta() << std::endl;
	
	/*int num1, num2;

	std::cout << "Digite 2 num: ";
	std::cin >> num1 >> num2;
	valNuevo(num1, num2);

	std::cout << "El nuevo valor del primer numero es: " << num1 << std::endl;
	std::cout << "El nuevo valor del segundo numero es: " << num2 << std::endl;*/

	/*int a, b, c;
	std::cin >> a >> b >> c;
	
	MyInt obj(a);
	std::cout << obj.get() << std::endl;

	obj.set(b);
	std::cout << obj.get() << std::endl;

	MyInt obj2(c);
	obj = obj2;
	std::cout << obj.get() << std::endl;*/

	/*int n;
	std::cin >> n;
	std::cout << fibo(n);
	*/

	/*Cool_list obj;
	obj.push_back(4.2);
	obj.push_back(6.4);
	obj.push_back(8.7);
	obj.push_back(9.1);

	std::cout << "Lista 1: ";
	obj.print_list();

	std::cout << std::endl;
	Cool_list obj2;*/
	/*obj2 = obj;
	std::cout << "Lista 2: ";
	obj2.print_list();*/

	/*obj2.push_back(10.15);
	obj += obj2;
	std::cout << std::endl << "Lista 1 con modifa: ";
	obj.print_list();*/
	
	//Point obj(2, 5);// anropar parame. construc
	//Point obj2 = obj;//se va a copiar del obj 

	//std::cout << "Obj, X: " << obj.getX() << std::endl;
	//std::cout << "Obj, Y: " << obj.getY() << std::endl;
	//std::cout << "Obj2, X: " << obj2.getX() << std::endl;
	//std::cout << "Obj2, Y: " << obj2.getY() << std::endl;

	/*MyInt obj(5);
	std::cin >> obj;
	MyInt obj2 = obj;
	std::cout << obj;
	std::cout << obj2;
	MyInt obj3(10);
	obj += obj3;
	std::cout << "Obj med (+=): " << obj.get() << std::endl;
	MyInt obj4(2);
	obj -= obj4;
	std::cout << "Obj med (-=): " << obj.get() << std::endl;*/
	/*h obj;
	obj.set_num(5);
	std::cout << obj.get_num() << std::endl;

	obj.set_ord("hola");
	std::cout << obj.get_ord() << std::endl;*/

	/*std::string a;
	unsigned int b = 0;
	unsigned int c = 0;
	std::cin >> a >> b >> c;

	Book b1(a, b);

	b1.change_page(c);
	std::cout << b1 << std::endl;

	b1.next_page();
	std::cout << b1 << std::endl;

	b1.prev_page();
	std::cout << b1 << std::endl;*/
	//int* p = new int[5];//il numero dentro della parentesi indica il size del array
	//int* q = new int[5];

	//q = p;
	//delete q;
	//q = p = nullptr;
	

	return 0;
}


void valNuevo(int& xnum, int& ynum) {//pasamos por ref. 2 direc. de memoria donde se salvan estos dos num.
	std::cout << "El valor del primer numero es: " << xnum << std::endl;
	std::cout << "El valor del segundo numero es: " << ynum << std::endl;
	
	//con & se puede cambiar el valor que esta salvado en la dir de memoria 
	xnum = 84;
	ynum = 12;
}