#pragma once
#include "Vec3.h"
#include <format>
#include <cassert>
#include <iostream>

class Vec3OpsTest
{
public:
	static void RunVec3Tests();
	static std::string TestHelloWorld();
	static std::string Vec3DebugStr(const Vec3& v);
	static void TestCross(const Vec3& a, const Vec3& b, const Vec3& expected);
	static void TestDot(const Vec3& a, const Vec3& b, const float& expected);
	static void TestDistanceSquared(const Vec3& a, const Vec3& b, const float& expected);
	static void TestDistance(const Vec3& a, const Vec3& b, const float& expected);
	static void TestMagnitude(const Vec3& v, const float& expected);
	static void TestNormalize(const Vec3& v, const Vec3& expected);
	static void TestIsNormalized(const Vec3& v, const bool& expected);
	static void TestLerp(const Vec3& a, const Vec3& b, const float& t, const Vec3& expected);

	static void TestTheta(const Vec3& a, const Vec3 b, const float& expected);
	static void TestReflection(const Vec3& v, const Vec3& n, const Vec3& expected);

private:
	static bool AreEqual(const Vec3& a, const Vec3& b);
	static void log(const std::string& msg);
	static std::string DebugFloat(const float& f);
	static std::string DebugBool(const bool& b);
};

void Vec3OpsTest::log(const std::string& msg)
{
	std::cout << msg << "\n";
}

std::string Vec3OpsTest::TestHelloWorld()
{
	return "Hello World";
}
std::string Vec3OpsTest::Vec3DebugStr(const Vec3& v)
{
	std::string xStr = std::format("{:.2f}", v.x);
	std::string yStr = std::format("{:.2f}", v.y);
	std::string zStr = std::format("{:.2f}", v.z);
	return "(" + xStr + ", " + yStr + ", " + zStr + ")";
}
std::string Vec3OpsTest::DebugFloat(const float& f)
{
	return std::format("{:.2f}", f);
}
std::string Vec3OpsTest::DebugBool(const bool& b)
{
	std::string d = b ? "TRUE" : "FALSE";
	return d;
}
bool Vec3OpsTest::AreEqual(const Vec3& a, const Vec3& b)
{
	return (Vec3::isFloatCloseEnough(a.x, b.x) && Vec3::isFloatCloseEnough(a.y, b.y) && Vec3::isFloatCloseEnough(a.z, b.z));
}

void Vec3OpsTest::TestCross(const Vec3& a, const Vec3& b, const Vec3& expected)
{
	log("--CROSS--");
	log("Input A:  " + Vec3DebugStr(a));
	log("Input B:  " + Vec3DebugStr(b));
	log("Expected: " + Vec3DebugStr(expected));
	log("Observed: " + Vec3DebugStr(a.cross(b)));
	assert(AreEqual(a.cross(b), expected) && "CROSS FAILED :(");
	log("CROSS PASSED!\n");
}
void Vec3OpsTest::TestDot(const Vec3& a, const Vec3& b, const float& expected)
{
	log("--DOT--");
	log("Input A:  " + Vec3DebugStr(a));
	log("Input B:  " + Vec3DebugStr(b));
	log("Expected: " + DebugFloat(expected));
	log("Observed: " + DebugFloat(a.dot(b)));
	assert(Vec3::isFloatCloseEnough(a.dot(b), expected) && "DOT FAILED:(");
	log("DOT PASSED!\n");
}
void Vec3OpsTest::TestDistanceSquared(const Vec3& a, const Vec3& b, const float& expected)
{
	log("--DISTANCE SQUARED--");
	log("Input A:  " + Vec3DebugStr(a));
	log("Input B:  " + Vec3DebugStr(b));
	log("Expected: " + DebugFloat(expected));
	log("Observed: " + DebugFloat(a.distanceSquared(b)));
	assert(Vec3::isFloatCloseEnough(a.distanceSquared(b), expected) && "DISTANCE SQUARED FAILED :(");
	log("DISTANCE SQUARED PASSED!\n");
}
void Vec3OpsTest::TestDistance(const Vec3& a, const Vec3& b, const float& expected)
{
	log("--DISTANCE--");
	log("Input A:  " + Vec3DebugStr(a));
	log("Input B:  " + Vec3DebugStr(b));
	log("Expected: " + DebugFloat(expected));
	log("Observed: " + DebugFloat(a.distance(b)));
	assert(Vec3::isFloatCloseEnough(a.distance(b), expected) && "DISTANCE FAILED :(");
	log("DISTANCE PASSED!\n");
}
void Vec3OpsTest::TestMagnitude(const Vec3& v, const float& expected)
{

	log("--MAGNITUDE--");
	log("Input:    " + Vec3DebugStr(v));
	log("Expected: " + DebugFloat(expected));
	log("Observed: " + DebugFloat(v.magnitude()));
	assert(Vec3::isFloatCloseEnough(v.magnitude(), expected) && "MAGNITUDE FAILED :(");
	log("MAGNITUDE PASSED!\n");
}
void Vec3OpsTest::TestNormalize(const Vec3& v, const Vec3& expected)
{
	log("--NORMALIZE--");
	log("Input:    " + Vec3DebugStr(v));
	log("Expected: " + Vec3DebugStr(expected));
	log("Observed: " + Vec3DebugStr(v.normalize()));
	assert(AreEqual(v.normalize(), expected) && "NORMALIZE FAILED :(");
	log("NORMALIZE PASSED!\n");
}
void Vec3OpsTest::TestIsNormalized(const Vec3& v, const bool& expected)
{
	log("--IS NORMALIZED--");
	log("Input:    " + Vec3DebugStr(v));
	log("Expected: " + DebugBool(expected));
	log("Expected: " + DebugBool(v.isNormalized()));
	assert(v.isNormalized() == expected && "IS_NORMALIZED FAILED :(");
	log("IS NORMALIZED PASSED\n");
}
void Vec3OpsTest::TestLerp(const Vec3& a, const Vec3& b, const float& t, const Vec3& expected)
{
	log("--LERP--");
	log("Input A:  " + Vec3DebugStr(a));
	log("Input B:  " + Vec3DebugStr(b));
	log("Input C:  " + DebugFloat(t));
	log("Expected: " + Vec3DebugStr(expected));
	log("Observed: " + Vec3DebugStr(a.lerp(b, t)));
	assert(AreEqual(a.lerp(b, t), expected) && "LERP FAILED :(");
	log("LERP PASSED!\n");
}
void Vec3OpsTest::TestTheta(const Vec3& a, const Vec3 b, const float& expected)
{
	log("--THETA--");
	log("Input A:  " + Vec3DebugStr(a));
	log("Input B:  " + Vec3DebugStr(b));
	log("Expected: " + DebugFloat(expected));
	log("Observed: " + DebugFloat(a.theta(b)));
	assert(Vec3::isFloatCloseEnough(a.theta(b), expected) && "THETA FAILED");
	log("THETA PASSED!\n");
}
void Vec3OpsTest::TestReflection(const Vec3& v, const Vec3& n, const Vec3& expected)
{
	log("--REFLECTION--");
	log("Input A:  " + Vec3DebugStr(v));
	log("Input B:  " + Vec3DebugStr(n));
	log("Expected: " + Vec3DebugStr(expected));
	log("Observed: " + Vec3DebugStr(v.reflection(n)));
	assert(AreEqual(v.reflection(n), expected) && "REFLECTION FAILED");
	log("REFLECTION PASSED\n");
}
//

void Vec3OpsTest::RunVec3Tests()
{
	TestCross(Vec3(1, 0, 0), Vec3(0, 1, 0), Vec3(0, 0, 1));
	TestCross(Vec3(0, 1, 0), Vec3(1, 0, 0), Vec3(0, 0, -1));
	TestCross(Vec3(1, 0, 0), Vec3(1, 0, 0), Vec3(0, 0, 0));
	TestCross(Vec3(0, 0, 0), Vec3(1, 2, 3), Vec3(0, 0, 0));

	TestDot(Vec3(1, 0, 0), Vec3(1, 0, 0), 1);
	TestDot(Vec3(1, 0, 0), Vec3(0, 1, 0), 0);
	TestDot(Vec3(1, 2, 3), Vec3(-1, -2, -3), -14);
	TestDot(Vec3(0, 0, 0), Vec3(5, 6, 7), 0);

	TestDistanceSquared(Vec3(0, 0, 0), Vec3(0, 0, 0), 0);
	TestDistanceSquared(Vec3(0, 0, 0), Vec3(1, 0, 0), 1);
	TestDistanceSquared(Vec3(1, 2, 3), Vec3(4, 6, 3), 25);
	TestDistanceSquared(Vec3(-1, -2, -3), Vec3(1, 2, 3), 56);

	TestDistance(Vec3(0, 0, 0), Vec3(0, 0, 0), 0);
	TestDistance(Vec3(0, 0, 0), Vec3(1, 0, 0), 1);
	TestDistance(Vec3(1, 2, 3), Vec3(4, 6, 3), 5);

	TestMagnitude(Vec3(0, 0, 0), 0);
	TestMagnitude(Vec3(1, 0, 0), 1);
	TestMagnitude(Vec3(1, 2, 2), 3);
	TestMagnitude(Vec3(-3, 4, 0), 5);
	TestMagnitude(Vec3::unit(), 1);

	TestNormalize(Vec3(0, 0, 0), Vec3(0, 0, 0));
	TestNormalize(Vec3(1, 0, 0), Vec3(1, 0, 0));
	TestNormalize(Vec3(0, 3, 0), Vec3(0, 1, 0));
	TestNormalize(Vec3(1, 2, 2), Vec3((float)1 / (float)3, (float)2 / (float)3, (float)2 / (float)3));
	TestNormalize(Vec3::one(), Vec3::unit());

	TestIsNormalized(Vec3(1, 0, 0), true);
	TestIsNormalized(Vec3(0, 1, 0), true);
	TestIsNormalized(Vec3(1, 0, 1), false);
	TestIsNormalized(Vec3::unit(), true);

	TestLerp(Vec3(0, 0, 0), Vec3(10, 0, 0), 0, Vec3(0, 0, 0));
	TestLerp(Vec3(0, 0, 0), Vec3(10, 0, 0), 1, Vec3(10, 0, 0));
	TestLerp(Vec3(0, 0, 0), Vec3(10, 0, 0), .5f, Vec3(5, 0, 0));
	TestLerp(Vec3(1, 2, 3), Vec3(3, 6, 9), .25f, Vec3(1.5f, 3.0f, 4.5f));
	TestLerp(Vec3(0, 0, 0), Vec3(10, 0, 0), -1, Vec3(0, 0, 0));
	TestLerp(Vec3(0, 0, 0), Vec3(10, 0, 0), 2, Vec3(10, 0, 0));

	TestTheta(Vec3(1, 0, 0), Vec3(1, 0, 0), 0.0f);
	TestTheta(Vec3(1, 0, 0), Vec3(-1, 0, 0), 3.14159f);

	TestReflection(Vec3(0, 0, 0), Vec3(0, 1, 0), Vec3(0, 0, 0));
	TestReflection(Vec3(1, 0, 0), Vec3(1, 0, 0), Vec3(-1, 0, 0));
	TestReflection(Vec3(1, -1, 0), Vec3(0, 1, 0), Vec3(1, 1, 0));
	TestReflection(Vec3(1, -1, 0), Vec3(0, 2, 0), Vec3(1, 1, 0));
}

/*
Hello World!
--CROSS--
Input A:  (1.00, 0.00, 0.00)
Input B:  (0.00, 1.00, 0.00)
Expected: (0.00, 0.00, 1.00)
Observed: (0.00, 0.00, 1.00)
CROSS PASSED!

--CROSS--
Input A:  (0.00, 1.00, 0.00)
Input B:  (1.00, 0.00, 0.00)
Expected: (0.00, 0.00, -1.00)
Observed: (0.00, 0.00, -1.00)
CROSS PASSED!

--CROSS--
Input A:  (1.00, 0.00, 0.00)
Input B:  (1.00, 0.00, 0.00)
Expected: (0.00, 0.00, 0.00)
Observed: (0.00, 0.00, 0.00)
CROSS PASSED!

--CROSS--
Input A:  (0.00, 0.00, 0.00)
Input B:  (1.00, 2.00, 3.00)
Expected: (0.00, 0.00, 0.00)
Observed: (0.00, 0.00, 0.00)
CROSS PASSED!

--DOT--
Input A:  (1.00, 0.00, 0.00)
Input B:  (1.00, 0.00, 0.00)
Expected: 1.00
Observed: 1.00
DOT PASSED!

--DOT--
Input A:  (1.00, 0.00, 0.00)
Input B:  (0.00, 1.00, 0.00)
Expected: 0.00
Observed: 0.00
DOT PASSED!

--DOT--
Input A:  (1.00, 2.00, 3.00)
Input B:  (-1.00, -2.00, -3.00)
Expected: -14.00
Observed: -14.00
DOT PASSED!

--DOT--
Input A:  (0.00, 0.00, 0.00)
Input B:  (5.00, 6.00, 7.00)
Expected: 0.00
Observed: 0.00
DOT PASSED!

--DISTANCE SQUARED--
Input A:  (0.00, 0.00, 0.00)
Input B:  (0.00, 0.00, 0.00)
Expected: 0.00
Observed: 0.00
DISTANCE SQUARED PASSED!

--DISTANCE SQUARED--
Input A:  (0.00, 0.00, 0.00)
Input B:  (1.00, 0.00, 0.00)
Expected: 1.00
Observed: 1.00
DISTANCE SQUARED PASSED!

--DISTANCE SQUARED--
Input A:  (1.00, 2.00, 3.00)
Input B:  (4.00, 6.00, 3.00)
Expected: 25.00
Observed: 25.00
DISTANCE SQUARED PASSED!

--DISTANCE SQUARED--
Input A:  (-1.00, -2.00, -3.00)
Input B:  (1.00, 2.00, 3.00)
Expected: 56.00
Observed: 56.00
DISTANCE SQUARED PASSED!

--DISTANCE--
Input A:  (0.00, 0.00, 0.00)
Input B:  (0.00, 0.00, 0.00)
Expected: 0.00
Observed: 0.00
DISTANCE PASSED!

--DISTANCE--
Input A:  (0.00, 0.00, 0.00)
Input B:  (1.00, 0.00, 0.00)
Expected: 1.00
Observed: 1.00
DISTANCE PASSED!

--DISTANCE--
Input A:  (1.00, 2.00, 3.00)
Input B:  (4.00, 6.00, 3.00)
Expected: 5.00
Observed: 5.00
DISTANCE PASSED!

--MAGNITUDE--
Input:    (0.00, 0.00, 0.00)
Expected: 0.00
Observed: 0.00
MAGNITUDE PASSED!

--MAGNITUDE--
Input:    (1.00, 0.00, 0.00)
Expected: 1.00
Observed: 1.00
MAGNITUDE PASSED!

--MAGNITUDE--
Input:    (1.00, 2.00, 2.00)
Expected: 3.00
Observed: 3.00
MAGNITUDE PASSED!

--MAGNITUDE--
Input:    (-3.00, 4.00, 0.00)
Expected: 5.00
Observed: 5.00
MAGNITUDE PASSED!

--MAGNITUDE--
Input:    (0.58, 0.58, 0.58)
Expected: 1.00
Observed: 1.00
MAGNITUDE PASSED!

--NORMALIZE--
Input:    (0.00, 0.00, 0.00)
Expected: (0.00, 0.00, 0.00)
Observed: (0.00, 0.00, 0.00)
NORMALIZE PASSED!

--NORMALIZE--
Input:    (1.00, 0.00, 0.00)
Expected: (1.00, 0.00, 0.00)
Observed: (1.00, 0.00, 0.00)
NORMALIZE PASSED!

--NORMALIZE--
Input:    (0.00, 3.00, 0.00)
Expected: (0.00, 1.00, 0.00)
Observed: (0.00, 1.00, 0.00)
NORMALIZE PASSED!

--NORMALIZE--
Input:    (1.00, 2.00, 2.00)
Expected: (0.33, 0.67, 0.67)
Observed: (0.33, 0.67, 0.67)
NORMALIZE PASSED!

--NORMALIZE--
Input:    (1.00, 1.00, 1.00)
Expected: (0.58, 0.58, 0.58)
Observed: (0.58, 0.58, 0.58)
NORMALIZE PASSED!

--IS NORMALIZED--
Input:    (1.00, 0.00, 0.00)
Expected: TRUE
Expected: TRUE
IS NORMALIZED PASSED

--IS NORMALIZED--
Input:    (0.00, 1.00, 0.00)
Expected: TRUE
Expected: TRUE
IS NORMALIZED PASSED

--IS NORMALIZED--
Input:    (1.00, 0.00, 1.00)
Expected: FALSE
Expected: FALSE
IS NORMALIZED PASSED

--IS NORMALIZED--
Input:    (0.58, 0.58, 0.58)
Expected: TRUE
Expected: TRUE
IS NORMALIZED PASSED

--LERP--
Input A:  (0.00, 0.00, 0.00)
Input B:  (10.00, 0.00, 0.00)
Input C:  0.00
Expected: (0.00, 0.00, 0.00)
Observed: (0.00, 0.00, 0.00)
LERP PASSED!

--LERP--
Input A:  (0.00, 0.00, 0.00)
Input B:  (10.00, 0.00, 0.00)
Input C:  1.00
Expected: (10.00, 0.00, 0.00)
Observed: (10.00, 0.00, 0.00)
LERP PASSED!

--LERP--
Input A:  (0.00, 0.00, 0.00)
Input B:  (10.00, 0.00, 0.00)
Input C:  0.50
Expected: (5.00, 0.00, 0.00)
Observed: (5.00, 0.00, 0.00)
LERP PASSED!

--LERP--
Input A:  (1.00, 2.00, 3.00)
Input B:  (3.00, 6.00, 9.00)
Input C:  0.25
Expected: (1.50, 3.00, 4.50)
Observed: (1.50, 3.00, 4.50)
LERP PASSED!

--LERP--
Input A:  (0.00, 0.00, 0.00)
Input B:  (10.00, 0.00, 0.00)
Input C:  -1.00
Expected: (0.00, 0.00, 0.00)
Observed: (0.00, 0.00, 0.00)
LERP PASSED!

--LERP--
Input A:  (0.00, 0.00, 0.00)
Input B:  (10.00, 0.00, 0.00)
Input C:  2.00
Expected: (10.00, 0.00, 0.00)
Observed: (10.00, 0.00, 0.00)
LERP PASSED!

--THETA--
Input A:  (1.00, 0.00, 0.00)
Input B:  (1.00, 0.00, 0.00)
Expected: 0.00
Observed: 0.00
THETA PASSED!

--THETA--
Input A:  (1.00, 0.00, 0.00)
Input B:  (-1.00, 0.00, 0.00)
Expected: 3.14
Observed: 3.14
THETA PASSED!

--REFLECTION--
Input A:  (0.00, 0.00, 0.00)
Input B:  (0.00, 1.00, 0.00)
Expected: (0.00, 0.00, 0.00)
Observed: (0.00, 0.00, 0.00)
REFLECTION PASSED

--REFLECTION--
Input A:  (1.00, 0.00, 0.00)
Input B:  (1.00, 0.00, 0.00)
Expected: (-1.00, 0.00, 0.00)
Observed: (-1.00, 0.00, 0.00)
REFLECTION PASSED

--REFLECTION--
Input A:  (1.00, -1.00, 0.00)
Input B:  (0.00, 1.00, 0.00)
Expected: (1.00, 1.00, 0.00)
Observed: (1.00, 1.00, 0.00)
REFLECTION PASSED

--REFLECTION--
Input A:  (1.00, -1.00, 0.00)
Input B:  (0.00, 2.00, 0.00)
Expected: (1.00, 1.00, 0.00)
Observed: (1.00, 1.00, 0.00)
REFLECTION PASSED
*/