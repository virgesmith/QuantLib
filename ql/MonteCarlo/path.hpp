
/*
 Copyright (C) 2003 Ferdinando Ametrano
 Copyright (C) 2000, 2001, 2002, 2003 RiskMap srl

 This file is part of QuantLib, a free-software/open-source library
 for financial quantitative analysts and developers - http://quantlib.org/

 QuantLib is free software: you can redistribute it and/or modify it under the
 terms of the QuantLib license.  You should have received a copy of the
 license along with this program; if not, please email ferdinando@ametrano.net
 The license is also available online at http://quantlib.org/html/license.html

 This program is distributed in the hope that it will be useful, but WITHOUT
 ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 FOR A PARTICULAR PURPOSE.  See the license for more details.
*/

/*! \file path.hpp
    \brief single factor random walk
*/

#ifndef quantlib_montecarlo_path_h
#define quantlib_montecarlo_path_h

#include <ql/grid.hpp>
#include <ql/handle.hpp>

namespace QuantLib {

    namespace MonteCarlo {

        //! single factor random walk
        class Path {
          public:
            Path(const TimeGrid& timeGrid,
                 const Array& drift = Array(),
                 const Array& diffusion = Array());
            //! \name inspectors
            //@{
            double operator[](int i) const;
            Size size() const;
            //@}
            //! \name read/write access to components
            //@{
            const TimeGrid& timeGrid() const;
            TimeGrid& timeGrid();
            const Array& drift() const;
            Array& drift();
            const Array& diffusion() const;
            Array& diffusion();
            //@}
          private:
            TimeGrid timeGrid_;
            Array drift_;
            Array diffusion_;
        };

        // inline definitions

        inline Path::Path(const TimeGrid& timeGrid, const Array& drift,
            const Array& diffusion)
        : timeGrid_(timeGrid), drift_(drift), diffusion_(diffusion) {
            if (drift_.size()==0) {
                if (timeGrid_.size() > 0)
                    drift_ = Array(timeGrid_.size()-1);
            } else {
                QL_REQUIRE(drift_.size() == timeGrid_.size()-1,
                    "Path: drift and times have different size");
            }
            if (diffusion_.size()==0) {
                if (timeGrid_.size() > 0)
                    diffusion_ = Array(timeGrid_.size()-1);
            } else {
                QL_REQUIRE(diffusion_.size() == timeGrid_.size()-1,
                    "Path: diffusion and times have different size");
            }

        }

        inline double Path::operator[](int i) const {
            return drift_[i] + diffusion_[i];
        }

        inline Size Path::size() const {
            return drift_.size();
        }

        inline const TimeGrid& Path::timeGrid() const {
            return timeGrid_;
        }

        inline TimeGrid& Path::timeGrid() {
            return timeGrid_;
        }

        inline const Array& Path::drift() const {
            return drift_;
        }

        inline Array& Path::drift() {
            return drift_;
        }

        inline const Array& Path::diffusion() const {
            return diffusion_;
        }

        inline Array& Path::diffusion() {
            return diffusion_;
        }





    }

}


#endif
