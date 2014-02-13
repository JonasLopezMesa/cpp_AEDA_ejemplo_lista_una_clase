//
//  main.cpp
//  Práctica_5
//
//  Created by Jonás López Mesa on 23/04/12.
//  Copyright 2012 __MyCompanyName__. All rights reserved.
//
#include <iostream>
using namespace std;
#define NULO -1
#define LIBRE -2
typedef char dato_t;
typedef int link_t;

class nodo_t{
    dato_t dato_;
    link_t siguiente_;
public:
    nodo_t():
    dato_(0),
    siguiente_(LIBRE){}
    ~nodo_t(){
        siguiente_ = LIBRE;
    }
    void inicializa(dato_t dato){ //asigna el valor del dato
        dato_ = dato;
    }
    bool libre(){ //dice si ese nodo apunta a otro nodo o está libre
        return siguiente_ == LIBRE;
    }
    bool nulo(){
        return siguiente_ == NULO;
    }
    link_t get_siguiente(){ //obtiene el siguiente nodo al que apunta ese nodo
        return siguiente_; 
    }
    void set_siguiente(link_t siguiente){ //establece cual es el siguiente nodo al que apunta ese nodo
        siguiente_ = siguiente;
    }
    void imprimir(){ //Imprime el dato : y su siguiente
        if (siguiente_ == LIBRE) {
            cout << " [ LIBRE ] " << endl;
        } else if (siguiente_ == NULO) {
            cout << " [" << dato_ << " : NULO] " << endl;
        } else  {
            cout << " [" << dato_ << " : " << siguiente_ << " ]" << endl;
        }
    }
};

class lista_t{
    nodo_t* vector_;
    int sz_;
    link_t inicio_;
    link_t fin_;
    int n_ele_;
public:
    lista_t(int sz):
    sz_(sz),
    vector_(NULL),
    n_ele_(0),
    inicio_(NULO),
    fin_(NULO) {
        vector_ = new nodo_t[sz_];
        cout << "Tamaño de la lista: " << sz_ << ". " << endl;
    }
    ~lista_t() {
        delete [] vector_;
        sz_ = 0;
        n_ele_ = 0;
        inicio_ = NULO;
        fin_ = NULO;
    }
    void imprimir() { //BUENO
        link_t inx = inicio_;
        while (inx != NULO) {
            vector_[inx].imprimir();
            inx = vector_[inx].get_siguiente();
        }
        cout << endl;
    }
    void mostrar_lista(void) { //CHUNGO
        for (int i = 0; i < sz_; i++) {
            cout << i << " ";
            vector_[i].imprimir();
        }
        cout << endl;
    }
    bool empty() { //dice si la lista está vacia o no
        if (n_ele_ == 0) {
            return true;
        } else {
            return false;
        }
    }
    bool full() { //dice si la lista está llena o no
        return n_ele_ >= sz_ -1;
    }
    void libera (link_t inx) { //
        vector_[inx].set_siguiente(LIBRE);
    }
    link_t nuevo (){
        if (full()) {
            return NULO;
        } else {
            link_t inx = 0;
            cout << "Creando nuevo elemento...";
            while ((!vector_[inx].libre()) && (inx < sz_)) {
                inx++;
            }
            cout << endl;
            if (inx == sz_) {
                cerr << "ERROR TERRIBLE" << endl;
                exit(1);
            }
            vector_[inx].set_siguiente(NULO);
            return inx;
        }
    }
    int espacio_libre() {
        return sz_ - n_ele_;
    }
    void insertar_empty(link_t inx) {
        char a;
        cout << "Lista vacía" << endl;
        cout << "¿Qué dato quieres meter?" << endl;
        cin >> a;
        vector_[inx].inicializa(a);
        inicio_ = inx;
        fin_ = inx;
        n_ele_++;
    }
    void insertar_principio (link_t inx){
        if (empty() == true) {
            insertar_empty(inx);
        } else if (full() == true) {
            cerr << "LISTA LLENA" << endl;
        } else {
            char a;
            cout << "¿Qué dato quieres meter?" << endl;
            cin >> a;
            vector_[inx].inicializa(a);
            vector_[inx].set_siguiente(inicio_);
            inicio_ = inx;
            n_ele_++;
        }
    }
    void insertar_final (link_t inx) {
        if (empty()) {
            insertar_empty(inx);
        } else if (full()) {
            cerr << "LISTA LLENA" << endl;
        } else {
            char a;
            cout << "¿Qué dato quieres meter?" << endl;
            cin >> a;
            vector_[inx].inicializa(a);
            vector_[fin_].set_siguiente(inx);
            vector_[inx].set_siguiente(NULO);
            fin_ = inx;
            n_ele_++;
        }
    }
    void insertar_after(link_t after, link_t inx) {
        if (full()) {
            cerr << "LISTA LLENA" << endl;
        } else if (empty()) {
            insertar_empty(inx);
        } else {
            char a;
            cout << "¿Qué dato quieres meter?" << endl;
            cin >> a;
            vector_[inx].inicializa(a);
            vector_[inx].set_siguiente(vector_[after].get_siguiente());
            vector_[after].set_siguiente(inx);
            if (fin_ == after) {
                fin_ = inx;
            }
            n_ele_++;
        }
    }
    void extraer_principio(){
        vector_[inicio_].inicializa(0);
        link_t inx = inicio_;
        inicio_ = vector_[inicio_].get_siguiente();
        vector_[inx].set_siguiente(LIBRE);
        
        n_ele_--;
    }
    void extraer_final(){
        vector_[fin_].set_siguiente(LIBRE);
        link_t inx2 = fin_;
        vector_[inx2+1].set_siguiente(NULO);
        fin_ = inx2+1;
        n_ele_--;
    } 
};

int main (){
    unsigned short int a = 0;
    unsigned short int c = 0;
    int sz;
    cout << "Primero introduzca el tamaño que desee para crear la lista: " << endl;
    cin >> sz;
    lista_t lista(sz);
    c = 1;
    while (a == 0) {
        unsigned short int x;
        cout << "**********************************" << endl;
        cout << "               MENÚ" << endl;
        cout << "**********************************" << endl;
        cout << "1. Reasignar tamaño" << endl;
        cout << "2. Mostrar Lista" << endl;
        cout << "3. Imprimir Lista" << endl;
        cout << "4. Mostrar espacio Libre" << endl;
        cout << "5. Insertar por el principio" << endl;
        cout << "6. Insertar por el final" << endl;
        cout << "7. Insertar después del nodo seleccionado" << endl;
        cout << "8. Extraer por el principio" << endl;
        cout << "9. Extraer por el final" << endl;
        cout << "10. Salir" << endl;
        cout << "**********************************" << endl;
        cout << "Introduzca la opción que desee: ";
        cin >> x;
        if (x == 1) {
            int sz;
            cout << "introduzca el tamaño de la lista que desee: " << endl;
            cin >> sz;
            lista_t lista(sz);
            c = 1;
        }
        if (x == 2) {
            lista.mostrar_lista();
        }
        if (x == 3) {
            if (lista.empty() == true) {
                cout << "la lista está vacía, primero introduzca datos" << endl;
            } else {
                lista.imprimir();
            }
        }
        if (x == 4) {
            cout << "El espacio libre de la lista es: " << lista.espacio_libre() << " espacios." << endl;
        }
        if (x == 5) {
            link_t nuevo = lista.nuevo();
            lista.insertar_principio(nuevo);
        }
        if (x == 6) {
            link_t nuevo1 = lista.nuevo();
            lista.insertar_final(nuevo1);
        }
        if (x == 7) {
            link_t s;
            cout << "¿Después de que nodo quieres insertarlo?" << endl;
            cin >> s;
            link_t nuevo3 = lista.nuevo();
            lista.insertar_after(s, nuevo3);
        }
        if (x == 8) {
            lista.extraer_principio();
        }
        if (x == 9) {
            lista.extraer_final();
        }
        if (x == 10) {
            cout << "FIN DEL PROGRAMA" << endl;
            a = 1;
            return 0;
        }
        if ((x != 1) && (x != 2) && (x != 3) && (x != 4) && (x != 5) && (x != 6) && (x != 7) && (x != 8) && (x != 9) && (x != 10)) {
            cout << "ERROR: Opción incorrecta, seleccione una opción correcta del menú." << endl;
        }
    }
    return 0;
}


















