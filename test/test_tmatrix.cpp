#include "tmatrix.h"

#include <gtest.h>

TEST(TDynamicMatrix, can_create_matrix_with_positive_length)
{
  ASSERT_NO_THROW(TDynamicMatrix<int> m(5));
}

TEST(TDynamicMatrix, cant_create_too_large_matrix)
{
  ASSERT_ANY_THROW(TDynamicMatrix<int> m(MAX_MATRIX_SIZE + 1));
}

TEST(TDynamicMatrix, throws_when_create_matrix_with_negative_length)
{
  ASSERT_ANY_THROW(TDynamicMatrix<int> m(-5));
}

TEST(TDynamicMatrix, can_create_copied_matrix)
{
  TDynamicMatrix<int> m(5);

  ASSERT_NO_THROW(TDynamicMatrix<int> m1(m));
}

TEST(TDynamicMatrix, copied_matrix_is_equal_to_source_one)
{
	TDynamicMatrix<int> m1(3);
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			m1[i][j] = i + j;

	TDynamicMatrix<int> m2(m1);

	EXPECT_EQ(m1, m2);
}

TEST(TDynamicMatrix, copied_matrix_has_its_own_memory)
{
	TDynamicMatrix<int> m1(3);
	TDynamicMatrix<int> m2(m1);

	EXPECT_NE(&m1, &m2);
}

TEST(TDynamicMatrix, can_get_size)
{
	TDynamicMatrix<int> m(3);
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			m[i][j] = i + j;

	EXPECT_EQ(3, m.size());
}

TEST(TDynamicMatrix, can_set_and_get_element)
{
	TDynamicMatrix<int> m(3);
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			m[i][j] = i + j;

	EXPECT_EQ(m[1][1], 2);
}

TEST(TDynamicMatrix, throws_when_set_element_with_negative_index)
{
	TDynamicMatrix<int> m(3);

	ASSERT_ANY_THROW(m.at(-1) = 1);
}

TEST(TDynamicMatrix, throws_when_set_element_with_too_large_index)
{
	TDynamicMatrix<int> m(3);

	ASSERT_ANY_THROW(m.at(MAX_MATRIX_SIZE + 1) = 1);
}

TEST(TDynamicMatrix, can_assign_matrix_to_itself)
{
	TDynamicMatrix<int> m(3);

	ASSERT_NO_THROW(m = m);
}

TEST(TDynamicMatrix, can_assign_matrices_of_equal_size)
{
	TDynamicMatrix<int> m1(3), m2(3);
	for (int i = 0; i < m1.size(); i++)
		for (int j = 0; j < m1.size(); j++)
			m1[i][j] = i + j;
	m2 = m1;

	EXPECT_EQ(m1, m2);
}

TEST(TDynamicMatrix, assign_operator_change_matrix_size)
{
	TDynamicMatrix<int> m1(5), m2(3);
	m2 = m1;

	EXPECT_EQ(m1.size(), m2.size());
}

TEST(TDynamicMatrix, can_assign_matrices_of_different_size)
{
	TDynamicMatrix<int> m1(3), m2(5);
	
	ASSERT_NO_THROW(m1 = m2);
}

TEST(TDynamicMatrix, compare_equal_matrices_return_true)
{
	TDynamicMatrix<int> m1(3), m2(3);
	for (int i = 0; i < m1.size(); i++) {
		for (int j = 0; j < m1.size(); j++) {
			m1[i][j] = i + j;
			m2[i][j] = i + j;
		}
	}
	
	EXPECT_TRUE(m1 == m2);
}

TEST(TDynamicMatrix, compare_matrix_with_itself_return_true)
{
	TDynamicMatrix<int> m1(3);
	for (int i = 0; i < m1.size(); i++)
		for (int j = 0; j < m1.size(); j++)
			m1[i][j] = i + j;

	EXPECT_TRUE(m1 == m1);
}

TEST(TDynamicMatrix, matrices_with_different_size_are_not_equal)
{
	TDynamicMatrix<int> m1(3), m2(5);
	
	EXPECT_FALSE(m1 == m2);
}

TEST(TDynamicMatrix, can_add_matrices_with_equal_size)
{
	TDynamicMatrix<int> m1(3), m2(3), m3(3);
	for (int i = 0; i < m1.size(); i++) {
		for (int j = 0; j < m1[i].size(); j++) {
			m1[i][j] = i + j;
			m2[i][j] = i + j;
			m3[i][j] = 2 * i + 2 * j;
		}
	}
	
	EXPECT_EQ(m1 + m2, m3);
}

TEST(TDynamicMatrix, cant_add_matrices_with_not_equal_size)
{
	TDynamicMatrix<int> m1(3), m2(5);
	
	ASSERT_ANY_THROW(m1 + m2);
}

TEST(TDynamicMatrix, can_subtract_matrices_with_equal_size)
{
	TDynamicMatrix<int> m1(3), m2(3), m3(3);
	for (int i = 0; i < m1.size(); i++) {
		for (int j = 0; j < m1[i].size(); j++) {
			m1[i][j] = i + j;
			m2[i][j] = i + j;
			m3[i][j] = 0;
		}
	}

	EXPECT_EQ(m1 - m2, m3);
}

TEST(TDynamicMatrix, cant_subtract_matrixes_with_not_equal_size)
{
	TDynamicMatrix<int> m1(3), m2(5);

	ASSERT_ANY_THROW(m1 - m2);
}

TEST(TDynamicMatrix, cant_multiply_matrixes_with_not_equal_size)
{
	TDynamicMatrix<int> m1(3), m2(50);

	ASSERT_ANY_THROW(m1 * m2);
}

TEST(TDynamicMatrix, can_multiply_matrixes_with_equal_size)
{
	TDynamicMatrix<int> m1(3), m2(3), m3(3);

	m1[0][0] = 1, m1[0][1] = 2, m1[0][2] = 4;
	m1[1][0] = 4, m1[1][1] = 6, m1[1][2] = 7;
	m1[2][0] = 6, m1[2][1] = 7, m1[2][2] = 3;
	
	m2[0][0] = 2, m2[0][1] = 3, m2[0][2] = 4;
	m2[1][0] = 3, m2[1][1] = 4, m2[1][2] = 5;
	m2[2][0] = 2, m2[2][1] = 7, m2[2][2] = 8;
	
	m3[0][0] = 16, m3[0][1] = 39, m3[0][2] = 46;
	m3[1][0] = 40, m3[1][1] = 85, m3[1][2] = 102;
	m3[2][0] = 39, m3[2][1] = 67, m3[2][2] = 83;

	EXPECT_EQ(m1 * m2, m3);
}

TEST(TDynamicMatrix, can_multiply_matrix_on_vector) 
{
	TDynamicMatrix<int> m(3);
	TDynamicVector<int> v(3), vr(3);
	for (int i = 0; i < m.size(); i++)
		for (int j = 0; j < m.size(); j++)
			m[i][j] = i + j;

	for (int i = 0; i < v.size(); i++)
		v[i] = i + 1;

	vr[0] = 8, vr[1] = 14, vr[2] = 20;

	EXPECT_EQ(m * v, vr);
}

TEST(TDynamicMatrix, cant_multiply_matrix_on_vector_not_equal_size) 
{
	TDynamicMatrix<int> m(3);
	TDynamicVector<int> v(5);

	ASSERT_ANY_THROW(m*v);
}
