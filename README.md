# libreactor
A C++ library that utilizes CPPZMQ and Google Protocol Buffers to make a reactor and event service that allows reactors to pass events to each other.

CPPZMQ - https://github.com/zeromq/cppzmq (Based off of ZeroMQ)

Google Protocol Buffers (protobuf/protoc) - https://github.com/protocolbuffers/protobuf

# Installation
**NOTE**: This was compiled, tested, and ran on Ubuntu <version>. There could be a possibilty for cross compiling in the future but for now there is not.
  
You can install the library in one of two ways! My favorite, you can download the .so and header files from the release and you can move the .so and header files where you would like to, or you can build the library from the source code.

## Downloading the release
To download the release, find the release you would like and download it to your machine. From there you can paste the .so file where you would normally link libraries and put the header files where your compiler will search for.
  
## Installing from source

Installing the library requires external libraries to be installed on your machine.

```$ git clone git@github.com:Kyle-Gagnon-99/libreactor.git```

Next is to build and install the library. 

```
$ cd libreactor
$ sudo make full-installation
```

Both the .so and header files will be copied into /usr/local/ (lib and include respectivley). If you wish to override where the installation will go you can override ```INSTALL_SO_DIR``` for the shared object and ```INSTALL_H_DIR``` for the headers. Example:

```
$ sudo make full-installation INSTALL_SO_DIR=/usr/lib INSTALL_H_DIR=/usr/include
```

To use the development version of libreactor do the following

```
$ cd libreactor
$ git checkout remotes/origin/development -b development
$ sudo make full-installation
```

For now you can only build the shared object from source and install it from there.
