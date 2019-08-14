#include "lib.h"
#include <gtest/gtest.h>

TEST(test_01, basic_test_set)
{
   homework::my_container<int,homework::my_allocator<int,5>> container;
   container.push_back(1);
   container.push_back(2);
   container.push_back(3);
   container.push_back(4);
   container.push_back(5);

   ASSERT_TRUE((container[0]==1)&&
               (container[1]==2)&&
               (container[2]==3)&&
               (container[3]==4)&&
               (container[4]==5));
}

TEST(test_02, basic_test_set)
{
   homework::my_container<int,homework::my_allocator<int,10>> container;
   container.push_back(1);
   container.push_back(2);
   container.push_back(3);
   container.push_back(4);
   container.push_back(5);

   auto it = container.begin();
   ++it;
   container.erase(it);

   ASSERT_TRUE((container[0]==1)&&
               (container[1]==3)&&
               (container[2]==4)&&
               (container[3]==5));
}

TEST(test_03, basic_test_set)
{
   homework::my_container<int,homework::my_allocator<int,10>> container;
   container.push_back(1);
   container.push_back(2);
   container.push_back(3);
   container.push_back(4);
   container.push_back(5);

   container.erase(container.begin());
   container.erase(container.begin());
   container.erase(container.begin());
   container.erase(container.begin());
   container.erase(container.begin());
   ASSERT_TRUE(container.size()==0);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}