/************************************************************************\
� 2024-2025 Denis Brunet, University of Geneva, Switzerland.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

   http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
\************************************************************************/

#pragma once

#include    "Geometry.TDipole.h"

namespace crtl {

//----------------------------------------------------------------------------
//----------------------------------------------------------------------------

constexpr char*     GenerateOscillatingDataTitle    = "Generating Data";


class                       TLeadField;
template <class> class      TTracks;


void        GenerateOscillatingData (
                            TLeadField&         leadfield,          TTracks<float>& K,                  
                            TDipole             dipoles[],          int             numsources,
                            int                 fileduration,       double          samplingfrequency,
                            const char*         basefilename,
                            bool                savemaps,           bool            saveris
                            );

//----------------------------------------------------------------------------
//----------------------------------------------------------------------------

}
