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

#include    "Files.Utils.h"
#include    "OpenGL.Colors.h"           // TGLColoring

namespace crtl {

//----------------------------------------------------------------------------
//----------------------------------------------------------------------------

class       TTracksDoc;

                                        // Marker codes are obsoletes
using               MarkerCode                  = USHORT;
constexpr MarkerCode MarkerDefaultCode          = 100;

                                        // just upgrade a bit the max length, for MFF triggers can be long
constexpr int       MarkerNameMaxLength         = 256;

constexpr char*     MarkerNameTrigger           = "Trigger";
constexpr char*     MarkerNameEvent             = "Event";
constexpr char*     MarkerNameMarker            = "Marker";
constexpr char*     MarkerNameEpoch             = "Epoch";
constexpr char*     MarkerNameBlock             = "Block";
constexpr char*     MarkerNameMax               = "Max";
constexpr char*     MarkerNameTemporary         = "Temporary";
constexpr char*     MarkerNameToRemove          = "To Remove";
constexpr char*     MarkerNameDefault           = MarkerNameMarker;

constexpr int       MarkersMaxColors            = 6;


enum                MarkerType
                    {
                    MarkerTypeUnknown           = 0x0000,

                    MarkerTypeTrigger           = 0x0001,
                    MarkerTypeEvent             = 0x0002,
                    MarkerTypeHardCoded         = MarkerTypeTrigger | MarkerTypeEvent,

                    MarkerTypeMarker            = 0x0010,
                    MarkerTypeUserCoded         = MarkerTypeMarker,

                    MarkerTypeTemp              = 0x0100,
                    MarkerTypeToRemove          = 0x0200,
                    MarkerTypeSpecialCoded      = MarkerTypeTemp | MarkerTypeToRemove,

                    AllMarkerTypes              = MarkerTypeHardCoded | MarkerTypeUserCoded | MarkerTypeSpecialCoded
                    };


//----------------------------------------------------------------------------

class   TMarker
{
public:
                    TMarker ();
                    TMarker ( long pos, const char* name, MarkerType type );
                    TMarker ( long from, long to, MarkerCode code, const char* name, MarkerType type );


    long            From;                   // beginning of marker
    long            To;                     // end of marker
    MarkerCode      Code;                   // generated by the recording machine
    MarkerType      Type;                   // original / added
    char            Name[ MarkerNameMaxLength ]; // tested when making ep
                                            // total = 114 bytes

    bool            IsNotExtended               ()                                  const   { return From == To; }
    bool            IsExtended                  ()                                  const   { return From != To; }
    bool            SamePosition                ( const TMarker& marker )           const   { return From == marker.From && To == marker.To; }
    bool            IsNotOverlappingInterval    ( long from, long to )              const   { return crtl::IsNotOverlappingInterval ( From, To, from, to ); }
    bool            IsOverlappingInterval       ( long from, long to )              const   { return crtl::IsOverlappingInterval    ( From, To, from, to ); }
    bool            IsInsideLimits              ( long from, long to )              const   { return crtl::IsInsideLimits           ( From, To, from, to ); }
    double          Overlap                     ( const TMarker& marker, RelativeIntervalOverlapEnum how )     const;


    long            Length ()                                                       const   { return To - From + 1; }
    long            Center ()                                                       const   { return ( From + To ) / 2; }


    void            Set ( long pos )                                                        { From = To = pos; }
    void            Set ( long from, long to )                                              { From = min ( from, to );  To = max ( from, to ); }


    void            Show                ( const char* title = 0 )   const;

                                        // wrap the stream output
    friend inline   std::ostream&    operator    <<  ( std::ostream& os, const TMarker& marker );
    friend inline   std::ostream&    operator    <<  ( std::ostream& os, const TMarker* marker );

                                        // OpenGL
    static  TGLColoring  TriggerColors;
    void            ColorGLize          ()  const;


                    TMarker         ( const TMarker& op  );
    TMarker&        operator    =   ( const TMarker& op2 );


    friend bool     operator    ==  ( const TMarker& op1, const TMarker& op2 );   // testing position, type and name - used to test for duplicates
    friend bool     operator    !=  ( const TMarker& op1, const TMarker& op2 );   // testing position, type and name - used to test for duplicates
    friend bool     operator    >   ( const TMarker& op1, const TMarker& op2 );   // testing ONLY position - used for sorting
    friend bool     operator    <   ( const TMarker& op1, const TMarker& op2 );   // testing ONLY position - used for sorting
};


//----------------------------------------------------------------------------

enum                MarkersChunksFlags
                    {
                    KeepingMarkers,
                    ExcludingMarkers,
                    };


constexpr char*     MarkerNameAutoEpochs        = "AutoEpochs";
constexpr char*     MarkerNameAutoMaxGfp        = "AutoMaxGfp";
constexpr char*     MarkerNameAutoBadEpoch      = "AutoBadEpoch";

                                        // Utilities for outputting markers to marker file, without creating/using a TMarker object
void        WriteMarkerHeader   (   std::ofstream&  os  );

void        WriteMarker         (   std::ofstream&  os,     
                                    long            Pos,    const char*     Name
                                );
void        WriteMarker         (   std::ofstream&  os,     
                                    long            From,   long        To,     const char*     Name
                                );


//----------------------------------------------------------------------------

enum                EpochsType;

class               TTFCursor;
class               TStrings;
                                        // comes in handy to define this type:
using               MarkersList         = TList<TMarker>;  // Cartool thread-safe, double-linked list


class   TMarkers
{
public:
                    TMarkers ();
                    TMarkers ( const MarkersList& markerslist );
                    TMarkers ( const TTracksDoc* tracksdoc );
                    TMarkers ( const char* file );
                   ~TMarkers ();


    bool            InitMarkers         ( const char* file = 0 );   // reads both EEG triggers and .mrk file - does not commit before, nor after loading, MarkersDirty is false
    bool            CommitMarkers       ( bool force = false );
    virtual void    ReadNativeMarkers   ()                  {}      // to read any associated file with markers
    void            ResetMarkers        ();


    bool            IsEmpty             ()      const       { return    Markers.IsEmpty ();                        }
    bool            IsNotEmpty          ()      const       { return    Markers.IsNotEmpty ();                     }
    bool            IsInMemory          ()      const       { return    TracksDoc == 0 && MarkersFileName.IsEmpty ();    }
    bool            AreMarkersDirty     ()      const       { return    MarkersDirty;                              }

    int             GetNumMarkers       ()      const       { return    Markers.Num ();                            }
    int             GetNumMarkers       ( MarkerType type )               const;

    bool            HasMarker           ( const TMarker& marker );     // !test for equivalent content, NOT pointers!

    const TMarker*  GetMarker           ( const char*    markername )   const;
                                                        
    bool            GetNextMarker       ( TMarker& marker, bool forward = true, MarkerType type = AllMarkerTypes )  const;  // currently skipping duplicate markers
    bool            GetNextMarker       ( const TTFCursor* tfc, TMarker& marker, bool forward = true, MarkerType type = AllMarkerTypes )  const;

    void            GetMarkerNames      ( TStrings&    markernames, MarkerType type = AllMarkerTypes, int maxnames = INT_MAX );  // returns an array of all the names encountered, without duplicates


    long            GetMinPosition      ( MarkerType type = AllMarkerTypes )  const;
    long            GetMaxPosition      ( MarkerType type = AllMarkerTypes )  const;
    long            GetLongestMarker    ( MarkerType type = AllMarkerTypes )  const;
    long            GetMarkersTotalLength(MarkerType type = AllMarkerTypes )  const;

                                                                                                        // Sorting is enforced
    void            SetMarkers          ( const TMarkers& markers );
    void            SetMarkers          ( const MarkersList& markerslist );
    void            SetMarkers          ( const char* file );
                                                                                                        // Sorting is not enforced
    void            AppendMarker        ( const TMarker& marker );
    void            AppendMarkers       ( const TMarkers& markers );
    void            AppendMarkers       ( const MarkersList& markerslist );
    void            AppendMarkers       ( const char* file );
                                                                                                        // Sorting is enforced
    int             InsertMarker        ( const TMarker& marker, bool commit = true, int indexfrom = 0 );
    void            InsertMarkers       ( const char* file, bool commit = true );
    void            InsertMarkers       ( const TMarkers& markers, const char *filteredwith = "*" );    // copy from another marker list while also filtering
    void            InsertMarkers       ( const MarkersList& markerslist );

    void            RemoveMarkers       ( long from, long to, MarkerType type, bool commit );           // removes markers fully included into time interval
    void            RemoveMarkers       ( MarkerType type, bool commit );                               // removes markers of given type
    void            RemoveMarkers       ( const char* greppedwith, MarkerType type, bool commit );      // removes grepped markers
    void            RemoveMarkers       ( const TMarkers& removelist, MarkerType type, bool commit );   // remove every parts from the list

    void            ClipMarkers         ( long from, long to, MarkerType type, bool commit );           // punching markers with time interval
    void            ClipMarkers         ( const TMarkers& cliplist, MarkerType type, bool commit );     // punching markers with the given marker list

    void            KeepMarkers         ( long from, long to, MarkerType type, bool commit );
    void            KeepMarkers         ( const char* greppedwith, bool commit );

    void            SortMarkers         ();
    void            SortAndCleanMarkers ();                                                             // Sorting and removing duplicates


    void            EpochsToMarkers         ( EpochsType epochs, const TStrings* epochfrom, const TStrings* epochto, long mintf, long maxtf, long periodiclength );   // will not include non-overlapping epochs
    void            TrackToMarkers          ( const TArray1<float>& track, const char* markerprefix, bool postfixvalue );
    void            GeneratePeriodicEpochs  ( long mintf, long maxtf, long step, bool firstincomplete, bool lastincomplete, const char* name );
    void            MaxTrackToMarkers       ( TTracksDoc* EEGDoc, long mintf, long maxtf, int tracki, const char* name = 0 );         // scan a track, save local max positions
    void            MaxTrackToMarkers       ( const TArray1<double> &track, long mintf, long maxtf, bool peak, const char* name = 0 );    // scan a track, save local max positions
    void            MarkersToTimeChunks     ( const TMarkers& inputmarkers, const char* inputmarkernames, MarkersChunksFlags flag, long fromtf, long totf, const char* newmarkername = 0 ); // create markers from a list of markers, within a range of time frames - !also consolidate overlapping epochs!
    void            CreateTimeChunks        ( const TTracksDoc* EEGDoc, double blockdurationms, long fromtf, long totf );                   // create markers from arbitrary length
    void            BadEpochsToMarkers      ( const TMaps* mapsin, const char* filename, double tolerance, const char* newmarkername = 0, const TSelection* ignoretracks = 0 );  // scan tracks, guessing where the bad epochs are
    void            TestingAgainst          ( const TMarkers& trainingset, long numtf, double& truepositiverate, double& truenegativerate, double& falsepositiverate, double& falsenegativerate )    const;
    bool            IsOverlapping           ( long mintf, long maxtf )  const;

    void            GranularizeMarkers      ( int downsampling );
    void            DownsampleMarkers       ( int downsampling );
    void            UpsampleMarkers         ( int upsampling );
    void            ResliceMarkers          ();
    void            ConcatenateToVector     ( TArray1<long>& concattf )                const;
    void            ProjectToVector         ( TArray1<bool>& projecttf, long numtf )   const;

    bool            CompactConsecutiveMarkers   ( bool identicalnames, long mergedmaxlength = Highest<long> (), bool commit = true );


    const MarkersList&  GetMarkersList      ()  const       { return Markers; }
          MarkersList&  GetMarkersList      ()              { return Markers; }
    bool            TimeRangeToIndexes      ( MarkerType type, long timemin, long timemax, int &indexmin, int &indexmax );


    void            ReadFile            ( const char* file );     // reads marker file
    void            WriteFile           ( const char* file, MarkerType type = AllMarkerTypes, long mintf = -1, long maxtf = -1 )    const;
    void            Show                ( const char* title = 0 )                           const;


    TMarkers                            ( const TMarkers &op  );
    TMarkers&       operator    =       ( const TMarkers &op2 );


    TMarker*        operator []         ( int index )       { return Markers[ index ]; }
    const TMarker*  operator []         ( int index ) const { return Markers[ index ]; }

                    operator bool       ()  const           { return    (bool) Markers; }
                    operator int        ()  const           { return    (int)  Markers;     }

protected:

    MarkersList     Markers;
    TFileName       MarkersFileName;
    bool            MarkersDirty;


    void            _Sort  ( int l, int r );

private:

    const TTracksDoc*   TracksDoc;        // used for internal affairs
};


//----------------------------------------------------------------------------
//----------------------------------------------------------------------------

}
