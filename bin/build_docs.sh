#!/bin/bash

doxygen && rm -r docs/*; cp -r docs_all/html/* docs