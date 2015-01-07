if [ -f ~/.bashrc ]; then
	. ~/.bashrc
fi

export BOOST_INCLUDE=/usr/include/boost
export BOOST_LIB=/usr/local/lib

export WS_PATH=/home/ubuntu/workspace/server

export PATH=${WS_PATH}/tools:$PATH

export GD_ENV="-DDEBUG_LDH"

alias ls='ls --color=auto'

cd ${WS_PATH}
