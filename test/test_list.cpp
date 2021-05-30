#include <list.h>
#include <gtest.h>


TEST(AVLTree, can_create_tree)
{
	ASSERT_NO_THROW(AVLTree<int>());
}

TEST(AVLTree, can_delete_element)
{
	AVLTree<int> me;
	me.Insert(1, 5);
	me.Delete(5);
	ASSERT_ANY_THROW(me.Find(5));
}

TEST(AVLTree, can_insert_element)
{
	AVLTree<int> me;
	me.Insert(1, 5);
	EXPECT_EQ(1, me.Find(5));
}