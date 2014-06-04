/*
Yates Monteith
CPSC 870: OO Development
Milestone 1: Vecto2D Class
9/7/2010
Class Header
*/

#ifndef vector2d__H
#define vector2d__H

class Vector2D {
   public:
   
   	//Constructors
      Vector2D() : x(0.0), y(0.0) {}
      Vector2D(const Vector2D& v) : x(v.x), y(v.y) {}
      Vector2D(const float& vx, const float& vy) : x(vx), y(vy) {}
      
      //Empty destructor, no heap memory allocated
      ~Vector2D() {}
      
      //Accessors
      float getX() { return x; }
      float getY() { return y; }

      //Mutators
      void setX(float xx) { x = xx; }
      void setY(float yy) { y = yy; }
      
      //Overloaded Accessors
      float& operator[](const int index);
      const float& operator[](const int index) const;
      
      //Overloaded assignment
      Vector2D& operator=(const Vector2D& rhs);
      
      //Overloaded binary arithmetic operators
		const Vector2D operator+(const float& rhs);
		const Vector2D operator+(const Vector2D& rhs);
		
		const Vector2D operator-(const float& rhs);
		const Vector2D operator-(const Vector2D& rhs);
		
		const Vector2D operator*(const float& rhs);
		const Vector2D operator*(const Vector2D& rhs);
		
		const Vector2D operator/(const float& rhs);
		const Vector2D operator/(const Vector2D& rhs);
    	
    	//Overloaded compound arithmetic operators
		Vector2D operator+=(const float& rhs);
	   Vector2D operator+=(const Vector2D& rhs);
		
		Vector2D operator-=(const float& rhs);
		Vector2D operator-=(const Vector2D& rhs);

      Vector2D operator*=(const float& rhs);
		Vector2D operator*=(const Vector2D& rhs);
		
      Vector2D operator/=(const float& rhs);
		Vector2D operator/=(const Vector2D& rhs);
		
		//Boolean operators
      bool operator==(const Vector2D& rhs) const;
      bool operator!=(const Vector2D& rhs) const;
      
      //Vector operations
      float dot(const Vector2D& v);
      float cross(const Vector2D& v);
      Vector2D normal();
      void normalize();
      
      //Overloaded output operator
      friend std::ostream& operator<<(std::ostream& out, const Vector2D& rhs);
      
      //Friend functions for overloaded lhs-caller binary arithmetic operations
      friend const Vector2D operator+(const float& lhs, Vector2D& rhs);
      friend const Vector2D operator-(const float& lhs, Vector2D& rhs);      
      friend const Vector2D operator*(const float& lhs, Vector2D& rhs);      
      friend const Vector2D operator/(const float& lhs, Vector2D& rhs);      

   private:
      float x;
      float y;
};
#endif
