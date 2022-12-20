#ifndef SHAPE_H_
#define SHAPE_H_

#include<iostream>
#include<cmath>
#include<string>
#include<algorithm>
#include<list>
#include<fstream>
#include <iomanip>    

using namespace std;

/* Intro Paragraph MP12:
 * In this MP, I implemented the Shape hierarchy with four different shape types: Circle, Rectangle, Sphere, and RectPrism
 * I first wrote the constructor for the Shape class. This initialized a name member for each object.
 * It also initialized getArea() and getVolume() functions.
 * I then wrote the constructors of the other objects. I set the parameter variables to the local object variables.
 * I used the length, width, and radius variables to create accessor methods as well as create getArea() and getVolume() functions for each object
 * For operator methods, I followed the psuedocode from the wiki. I made sure to use accessor methods like getLength() for the objects in the parameter
 * I then implemented MaxArea() or MaxVolume() by iterating through a list of shapes and checking the area or volume of each object using accesor methods.
 * Finally, I implemented the CreateShapes() function. I read the input file and parsed the information.
 * I initialzied the shape variables for each object and read the name of the shape from the file.
 * I checked the name of the object and used the appropriate constructor to create each shape and add it to the list of shapes.
 */


//Base class
//Please implement Shape's member functions
//constructor, getName()
class Shape{
public:
	//Base class' constructor should be called in derived classes'
	//constructor to initizlize Shape's private variable 
  	Shape(string name) {
		name_ = name;
	}
	
  	string getName() {
		return name_;
	}
	
  	virtual double getArea() const = 0;
  	virtual double getVolume() const = 0;
	
private:
  string name_;


};

//Rectangle
//Please implement the member functions of Rectangle:
//constructor, getArea(), getVolume(), operator+, operator-

template <class T>
class Rectangle : public Shape{
public:
  	Rectangle<T>(T width = 0, T length = 0):Shape("Rectangle") {
		width_ = width;
		length_ = length;
	}
	
  	double getArea() const {
		return (double)(width_*length_);
	}
	
  	double getVolume() const {
		return 0.0;
	}
	
	Rectangle<T> operator + (const Rectangle<T>& rec) {
		T newL = length_ + rec.getLength();
		T newW = width_ + rec.getWidth();
		return Rectangle<T>(newW, newL);
	}
	
	Rectangle<T> operator - (const Rectangle<T>& rec) {
		T newL = max((T)0, (T)(length_ - rec.getLength()));
		T newW = max((T)0, (T)(width_ - rec.getWidth()));
		return Rectangle<T>(newW, newL);
	} 
	
	T getWidth() const { 
		return width_;
	}
	
	T getLength() const { 
		return length_;
	}
private:
	T width_;
    T length_;

};

//Circle
//Please implement the member functions of Circle:
//constructor, getArea(), getVolume(), operator+, operator-
//@@Insert your code here

class Circle : public Shape{
public:
  	Circle(double radius):Shape("Circle") {
		radius_ = radius;
	}
	
  	double getArea() const{
		return (radius_*radius_*M_PI);
	}
	
 	double getVolume() const{
		return 0;
	}
	
  	Circle operator + (const Circle& cir){
		double newR = radius_ + cir.getRadius();
		return Circle(newR);
	}
	
	Circle operator - (const Circle& cir){
		double newR = max(0.0, (double)(radius_ - cir.getRadius()));
		return Circle(newR);
	} 

	double getRadius() const { 
		return radius_;
	}
	
private:
	double radius_;

};



//Sphere
//Please implement the member functions of Sphere:
//constructor, getArea(), getVolume(), operator+, operator-
//@@Insert your code here

class Sphere : public Shape{
public:
  	Sphere(double radius):Shape("Sphere") {
		radius_ = radius;
	}

  	double getVolume() const {
		return (4.0/3.0 * pow(radius_, 3) * M_PI);
	}
	
  	double getArea() const {
		return (4.0*M_PI*pow(radius_, 2));
	}

	Sphere operator + (const Sphere& sph) {
		double newR = radius_ + sph.getRadius();
		return Sphere(newR);
	}

	Sphere operator - (const Sphere& sph) {
		double newR = max(0.0, (double)(radius_ - sph.getRadius()));
		return Sphere(newR);
	} 
	
	double getRadius() const {
		return radius_;
	}

private:
	double radius_;

};

//Rectprism
//Please implement the member functions of RectPrism:
//constructor, getArea(), getVolume(), operator+, operator-
//@@Insert your code here
class RectPrism : public Shape{
public:
  	RectPrism(double width, double length, double height):Shape("RectPrism") {
		  width_ = width;
		  length_ = length;
		  height_ = height;
	}
	
  	double getVolume() const {
		  return (length_*width_*height_);
	}
  	
	double getArea() const {
		return (2*(length_ * width_ + length_ * height_ + width_ * height_));

	}
	
	RectPrism operator + (const RectPrism& rectp){
		double newL = length_ + rectp.getLength();
		double newW = width_ + rectp.getWidth();
		double newH = height_ + rectp.getHeight();
		return RectPrism(newW, newL, newH);
	}
	
	RectPrism operator - (const RectPrism& rectp){
		double newL = max(0.0, (double)(length_ - rectp.getLength()));
		double newW = max(0.0, (double)(width_ - rectp.getWidth()));
		double newH = max(0.0, (double)(height_ - rectp.getHeight()));
		return RectPrism(newW, newL, newH);
	}	
	
	double getWidth() const { 
		return width_;
	}
	
	double getLength() const { 
		return length_;
	}
	
	double getHeight() const { 
		return height_;
	}
private:
  	double length_;
  	double width_;
  	double height_;

};

// Read shapes from test.txt and initialize the objects
// Return a vector of pointers that points to the objects 
static list<Shape*> CreateShapes(char* file_name) {
	//@@Insert your code here
	int numShapes;
	double l, w, h, r;
	list<Shape*> shapes;
	string name;
	ifstream ifs (file_name, std::ifstream::in);
	ifs >> numShapes;
	for (int i=0; i<numShapes; i++){
		Shape* shape_ptr;
		ifs >> name;
		if (name == "Rectangle"){
			ifs >> w >> h;
			shape_ptr = new Rectangle<double>(w, h);
		} else if (name == "Circle"){
			ifs >> r;
			shape_ptr = new Circle(r);
		} else if (name == "Sphere"){
			ifs >> r;
			shape_ptr = new Sphere(r);
		} else if (name == "RectPrism"){
			ifs >> w >> l >> h;
			shape_ptr = new RectPrism(w, l, h);
		}
		shapes.push_back(shape_ptr);
	}
	ifs.close();
	return shapes;
}

// call getArea() of each object 
// return the max area
static double MaxArea(list<Shape*> shapes){
	double max_area = 0;
	//@@Insert your code here
	for (list<Shape*>::iterator it = shapes.begin(); it != shapes.end(); it++){
		if ((*it)->getArea() > max_area){
			max_area = (*it)->getArea();
		}
	}
	return max_area;
}

// call getVolume() of each object 
// return the max volume
static double MaxVolume(list<Shape*> shapes){
	double max_volume = 0;
	//@@Insert your code here
	for (list<Shape*>::iterator it = shapes.begin(); it != shapes.end(); it++){
		if ((*it)->getVolume() > max_volume){
			max_volume = (*it)->getVolume();
		}
	}
	return max_volume;
}
#endif

