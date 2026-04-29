#include "mat4x4_test.h"
#include <iostream>
#include <assert.h>

namespace math_tests {

	void run_mat4x4_tests() {
		Mat4x4 a{};
		a.m12 = 1.0f;
		test_mat4x4_transpose(a);
	}

	// If we transpose a matrix, then transpose it again we should get the original matrix 
	void test_mat4x4_transpose(Mat4x4& a)
	{
		std::cout << "============ TEST_MAT4X4_TRANSPOSE ============\n";
		std::cout << "Mat4x4 A\n" << a << "\n";

		Mat4x4 temp{ a };

		a.transpose();
		std::cout << "Mat4x4 A Transposed once\n" << a << "\n";

		a.transpose();
		std::cout << "Mat4x4 A Transposed twice\n" << a << "\n";

		assert(a == temp);
		std::cout << "============ SUCCESS ============\n";
	}

}

