template < typename T >
T div(T lhs, T rhs) {
    if (rhs == 0)
        throw zero_div("division by zero");
    return lhs / rhs;
}
