/**
 * @author: walther
 * @date: Sept 2018
 * @brief: Uses reflection to print members in JSON format.
 */

#include <boost/fusion/include/at_c.hpp>
#include <boost/fusion/include/size.hpp>
#include <boost/fusion/sequence/intrinsic/size.hpp>

#include <boost/bind.hpp>
#include <boost/ref.hpp>

#include <boost/mpl/for_each.hpp>
#include <boost/mpl/range_c.hpp> 


// Define methods to handle commas.
template < typename S, typename N >
struct Comma
{
    template < typename Ostream >
    static inline void comma(Ostream& os)
    {
        os << ", ";
    }
};

template < typename S >
struct Comma< S, typename boost::mpl::prior< typename boost::fusion::result_of::size< S >::type >::type >
{
    template < typename Ostream >
    static inline void comma(Ostream& os)
    {
    }
};


// Define a visitor for each member of the current structure.
struct PrintVisitor {
    template < class Index, class ObjectType >
    void operator()(Index, ObjectType & obj) {
        std::cout << boost::fusion::extension::struct_member_name< ObjectType, Index::value >::call() 
		<< ": " << boost::fusion::at< Index >(obj);
		// Print a comma, if necessary.
		Comma< ObjectType, Index >::comma(std::cout);
    }
};

// Define a templated function to call the PrintVisitor on each member.
template < class ObjectType >
void PrintMembers(ObjectType & obj) {
	std::cout << "{ ";
	// Alias the MPL range of members in this structure.
    typedef boost::mpl::range_c< int, 0, boost::fusion::result_of::size< ObjectType >::type::value > ObjectMembersRangeType;
	// Call the PrintVisitor on the current structure.
    boost::mpl::for_each< ObjectMembersRangeType >(boost::bind< void >(PrintVisitor(), _1, boost::ref(obj)));
	std::cout << " }";
}
