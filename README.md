# Rya

Snazzy functions in C.  Rya is short for Ryan, cos that's my name!

Currently, I'm on version 0.2.3.

## Install

### Dependencies

You need `cmake` to compile.  Check if you have `cmake` with

```bash
which cmake
```

If you don't have CMake installed, please go [here](https://cmake.org/install/) and install it.

### From the latest release

Here are some detailed instructions in case you are not a C programmer and need to install this library because another program relies on it.  (E.g., my [sampling reads](https://github.com/mooreryan/sample_seqs) program.)

First, make a directory to hold the source code.

```bash
mkdir rya_c_source
cd rya_c_source
```

Then download the code.  

If you have `curl` run:

```bash
\curl -L 'https://github.com/mooreryan/rya_c/archive/v0.2.3.tar.gz' > v0.2.3.tar.gz
```

If you have `wget`, run

```bash
wget 'https://github.com/mooreryan/rya_c/archive/v0.2.3.tar.gz'
```

Unzip the tar file and enter the resulting directory.

```bash
tar xzf v0.2.3.tar.gz
cd rya_c-0.2.3
```

Now we can build and install the library.

```bash
mkdir build
cd build
cmake ..
make
make install
```

#### Potential problems

##### Switching compilers

If you're on a Mac you may need to use an actual `gcc` rather than the default apple compiler.  If you're having issues, try switching like this:

```bash
CC=/usr/local/bin/gcc-7 cmake ..
```

*Note*:  depending on which version of `gcc` you have installed, you may need to change `gcc-7` (version 7), to `gcc-8` (version 8), for example.


##### Changing the install directory 

If you want to change the location where the library is installed (for example, if you don't have sudo privileges), you can run `cmake` like this

```bash
cmake -DCMAKE_INSTALL_PREFIX=$HOME ..
```

which would put the library files under `$HOME/lib` or `$HOME/lib64` and the header files under `$HOME/include`.

You'll also probably want to edit your shell config file to modify the `LD_LIBRARY_PATH` so that programs can find the shared object files.

So you should add the following to your shell config file (e.g., `~/.profile`, `~/.bash_profile`, or whatever you use):

```bash
# Local shared object libs
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:"$HOME"/lib
```
or 

```bash
# Local shared object libs
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:"$HOME"/lib64
```

depending on if the file is in `$HOME/lib` or `$HOME/lib64`.


##### No super user privileges

You may need to run `sudo make install` rather than just `make install` depending on where you want the library installed.

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

(This step is completely optional).  

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
