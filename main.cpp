//  Created by Emanuel Estrada Larios
//  A01633605

//  Metodos Numericos - Proyecto final

#include <iostream>
#include <cmath>
using namespace std;

float V = 0;
float A, B = 0;
float R, L = 0;

// Redondeo
float red(float x){
    return roundf(x * 1000) / 1000;
}

// Definicion de funciones particulares de caso 1
float f(float x){
    return red(pow(x,6) + 2*V*pow(x,2) + 2*V*x - V);
}
float f1(float x){
    return red(6*pow(x,5) + 4*V*x + 2*V);
}
float f2(float x){
    return red(30*pow(x,4) + 4*V);
}

// Definicion de funciones particulares de caso 2
float g(float x){
    return red(12*pow(x,2) + 4*A*x + 4*B*x + A*B);
}
float g1(float x){
    return red(24*x + 4*A + 4*B);
}
float g2(float x){
    return 24;
}

// Definicion de funciones particulares de caso 3
float h(float x){
    return red((0.5*pow(L,3) - 2*L*R*x - R*pow(x,2)) / (pow(L,2) - 2*R*x));
}
float h1(float x){
    return red(((-2*L*R - 2*R*x)*(pow(L,2) - 2*R*x) - (-2*R)*(0.5*pow(L,3) - 2*L*R*x - R*pow(x,2))) / pow((pow(L,2) - 2*R*x),2));
}
float h2(float x){
    return red(((-2*pow(L,2)*R + 4*pow(R,2)*x) * pow((pow(L,2) - 2*R*x),2) - 4*R * (pow(L,2) - 2*R)) / pow((pow(L,2) - 2*R*x), 4));
}

// Implementacion de metodos numericos
float newtonRapson(float x0, float (*f)(float), float (*f1)(float)){
    
    //float tol = -0.0001;
    float x = x0;
    
    for (int i=0; i<100000; i++) {
        if(f(x) == 0){
            break;
        }
        x = x - (f(x)/f1(x));
    }
    
    return red(x);
}

float newtonRapson2(float x0, float (*f)(float), float (*f1)(float), float (*f2)(float)){
    
    float tol = 0.0001;
    float deltaX;
    float x = x0;
    
    for (int i=0; i<100000; i++) {
        deltaX = 1 / ((f2(x)/(2*f1(x))) - (f1(x)/f(x)));
        if(f(x) < tol){
            break;
        }
        x = x + deltaX;
    }
    
    return red(x);
}

// Metodo regresa dimensiones sugeridas de caja para minimizar materiales,
// considerando la restriccion de ancho = largo^2.
string minimizarMaterial(float volumen){

    if (volumen > 0){
        V = volumen;
        
        float x = newtonRapson2(0.4,f,f1,f2);
        float y = red(pow(x,2));
        float z = red(volumen / pow(x,3));
        
        return "Largo = " + to_string(x) + ", Ancho = " + to_string(y) + ", Alto = " + to_string(z) + "\n";
    } else {
        return "El volmuen no puede ser cero. \n";
    }
    
}

// Metodo regresa magnitud de x sugerida de caja para maximizar materiales.
float maximizarVolumen(float a, float b){
    
    if(a > 0 && b > 0){
        A = a;
        B = b;
        return red(abs(newtonRapson2(180, g, g1, g2)));
    } else {
        return -1;
    }
    
}

// Metodo regresa la magnitud del vector CG, y especifica que tan cerca este del CG
// mas bajo posible dadas las dimensiones
float calcularCentroGravedad(float l, float r){
    
    if(l > 0 && r > 0){
        
        R = r;
        L = l;
        
        float x = newtonRapson(25, h1, h2);
        return h(x);
        
    } else {
        return -1;
    }
    
}

int main(int argc, const char * argv[]) {
    
    // Pruebas con valores proporcionados
    cout << minimizarMaterial(1);
    cout << maximizarVolumen(1.5, 0.75) << "\n";
    cout << calcularCentroGravedad(50, 5) << "\n";
    
    return 0;
}
