# libreactor
A C++ library that utilizes CPPZMQ and Google Protocol Buffers to make a reactor and event service that allows reactors to pass events to each other.

CPPZMQ - https://github.com/zeromq/cppzmq (Based off of ZeroMQ)

Google Protocol Buffers (protobuf/protoc) - https://github.com/protocolbuffers/protobuf

# Overview
The libreactor library uses CPPZMQ and Google Protocol Buffers to be able to send messages from one class to another and react to when that message is being
sent to them. The libreactor library uses C++ std::string as a wrapper class for the data. In reality all data can be serialized to a char* and then passed
in as a C++ string.

# Example
Given that the library install correctly here is a basic example

MessageReactor.cpp
```
#include <string>
#include "reactor/Reactor.h"
#include "reactor/EventService.h"
#include "MessageReactor.h"

MessageReactor::MessageReactor(int p_rid) : reactor::Reactor(p_rid) {
    /*
     * Extends off of the abstract Reactor class. Do anything more you need here
     */
}

MessageReactor::MessageReactor(int p_rid, std::string p_conEndPoint) : reactor::Reactor(p_rid, p_conEndPoint) {
    /*
     * Extends off of the abstract Reactor class. Do anything more you need here
     */
}

// When you get a message print out what the message was
void MessageReactor::consumeMsg(std::string p_msg) {
    spdlog::debug("RID {} RECEIVED: {}", rid, p_msg);
}

// If the message failed to deliver we should decide what to do with it
void MessageReactor::processFailMsg(std::string p_failMsgStr, int p_dest) {
    spdlog::debug("RID {} failed to deliver to {}", rid, p_dest);
}

// NOTE: It is highly suggested you join the thread at the end of the base class' life
MessageReactor::~MessageReactor() {
    thread_object.join();
}
```

Main.cpp
```
#include "spdlog/spdlog.h"
#include "MessageReactor.h"
#include <string>

int main() {
    
    spdlog::set_level(spdlog::level::debug);

    spdlog::debug("Here is an example / testing");

    // Start the event service so that messages can be passed.
    reactor::EventService evService;
    evService.start();

    // Start up the reactor with a unique id of 5
    MessageReactor MessageReactor(5);
    MessageReactor.start();

    // Send a message back to itself
    std::string str = "This is rid 5 sending to rid 5!";
    fullReactor.sendMessage(5, str);

    return 0;
}
```

# Installation
Installing the library normal requires sudo unless you would like to install the .so and header files to a different location. First

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
