#include "Vector2D.h"

//default constructor
Vector2D::Vector2D() {
	x = 0.0f;
	y = 0.0f;
}

//default constructor
Vector2D::Vector2D(float x, float y) {
	this->x = x;
	this->y = y;
}

/*
* basic math functions that takes a vector and changes the calling vector
*/
Vector2D& Vector2D::Add(const Vector2D& vec) {
	//add the values to the current vector
	this->x += vec.x;
	this->y += vec.y;

	//return itself
	return *this;
}

Vector2D& Vector2D::Subtract(const Vector2D& vec)
{
	//add the values to the current vector
	this->x -= vec.x;
	this->y -= vec.y;

	//return itself
	return *this;
}

Vector2D& Vector2D::Multiply(const Vector2D& vec)
{
	//add the values to the current vector
	this->x *= vec.x;
	this->y *= vec.y;

	//return itself
	return *this;
}

Vector2D& Vector2D::Divide(const Vector2D& vec)
{
	//add the values to the current vector
	this->x /= vec.x;
	this->y /= vec.y;

	//return itself
	return *this;
}


/*
* basic math functions given 2 vectors
*/
Vector2D& operator+(Vector2D& v1, const Vector2D& v2)
{
	return v1.Add(v2);
}

Vector2D& operator-(Vector2D& v1, const Vector2D& v2)
{
	return v1.Subtract(v2);
}

Vector2D& operator*(Vector2D& v1, const Vector2D& v2)
{
	return v1.Multiply(v2);
}

Vector2D& operator/(Vector2D& v1, const Vector2D& v2)
{
	return v1.Divide(v2);
}




/*
* basic math functions that uses a x= thing, where x is the operand 
*/
Vector2D& Vector2D::operator+=(const Vector2D& vec)
{
	this->Add(vec);
	return *this;
}

Vector2D& Vector2D::operator-=(const Vector2D& vec)
{
	this->Subtract(vec);
	return *this;
}

Vector2D& Vector2D::operator*=(const Vector2D& vec)
{
	this->Multiply(vec);
	return *this;
}

Vector2D& Vector2D::operator/=(const Vector2D& vec)
{
	this->Divide(vec);
	return *this;
}

//print out vector so it looks like (x,y)
std::ostream& operator<<(std::ostream& stream, const Vector2D& vec){
	stream << "(" << vec.x << "," << vec.y << ")";
	return stream;
}

//takes a reference to an integer to multiply vector by scalar number
Vector2D& Vector2D::operator*(const int& i) {
	//multiply (x,y) by a scalar number
	this->x *= i;
	this->y *= i;

	//return the reference to itself
	return *this;
}
//zero out the vector and set the position of the object to be the start
Vector2D& Vector2D::Zero() {
	this->x = 0;
	this->y = 0;

	return *this;
}

