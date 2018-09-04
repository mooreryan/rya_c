# Rya

Snazzy functions in C.  Rya is short for Ryan, cos that's my name!

Currently, I'm on version 0.2.0.

## Install

Basic install...

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

If you're on a Mac and want to use `gcc`, you could replace the cmake line above with this

```bash
CC=/usr/local/bin/gcc-7 cmake ..
```

## Tests

If you want to run the tests, you need to have `ceedling` installed.

```bash
gem install ceedling
```

Then run the tests.

```bash
ceedling
```

## Api docs

Doxygen docs can be found [here](https://mooreryan.github.io/rya_c/).
