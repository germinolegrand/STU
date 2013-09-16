#ifndef COLLISION_H
#define COLLISION_H

#include <algorithm>

template <class A, class B>
bool collides(A& a, B& b)
{
    return getCollisionBox(a).intersects(getCollisionBox(b));
}

template <class It1, class It2, class F>
void collisions(It1 it1_begin, It1 it1_end, It2 it2_begin, It2 it2_end, F f)
{
    std::for_each(it1_begin, it1_end, [&](decltype(*it1_begin)& e1)
    {
        std::for_each(it2_begin, it2_end, [&](decltype(*it2_begin)& e2)
        {
            if(collides(e1, e2))
                f(e1, e2);
        });
    });
}

#endif // COLLISION_H
