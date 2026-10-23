# MyFTP

MyFTP is a lightweight FTP server written in C. It accepts multiple clients and supports authentication with the `Anonymous` user, directory navigation, file listing, file upload and download, and both active and passive data connections.

## Requirements

- GCC
- GNU Make
- Linux or another POSIX-compatible system
- Criterion and gcovr (only required for tests and coverage)

## Build

```sh
make
```

## Run

```sh
./myftp <port> <home_directory>
```

For example:

```sh
./myftp 2121 ./ftp_root
```

Connect with an FTP client using the `Anonymous` username. The password can be any value.

## Tests

```sh
make tests_run
```

Generate a coverage report with:

```sh
make coverage
```

## Technologies

- C (POSIX sockets, `poll`, signals and filesystem APIs)
- GCC
- GNU Make
- Criterion for unit tests
- gcovr for code coverage
