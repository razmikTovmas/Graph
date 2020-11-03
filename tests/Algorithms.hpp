#include <gtest/gtest.h>

TEST(Algorithms, is_cyclic_false)
{
    impl::graph g;
    g.add_edge("A", "B", 5);
    g.add_edge("A", "C", 2);
    g.add_edge("B", "D", 1);
    g.add_edge("D", "E", 3);
    g.add_edge("C", "E", 4);

    ASSERT_EQ(false, g.is_cyclic());
}

TEST(Algorithms, is_cyclic_true)
{
    impl::graph g;
    g.add_edge("A", "B", 5);
    g.add_edge("A", "C", 2);
    g.add_edge("B", "D", 1);
    g.add_edge("D", "E", 3);
    g.add_edge("C", "E", 4);
    g.add_edge("E", "A", 1);

    ASSERT_EQ(true, g.is_cyclic());
}

TEST(Algorithms, has_negative_cycle_false)
{
    impl::graph g;

    g.add_edge("A", "B", -1);
    g.add_edge("A", "C", 4);
    g.add_edge("B", "C", 3);
    g.add_edge("B", "D", 2);
    g.add_edge("A", "E", 2);
    g.add_edge("D", "C", 5);
    g.add_edge("D", "B", 1);
    g.add_edge("E", "D", -3);

    ASSERT_EQ(false, g.has_negative_cycle());
}

TEST(Algorithms, has_negative_cycle_true)
{
    impl::graph g;

    g.add_edge("A", "B", -1);
    g.add_edge("A", "C", 4);
    g.add_edge("B", "C", 3);
    g.add_edge("B", "D", 2);
    g.add_edge("A", "E", 2);
    g.add_edge("D", "A", -1);
    g.add_edge("D", "C", 5);
    g.add_edge("D", "B", 1);
    g.add_edge("E", "D", -3);

    ASSERT_EQ(true, g.has_negative_cycle());
}
