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

namespace crtl {

//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
                                        // Storing the AAL Atlas codes
                                        // See:  https://www.gin.cnrs.fr/en/tools/aal/
//constexpr int     NumAAL1Codes        = 116;
constexpr int       NumAAL3v1Codes      = 170;


class  TAALRoi
{
public:
    int             Index;              // index in volume, starting from 1
    char            ShortName[ 32 ];
    char            LongName [ 32 ];
    int             Value;              // value associated with that region, whatever
};


//extern const TAALRoi    AAL1Codes  [ NumAAL1Codes   ];
extern const TAALRoi    AAL3v1Codes[ NumAAL3v1Codes ];


//----------------------------------------------------------------------------
//----------------------------------------------------------------------------

}
