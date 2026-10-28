#!/bin/bash

[[ -f /a/null/msvc/vcvars.env ]] || build-vcvars
source load-vcvars
