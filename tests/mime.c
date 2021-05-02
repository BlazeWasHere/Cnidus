//          Copyright Blaze 2021.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE or copy at
//          https://www.boost.org/LICENSE_1_0.txt)

// CMOCKA DEPS...
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <stdint.h>
// END CMOCKA DEPS...
#include <cmocka.h>

#include "mime.h"

static void test_mime_string_empty() {
    assert_string_equal(mime_string(null), "\r\n");
    assert_string_equal(mime_string(21321), "\r\n");
}

static void test_mime_string_all() {
    assert_string_equal(mime_string(aac), "audio/aac\r\n");
    assert_string_equal(mime_string(abw), "application/x-abiword\r\n");
    assert_string_equal(mime_string(arc), "application/x-freearc\r\n");
    assert_string_equal(mime_string(avi), "video/x-msvideo\r\n");
    assert_string_equal(mime_string(azw), "application/vnd.amazon.ebook\r\n");
    assert_string_equal(mime_string(bin), "application/octet-stream\r\n");
    assert_string_equal(mime_string(bmp), "image/bmp\r\n");
    assert_string_equal(mime_string(bz), "application/x-bzip\r\n");
    assert_string_equal(mime_string(bz2), "application/x-bzip2\r\n");
    assert_string_equal(mime_string(csh), "application/x-csh\r\n");
    assert_string_equal(mime_string(css), "text/css\r\n");
    assert_string_equal(mime_string(csv), "text/csv\r\n");
    assert_string_equal(mime_string(doc), "application/msword\r\n");
    assert_string_equal(mime_string(docx), "application/vnd.openxmlformats-officedocument.wordprocessingml.document\r\n");
    assert_string_equal(mime_string(eot), "application/vnd.ms-fontobject\r\n");
    assert_string_equal(mime_string(epub), "application/epub+zip\r\n");
    assert_string_equal(mime_string(gz), "application/gzip\r\n");
    assert_string_equal(mime_string(gif), "image/gif\r\n");
    assert_string_equal(mime_string(htm), "text/html\r\n");
    assert_string_equal(mime_string(ico), "image/vnd.microsoft.icon\r\n");
    assert_string_equal(mime_string(ics), "text/calendar\r\n");
    assert_string_equal(mime_string(jar), "application/java-archive\r\n");
    assert_string_equal(mime_string(jpeg), "image/jpeg\r\n");
    assert_string_equal(mime_string(js), "text/javascript\r\n");
    assert_string_equal(mime_string(json), "application/json\r\n");
    assert_string_equal(mime_string(jsonld), "application/ld+json\r\n");
    assert_string_equal(mime_string(mid), "audio/midi\r\n");
    assert_string_equal(mime_string(mjs), "text/javascript\r\n");
    assert_string_equal(mime_string(mp3), "audio/mpeg\r\n");
    assert_string_equal(mime_string(cda), "application/x-cdf\r\n");
    assert_string_equal(mime_string(mp4), "video/mp4\r\n");
    assert_string_equal(mime_string(mpeg), "video/mpeg\r\n");
    assert_string_equal(mime_string(mpkg), "application/vnd.apple.installer+xml\r\n");
    assert_string_equal(mime_string(odp), "application/vnd.oasis.opendocument.presentation\r\n");
    assert_string_equal(mime_string(ods), "application/vnd.oasis.opendocument.spreadsheet\r\n");
    assert_string_equal(mime_string(odt), "application/vnd.oasis.opendocument.text\r\n");
    assert_string_equal(mime_string(oga), "audio/ogg\r\n");
    assert_string_equal(mime_string(ogv), "video/ogg\r\n");
    assert_string_equal(mime_string(ogx), "application/ogg\r\n");
    assert_string_equal(mime_string(opus), "audio/opus\r\n");
    assert_string_equal(mime_string(otf), "font/otf\r\n");
    assert_string_equal(mime_string(png), "image/png\r\n");
    assert_string_equal(mime_string(pdf), "application/pdf\r\n");
    assert_string_equal(mime_string(php), "application/x-httpd-php\r\n");
    assert_string_equal(mime_string(ppt), "application/vnd.ms-powerpoint\r\n");
    assert_string_equal(mime_string(pptx), "application/vnd.openxmlformats-officedocument.presentationml.presentation\r\n");
    assert_string_equal(mime_string(rar), "application/vnd.rar\r\n");
    assert_string_equal(mime_string(rtf), "application/rtf\r\n");
    assert_string_equal(mime_string(sh), "application/x-sh\r\n");
    assert_string_equal(mime_string(svg), "image/svg+xml\r\n");
    assert_string_equal(mime_string(swf), "application/x-shockwave-flash\r\n");
    assert_string_equal(mime_string(tar), "application/x-tar\r\n");
    assert_string_equal(mime_string(tif), "image/tiff\r\n");
    assert_string_equal(mime_string(ts), "video/mp2t\r\n");
    assert_string_equal(mime_string(ttf), "font/ttf\r\n");
    assert_string_equal(mime_string(txt), "text/plain\r\n");
    assert_string_equal(mime_string(vsd), "application/vnd.visio\r\n");
    assert_string_equal(mime_string(wav), "audio/wav\r\n");
    assert_string_equal(mime_string(weba), "audio/webm\r\n");
    assert_string_equal(mime_string(webm), "video/webm\r\n");
    assert_string_equal(mime_string(webp), "image/webp\r\n");
    assert_string_equal(mime_string(woff), "font/woff\r\n");
    assert_string_equal(mime_string(woff2), "font/woff2\r\n");
    assert_string_equal(mime_string(xhtml), "application/xhtml+xml\r\n");
    assert_string_equal(mime_string(xls), "application/vnd.ms-excel\r\n");
    assert_string_equal(mime_string(xlsx), "application/vnd.openxmlformats-officedocument.spreadsheetml.sheet\r\n");
    assert_string_equal(mime_string(xml), "text/xml\r\n");
    assert_string_equal(mime_string(xul), "application/vnd.mozilla.xul+xml\r\n");
    assert_string_equal(mime_string(zip), "application/zip\r\n");
    assert_string_equal(mime_string(_3gp), "video/3gpp\r\n");
    assert_string_equal(mime_string(_3g2), "video/3gpp2\r\n");
    assert_string_equal(mime_string(_7z), "application/x-7z-compressed\r\n");
}

int main() {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_mime_string_empty),
        cmocka_unit_test(test_mime_string_all),
    };

    return cmocka_run_group_tests(tests, NULL, NULL);
}