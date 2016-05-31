#!/bin/bash

a=`pwd`

export WS_PATH=${a}
export PATH=${WS_PATH}/tools:$PATH
export | grep WS_PATH
