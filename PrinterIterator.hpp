/**
 * @author: walther
 * @date: Sept 2018
 */

#include <boost/fusion/include/at_c.hpp>
#include <boost/fusion/include/size.hpp>
#include <boost/fusion/sequence/intrinsic/size.hpp>

#include <boost/bind.hpp>
#include <boost/ref.hpp>

#include <boost/mpl/for_each.hpp>
#include <boost/mpl/range_c.hpp> 


// Define a visitor for each member of the current structure.
struct PrintVisitor {
    template < class Index, class ObjectType >
    void operator()(Index, ObjectType & obj) {
        std::cout << boost::fusion::extension::struct_member_name< ObjectType, Index::value >::call() 
                  << "=" << boost::fusion::at< Index >(obj) << std::endl;
    }
};

// Define a templated function to call the PrintVisitor on each member.
template < class ObjectType >
void PrintMembers(ObjectType & obj) {
	// Alias the MPL range of members in this structure.
    typedef boost::mpl::range_c< int, 0, boost::fusion::result_of::size< ObjectType >::type::value > ObjectMembersRangeType;
	// Call the PrintVisitor on the current structure.
    boost::mpl::for_each< ObjectMembersRangeType >(boost::bind< void >(PrintVisitor(), _1, boost::ref(obj)));
}
