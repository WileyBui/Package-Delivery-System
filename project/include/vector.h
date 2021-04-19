/**
 * @file vector.h
 *
 * @copyright Lin Huynh, All rights reserved.
 */

#ifndef INC_VECTOR_H_
#define INC_VECTOR_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <vector>         // Used for vector like vector3D and vector2D
#include <string>
#include <iostream>
#include <cmath>
#include <iomanip>         // Used for set precision


namespace csci3081 {
/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief This is the interface class for the Vector3D and Vector2D classes
 *
 * This class will set up (virtual) common methods as well as attributes 
 * shared by both Vector3D and vector2D class. Also has some friends 
 * functions to find relationship between more than one vector instances
 */
class Vector {
    protected:
        float x,y,z;    //!< Coordinates of a vector
    public: 
        /**
        *  @brief This function uses to set x coordinator of a vector instance
        */
        void SetX(float x_);

        /**
        *  @brief This function uses to set z coordinator of a vector instance
        */
        void SetZ(float z_);

        /**
        *  @brief This function uses to get x coordinator of a vector instance
        */
        float GetX() const {return x;};

        /**
        *  @brief This function uses to get z coordinator of a vector instance
        */
        float GetZ() const {return z;};

        /**
        *  @brief This function uses to get y coordinator of a vector instance
        */
        float GetY() const {return y;};

        /**
        *  @brief This function returns the magitude of a vector instance
        */
        float Magnitude();

        /**
        * @brief Compute the dot product (float variable) between two vectors 
        * instances
        * @param[in] v1        Vector instance
        * @param[in] v2        Vector instance
        * @return float    Dot product of v1 and v2
        */
        friend float DotProduct(const Vector& v1, const Vector& v2);

        /**
        * @brief Compute the distance (float variable) between two vectors 
        * instances
        * @param[in] v1        Vector instance
        * @param[in] v2        Vector instance
        * @return float    Distance of v1 and v2
        */
        friend float Distance(const Vector& v1, const Vector& v2);

        /**
        * @brief Convert vector distance to std::vector<float> 
        * instances
        * @param[in] v                     Vector instance
        * @return std::vector<float>   Have x,y,z as its elements
        */
        friend std::vector<float> toVectorFloat(Vector& v);

        /**
        * @brief Convert vector distance to std::vector<float> 
        * instances
        * @param[in] v                     Vector instance
        * @return  True if argument vector is equal to current object
        *               False otherwise
        */
        bool operator == (const Vector&);

        /**
        * @brief Function to print the coordinate of a vector instance
        */
        virtual void Print()  = 0;  
};

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief This is the Vector3D class
 *
 * This class instantiates a Vector3D object and with basic overload math
 * expression that can be done with Vector in 3D
 */
class Vector3D: public Vector {

    public:
        /**
        * @brief Constructor.
        * This sets up an instance of Vector3D with 3 coordinates as arguments
        * @param[in] x_     float, x-coordinate
        * @param[in] y_     float, y-coordinate
        * @param[in] z_     float, z-coordinate
        */
        Vector3D(float x_, float y_, float z_);

        /**
        * @brief Constructor.
        * This sets up an instance of Vector3D with 3 coordinates as arguments
        * @param[in] arg std::vector<float> that stores coordinates
        */
        Vector3D(std::vector<float> arg);

        /**
        * @brief Constructor.
        * This sets up an instance of Vector3D with zero coordinates
        */
        Vector3D();

        /**
        * @brief Copy Constructor.
        * This creates a new instance of Vector3D that has the same content
        * as the Vector3D argument
        * @param[in] copy Vector3D instance that wants to be copied
        */
        Vector3D(const Vector3D&);

        /**
        *  @brief This function uses to set y coordinator of a vector instance
        * @param y_     float, new y-coordinate
        */
        void SetY(float y_);

        /**
        *  @brief overloading operator + to do addition between Vector3D instances
        * @param other the right hand side Vector3D of the addition 
        */
        Vector3D operator +(const Vector3D&);      

        /**
        *  @brief overloading operator - to do addition between Vector3D instances
        * @param other the right hand side Vector3D of the subtraction 
        */
        Vector3D operator -(const Vector3D&);  

        /**
        *  @brief overloading operator * to do multiply a Vector3D instance to a float
        * @param other float factor that want to multiply the Vector3D with
        */   
        Vector3D operator *(float);    

        /**
        *  @brief overloading operator / to do division a Vector3D instance to a float
        * @param other float factor that want to divide the Vector3D with
        */   
        Vector3D operator /(float);  

        /**
        *  @brief overloading operator = to copy one Vector3D to another
        * @param cpy the Vector3D object that wants to copy 
        */     
        Vector3D& operator =(const Vector3D&);

        /**
        *  @brief This function normalizes a Vector3D instance
        */
        Vector3D Normalize();

        /**
        * @copydoc Vector::Print()
        */
        void Print();

        bool IsWithinXandZRange(const Vector3D&, float precision);
};

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief This is the Vector2D class
 *
 * This class instantiates a Vector2D object and with basic overload math
 * expression that can be done with Vector in 2D
 */
class Vector2D: public Vector {
    public:
        /**
        * @brief Constructor.
        * This sets up an instance of Vector2D with zero coordinates
        */
        Vector2D();

        /**
        * @brief Constructor.
        * This sets up an instance of Vector2D with 2 coordinates as arguments
        * @param[in] arg std::vector<float> that stores coordinates
        */
        Vector2D(std::vector<float> arg);

        /**
        * @brief Constructor.
        * This sets up an instance of Vector3D with 3 coordinates as arguments
        * @param[in] x_     float, x-coordinate
        * @param[in] z_     float, z-coordinate
        */
        Vector2D(float x_, float z_);

        /**
        * @brief Copy Constructor.
        * This creates a new instance of Vector2D that has the same content
        * as the Vector2D argument
        * @param[in] copy Vector2D instance that wants to be copied
        */        
        Vector2D(const Vector2D&);
        
        /**
        *  @brief overloading operator + to do addition between Vector2D instances
        * @param other the right hand side Vector2D of the addition 
        */
        Vector2D operator +(const Vector2D&);      

        /**
        *  @brief overloading operator - to do addition between Vector2D instances
        * @param other the right hand side Vector2D of the subtraction 
        */
        Vector2D operator -(const Vector2D&);     

        /**
        *  @brief overloading operator * to do multiply a Vector2D instance to a float
        * @param other float factor that want to multiply the Vector2D with
        */   
        Vector2D operator *(float);    

        /**
        *  @brief overloading operator / to do division a Vector2D instance to a float
        * @param other float factor that want to divide the Vector2D with
        */  
        Vector2D operator /(float);     

        /**
        *  @brief overloading operator = to copy one Vector2D to another
        * @param cpy the Vector2D object that wants to copy 
        */ 
        Vector2D& operator =(const Vector2D&);     

        /**
        *  @brief This function normalizes a Vector2D instance
        */
        Vector2D Normalize();

        /**
        * @copydoc Vector::Print()
        */
        void Print();
};

/**
* @brief This function converts a Vector3D instance to a Vector2D
* @param[in] other Vector3D object
* @return Vector2D object
*/
Vector2D to2D(Vector3D&);

/**
* @brief This function converts a Vector2D instance to a Vector3D
* @param[in] other Vector2D object
* @return Vector3D object
*/
Vector3D to3D(Vector2D&);

/**
* @brief This function computes the cross product between two vector objects
* @param[in] v1            Vector object
* @param[in] v2            Vector object
* @return Vector3D object
*/
Vector3D CrossProduct(const Vector& v1, const Vector& v2);
} // ending namepsace

#endif /* INC_VECTOR_H_ */