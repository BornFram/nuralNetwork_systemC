#ifndef _DTO_H
#define _DTO_H
#include <string>

#include "systemc.h"

class Pair {
    public:
    float left = 0;
    float right = 0;
 
    Pair() {};

    Pair(float lhs, float rhs) {
        left = lhs;
        right = rhs;
    }

    inline bool operator ==(const Pair & rhs) const {
        return (left == rhs.left && right == rhs.right); }

    std::string string() const {
        char c[100];
        snprintf(c, sizeof(c), "Pair (%5f; %5f)", left, right);

        return std::string(c);
    }

};


inline ostream & operator <<(ostream & os, const Pair & command)
{

    os << command.string() << endl;

    return os;
}

inline void sc_trace(sc_trace_file * tf, const Pair & command, const std::string & name)
{
    sc_trace(tf, command.string().c_str(), name + ".cmdType");
}


#endif
