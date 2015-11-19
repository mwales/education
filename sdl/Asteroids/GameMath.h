#pragma once

#include <iostream>

// Leverage boost vector for most vector operations
#include <boost/numeric/ublas/vector.hpp>
#include <boost/numeric/ublas/io.hpp>

//typedef boost::numeric::ublas::vector<float> XYPair;

class XYPair : public boost::numeric::ublas::vector<float>
{
public:
   XYPair();

   XYPair(XYPair const & rhs);

   XYPair(float x, float y);
};



class GameMath
{
public:


   static XYPair GetUnitVector(float angle);

   static float VectorMagnitude(XYPair v);

   static std::string VectorToString(XYPair v);
};
