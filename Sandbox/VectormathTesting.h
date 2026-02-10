//#pragma once
//#include "Vec3.h"
//#include <format>
//#include <cassert>
//#include <iostream>

/*
* 
* --DEPRECATED--
* Now implemented in TestLab project
* 
* 
class VMathTests
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

void VMathTests::log(const std::string& msg)
{
	std::cout << msg << "\n";
}

std::string VMathTests::TestHelloWorld()
{
	return "Hello World";
}
std::string VMathTests::Vec3DebugStr(const Vec3& v)
{
	std::string xStr = std::format("{:.2f}", v.x);
	std::string yStr = std::format("{:.2f}", v.y);
	std::string zStr = std::format("{:.2f}", v.z);
	return "(" + xStr + ", " + yStr + ", " + zStr + ")";
}
std::string VMathTests::DebugFloat(const float& f)
{
	return std::format("{:.2f}", f);
}
std::string VMathTests::DebugBool(const bool& b)
{
	std::string d = b ? "TRUE" : "FALSE";
	return d;
}
bool VMathTests::AreEqual(const Vec3& a, const Vec3& b)
{
	return (Vec3::isFloatCloseEnough(a.x, b.x) && Vec3::isFloatCloseEnough(a.y, b.y) && Vec3::isFloatCloseEnough(a.z, b.z));
}

void VMathTests::TestCross(const Vec3& a, const Vec3& b, const Vec3& expected)
{
	log("--CROSS--");
	log("Input A:  " + Vec3DebugStr(a));
	log("Input B:  " + Vec3DebugStr(b));
	log("Expected: " + Vec3DebugStr(expected));
	log("Observed: " + Vec3DebugStr(a.cross(b)));
	assert(AreEqual(a.cross(b), expected) && "CROSS FAILED :(");
	log("CROSS PASSED!\n");
}
void VMathTests::TestDot(const Vec3& a, const Vec3& b, const float& expected)
{
	log("--DOT--");
	log("Input A:  " + Vec3DebugStr(a));
	log("Input B:  " + Vec3DebugStr(b));
	log("Expected: " + DebugFloat(expected));
	log("Observed: " + DebugFloat(a.dot(b)));
	assert(Vec3::isFloatCloseEnough( a.dot(b), expected) && "DOT FAILED:(");
	log("DOT PASSED!\n");
}
void VMathTests::TestDistanceSquared(const Vec3& a, const Vec3& b, const float& expected)
{
	log("--DISTANCE SQUARED--");
	log("Input A:  " + Vec3DebugStr(a));
	log("Input B:  " + Vec3DebugStr(b));
	log("Expected: " + DebugFloat(expected));
	log("Observed: " + DebugFloat(a.distanceSquared(b)));
	assert( Vec3::isFloatCloseEnough( a.distanceSquared(b), expected) && "DISTANCE SQUARED FAILED :(");
	log("DISTANCE SQUARED PASSED!\n");
}
void VMathTests::TestDistance(const Vec3& a, const Vec3& b, const float& expected)
{
	log("--DISTANCE--");
	log("Input A:  " + Vec3DebugStr(a));
	log("Input B:  " + Vec3DebugStr(b));
	log("Expected: " + DebugFloat(expected));
	log("Observed: " + DebugFloat(a.distance(b)));
	assert(Vec3::isFloatCloseEnough(a.distance(b), expected) && "DISTANCE FAILED :(");
	log("DISTANCE PASSED!\n");
}
void VMathTests::TestMagnitude(const Vec3& v, const float& expected)
{

	log("--MAGNITUDE--");
	log("Input:    " + Vec3DebugStr(v));
	log("Expected: " + DebugFloat(expected));
	log("Observed: " + DebugFloat(v.magnitude()));
	assert(Vec3::isFloatCloseEnough(v.magnitude(), expected) && "MAGNITUDE FAILED :(");
	log("MAGNITUDE PASSED!\n");
}
void VMathTests::TestNormalize(const Vec3& v, const Vec3& expected)
{
	log("--NORMALIZE--");
	log("Input:    " + Vec3DebugStr(v));
	log("Expected: " + Vec3DebugStr(expected));
	log("Observed: " + Vec3DebugStr(v.normalize()));
	assert(AreEqual(v.normalize(), expected) && "NORMALIZE FAILED :(");
	log("NORMALIZE PASSED!\n");
}
void VMathTests::TestIsNormalized(const Vec3& v, const bool& expected)
{
	log("--IS NORMALIZED--");
	log("Input:    " + Vec3DebugStr(v));
	log("Expected: " + DebugBool(expected));
	log("Expected: " + DebugBool(v.isNormalized()));
	assert(v.isNormalized() == expected && "IS_NORMALIZED FAILED :(");
	log("IS NORMALIZED PASSED\n");
}
void VMathTests::TestLerp(const Vec3& a, const Vec3& b, const float& t, const Vec3& expected)
{
	log("--LERP--");
	log("Input A:  " + Vec3DebugStr(a));
	log("Input B:  " + Vec3DebugStr(b));
	log("Input C:  " + DebugFloat(t));
	log("Expected: " + Vec3DebugStr(expected));
	log("Observed: " + Vec3DebugStr(a.lerp(b, t)));
	assert(AreEqual(a.lerp(b,t), expected) && "LERP FAILED :(");
	log("LERP PASSED!\n");
}
void VMathTests::TestTheta(const Vec3& a, const Vec3 b, const float& expected)
{
	log("--THETA--");
	log("Input A:  " + Vec3DebugStr(a));
	log("Input B:  " + Vec3DebugStr(b));
	log("Expected: " + DebugFloat(expected));
	log("Observed: " + DebugFloat(a.theta(b)));
	assert(Vec3::isFloatCloseEnough(a.theta(b), expected) && "THETA FAILED");
	log("THETA PASSED!\n");
}
void VMathTests::TestReflection(const Vec3& v, const Vec3& n, const Vec3& expected)
{
	log("--REFLECTION--");
	log("Input A:  " + Vec3DebugStr(v));
	log("Input B:  " + Vec3DebugStr(n));
	log("Expected: " + Vec3DebugStr(expected));
	log("Observed: " + Vec3DebugStr(v.reflection(n)));
	assert(AreEqual( v.reflection(n), expected) && "REFLECTION FAILED");
	log("REFLECTION PASSED\n");
}
//

void VMathTests::RunVec3Tests()
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
	TestDistanceSquared(Vec3(-1, -2, -3), Vec3(1, 2, 3),56);

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
	TestNormalize(Vec3(1, 2, 2), Vec3((float)1/ (float)3, (float)2/ (float)3, (float)2/ (float)3));
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
	TestReflection(Vec3( 1, -1, 0), Vec3(0, 1, 0), Vec3(1, 1, 0));
	TestReflection(Vec3(1, -1, 0), Vec3(0, 2, 0), Vec3(1, 1, 0));
}
*/

