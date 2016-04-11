#ifndef COCL_MATRIX_H
#define COCL_MATRIX_H

#include <fstream>                  // ostream
#include <string>                   // string
#include <vector>                   // vector

#include "indexer.h"

namespace cocl {

template<class T>
class HyperMatrix {
public:
    typedef std::vector<std::vector<std::string>> labels_t;

    /// CONSTRUCTORS and DESTRUCTORS

    Matrix() {}

    Matrix(const Matrix& source)
    : data_(source.data_), labels_(source.labels_) {}

    Matrix(const std::vector<int> & dim) {
        labels_.clear();
        for (size_t i = 0; i != dim.size(); i++)
            labels_.emplace_back(std::vector<std::string>(dim[i]));
        size_t size = 1;
        for (size_t i = 0; i != dim.size(); ++i) size *= dim[i];
        data_ = std::vector<T>(size);
    }

    /// MODIFICATION MEMBER FUNCTIONS

    Matrix& operator =(const Matrix& source) {
        data_ = source.data_;
        labels_ = source.labels_;
        return *this;
    }

    T& operator [](int index)
    // Precondition: index is within range
    // Postcondition: Return value is reference to matrix element
    // Library facilities used: assert
    {
        assert(index < static_cast<int>(data_.size()));
        return data_[index];
    }

    /// CONSTANT MEMBER FUNCTIONS

    T operator [](int index) const
    // Precondition: index is within range
    // Postcondition: Return value is the matrix element
    // Library facilities used: assert
    {
        assert(index < static_cast<int>(data_.size()));
        return data_[index];
    }

    size_t size() const {return data_.size();}
    // Precondition: none
    // Postcondition: The return value is the number of elements in matrix

    std::vector<size_t> dimensions() const
    // Precondition: none
    // Postcondition: The return value is a vector of way sizes
    {
        std::vector<size_t> ret(labels_.size());
        for (size_t i = 0; i != labels_.size(); ++i)
            ret[i] = labels_[i].size();
        return ret;
    }

    bool operator ==(const Matrix& rhs) const
    // Precondition: none
    // Postcondition: Return value is true if equal, false otherwise
    {return data_ == rhs.data_ && labels_ == rhs.labels_;}

    bool operator !=(const HyperMatrix& rhs) const
    // Precondition: none
    // Postcondition: Return value is true if not equal, false otherwise
    {return !operator==(rhs);}

    void print_2D_slice
    (const std::vector<int>& dim, std::ostream& os) const
    // Precondition: os is an open output stream
    // Postcondition: 2-dim slice of matrix data is printed to os
    // Library facilities used: assert
    {
        const std::vector<size_t> dims = dimensions();
        assert(dim.size() == dims.size());

        const int WAYS = static_cast<int>(dims.size());

        // get row and column ways
        std::vector<int> plane;
        for (int way = 0; way != WAYS; ++way)
            if (dime[way] == -1) plane.push_back(way);
        assert(plane.size() == 2);

        const int ROW = plane[0];
        const int COL = plane[1];

        assert(ROW < COL);

        // set indexer tuple
        std::vector<int> tuple(WAYS);
        for (int way = 0; way != WAYS; ++way)
            if (dim[way] == -1) tuple[way] = 0;

        // build hyper-cube indexer
        std::vector<bool> mask(WAYS, true); mask[ROW] = mask[COL] = false;
        Indexer* indexer = new Indexer(*this, tuple, mask);

        // print
        int ccount = 0;
        while (!indexer->end()) {
            os << operator[](indexer->index());
            if (++ccount % dims[COL] == 0) os << " " << std::endl;
            indexer->forward();
        }
    }

    std::vector<std::vector<int>> indexes() const
    // Library facilities used: none
    {
        const std::vector<size_t> dims = dimensions();
        const int ways = int(dims.size());
        std::vector<std::vector<int>> ret(ways);
        for (int way = 0; way != ways; ++way)
            for (int index = 0; index != dimensions[way]; ++index)
                ret[way].push_back(index);
        return ret;
    }

private:
    // MEMBER VARIABLES
    std::vector<T> data_;   // data
    labels_t labels_;       // way labels
  };

} // namespace cocl

//#include "HyperMatrix.cpp"

#endif // COCL_MATRIX_H
