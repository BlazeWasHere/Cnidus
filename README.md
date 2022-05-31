# Cnidus
An ancient city in SW Asia Minor, in Caria: the Athenians defeated the Spartans in a naval battle near here 394 b.c.
Pronounced as *see-nay-dhus*.

# Info
Cnidus is a web framework in C based on [liburing](https://github.com/axboe/liburing), which requires Linux Kernel 5.1+.

Cnidus is still a work in progress, and is **not** production ready, as it probably contains a ton of bugs. An example of usage can be found [here](https://github.com/BlazeWasHere/Cnidus/blob/master/src/main.c).

Cnidus aims to be a simple interface to create REST APIs and static file serving, using an asynchronous I/O framework as the backend. A quick example:

```c
#include <signal.h>
#include <stdio.h>

#include "cnidus.h"

#define PORT 1337
#define ENTRIES 256

static void home(context *ctx) {
    const char *res = "welcome to cnidus!";
    respond(ctx, res, sizeof(res), OK, txt, 1);
}

int main() {
    signal(SIGINT, sigint_handler);

    int socket = setup_socket(PORT);
    setup_context(ENTRIES);

    add_route(GET, "/", home);

    event_loop(socket);
}
```

# Compile
This probably isn't the most ideal way to do it.

```sh
$ make
[...]
$ ./cnidus
```
Then visit [localhost](http://localhost:1337)

# Tests
```sh
# in project root (make sure cnidus is built and the objects exist)
$ make
$ cd tests
$ make
[...]
testing bin/dict...

[==========] tests: Running 3 test(s).
[ RUN      ] null_test_success
[       OK ] null_test_success
[ RUN      ] test_size_dict_new
[       OK ] test_size_dict_new
[ RUN      ] test_dict_add_find
[       OK ] test_dict_add_find
[==========] tests: 3 test(s) run.
[  PASSED  ] 3 test(s).

testing bin/mime...

[==========] tests: Running 2 test(s).
[ RUN      ] test_mime_string_empty
[       OK ] test_mime_string_empty
[ RUN      ] test_mime_string_all
[       OK ] test_mime_string_all
[==========] tests: 2 test(s) run.
[  PASSED  ] 2 test(s)
[...]
```

# Documentation
On the TODO list.

# TODO
  - Create documentation.
  - Static file serving.
  - Write some tests.
  - More example usages.
  - Cache.
  - Make Cnidus as a shared library.
  - Finish the JSON parsing (jsmn)

# License
[BSL-1.0 License](https://github.com/BlazeWasHere/Cnidus/blob/master/LICENSE)
