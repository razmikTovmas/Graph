#pragma once

#include <tuple>

class Node;

class Edge
{
public:
    using Cost_t = int;

public:
    Edge(Node* from, Node* to, Cost_t cost)
        : m_from{from}
        , m_to{to}
        , m_cost{cost}
    { }

    inline void SetFrom(Node* from) noexcept { m_from = from; }
    inline void SetTo(Node* to) noexcept { m_to = to; }

    [[nodiscard]] const Node* GetFrom() const noexcept { return m_from; }
    [[nodiscard]] const Node* GetTo() const noexcept { return m_to; }

    inline void SetCost(Cost_t cost) noexcept { m_cost = cost; }
    [[nodiscard]] Cost_t GetCost() const noexcept { return m_cost; }

private:
    Node* m_from;
    Node* m_to;
    Cost_t m_cost;

};

/**
 * @class EdgeEquality
 * @brief Designed to check equality of two edges.
 */
class EdgeEquality
{
public:
    bool operator()(const Edge* lhs, const Edge* rhs)
    {
        return std::make_tuple(lhs->GetFrom(), lhs->GetTo(), lhs->GetCost())
            == std::make_tuple(rhs->GetFrom(), rhs->GetTo(), rhs->GetCost());
    }
};

/**
 * @class EdgeEquivalency
 * @brief Designed to check equivalency of two edges.
 */
class EdgeEquivalency
{
public:
    bool operator()(const Edge* lhs, const Edge* rhs)
    {
        return std::make_tuple(lhs->GetFrom(), lhs->GetTo(), lhs->GetCost())
             < std::make_tuple(rhs->GetFrom(), rhs->GetTo(), rhs->GetCost());
    }
};
