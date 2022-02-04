# libreactor
A C++ library that utilizes CPPZMQ and Google Protocol Buffers to make a reactor and event service that allows reactors to pass events to each other.

CPPZMQ - https://github.com/zeromq/cppzmq (Based off of ZeroMQ)

Google Protocol Buffers (protobuf/protoc) - https://github.com/protocolbuffers/protobuf

# Installation
**NOTE**: This was compiled, tested, and ran on Ubuntu 20.04. There could be a possibilty for cross compiling in the future but for now there is not.
  
To install the library download the release, clone the repo, copy the .so file to the repo and run one command. That's it!

## Downloading the release
To download the release as is, first, clone the repo to your machine.
  
  ```$ git clone git@github.com:Kyle-Gagnon-99/libreactor.git```
(This is assuming you are using ssh. If you are not use the HTTPS link to the repo)
  
After you clone the repo to your machine, download the relase and unzip the folder. In the folder you will find a .so (shared object) file in the release. Copy the .so file to be inside the repository. (<Clone Location>/libreactor/). Then move to inside the repository file and run the following command.
  
```$ sudo make full-installation```
  
This will copy the .so file and header files to ```/usr/local/<**include** for headers and **library** for the .so file>```. If you would like to change the location of where these get installed to then you can run the following instead
  
```
$ sudo make full-installation INSTALL_SO_DIR=/usr/lib INSTALL_H_DIR=/usr/include
```
  
Once that is done you are now ready to use the library!
