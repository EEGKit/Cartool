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

#include    "TTracksDoc.h"

using namespace std;
using namespace crtl;

void    ExampleTTracksDoc ()
{
cout << fastendl;
cout << "--------------------------------------------------------------------------------" << fastendl;
cout << "ExampleTTracksDoc:" << fastendl;
cout << fastendl;


//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

TFileName           fileeeg         ( "E:\\Data\\Test Files\\Spontaneous\\cenbas.nsr" );


//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
                                        // TTracksDoc class holds everything about a given tracks file (EEG, correlation, results of inverse etc..)
                                        // As all "doc" classes, they are handled by the application doc manager (opening, closing etc...)
                                        // The TOpenDoc class will nicely hide all the calls to said doc manager, though.

TOpenDoc<TTracksDoc>    tracks  ( fileeeg, OpenDocHidden );     // there is no GUI, so open file hidden-style
char                    buff[ KiloByte ];

                                        // Let's squeeze out some info...
cout << "File path                  = " << tracks->GetDocPath () << fastendl;
cout << "Content type               = " << tracks->GetContentTypeName ( buff ) << fastendl; // both ContentType & ExtraContentType
cout << "Type of second dimension   = " << tracks->GetDim2TypeName () << fastendl;
cout << "Original atom type         = " << tracks->GetAtomTypeName ( AtomTypeUseOriginal ) << fastendl;
cout << "IsSpontaneous              = " << BoolToString ( tracks->IsSpontaneous () ) << fastendl;
cout << "IsErp                      = " << BoolToString ( tracks->IsErp ()         ) << fastendl;
cout << "IsTemplates                = " << BoolToString ( tracks->IsTemplates ()   ) << fastendl;
cout << fastendl;

cout << "Num electrodes             = " << tracks->GetNumElectrodes () << fastendl;
cout << "Num aux electrodes         = " << tracks->GetNumAuxElectrodes () << fastendl;
cout << "Num bad electrodes         = " << tracks->GetNumBadElectrodes () << fastendl;
cout << "Num valid electrodes       = " << tracks->GetNumValidElectrodes () << fastendl;
cout << "Num pseudo electrodes      = " << tracks->GetNumPseudoElectrodes () << fastendl;
cout << "Total electrodes           = " << tracks->GetTotalElectrodes () << fastendl;
cout << fastendl;

cout << "Starting date              = " << tracks->DateTime.GetStringDate ( buff ) << fastendl;
cout << "Starting time              = " << tracks->DateTime.GetStringTime ( 0, buff ) << fastendl;
cout << "Num time points            = " << tracks->GetNumTimeFrames () << fastendl;
cout << "Sampling Frequency         = " << tracks->GetSamplingFrequency () << fastendl;
cout << fastendl;

cout << "Reference                  = " << ReferenceNames[ tracks->GetReferenceType () ] << fastendl;
cout << "Num sessions               = " << AtLeast ( 1, tracks->GetNumSessions () ) << fastendl;
cout << "Can use filters            = " << BoolToString ( tracks->CanFilter () ) << fastendl;
cout << fastendl;

cout << "Num event markers          = " << tracks->GetNumMarkers ( MarkerTypeEvent   ) << fastendl;
cout << "Num trigger markers        = " << tracks->GetNumMarkers ( MarkerTypeTrigger ) << fastendl;
cout << "Num manual markers         = " << tracks->GetNumMarkers ( MarkerTypeMarker  ) << fastendl;
cout << "Total num markers          = " << tracks->GetNumMarkers () << fastendl;
cout << fastendl;


//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

cout << fastendl;
}
