#pragma once
#include <iostream>

class Vector2D {
public:
	float x;
	float y;

	//default constructor
	Vector2D();
	//constructor
	Vector2D(float x, float y);

	/*
	* performs a math action to a vector
	* @params {const} we do not want to change the second vector
	* 
	* @returns returns reference to the vector class
	*/
	Vector2D& Add(const Vector2D& vec);
	Vector2D& Subtract(const Vector2D& vec);
	Vector2D& Multiply(const Vector2D& vec);
	Vector2D& Divide(const Vector2D& vec);

	/*
	* friend declaration grants a function or another class access to private and protected members of the class
	* operator overloading 
	* 
	* @params	{Vector2D} reference to 2 different Vectors
	* 
	* @returns returns reference to a vector2D
	*/
	friend Vector2D& operator+(Vector2D& v1, const Vector2D& v2);
	friend Vector2D& operator-(Vector2D& v1, const Vector2D& v2);
	friend Vector2D& operator*(Vector2D& v1, const Vector2D& v2);
	friend Vector2D& operator/(Vector2D& v1, const Vector2D& v2);



	Vector2D& operator+=(const Vector2D& vec);
	Vector2D& operator-=(const Vector2D& vec);
	Vector2D& operator*=(const Vector2D& vec);
	Vector2D& operator/=(const Vector2D& vec);

	
	/*
	* return reference to output stream(osstream)
	* ostream is output stream that can write sequences of characters and represent other kinds of data
	* overloading the operator for our class that such that prints out the vector as (x,y)
	* https://docs.microsoft.com/en-us/cpp/standard-library/overloading-the-output-operator-for-your-own-classes?view=msvc-170
	* 
	* @params {ostream}		reference to an output stream
	* @params {Vector2D}	reference to a vector
	* 
	*/
	friend std::ostream& operator<<(std::ostream& stream, const Vector2D& vec);
};