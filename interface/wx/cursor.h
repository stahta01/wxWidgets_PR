/////////////////////////////////////////////////////////////////////////////
// Name:        cursor.h
// Purpose:     interface of wxCursor
// Author:      wxWidgets team
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////

/**
    @class wxCursor

    A cursor is a small bitmap usually used for denoting where the mouse
    pointer is, with a picture that might indicate the interpretation of a
    mouse click. As with icons, cursors in X and MS Windows are created in a
    different manner. Therefore, separate cursors will be created for the
    different environments. Platform-specific methods for creating a wxCursor
    object are catered for, and this is an occasion where conditional
    compilation will probably be required (see wxIcon for an example).

    A single cursor object may be used in many windows (any subwindow type).
    The wxWidgets convention is to set the cursor for a window, as in X, rather
    than to set it globally as in MS Windows, although a global wxSetCursor()
    function is also available for MS Windows use.

    @section cursor_custom Creating a Custom Cursor

    The following is an example of creating a cursor from 32x32 bitmap data
    (down_bits) and a mask (down_mask) where 1 is black and 0 is white for the
    bits, and 1 is opaque and 0 is transparent for the mask.
    It works on Windows and GTK+.

    @code
    static char down_bits[] = { 255, 255, 255, 255, 31,
        255, 255, 255, 31, 255, 255, 255, 31, 255, 255, 255,
        31, 255, 255, 255, 31, 255, 255, 255, 31, 255, 255,
        255, 31, 255, 255, 255, 31, 255, 255, 255, 25, 243,
        255, 255, 19, 249, 255, 255, 7, 252, 255, 255, 15, 254,
        255, 255, 31, 255, 255, 255, 191, 255, 255, 255, 255,
        255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
        255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
        255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
        255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
        255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
        255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
        255 };

    static char down_mask[] = { 240, 1, 0, 0, 240, 1,
        0, 0, 240, 1, 0, 0, 240, 1, 0, 0, 240, 1, 0, 0, 240, 1,
        0, 0, 240, 1, 0, 0, 240, 1, 0, 0, 255, 31, 0, 0, 255,
        31, 0, 0, 254, 15, 0, 0, 252, 7, 0, 0, 248, 3, 0, 0,
        240, 1, 0, 0, 224, 0, 0, 0, 64, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0 };

    #ifdef __WXMSW__
        wxBitmap down_bitmap(down_bits, 32, 32);
        wxBitmap down_mask_bitmap(down_mask, 32, 32);

        down_bitmap.SetMask(new wxMask(down_mask_bitmap));
        wxImage down_image = down_bitmap.ConvertToImage();
        down_image.SetOption(wxIMAGE_OPTION_CUR_HOTSPOT_X, 6);
        down_image.SetOption(wxIMAGE_OPTION_CUR_HOTSPOT_Y, 14);
        wxCursor down_cursor = wxCursor(down_image);
    #elif defined(__WXGTK__)
        wxCursor down_cursor = wxCursor(down_bits, 32, 32, 6, 14,
                                        down_mask, wxWHITE, wxBLACK);
    #endif
    @endcode

    @library{wxcore}
    @category{gdi}

    @stdobjects
    - ::wxNullCursor
    - ::wxSTANDARD_CURSOR
    - ::wxHOURGLASS_CURSOR
    - ::wxCROSS_CURSOR

    @see wxBitmap, wxIcon, wxWindow::SetCursor(), wxSetCursor(), ::wxStockCursor
*/
class wxCursor : public wxGDIObject
{
public:
    /**
        Default constructor.
    */
    wxCursor();

    /**
        Constructs a cursor from the provided bitmap and hotspot position.

        @param bitmap
            The bitmap to use for the cursor, should be valid.
        @param hotSpotX
            Hotspot x coordinate (relative to the top left of the image).
        @param hotSpotY
            Hotspot y coordinate (relative to the top left of the image).

        @since 3.3.0
     */
    wxCursor(const wxBitmap& bitmap, int hotSpotX = 0, int hotSpotY = 0);

    /**
        @overload

        @since 3.3.0
     */
    wxCursor(const wxBitmap& bitmap, const wxPoint& hotSpot);

    /**
        Constructs a cursor by passing a string resource name or filename.

        The arguments @a hotSpotX and @a hotSpotY are only used when there's no
        hotspot info in the resource/image-file to load (e.g. when using
        @c wxBITMAP_TYPE_ICO under wxMSW or @c wxBITMAP_TYPE_XPM under wxGTK).

        @param cursorName
            The name of the resource or the image file to load.
        @param type
            Icon type to load. It defaults to @c wxCURSOR_DEFAULT_TYPE,
            which is a @#define associated to different values on different
            platforms:
            - under Windows, it defaults to @c wxBITMAP_TYPE_CUR_RESOURCE.
              Other permitted types under Windows are @c wxBITMAP_TYPE_CUR
              (to load a cursor from a .cur cursor file), @c wxBITMAP_TYPE_ICO
              (to load a cursor from a .ico icon file) and @c wxBITMAP_TYPE_ANI
              (to load a cursor from a .ani icon file).
            - under MacOS, it defaults to @c wxBITMAP_TYPE_MACCURSOR_RESOURCE;
              when specifying a string resource name, first a PNG and then a CUR
              image is searched in resources.
            - under GTK, it defaults to @c wxBITMAP_TYPE_XPM.
              See the wxCursor(const wxImage& image) ctor for more info.
            - under X11, it defaults to @c wxBITMAP_TYPE_XPM.
        @param hotSpotX
            Hotspot x coordinate (relative to the top left of the image).
        @param hotSpotY
            Hotspot y coordinate (relative to the top left of the image).
    */
    wxCursor(const wxString& cursorName,
             wxBitmapType type = wxCURSOR_DEFAULT_TYPE,
             int hotSpotX = 0, int hotSpotY = 0);

    /**
        @overload

        @since 3.3.0
     */
    wxCursor(const wxString& name, wxBitmapType type, const wxPoint& hotSpot);

    /**
        Constructs a cursor using a cursor identifier.

        @param cursorId
            A stock cursor identifier. See ::wxStockCursor.
    */
    wxCursor(wxStockCursor cursorId);

    /**
        Constructs a cursor from a wxImage. If cursor are monochrome on the
        current platform, colors with the RGB elements all greater than 127
        will be foreground, colors less than this background. The mask (if any)
        will be used to specify the transparent area.

        In wxMSW the foreground will be white and the background black.
        If the cursor is larger than 32x32 it is resized.

        In wxGTK, colour cursors and alpha channel are supported (starting from
        GTK+ 2.2). Otherwise the two most frequent colors will be used for
        foreground and background. In any case, the cursor will be displayed
        at the size of the image.

        Under wxMac (Cocoa), large cursors are supported.

        Notice that the @a image can define the cursor hot spot. To set it you
        need to use wxImage::SetOption() with @c wxIMAGE_OPTION_CUR_HOTSPOT_X
        or @c wxIMAGE_OPTION_CUR_HOTSPOT_Y, e.g.
        @code
            image.SetOption(wxIMAGE_OPTION_CUR_HOTSPOT_X, hotSpotX);
            image.SetOption(wxIMAGE_OPTION_CUR_HOTSPOT_X, hotSpotY);
        @endcode
    */
    wxCursor(const wxImage& image);

    /**
        Constructs a cursor from XPM data.

        In versions of wxWidgets until 3.1.6 constructing wxCursor from XPM
        data implicitly used wxImage constructor from XPM data and wxCursor
        constructor from wxImage. Since 3.1.6 this constructor overload is
        available to allow constructing wxCursor from XPM to still work, even
        though wxImage constructor from XPM is now @c explicit.
     */
    wxCursor(const char* const* xpmData);

    /**
        wxGTK-specific constructor from data in XBM format.

        The parameters @a fg and @a bg have an effect only on GTK+, and force
        the cursor to use particular background and foreground colours.

        @param bits
            An array of XBM data bits.
        @param width
            Cursor width.
        @param height
            Cursor height.
        @param hotSpotX
            Hotspot x coordinate (relative to the top left of the image).
        @param hotSpotY
            Hotspot y coordinate (relative to the top left of the image).
        @param maskBits
            Bits for a mask bitmap.
        @param fg
            Foreground colour.
        @param bg
            Background colour.

        @onlyfor{wxgtk}

        @beginWxPerlOnly
        In wxPerl use Wx::Cursor->newData(bits, width, height, hotSpotX = -1, hotSpotY = -1, maskBits = 0).
        @endWxPerlOnly
    */
    wxCursor(const char bits[], int width, int height,
             int hotSpotX = -1, int hotSpotY = -1,
             const char maskBits[] = nullptr,
             const wxColour* fg = nullptr, const wxColour* bg = nullptr);

    /**
        Copy constructor, uses @ref overview_refcount "reference counting".

        @param cursor
            Pointer or reference to a cursor to copy.
    */
    wxCursor(const wxCursor& cursor);

    /**
        Returns @true if cursor data is present.
    */
    virtual bool IsOk() const;

    /**
        Returns the coordinates of the cursor hot spot.

        The hot spot is the point at which the mouse is actually considered to
        be when this cursor is used.

        This method is currently implemented in wxMSW, wxGTK and wxOSX (since
        wxWidgets 3.3.0) and returns ::wxDefaultPosition in the other ports.

        @since 3.1.0
     */
    wxPoint GetHotSpot() const;

    /**
        Assignment operator, using @ref overview_refcount "reference counting".
    */
    wxCursor& operator =(const wxCursor& cursor);
};


/**
    @name Predefined cursors.

    @see wxStockCursor
*/
///@{
wxCursor wxNullCursor;
wxCursor* wxSTANDARD_CURSOR;
wxCursor* wxHOURGLASS_CURSOR;
wxCursor* wxCROSS_CURSOR;
///@}

