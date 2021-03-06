//          Copyright Blaze 2021.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE or copy at
//          https://www.boost.org/LICENSE_1_0.txt)

#include "mime.h"

const char *mime_string(enum mime mime) {
    switch (mime) {
    case null:
        return "\r\n";
    case aac:
        return "audio/aac\r\n";
    case abw:
        return "application/x-abiword\r\n";
    case arc:
        return "application/x-freearc\r\n";
    case avi:
        return "video/x-msvideo\r\n";
    case azw:
        return "application/vnd.amazon.ebook\r\n";
    case bin:
        return "application/octet-stream\r\n";
    case bmp:
        return "image/bmp\r\n";
    case bz:
        return "application/x-bzip\r\n";
    case bz2:
        return "application/x-bzip2\r\n";
    case csh:
        return "application/x-csh\r\n";
    case css:
        return "text/css\r\n";
    case csv:
        return "text/csv\r\n";
    case doc:
        return "application/msword\r\n";
    case docx:
        return "application/"
               "vnd.openxmlformats-officedocument.wordprocessingml."
               "document\r\n";
    case eot:
        return "application/vnd.ms-fontobject\r\n";
    case epub:
        return "application/epub+zip\r\n";
    case gz:
        return "application/gzip\r\n";
    case gif:
        return "image/gif\r\n";
    case htm:
        return "text/html\r\n";
    case ico:
        return "image/vnd.microsoft.icon\r\n";
    case ics:
        return "text/calendar\r\n";
    case jar:
        return "application/java-archive\r\n";
    case jpeg:
        return "image/jpeg\r\n";
    case js:
        return "text/javascript\r\n";
    case json:
        return "application/json\r\n";
    case jsonld:
        return "application/ld+json\r\n";
    case mid:
        return "audio/midi\r\n";
    case mjs:
        return "text/javascript\r\n";
    case mp3:
        return "audio/mpeg\r\n";
    case cda:
        return "application/x-cdf\r\n";
    case mp4:
        return "video/mp4\r\n";
    case mpeg:
        return "video/mpeg\r\n";
    case mpkg:
        return "application/vnd.apple.installer+xml\r\n";
    case odp:
        return "application/vnd.oasis.opendocument.presentation\r\n";
    case ods:
        return "application/vnd.oasis.opendocument.spreadsheet\r\n";
    case odt:
        return "application/vnd.oasis.opendocument.text\r\n";
    case oga:
        return "audio/ogg\r\n";
    case ogv:
        return "video/ogg\r\n";
    case ogx:
        return "application/ogg\r\n";
    case opus:
        return "audio/opus\r\n";
    case otf:
        return "font/otf\r\n";
    case png:
        return "image/png\r\n";
    case pdf:
        return "application/pdf\r\n";
    case php:
        return "application/x-httpd-php\r\n";
    case ppt:
        return "application/vnd.ms-powerpoint\r\n";
    case pptx:
        return "application/"
               "vnd.openxmlformats-officedocument.presentationml."
               "presentation\r\n";
    case rar:
        return "application/vnd.rar\r\n";
    case rtf:
        return "application/rtf\r\n";
    case sh:
        return "application/x-sh\r\n";
    case svg:
        return "image/svg+xml\r\n";
    case swf:
        return "application/x-shockwave-flash\r\n";
    case tar:
        return "application/x-tar\r\n";
    case tif:
        return "image/tiff\r\n";
    case ts:
        return "video/mp2t\r\n";
    case ttf:
        return "font/ttf\r\n";
    case txt:
        return "text/plain\r\n";
    case vsd:
        return "application/vnd.visio\r\n";
    case wav:
        return "audio/wav\r\n";
    case weba:
        return "audio/webm\r\n";
    case webm:
        return "video/webm\r\n";
    case webp:
        return "image/webp\r\n";
    case woff:
        return "font/woff\r\n";
    case woff2:
        return "font/woff2\r\n";
    case xhtml:
        return "application/xhtml+xml\r\n";
    case xls:
        return "application/vnd.ms-excel\r\n";
    case xlsx:
        return "application/"
               "vnd.openxmlformats-officedocument.spreadsheetml.sheet\r\n";
    case xml:
        return "text/xml\r\n";
    case xul:
        return "application/vnd.mozilla.xul+xml\r\n";
    case zip:
        return "application/zip\r\n";
    case _3gp:
        return "video/3gpp\r\n";
    case _3g2:
        return "video/3gpp2\r\n";
    case _7z:
        return "application/x-7z-compressed\r\n";
    }

    // should never come here, but if it does an empty string is returned
    return "\r\n";
}
