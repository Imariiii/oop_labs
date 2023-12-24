#include <gtest/gtest.h>

#include "../include/allocator.h"
#include "../include/queue.h"
#include <string>

using namespace my_q;

TEST(allocator_01, map_alloc_test)
{
    std::map<int, int, std::less<int>,mystd::Allocator<std::pair<const int,int>,11>> my_map;

    my_map[0] = 1;

    for(int i{1}; i <= 10; ++i){
        my_map[i] = my_map[i-1] * i;
    }

    EXPECT_EQ(24,my_map[4]);
}

TEST(allocator_02, vector_alloc_test)
{
    std::vector<int, mystd::Allocator<int>> vec;

    vec.push_back(1);

    EXPECT_EQ(1, vec[0]);
}

TEST(copy_constructor_test, test) {
    Queue<std::string> queue;
    queue.push("helmet");

    Queue<std::string> queue1 = queue;

    EXPECT_TRUE(queue1 == queue);
}

TEST(move_constructor_test, test) {
    Queue<std::string> queue;
    queue.push("helmet");

    Queue<std::string> queue1 = std::move(queue);

    EXPECT_EQ(queue.head, queue.block_ptr);
    EXPECT_EQ(queue.size, 0);
}

TEST(copy_assignment_test, test) {
    Queue<std::string> queue;
    Queue<std::string> queue1;

    queue.push("helmet");

    queue1 = queue;

    EXPECT_TRUE(queue == queue1);
}

TEST(move_assignment_test, test) {
    Queue<std::string> queue;
    Queue<std::string> queue1;

    queue.push("helmet");

    queue1 = std::move(queue);

    EXPECT_EQ(queue.head, queue.block_ptr);
    EXPECT_EQ(queue.size, 0);

    queue.push("123");
}

TEST(equal_operator_test, true_test) {
    Queue<size_t> queue;
    Queue<size_t> queue1;

    for (size_t i = 0; i < 10; ++i) {
      queue.push(i);
      queue1.push(i);
    }

    EXPECT_TRUE(queue == queue1);
}

TEST(equal_operator_test, false_test) {
    Queue<size_t> queue;
    Queue<size_t> queue1;

    for (size_t i = 0; i < 10; ++i) {
      queue.push(i);
      queue1.push(1 + i);
    }

    EXPECT_FALSE(queue == queue1);
}

TEST(not_equal_operator_test, true_test) {
    Queue<size_t> queue;
    Queue<size_t> queue1;

    for (size_t i = 0; i < 10; ++i) {
      queue.push(i);
      queue1.push(i + 1);
    }

    EXPECT_TRUE(queue != queue1);
}

TEST(not_equal_operator_test, false_test) {
    Queue<size_t> queue;
    Queue<size_t> queue1;

    for (size_t i = 0; i < 10; ++i) {
      queue.push(i);
      queue1.push(i);
    }

    EXPECT_FALSE(queue != queue1);
}

TEST(empty_test, true_test) {
    Queue<size_t> queue;

    EXPECT_TRUE(queue.empty());
}

TEST(empty_test, false_test) {
    Queue<size_t> queue;

    queue.push(123);

    EXPECT_FALSE(queue.empty());
}

TEST(get_size_test, test) {
    Queue<size_t> queue;

    for (size_t i = 0; i < 10; ++i) {
      queue.push(i);
    }

    EXPECT_EQ(queue.get_size(), 10);
}

TEST(front_test, test_empty_list) {
    Queue<size_t> queue;

    EXPECT_ANY_THROW(queue.front());
}

TEST(front_test, test_not_empty_list) {
    Queue<size_t> queue;

    queue.push(123);

    EXPECT_EQ(queue.front(), 123);
}

TEST(clear_test, test_empty) {
    Queue<size_t> queue;

    EXPECT_NO_THROW(queue.clear());
    EXPECT_EQ(queue.size, 0);
    EXPECT_EQ(queue.block_ptr, queue.head);
}

TEST(clear_test, test_non_empty) {
    Queue<size_t> queue;

    for (size_t i = 0; i < 10; ++i) {
      queue.push(i);
    }

    EXPECT_NO_THROW(queue.clear());
    EXPECT_EQ(queue.size, 0);
    EXPECT_EQ(queue.block_ptr, queue.head);
}

TEST(push_test, test) {
    Queue<size_t> queue;

    for (size_t i = 0; i < 10; ++i) {
      queue.push(i);
    }

    EXPECT_EQ(queue.back(), 9);
}

TEST(pop_test, test) {
    Queue<size_t> queue;

    for (size_t i = 0; i < 10; ++i) {
      queue.push(i);
    }

    queue.pop();

    EXPECT_EQ(queue.front(), 1);
}

TEST(pop_test, empty_list_test) {
    Queue<size_t> queue;

    EXPECT_ANY_THROW(queue.pop());
}

TEST(begin_test, test) {
    Queue<size_t> queue;

    queue.push(13);

    Queue<size_t>::Iterator it = queue.begin();

    EXPECT_TRUE(Queue<size_t>::Iterator(queue.head) == it);
}

TEST(end_test, test) {
    Queue<size_t> queue;
    queue.push(13);
    
    Queue<size_t>::Iterator it = queue.end();

    EXPECT_TRUE(Queue<size_t>::Iterator(queue.block_ptr) == it);
}

TEST(iterator_increment_test, test) {
    Queue<std::string> queue;
    queue.push("privet");
    queue.push("hello");

    Queue<std::string>::Iterator it = queue.begin();
    EXPECT_EQ(++it, Queue<std::string>::Iterator(queue.head->next));
}

TEST(plus_equal_operator_test, test) {
    Queue<std::string> queue;
    queue.push("privet");
    queue.push("hello");
    queue.push("run");
    queue.push("thread");

    Queue<std::string>::Iterator it = queue.begin();
    it += 3;
    EXPECT_EQ(it, Queue<std::string>::Iterator(queue.head->next->next->next));
}

TEST(operator_plus_test, test) {
    Queue<std::string> queue;
    queue.push("privet");
    queue.push("hello");
    queue.push("run");
    queue.push("thread");

    Queue<std::string>::Iterator it = queue.begin();
    it = it + 3;
    EXPECT_EQ(it, Queue<std::string>::Iterator(queue.head->next->next->next));
}

TEST(dereferencing_test, test) {
    Queue<std::string> queue;
    queue.push("privet");
    queue.push("hello");
    queue.push("run");
    queue.push("thread");

    Queue<std::string>::Iterator it = queue.begin();
    it = it + 3;
    EXPECT_EQ(*it, queue.head->next->next->next->value);
}

TEST(Iterator_equal_operator, true_test) {
    Queue<std::string> queue;
    queue.push("privet");
    queue.push("hello");
    queue.push("run");
    queue.push("thread");

    Queue<std::string>::Iterator it = queue.begin();
    Queue<std::string>::Iterator it1 = queue.begin();
    it = it + 3;
    it1 = it1 + 3;
    EXPECT_TRUE(it == it1);
}

TEST(Iterator_equal_operator, false_test) {
    Queue<std::string> queue;
    queue.push("privet");
    queue.push("hello");
    queue.push("run");
    queue.push("thread");

    Queue<std::string>::Iterator it = queue.begin();
    Queue<std::string>::Iterator it1 = queue.begin();
    it = it + 3;
    it1 = it1 + 2;
    EXPECT_FALSE(it == it1);
}

TEST(Iterator_not_equal_operator, true_test) {
    Queue<std::string> queue;
    queue.push("privet");
    queue.push("hello");
    queue.push("run");
    queue.push("thread");

    Queue<std::string>::Iterator it = queue.begin();
    Queue<std::string>::Iterator it1 = queue.begin();
    it = it + 3;
    it1 = it1 + 3;
    EXPECT_FALSE(it != it1);
}

TEST(Iterator_not_equal_operator, false_test) {
    Queue<std::string> queue;
    queue.push("privet");
    queue.push("hello");
    queue.push("run");
    queue.push("thread");

    Queue<std::string>::Iterator it = queue.begin();
    Queue<std::string>::Iterator it1 = queue.begin();
    it = it + 3;
    it1 = it1 + 2;
    EXPECT_TRUE(it != it1);
}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}