#!/bin/bash

[[ -f /a/local/msvc/vcvars.env ]] || build-vcvars
source load-vcvars
