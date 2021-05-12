//          Copyright Blaze 2021.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE or copy at
//          https://www.boost.org/LICENSE_1_0.txt)

#pragma once

/* taken from https://developer.mozilla.org/en-US/docs/Web/HTTP/Basics_of_HTTP/MIME_types/Common_types */
typedef enum {
    null    = -1,
    aac     = 0,
    abw     = 1,
    arc     = 2,
    avi     = 3,
    azw     = 4,
    bin     = 5,
    bmp     = 6,
    bz      = 7,
    bz2     = 8,
    csh     = 9,
    css     = 10,
    csv     = 11,
    doc     = 12,
    docx    = 13,
    eot     = 14,
    epub    = 15,
    gz      = 16,
    gif     = 17,
    htm     = 18,
    ico     = 19,
    ics     = 20,
    jar     = 21,
    jpeg    = 22,
    js      = 23,
    json    = 24,
    jsonld  = 25,
    mid     = 26,
    mjs     = 27,
    mp3     = 28,
    cda     = 29,
    mp4     = 30,
    mpeg    = 31,
    mpkg    = 32,
    odp     = 33,
    ods     = 34,
    odt     = 35,
    oga     = 36,
    ogv     = 37,
    ogx     = 38,
    opus    = 39,
    otf     = 40,
    png     = 41,
    pdf     = 42,
    php     = 43,
    ppt     = 44,
    pptx    = 45,
    rar     = 46,
    rtf     = 47,
    sh      = 48,
    svg     = 49,
    swf     = 50,
    tar     = 51,
    tif     = 52,
    ts      = 53,
    ttf     = 54,
    txt     = 55,
    vsd     = 56,
    wav     = 57,
    weba    = 58,
    webm    = 59,
    webp    = 60,
    woff    = 61,
    woff2   = 62,
    xhtml   = 63,
    xls     = 64,
    xlsx    = 65,
    xml     = 66,
    xul     = 67,
    zip     = 68,
    _3gp    = 69,
    _3g2    = 70,
    _7z     = 71,
} MIME_TYPE;

/**
 * convert a MIME_TYPE enum value to a string 
 * 
 * ```c
 *      mime_string(txt);
 *      returns -> "text/plain\r\n"
 * ```
 */
const char *mime_string(MIME_TYPE mime);
