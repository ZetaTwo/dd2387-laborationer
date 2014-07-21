#include <gtest/gtest.h>
#include "../vector/Vector.hpp"

TEST(Vector, DefaultConstructor) {
	EXPECT_NO_THROW({
		Vector<int> int_vector;
	});
}

TEST(Vector, CopyConstructor) {
	const size_t size = 4;
	Vector<int> int_vector1(size);

	int_vector1[1] = 13;
	Vector<int> int_vector2(int_vector1);
	int_vector1[2] = 14;
	int_vector2[3] = 15;

	EXPECT_EQ(13, int_vector1[1]);
	EXPECT_EQ(13, int_vector2[1]);

	EXPECT_EQ(14, int_vector1[2]);
	EXPECT_EQ(0, int_vector1[3]);

	EXPECT_EQ(0, int_vector2[2]);
	EXPECT_EQ(15, int_vector2[3]);
}

TEST(Vector, InitlistConstructor) {
	Vector<int> int_vector({ 13, 14, 15, 16 });

	EXPECT_EQ(13, int_vector[0]);
	EXPECT_EQ(14, int_vector[1]);
	EXPECT_EQ(15, int_vector[2]);
	EXPECT_EQ(16, int_vector[3]);
	EXPECT_EQ(4, int_vector.size());
}

TEST(Vector, SizeConstructor) {
	const size_t size = 32;

	Vector<int> int_vector(size);
	EXPECT_EQ(size, int_vector.size());

	for (size_t i = 0; i < size; i++)
	{
		EXPECT_EQ(0, int_vector[i]);
	}
}

TEST(Vector, SizeConstructorZero) {
	const size_t size = 0;

	Vector<int> int_vector(size);
	EXPECT_EQ(size, int_vector.size());
}

TEST(Vector, SizeConstructorRange) {
	const size_t size = -16;

	ASSERT_THROW({
		Vector<int> int_vector(size);
	},
	std::invalid_argument);
	
}

TEST(Vector, RepeatConstructor) {
	const size_t size = 4;

	Vector<int> int_vector(size, 13);
	for (size_t i = 0; i < size; i++)
	{
		EXPECT_EQ(13, int_vector[i]);
	}
}


TEST(Vector, OperatorBracket) {
	const size_t size = 4;

	Vector<int> int_vector(size);
	EXPECT_EQ(0, int_vector[0]);

	int_vector[0] = 10;
	int_vector[1] = 20;
	int_vector[2] = 30;
	int_vector[3] = 40;

	EXPECT_EQ(10, int_vector[0]);
	EXPECT_EQ(20, int_vector[1]);
	EXPECT_EQ(30, int_vector[2]);
	EXPECT_EQ(40, int_vector[3]);
}

TEST(Vector, OperatorBracketRange) {
	const size_t size = 4;
	Vector<int> int_vector(size);

	EXPECT_THROW({
		int_vector[size];
	}, std::out_of_range);

	EXPECT_THROW({
		int_vector[-1];
	}, std::out_of_range);
}

TEST(Vector, OperatorBracketConst) {
	const Vector<int> int_vector(4, 13);
	
	EXPECT_EQ(13, int_vector[0]);
	EXPECT_EQ(13, int_vector[1]);
	EXPECT_EQ(13, int_vector[2]);
	EXPECT_EQ(13, int_vector[3]);
}

TEST(Vector, AssignmentOperator) {
	const size_t size = 4;
	Vector<int> int_vector1(size);

	int_vector1[1] = 13;
	Vector<int> int_vector2 =int_vector1;
	int_vector1[2] = 14;
	int_vector2[3] = 15;

	EXPECT_EQ(13, int_vector1[1]);
	EXPECT_EQ(13, int_vector2[1]);

	EXPECT_EQ(14, int_vector1[2]);
	EXPECT_EQ(0, int_vector1[3]);

	EXPECT_EQ(0, int_vector2[2]);
	EXPECT_EQ(15, int_vector2[3]);
}

TEST(Vector, AssignmentOperatorSelf) {
	const size_t size = 4;
	Vector<int> int_vector1(size, 13);

	int_vector1 = int_vector1;
	EXPECT_EQ(size, int_vector1.size());
	EXPECT_EQ(13, int_vector1[3]);
}

TEST(Vector, AssignmentOperatorList) {
	Vector<int> int_vector = { 13, 14, 15, 16 };

	EXPECT_EQ(13, int_vector[0]);
	EXPECT_EQ(14, int_vector[1]);
	EXPECT_EQ(15, int_vector[2]);
	EXPECT_EQ(16, int_vector[3]);
	EXPECT_EQ(4, int_vector.size());
}

TEST(Vector, PushBack) {
	const size_t size = 4;
	Vector<int> int_vector(size);
	
	int_vector.push_back(13);

	EXPECT_EQ(size + 1, int_vector.size());
	EXPECT_EQ(13, int_vector[size]);
}

TEST(Vector, Insert) {
	const size_t size = 4;
	Vector<int> int_vector(size);

	EXPECT_EQ(0, int_vector[1]);
	int_vector.insert(1, 13);
	EXPECT_EQ(13, int_vector[1]);
	EXPECT_EQ(size + 1, int_vector.size());
}

TEST(Vector, InsertBeginning) {
	const size_t size = 4;
	Vector<int> int_vector(size);

	EXPECT_EQ(0, int_vector[1]);
	int_vector.insert(0, 13);
	EXPECT_EQ(13, int_vector[0]);
	EXPECT_EQ(size + 1, int_vector.size());
}

TEST(Vector, InsertEnd) {
	const size_t size = 4;
	Vector<int> int_vector(size);

	EXPECT_EQ(0, int_vector[1]);
	int_vector.insert(int_vector.size()-1, 13);
	EXPECT_EQ(13, int_vector[size]);
	EXPECT_EQ(size + 1, int_vector.size());
}

TEST(Vector, InsertRange) {
	const size_t size = 4;
	Vector<int> int_vector(size);

	EXPECT_THROW({
		int_vector.insert(-1, 13);
	}, std::out_of_range);

	EXPECT_THROW({
		int_vector.insert(size, 13);
	}, std::out_of_range);
}

TEST(Vector, Erase) {
	const size_t size = 4;
	Vector<int> int_vector(size);

	int_vector[1] = 13;
	int_vector[2] = 14;

	int_vector.erase(1);
	EXPECT_EQ(14, int_vector[1]);
	EXPECT_EQ(size - 1, int_vector.size());
}

TEST(Vector, EraseRange) {
	const size_t size = 4;
	Vector<int> int_vector(size);

	EXPECT_THROW({
		int_vector.erase(-1);
	}, std::out_of_range);

	EXPECT_THROW({
		int_vector.erase(size);
	}, std::out_of_range);
}

TEST(Vector, Clear) {
	const size_t size = 4;
	Vector<int> int_vector(size);

	int_vector.clear();
	EXPECT_EQ(0, int_vector.size());
}

TEST(Vector, SortAscending) {
	const size_t size = 4;
	Vector<int> int_vector(size);

	int_vector[0] = 40;
	int_vector[1] = 20;
	int_vector[2] = 30;
	int_vector[3] = 10;

	int_vector.sort();

	EXPECT_EQ(10, int_vector[0]);
	EXPECT_EQ(20, int_vector[1]);
	EXPECT_EQ(30, int_vector[2]);
	EXPECT_EQ(40, int_vector[3]);
}

TEST(Vector, SortDescending) {
	const size_t size = 4;
	Vector<int> int_vector(size);

	int_vector[0] = 40;
	int_vector[1] = 20;
	int_vector[2] = 30;
	int_vector[3] = 10;

	int_vector.sort(false);

	EXPECT_EQ(40, int_vector[0]);
	EXPECT_EQ(30, int_vector[1]);
	EXPECT_EQ(20, int_vector[2]);
	EXPECT_EQ(10, int_vector[3]);
}

TEST(Vector, SortUniqueAscending) {
	const size_t size = 4;
	Vector<int> int_vector(size);

	int_vector[0] = 30;
	int_vector[1] = 20;
	int_vector[2] = 30;
	int_vector[3] = 10;

	int_vector.unique_sort();

	EXPECT_EQ(3, int_vector.size());

	EXPECT_EQ(10, int_vector[0]);
	EXPECT_EQ(20, int_vector[1]);
	EXPECT_EQ(30, int_vector[2]);
}

TEST(Vector, SortUniqueDescending) {
	const size_t size = 4;
	Vector<int> int_vector(size);

	int_vector[0] = 30;
	int_vector[1] = 20;
	int_vector[2] = 30;
	int_vector[3] = 10;

	int_vector.unique_sort();

	EXPECT_EQ(3, int_vector.size());

	EXPECT_EQ(30, int_vector[0]);
	EXPECT_EQ(20, int_vector[1]);
	EXPECT_EQ(10, int_vector[2]);
}

TEST(Vector, ExistsTrue) {
	const size_t size = 4;
	Vector<int> int_vector(size);

	int_vector[2] = 13;

	EXPECT_TRUE(int_vector.exists(13));
}

TEST(Vector, ExistsFalse) {
	const size_t size = 4;
	Vector<int> int_vector(size);

	int_vector[2] = 13;

	EXPECT_FALSE(int_vector.exists(14));
}

TEST(Vector, Size) {
	const size_t size = 4;
	Vector<int> int_vector(size);

	EXPECT_EQ(size, int_vector.size());
}