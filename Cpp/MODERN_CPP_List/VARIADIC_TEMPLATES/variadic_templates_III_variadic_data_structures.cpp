#include <iostream>
#include <string>
#define LOG(x)	std::cout << x << std::endl

/* Variadic data structures 

	This can be more interesting,  because it was something that just wasn't possible prior to
	introduction of C++11, at least without considerable hackery


	Custom data structures (structs since the times of C and classes in C++) have compile-time defined fields.
	They can represent types that grow at runtime like std::vector.
	But to add a new field/member it has to be something that the compiler can see.

	Very well then. With variadic templates we can create a class that can have an arbitrary number of fields/members with less effort.

*/

// Lets start with the definition

// We start with a base case.
// the definition of a class template name tuple, which is empty.
template<class ... Ts> 
struct tuple {};

// The specialization that follows, PEELS OFF the first type from the parameter pack,
// and defines a member of that type, named tail.
// it also derives from the tuple instantiated with the rest of the pack.
// This is a recursive definition that stops when there are no more types to PEELS OFF.
// AND the base of the hierarchy is an empty tuple.
template <class T, class ...Ts>
struct tuple<T, Ts...> : tuple<Ts...>
{
	tuple(T t, Ts... ts) 
		: tuple<Ts...>(ts...), tail(t) 
	{

	}

	T tail;
};


// for a better understanding of how this is working.
// lets take a look to a more concrete code


tuple<double, uint64_t, const char*> t1(12.2, 42, "big");
// here is how this tuple would look like if hard coded (ignoring the constructor)

/*
struct tuple<double, uint64_t, const char*>
	: tuple<uint64_t, const char*>
{
	double tail;
};

struct tuple<uint64_t, const char*>
	: tuple<const char*>
{
	uint64_t tail;
};

struct tuple<const char*> : tuple<>
{
	const char * tail;
};

struct tuple<> {

};
*/

// the layout of data members in the original 3-element tuple will be
// [const char* tail, uint64_t tail, double tail]
// Note that the empty base consumes no space, due to empty base optimization




// So, we can create tuples, but there's not much else we can do with them yet.
// to access tuple members , we need the get function template.

// FIRST: we'll have to define a helper type that let us access the tupe of the k-th element in a tuple

template<class ...Ts>
struct elem_type_holder {};


// elem_type_holder is yet another variadic class template. It takes a numeber k, and the tuple type
// we're interested in as template parameters.

//Note that this is a  compile-time template metaprogramming construct. it acts on constants and
// types, not on runtime objects. for example:




int main() {
	
	 
	
}