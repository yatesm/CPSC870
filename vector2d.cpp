/*
Yates Monteith
CPSC 870: OO Development
Milestone 1: Vecto2D Class
9/7/2010
Class Implementation
*/

#include <cmath>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <memory.h>

#include "vector2d.h"

//Overloaded [] Accessor operator
//Precondition: 0 <= index < 2
//Postcondition: corresponding row in vector is returned
float& Vector2D::operator[](const int index)
{
   if(index == 0)
      return x;
   else if(index == 1)
      return y;
   else
      exit(1);
}

//Couldn't get this working, commented for now
const float& Vector2D::operator[](const int index) const
{
   if(index == 0)
      return x;
   else if(index == 1)
      return y;
   else
      exit(1);
}


/******************************************************************************/
/*                         COMPOUND OPERATIONS                                */
/******************************************************************************/

/**********************************ADDITION************************************/
Vector2D Vector2D::operator+=(const Vector2D& rhs) {
	x += rhs.x;
	y += rhs.y;
	return *this;
}

Vector2D Vector2D::operator+=(const float& rhs) {
	x += rhs;
	y += rhs;
	return *this;
}


/**********************************SUBTRACTION*********************************/
Vector2D Vector2D::operator-=(const Vector2D& rhs) {
	x -= rhs.x;
	y -= rhs.y;
	return *this;
}

Vector2D Vector2D::operator-=(const float& rhs) {
	x -= rhs;
	y -= rhs;
	return *this;
}

/**********************************MULTIPLICATION******************************/
Vector2D Vector2D::operator*=(const Vector2D& rhs) {
	x *= rhs.x;
	y *= rhs.y;
	return *this;
}

Vector2D Vector2D::operator*=(const float& rhs) {
	x *= rhs;
	y *= rhs;
	return *this;
}

/**********************************DIVISION************************************/
//Precondition: rhs.x and rhs.y must be non-zero floating point numbers
//Postcondition: function returns a stack vector where each member of the 
//					  dividend is divided by its corresponding vector member in
//					  divisor.
Vector2D Vector2D::operator/=(const Vector2D& rhs) {
	x /= rhs.x;
	y /= rhs.y;
	return *this;
}

//Precondition: rhs must be a non-zero floating point number
//Postcondition: function returns a stack vector where each member of the 
//					  dividend is divided by the passed floating parameter
Vector2D Vector2D::operator/=(const float& rhs) {
	Vector2D temporary;
	x /= rhs;
	y /= rhs;
	return *this;
}


/******************************************************************************/
/*                         BINARY OPERATIONS                                  */
/******************************************************************************/

/**********************************ASSIGNMENT**********************************/    
Vector2D& Vector2D::operator=(const Vector2D& rhs) { 
	if(this != &rhs){
		x = rhs.x; 
		y = rhs.y; 
	}
	return *this;
}

/**********************************ADDITION************************************/                    
const Vector2D Vector2D::operator+(const Vector2D& rhs) {
	return(Vector2D(*this) += rhs);
}

const Vector2D Vector2D::operator+(const float& rhs) {
	return(Vector2D(*this) += rhs);
}

//Friendly overloaded + for LHS-Caller Binary addition
const Vector2D operator+(const float& lhs, Vector2D& rhs) {
	return(Vector2D(lhs + rhs.x, lhs + rhs.y));
}

/**********************************SUBTRACTION*********************************/                    
const Vector2D Vector2D::operator-(const Vector2D& rhs) {
	return(Vector2D(*this) -= rhs);
}

const Vector2D Vector2D::operator-(const float& rhs) {
	return(Vector2D(*this) -= rhs);
}

//Friendly overloaded - for LHS-Caller Binary Subtraction
const Vector2D operator-(const float& lhs, Vector2D& rhs) {
	return(Vector2D(lhs - rhs.x, lhs - rhs.y));
}
 
/**********************************MULTIPLICATION******************************/
const Vector2D Vector2D::operator*(const Vector2D& rhs) {
	return(Vector2D(*this) *= rhs);
}

const Vector2D Vector2D::operator*(const float& rhs) {
	return(Vector2D(*this) *= rhs);
}

//Friendly overloaded * for LHS-Caller Binary Multiplication
const Vector2D operator*(const float& lhs, Vector2D& rhs) {
	return(Vector2D(lhs * rhs.x, lhs * rhs.y));
}

/**********************************DIVISION************************************/
//Precondition: rhs.x and rhs.y must be non-zero floating point numbers
//Postcondition: function returns a stack vector where each member of the 
//					  dividend is divided by its corresponding vector member in
//					  divisor.
const Vector2D Vector2D::operator/(const Vector2D& rhs) {
	return(Vector2D(*this) /= rhs);
}

//Precondition: rhs must be a non-zero floating point number
//Postcondition: function returns a stack vector where each member of the 
//					  dividend is divided by the passed floating parameter
const Vector2D Vector2D::operator/(const float& rhs) {
	return(Vector2D(*this) /= rhs);
}

//Friendly overloaded / for LHS-Caller Binary Division
//Precondition: rhs must be vector with all non-zero members
//Postcondition: function returns a stack vector where each member of the 
//					  the vector is the lhs / each component of passed vector
const Vector2D operator/(const float& lhs, Vector2D& rhs) {
	return(Vector2D(lhs / rhs.x, lhs / rhs.y));
}



/******************************************************************************/
/*                         BOOLEAN OPERATIONS                                 */
/******************************************************************************/
bool Vector2D::operator==(const Vector2D& rhs) const { 
	return(x == rhs.x && y == rhs.y);
}

bool Vector2D::operator!=(const Vector2D& rhs) const {
	return !(*this == rhs);
}

/******************************************************************************/
/*                         Vector2D OPERATIONS                                  */
/******************************************************************************/
float Vector2D::dot(const Vector2D& v) {
	return(x * v.x + y * v.y);
}

//2D Vector Cross Product.  Useless in 2 dimensions, kept for future use
float Vector2D::cross(const Vector2D& v) {
	return (x * v.y - y * v.x); 
}

//Normalization function that returns the normalized vector of the caller.  Does not
//Change the vector that calls this function
Vector2D Vector2D::normal() {
	Vector2D temporary;
	float length = sqrt(pow(x, 2) + pow(y, 2));
	temporary.x = x / length;
	temporary.y = y / length;
	return(temporary);
}

//Normalization function that normalize the calling vector
void Vector2D::normalize() {
	float length = sqrt(pow(x, 2) + pow(y, 2));
	x = x / length;
	y = y / length;
}

//Friendly overloaded output operator
std::ostream& operator<<(std::ostream& out, const Vector2D& rhs) {
	return(out << "(" << rhs.x << ", " << rhs.y << " )");
}
