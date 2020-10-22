#pragma once

namespace impl
{

node::node_iterator::node_iterator(std::vector<edge*>::iterator iter)
    : m_iter(iter)
{ }

node::node_iterator& node::node_iterator::operator++()
{
    ++m_iter;
    return *this;
}

node::node_iterator node::node_iterator::operator++(int)
{
    node_iterator temp{*this};
    ++m_iter;
    return temp;
}

//! NOTE: if iter_types are the same, and if nodes they point to
//        are the same, they are equal
bool node::node_iterator::operator==(const node_iterator& other) const
{
    return m_iter == other.m_iter;
}

bool node::node_iterator::operator!=(const node_iterator& other) const
{
    return m_iter != other.m_iter;
}

node::node_iterator::pointer node::node_iterator::operator*() const
{
    return (*m_iter)->get_to();
}

}
