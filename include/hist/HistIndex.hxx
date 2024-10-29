/// ============================================================================
/*! \file    HistIndex.hxx
 *  \authors Derek Anderson
 *  \date    10.24.2024
 *
 *  Base class for a histogram index.
 */
/// ============================================================================

#ifndef RAU_HISTINDEX_HXX
#define RAU_HISTINDEX_HXX

// c++ utilities
#include <array>
#include <string>



namespace ROOTAnalysisUtilities {
  namespace Hist {

    // ========================================================================
    //! Histogram Index
    // ========================================================================
    /*! Base class for a "histogram index", a collection
     *  of indices of various bins.
     *
     *  TODO the idea here is that specializations somehow provide
     *  rules that tell you how to
     *    (1) get a list of indices, given a group of arguments; and
     *    (2) get a string representation of these indices.
     *  But the thing to keep in mind is that get the index from a
     *  generic list of arguments, you have to know the corresponding
     *  generic list of bins...
     */ 
    template <std::size_t N, typename... Ts> class Index {

      protected:

        // data members
        std::array<std::size_t, N> m_values;

      public:

        // --------------------------------------------------------------------
        //! Overloaded < operator
        // --------------------------------------------------------------------
        friend bool operator <(const Index& lhs, const Index& rhs) {
          return lhs.m_values < rhs.m_values;
        }

        // --------------------------------------------------------------------
        //! Overloaded > operator
        // --------------------------------------------------------------------
        friend bool operator >(const Index& lhs, const Index& rhs) {
          return lhs.m_values > rhs.m_values;
        }

        // --------------------------------------------------------------------
        //! Overloaded == operator
        // --------------------------------------------------------------------
        friend bool operator ==(const Index& lhs, const Index& rhs) {
          return lhs.m_values == rhs.m_values;
        }

        // --------------------------------------------------------------------
        //! Get a specific index
        // --------------------------------------------------------------------
        std::size_t GetIndex(const std::size_t index) const {
          return m_values.at(index);
        }

        // --------------------------------------------------------------------
        //! Set a specific index
        // --------------------------------------------------------------------
        void SetIndex(const std::size_t index, const std::size_t value) {
          m_values.at(index) = value;
        }

        // --------------------------------------------------------------------
        //! Set index
        // --------------------------------------------------------------------
        /*! Derived class must specify how to extract
         *  index from provided arguments.
         */  
        virtual void Set(Ts...) = 0;

        // --------------------------------------------------------------------
        //! Get string representation
        // --------------------------------------------------------------------
        /*! Derived class must specify how to convert index
         *  to string representation.
         */
        virtual std::string Hash() = 0;

        // --------------------------------------------------------------------
        //! default ctor/dtor
        // --------------------------------------------------------------------
        Index()  {};
        ~Index() {};

        // --------------------------------------------------------------------
        //! ctor accepting arguments
        // --------------------------------------------------------------------
        Index(Ts... args) {
          Set(args...);
        }

    };

  }  // end Hist namespace
}  // end ROOTAnalysisUtilities namespace

#endif

// end ========================================================================
