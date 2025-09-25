#include <catch2/catch_test_macros.hpp>
#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>

// uncomment and replace the following with your own headers
#include "AVL.h"
//Nathan Waisserberg; 48420836

using namespace std;

// the syntax for defining a test is below. It is important for the name to be unique, but you can group multiple tests with [tags]. A test can have [multiple][tags] using that syntax.
TEST_CASE("Example Test Name - Change me!", "[flag]"){
	// instantiate any class members that you need to test here
	int one = 1;

	// anything that evaluates to false in a REQUIRE block will result in a failing test 
	REQUIRE(one == 1); // fix me!

	// all REQUIRE blocks must evaluate to true for the whole test to pass
	REQUIRE(true); // also fix me!
}

TEST_CASE("Test 2", "[flag]"){
	// you can also use "sections" to share setup code between tests, for example:
	int one = 1;

	SECTION("num is 2") {
		int num = one + 1;
		REQUIRE(num == 2);
	};

	SECTION("num is 3") {
		int num = one + 2;
		REQUIRE(num == 3);
	};

	// each section runs the setup code independently to ensure that they don't affect each other
}

// you must write 5 unique, meaningful tests for credit on the testing portion of this project!

// the provided test from the template is below.

/*TEST_CASE("Example BST Insert", "[flag]"){

		AVLTree tree;   // Create a Tree object
		tree.insert(3);
		tree.insert(2);
		tree.insert(1);
		std::vector<int> actualOutput = tree.inorder();
		std::vector<int> expectedOutput = {1, 2, 3};
		REQUIRE(expectedOutput.size() == actualOutput.size());
		REQUIRE(actualOutput == expectedOutput);
}*/

// Had help from ChatGPT to make a function to capture the output
 TEST_CASE("Custom Test 1: Incorrect Commands", "[I.C.]") {
	AVLTree tree;

	// 1.1 Invalid name
	stringstream buffer1;
	streambuf* old1 = cout.rdbuf(buffer1.rdbuf());
	tree.insert("A11y", 45679999);
	cout.rdbuf(old1);
	REQUIRE(buffer1.str() == "unsuccessful\n");
	cout << "Test 1.1 passed" << endl;

	// 1.2 Invalid ID (Too short)
	stringstream buffer2;
	streambuf* old2 = cout.rdbuf(buffer2.rdbuf());
	tree.insert("Alice", 1234567);
	cout.rdbuf(old2);
	REQUIRE(buffer2.str() == "unsuccessful\n");
	cout << "Test 1.2 passed" << endl;

	// 1.3 Invalid ID (Too long)
	stringstream buffer3;
	streambuf* old3 = cout.rdbuf(buffer3.rdbuf());
	tree.insert("Bob", 123456789);
	cout.rdbuf(old3);
	REQUIRE(buffer3.str() == "unsuccessful\n");
	cout << "Test 1.3 passed" << endl;

	// 1.4 Empty Name
	stringstream buffer4;
	streambuf* old4 = cout.rdbuf(buffer4.rdbuf());
	tree.insert("", 12345678);
	cout.rdbuf(old4);
	REQUIRE(buffer4.str() == "unsuccessful\n");
	cout << "Test 1.4 passed" << endl;

	// 1.5 Special Characters
	stringstream buffer5;
	streambuf* old5 = cout.rdbuf(buffer5.rdbuf());
	tree.insert("name@ufl.edu", 87654321);
	cout.rdbuf(old5);
	REQUIRE(buffer5.str() == "unsuccessful\n");
	cout << "Test 1.5 passed" << endl;

	// 1.6 Duplicate ID
	tree.insert("Charlie", 22446688);
	stringstream buffer6;
	streambuf* old6 = cout.rdbuf(buffer6.rdbuf());
	tree.insert("David", 22446688);
	cout.rdbuf(old6);
	REQUIRE(buffer6.str() == "unsuccessful\n");
	cout << "Test 1.6 passed" << endl;
}

TEST_CASE("Custom Test 2: Edge Cases", "[E.C.]") {
	AVLTree tree;

	// 2.1 Remove node from empty tree
	stringstream buffer1;
	streambuf* old1 = cout.rdbuf(buffer1.rdbuf());
	tree.remove(12345678);
	cout.rdbuf(old1);
	REQUIRE(buffer1.str() == "unsuccessful\n");
	cout << "Test 2.1 passed" << endl;

	// 2.2 Search for node in empty tree
	stringstream buffer2;
	streambuf* old2 = cout.rdbuf(buffer2.rdbuf());
	tree.search(12345678);
	cout.rdbuf(old2);
	REQUIRE(buffer2.str() == "unsuccessful\n");
	cout << "Test 2.2 passed" << endl;

	// 2.3 RemoveInOrder with invalid index (0)
	stringstream buffer3;
	streambuf* old3 = cout.rdbuf(buffer3.rdbuf());
	tree.removeInOrder(0);
	cout.rdbuf(old3);
	REQUIRE(buffer3.str() == "unsuccessful\n");
	cout << "Test 2.3 passed" << endl;

	// 2.4 RemoveInOrder with invalid index (negative)
	tree.insert("Alice", 12345678);
	stringstream buffer4;
	streambuf* old4 = cout.rdbuf(buffer4.rdbuf());
	tree.removeInOrder(-1);
	cout.rdbuf(old4);
	REQUIRE(buffer4.str() == "unsuccessful\n");
	cout << "Test 2.4 passed" << endl;

	// 2.5 RemoveInOrder with index out of bounds
	stringstream buffer5;
	streambuf* old5 = cout.rdbuf(buffer5.rdbuf());
	tree.removeInOrder(10);
	cout.rdbuf(old5);
	REQUIRE(buffer5.str() == "unsuccessful\n");
	cout << "Test 2.5 passed" << endl;
}

TEST_CASE("Custom Test 3: Rotations", "[R]") {
	AVLTree tree1, tree2, tree3, tree4;

	// 3.1 Left Left Case
	tree1.insert("Charlie", 30000000);
	tree1.insert("Bob", 20000000);
	tree1.insert("Alice", 10000000);

	stringstream buffer1;
	streambuf* old1 = cout.rdbuf(buffer1.rdbuf());
	tree1.printInOrder();
	cout.rdbuf(old1);
	REQUIRE(buffer1.str() == "Alice, Bob, Charlie\n");
	cout << "Test 3.1 passed" << endl;

	// 3.2 Right Right Case
	tree2.insert("Alice", 10000000);
	tree2.insert("Bob", 20000000);
	tree2.insert("Charlie", 30000000);

	stringstream buffer2;
	streambuf* old2 = cout.rdbuf(buffer2.rdbuf());
	tree2.printInOrder();
	cout.rdbuf(old2);
	REQUIRE(buffer2.str() == "Alice, Bob, Charlie\n");
	cout << "Test 3.2 passed" << endl;

	// 3.3 Left Right Case
	tree3.insert("Charlie", 30000000);
	tree3.insert("Alice", 10000000);
	tree3.insert("Bob", 20000000);

	stringstream buffer3;
	streambuf* old3 = cout.rdbuf(buffer3.rdbuf());
	tree3.printInOrder();
	cout.rdbuf(old3);
	REQUIRE(buffer3.str() == "Alice, Bob, Charlie\n");
	cout << "Test 3.3 passed" << endl;

	// 3.4 Right Left Case
	tree4.insert("Alice", 10000000);
	tree4.insert("Charlie", 30000000);
	tree4.insert("Bob", 20000000);

	stringstream buffer4;
	streambuf* old4 = cout.rdbuf(buffer4.rdbuf());
	tree4.printInOrder();
	cout.rdbuf(old4);
	REQUIRE(buffer4.str() == "Alice, Bob, Charlie\n");
	cout << "Test 3.4 passed" << endl;
}

TEST_CASE("Custom Test 4: Deletions", "[D]") {
	AVLTree tree;

	tree.insert("Delta", 40000000);     // Root
	tree.insert("Beta", 20000000);      // Left Child
	tree.insert("Foxtrot", 60000000);   // Right Child
	tree.insert("Alpha", 10000000);     // Left node
	tree.insert("Charlie", 30000000);   // Left Child of Beta
	tree.insert("Echo", 50000000);      // Left Child of Foxtrot
	tree.insert("Golf", 70000000);      // Right child of Foxtrot

	// 4.1 Delete node with no children
	stringstream buffer1;
	streambuf* old1 = cout.rdbuf(buffer1.rdbuf());
	tree.remove(10000000);
	cout.rdbuf(old1);
	REQUIRE(buffer1.str() == "successful\n");

	// Verify that the node is gone
	stringstream buffer1_verify;
	streambuf* old1_verify = cout.rdbuf(buffer1_verify.rdbuf());
	tree.search(10000000);
	cout.rdbuf(old1_verify);
	REQUIRE(buffer1_verify.str() == "unsuccessful\n");
	cout << "Test 4.1 passed" << endl;

	// 4.2 Delete node with 1 child
	stringstream buffer2;
	streambuf* old2 = cout.rdbuf(buffer2.rdbuf());
	tree.remove(50000000);
	cout.rdbuf(old2);
	REQUIRE(buffer2.str() == "successful\n");
	cout << "Test 4.2 passed" << endl;

	// 4.3 Delete node with 2 children
	stringstream buffer3;
	streambuf* old3 = cout.rdbuf(buffer3.rdbuf());
	tree.remove(60000000);
	cout.rdbuf(old3);
	REQUIRE(buffer3.str() == "successful\n");
	cout << "Test 4.3 passed" << endl;

	// 4.4 Verify tree is still valid
	stringstream buffer4;
	streambuf* old4 = cout.rdbuf(buffer4.rdbuf());
	tree.printInOrder();
	cout.rdbuf(old4);
	string result = buffer4.str();
	REQUIRE(!result.empty());
	REQUIRE(result.back() == '\n');
	cout << "Test 4.4 passed" << endl;
}

TEST_CASE("Custom Test 5: 100 Nodes", "[100]") {
	AVLTree tree;

	// 5.1 insert 100 nodes
	for (int i = 0; i < 100; i++) {
		string name = "Student";
		int id = 10000000 + i;

		stringstream buffer;
		streambuf* old = cout.rdbuf(buffer.rdbuf());
		tree.insert(name, id);
		cout.rdbuf(old);

		//Verify make sure each insertion is successful
		REQUIRE(buffer.str() == "successful\n");
	}
	cout << "Test 5.1 passed" << endl;

	// 5.2 Remove 10 nodes
	for (int i = 5; i < 100; i += 10) {
		int id = 10000000 + i;

		stringstream buffer;
		streambuf* old = cout.rdbuf(buffer.rdbuf());
		tree.remove(id);
		cout.rdbuf(old);

		REQUIRE(buffer.str() == "successful\n");
	}
	cout << "Test 5.2 passed" << endl;

	// 5.3 Verify 90 nodes remain
	int count = 0;
	for (int i = 0; i < 100; i++) {
		if (i % 5 == 0 && !(i % 10 == 0)) continue;
		int id = 10000000 + i;

		stringstream buffer;
		streambuf* old = cout.rdbuf(buffer.rdbuf());
		tree.remove(id);
		cout.rdbuf(old);

		REQUIRE(buffer.str() == "successful\n");
		count++;
	}
	REQUIRE(count == 90);
	cout << "Test 5.3 passed" << endl;
}