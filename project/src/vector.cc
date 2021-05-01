#include <iostream>
#include <cmath>
#include "../include/vector.h"


namespace csci3081 {

void Vector::SetX(float x_){
    x = x_;
}

void Vector::SetZ(float z_){
    z = z_;
}

float Vector::Magnitude() {
    return sqrt(pow(x,2)+pow(y,2)+pow(z,2));
}

bool Vector::operator==(const Vector& other){
    float threshold = 1e-6;
    return (fabs(x - other.x) < threshold) && (fabs(y - other.y) < threshold) && (fabs(z - other.z) < threshold);
}

std::vector<float> toVectorFloat(Vector& v){
    std::vector<float> result;
    result.push_back(v.x);
    result.push_back(v.y);
    result.push_back(v.z);
    return result;
} 


//--------------------------------------------------------------------------------------------------------------------//

Vector2D::Vector2D() {
    x = 0;
    y = 0;
    z = 0;
}

Vector2D::Vector2D(std::vector<float> arg) {
    x = arg.at(0);
    y = 0;

    
    if (arg.size() == 3) {
        z = arg.at(2);
    } else {
        z = arg.at(1);
    }
}

Vector2D::Vector2D(float x_, float z_) {
    x = x_;
    y = 0;
    z = z_;
}

Vector2D::Vector2D(const Vector2D& copy) {
    x = copy.x;
    z = copy.z;
}

Vector2D Vector2D::operator +(const Vector2D& other) {
    return Vector2D(x+other.x,z+other.z);
}

Vector2D Vector2D::operator -(const Vector2D& other) {
    return Vector2D(x-other.x,z-other.z);
}

Vector2D Vector2D::operator *(float other) {
    return Vector2D(x*other,z*other);
}

Vector2D Vector2D::operator /(float other) {
    return Vector2D(x/other,z/other);
}

Vector2D& Vector2D::operator =(const Vector2D& cpy) {
    x = cpy.x;
    z = cpy.z;
    return *this;
}

Vector2D Vector2D::Normalize() {
    return Vector2D(x/Magnitude(),z/Magnitude());
}

void Vector2D::Print() {
    std::cout << std::fixed << std::setprecision(3);
    std::cout << "<" << x << "," << z << ">";
}

//--------------------------------------------------------------------------------------------------------------------//

Vector3D::Vector3D(std::vector<float> arg) {
    x = arg.at(0);
    y = arg.at(1);
    z = arg.at(2);
}

Vector3D::Vector3D(float x_ = 0, float y_ = 0, float z_ = 0) {
    x = x_;
    y = y_;
    z = z_;
}

Vector3D::Vector3D(const Vector3D& copy) {
    x = copy.x;
    y = copy.y;
    z = copy.z;
}

Vector3D::Vector3D() {
    x=0;
    y=0;
    z=0;
}

void Vector3D::SetY(float y_){
    y=y_;
}

Vector3D Vector3D::operator +(const Vector3D& other) {
    return Vector3D(x+other.x,y+other.y,z+other.z);
}

Vector3D Vector3D::operator -(const Vector3D& other) {
    return Vector3D(x-other.x,y-other.y,z-other.z);
}

Vector3D Vector3D::operator *(float other) {
    return Vector3D(x*other,y*other,z*other);
}

Vector3D Vector3D::operator /(float other) {
    return Vector3D(x/other,y/other,z/other);
}

Vector3D& Vector3D::operator =(const Vector3D& cpy) {
    if (this != &cpy) {
        x = cpy.x;
        y = cpy.y;
        z = cpy.z;
    }
    return *this;
}

Vector3D Vector3D::Normalize() {
    return Vector3D(x/Magnitude(),y/Magnitude(),z/Magnitude());
}

void Vector3D::Print() {
    std::cout << std::fixed << std::setprecision(3);
    std::cout << "<" << x << "," << y << "," << z << ">";
}

bool Vector3D::IsWithinXandZRange(const Vector3D& other, float precision) {
    if ((abs(x - other.GetX()) <= precision) && (abs(z - other.GetZ()) <= precision)) {
        return true;
    }
    return false;
}

Vector2D to2D(Vector3D& other) {
    return Vector2D(other.GetX(),other.GetZ());
}

Vector3D to3D(Vector2D& other) {
    return Vector3D(other.GetX(),0,other.GetZ());
}

Vector3D CrossProduct(const Vector& v1, const Vector& v2){
    float a = (v1.GetY()*v2.GetZ())-(v1.GetZ()*v2.GetY());
    float b = (v1.GetZ()*v2.GetX())-(v1.GetX()*v2.GetZ());
    float c = (v1.GetX()*v2.GetY())-(v1.GetY()*v2.GetX());
    return Vector3D(a,b,c);
}

//--------------------------------------------------------------------------------------------------------------------//

float DotProduct(const Vector& v1, const Vector& v2) {
    return (v1.x*v2.x+v1.y*v2.y+v1.z*v2.z);
}

float Distance(const Vector& v1, const Vector& v2) {
    float x_diff = pow(v1.x-v2.x,2);
    float y_diff = pow(v1.y-v2.y,2);
    float z_diff = pow(v1.z-v2.z,2);
    return (sqrt(x_diff+y_diff+z_diff));
}
} // closing namespace 3081
