/************************************************************************\
Copyright 2024 CIBM (Center for Biomedical Imaging), Lausanne, Switzerland

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

enum        VolumeInterpolationPreset;
enum        FilterTypes;
enum        AtomFormatType;
class       TSolutionPointsDoc;
class       TVolumeDoc;
class       TGoF;
class       TSuperGauge;

                                        // "Renders" a RIS files, which are basically tracks, as volume(s)
void    RisToVolume (
                    const char*             risfile,
                    TSolutionPointsDoc*     spdoc,          VolumeInterpolationPreset   interpol,
                    const TVolumeDoc*       mrigrey,
                    int                     fromtf,         int             totf,           int             steptf,
                    FilterTypes             merging,
                    AtomFormatType          atomformat,     
                    const char*             fileprefix,     char*           fileext,
                    TGoF&                   volgof,
                    TSuperGauge*            gauge
                    );


//----------------------------------------------------------------------------
//----------------------------------------------------------------------------

}
