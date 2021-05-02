# Cnidus
An ancient city in SW Asia Minor, in Caria: the Athenians defeated the Spartans in a naval battle near here 394 b.c.
Pronounced as *see-nay-dhus*.

# Info
Cnidus is a web framework in C based on [liburing](https://github.com/axboe/liburing), which requires Linux Kernel 5.1+.

Cnidus is still a work in progress, and is **not** production ready, as it probably contains a ton of bugs. An example of usage can be found [here](https://github.com/BlazeWasHere/Cnidus/blob/master/src/main.c).

Cnidus aims to be a simple interface to create REST APISs and static file serving, using an asynchronous I/O framework as the backend. A quick example:

```c
#include <signal.h>
#include <stdio.h>

#include "response.h"
#include "status.h"
#include "server.h"
#include "utils.h"
#include "mime.h"

#define PORT 1337
#define ENTRIES 256

void home(context *ctx) {
    respond(ctx->socket, "welcome to cnidus!", OK, txt);
}

int main() {
    signal(SIGINT, sigint_handler);

    int socket = setup_socket(PORT);
    setup_context(ENTRIES);

    add_route("/", home);

    event_loop(socket);
}
```

# Compile
This probably isn't the most ideal to do.

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
$ chmod +x tests.sh
$ ./tests.sh
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

# Benchmarks
Benchmarks using [ab](https://httpd.apache.org/docs/2.4/programs/ab.html) with cnidus v0.0.1.

```sh
$ $ ab -n 20000  http://0.0.0.0:1337/
This is ApacheBench, Version 2.3 <$Revision: 1843412 $>
Copyright 1996 Adam Twiss, Zeus Technology Ltd, http://www.zeustech.net/
Licensed to The Apache Software Foundation, http://www.apache.org/

Benchmarking 0.0.0.0 (be patient)
Completed 2000 requests
Completed 4000 requests
Completed 6000 requests
Completed 8000 requests
Completed 10000 requests
Completed 12000 requests
Completed 14000 requests
Completed 16000 requests
Completed 18000 requests
Completed 20000 requests
Finished 20000 requests


Server Software:        
Server Hostname:        0.0.0.0
Server Port:            1337

Document Path:          /
Document Length:        18 bytes

Concurrency Level:      1
Time taken for tests:   2.725 seconds
Complete requests:      20000
Failed requests:        0
Total transferred:      1660000 bytes
HTML transferred:       360000 bytes
Requests per second:    7339.38 [#/sec] (mean)
Time per request:       0.136 [ms] (mean)
Time per request:       0.136 [ms] (mean, across all concurrent requests)
Transfer rate:          594.89 [Kbytes/sec] received

Connection Times (ms)
              min  mean[+/-sd] median   max
Connect:        0    0   0.0      0       1
Processing:     0    0   0.0      0       2
Waiting:        0    0   0.0      0       2
Total:          0    0   0.0      0       2

Percentage of the requests served within a certain time (ms)
  50%      0
  66%      0
  75%      0
  80%      0
  90%      0
  95%      0
  98%      0
  99%      0
 100%      2 (longest request)

$ ab -n 20000 -c 100 http://0.0.0.0:1337/
This is ApacheBench, Version 2.3 <$Revision: 1843412 $>
Copyright 1996 Adam Twiss, Zeus Technology Ltd, http://www.zeustech.net/
Licensed to The Apache Software Foundation, http://www.apache.org/

Benchmarking 0.0.0.0 (be patient)
Completed 2000 requests
Completed 4000 requests
Completed 6000 requests
Completed 8000 requests
Completed 10000 requests
Completed 12000 requests
Completed 14000 requests
Completed 16000 requests
Completed 18000 requests
Completed 20000 requests
Finished 20000 requests


Server Software:        
Server Hostname:        0.0.0.0
Server Port:            1337

Document Path:          /
Document Length:        18 bytes

Concurrency Level:      100
Time taken for tests:   1.245 seconds
Complete requests:      20000
Failed requests:        0
Total transferred:      1660000 bytes
HTML transferred:       360000 bytes
Requests per second:    16068.80 [#/sec] (mean)
Time per request:       6.223 [ms] (mean)
Time per request:       0.062 [ms] (mean, across all concurrent requests)
Transfer rate:          1302.45 [Kbytes/sec] received

Connection Times (ms)
              min  mean[+/-sd] median   max
Connect:        0    3   0.7      3       8
Processing:     1    4   0.8      4       9
Waiting:        0    3   0.8      3       7
Total:          4    6   1.0      6      13

Percentage of the requests served within a certain time (ms)
  50%      6
  66%      6
  75%      6
  80%      6
  90%      7
  95%      8
  98%     10
  99%     11
 100%     13 (longest request)

$ ab -n 20000 -c 300 http://0.0.0.0:1337/
This is ApacheBench, Version 2.3 <$Revision: 1843412 $>
Copyright 1996 Adam Twiss, Zeus Technology Ltd, http://www.zeustech.net/
Licensed to The Apache Software Foundation, http://www.apache.org/

Benchmarking 0.0.0.0 (be patient)
Completed 2000 requests
Completed 4000 requests
Completed 6000 requests
Completed 8000 requests
Completed 10000 requests
Completed 12000 requests
Completed 14000 requests
Completed 16000 requests
Completed 18000 requests
Completed 20000 requests
Finished 20000 requests


Server Software:        
Server Hostname:        0.0.0.0
Server Port:            1337

Document Path:          /
Document Length:        18 bytes

Concurrency Level:      300
Time taken for tests:   1.283 seconds
Complete requests:      20000
Failed requests:        0
Total transferred:      1660000 bytes
HTML transferred:       360000 bytes
Requests per second:    15594.31 [#/sec] (mean)
Time per request:       19.238 [ms] (mean)
Time per request:       0.064 [ms] (mean, across all concurrent requests)
Transfer rate:          1263.99 [Kbytes/sec] received

Connection Times (ms)
              min  mean[+/-sd] median   max
Connect:        0    8   2.0      8      23
Processing:     3   11   2.4     11      22
Waiting:        0    8   2.3      8      17
Total:         11   19   2.4     18      38

Percentage of the requests served within a certain time (ms)
  50%     18
  66%     19
  75%     20
  80%     20
  90%     23
  95%     24
  98%     26
  99%     26
 100%     38 (longest request)
```

# Documentation
On the TODO list.

# TODO
  - Create documentation.
  - Support more than GET method.
  - Static file serving.
  - Write some tests.
  - More example usages.

# License
[BSL-1.0 License](https://github.com/BlazeWasHere/Cnidus/blob/master/LICENSE)
