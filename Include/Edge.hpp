#pragma once

#include <tuple>

namespace impl
{

class node;

class edge
{
public:
    using Cost_t = int;

public:
    edge(node* from, node* to, Cost_t cost)
        : m_from{from}
        , m_to{to}
        , m_cost{cost}
    { }

    ~edge() = default;

    inline void set_from(node* from) noexcept { m_from = from; }
    inline void set_to(node* to) noexcept { m_to = to; }

    [[nodiscard]] const node* get_from() const noexcept { return m_from; }
    [[nodiscard]] node* get_from() noexcept { return m_from; }
    [[nodiscard]] const node* get_to() const noexcept { return m_to; }
    [[nodiscard]] node* get_to() noexcept { return m_to; }

    inline void set_cost(Cost_t cost) noexcept { m_cost = cost; }
    [[nodiscard]] Cost_t get_cost() const noexcept { return m_cost; }

private:
    node* m_from;
    node* m_to;
    Cost_t m_cost;

};

/**
 * @class EdgeEquality
 * @brief Designed to check equality of two edges.
 */
class EdgeEquality
{
public:
    bool operator()(const edge* lhs, const edge* rhs)
    {
        return std::make_tuple(lhs->get_from(), lhs->get_to(), lhs->get_cost())
            == std::make_tuple(rhs->get_from(), rhs->get_to(), rhs->get_cost());
    }
};

/**
 * @class EdgeEquivalency
 * @brief Designed to check equivalency of two edges.
 */
class EdgeEquivalency
{
public:
    bool operator()(const edge* lhs, const edge* rhs)
    {
        return std::make_tuple(lhs->get_from(), lhs->get_to(), lhs->get_cost())
             < std::make_tuple(rhs->get_from(), rhs->get_to(), rhs->get_cost());
    }
};

}
