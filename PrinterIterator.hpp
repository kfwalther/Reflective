#ifndef PRINTERITERATOR_HPP
#define PRINTERITERATOR_HPP

/**
 * @author: walther
 * @date: Sept 2018
 * @brief: Uses reflection to print members in JSON format. Design of these classes were 
 * 	inspired by https://stackoverflow.com/questions/12084781/c-iterate-into-nested-struct-field-with-boost-fusion-adapt-struct
 *
 */

#include <boost/type_traits.hpp> // is_array, is_class, remove_bounds

#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/mpl/next_prior.hpp>

#include <boost/fusion/mpl.hpp>
#include <boost/fusion/adapted.hpp> // BOOST_FUSION_ADAPT_STRUCT

// boost::fusion::result_of::value_at
#include <boost/fusion/sequence/intrinsic/value_at.hpp>
#include <boost/fusion/include/value_at.hpp>

// boost::fusion::result_of::size
#include <boost/fusion/sequence/intrinsic/size.hpp>
#include <boost/fusion/include/size.hpp>

// boost::fusion::at
#include <boost/fusion/sequence/intrinsic/at.hpp>
#include <boost/fusion/include/at.hpp>

#include <boost/bind.hpp>
#include <boost/ref.hpp>

#include <boost/mpl/for_each.hpp>
#include <boost/mpl/range_c.hpp> 

// Forward declarations.
struct PrintVisitor;

template < class ObjectType >
void printJson(ObjectType & obj);


// Define methods to handle commas.
template < class ObjectType, int Index >
struct Comma {
    template < class Ostream >
    static inline void comma(Ostream& os) {
        os << ", ";
    }
};

// Define the comma base case (checking to see if the last indexable position was provided) to prevent trailing comma.
template < class ObjectType >
struct Comma< ObjectType, boost::mpl::prior< typename boost::fusion::result_of::size< ObjectType >::type >::type::value > {
    template < typename Ostream >
    static inline void comma(Ostream& os) {}
};


// Define a visitor for each member of the current structure.
struct StructMemberVisitor {
    template < class Index, class ObjectType >
    void operator()(Index, ObjectType & obj) {
		// Print the member's name.
        std::cout << "\"" <<  boost::fusion::extension::struct_member_name< ObjectType, Index::value >::call() << "\": ";
		// Call the printJson dispatcher to print the member's value.
		printJson(boost::fusion::at< Index >(obj));
		// Print a comma, if necessary.
		Comma< ObjectType, Index::value >::comma(std::cout);
    }
};

// Define the struct printer.
template < class ObjectType >
struct JsonStructPrinter {
	// Define a print function for the struct case.
	static inline void print(ObjectType & obj) {
		std::cout << "{ ";
		// Alias the MPL range of members in this structure.
		typedef boost::mpl::range_c< int, 0, boost::fusion::result_of::size< ObjectType >::type::value > ObjectMembersRangeType;
		// Use Boost.MPL to loop through each member of the structure and call the visitor.
		boost::mpl::for_each< ObjectMembersRangeType >(boost::bind< void >(StructMemberVisitor(), _1, boost::ref(obj)));
		std::cout << " }";
	}
};

// Define the arithmetic value printer.
template < class ObjectType >
struct JsonArithmeticPrinter {
	// Define a print function to print the arithmetic value.
	static inline void print(ObjectType & obj) {
		std::cout << obj;
	}
};

// Define the array printer.
template < class ObjectType >
struct JsonArrayPrinter {
	// Determine the number of elements in the array.
	typedef typename boost::remove_bounds< ObjectType >::type slice_t;
    static size_t const numElements = sizeof(ObjectType) / sizeof(slice_t);
	// Define a print function for the array case.
	static inline void print(ObjectType & obj) {
		std::cout << "[ ";
		for (size_t idx = 0; idx < numElements; idx++) {
			// Call the printJson dispatcher to print each element in the array.
			printJson(obj[idx]);
			if (idx != (numElements-1)) {
				std::cout << ", ";
			}
		}
		std::cout << " ]";
	}
};

// Define a dispatcher class to look up a specific printer based on type.
template < class ObjectType >
struct JsonPrinterDispatcher
{
	typedef
			typename boost::mpl::eval_if< boost::is_array < ObjectType >, 
				boost::mpl::identity< JsonArrayPrinter < ObjectType > >,
			// else 
			typename boost::mpl::eval_if< boost::is_class < ObjectType >, 
				boost::mpl::identity< JsonStructPrinter < ObjectType > >,
			// else
			boost::mpl::identity< JsonArithmeticPrinter < ObjectType > >
		> >::type JsonPrinterType;
};

// Define a placeholder class which looks up a specific printer.
template < class ObjectType >
struct JsonPrinter : public JsonPrinterDispatcher < ObjectType >::JsonPrinterType {};

// Define a function that will take any type, and instantiate the templated dispatcher class with it.
template < class ObjectType >
void printJson(ObjectType & obj) {
	JsonPrinter< ObjectType >::print(obj);
}








#endif /* PRINTERITERATOR_HPP */

