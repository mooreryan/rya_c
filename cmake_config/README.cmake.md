# Rya

Snazzy functions in C.  Rya is short for Ryan, cos that's my name!

Currently, I'm on version @RYA_VERSION_STRING@.

## Install

### From the latest release

Here are some detailed instructions in case you are not a C programmer and need to install this library because another program relies on it.  (E.g., my sampling reads program.)

First, make a directory to hold the source code.

```bash
mkdir rya_c_source
cd rya_c_source
```

Then download the code.  If you have `wget`, run

```bash
wget 'https://github.com/mooreryan/rya_c/archive/v@RYA_VERSION_STRING@.tar.gz'
```

If you have `curl` run:

```bash
\curl -L 'https://github.com/mooreryan/rya_c/archive/v@RYA_VERSION_STRING@.tar.gz' > v@RYA_VERSION_STRING@.tar.gz
```

Unzip the tar file and enter the resulting directory.

```bash
tar xzf v@RYA_VERSION_STRING@.tar.gz
cd rya_c-@RYA_VERSION_STRING@
```

Now we can build and instal the library.

```bash
mkdir build
cd build
cmake ..
make
make install
```

*Note*:  You may need to run `sudo make install` rather than just `make install`.

### Install from git repository

```
git clone https://github.com/mooreryan/rya_c.git
cd rya_c
mkdir build
cd build
cmake ..
make
make install
```

### Switching compilers

(This step is completely optional).  If you're on a Mac and want to use `gcc`, you could replace the cmake line above with this

```bash
CC=/usr/local/bin/gcc-7 cmake ..
```

*Note*:  depending on which version of `gcc` you have installed, you may need to change `gcc-7` (version 7), to `gcc-8` (version 8), for example.

## Tests

If you want to run the tests, you need to have `ceedling` installed.  (It is a Ruby gem...to install those, you need `gem` and a working ruby installation.  Try [here](https://rvm.io) for more info.)

```bash
gem install ceedling
```

Then run the tests.

```bash
ceedling
```

You can find more about Ceedling [here](http://www.throwtheswitch.org/ceedling).

## Api docs

Doxygen API documentation can be found [here](https://mooreryan.github.io/rya_c/).
