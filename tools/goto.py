# -*- coding:utf-8 -*-

import sys
import os

hosts = {
    'pack':{
        'ssh':'ssh m1@172.16.100.86',
        'des':'打包机器 ip地址：172.16.100.86',
    },
    'jys0012':{
        'ssh':'ssh a2_dev@jys0012.s.ejoy.com',
        'des':'sudo vi /srv/apps/a2_dev/serverlist.trunk(pwd:123456a)',
    },
    'jys0026':{
        'ssh':'ssh -p 2222 linbinghao@jys0026.s.ejoy.com',
        'des':'UC测试服, su && su m1_uc && cd /home/m1_uc/game_server/m1 scp端口为16890',
    },
    'jys0052':{
        'ssh':'ssh -p 16890 cm@jys0052.s.ejoy.com',
        'des':'UC数据库 用\'/home/cm/mongo32/bin\'目录下的mongo',
    },
    'wai':{
        'ssh':'ssh -p 18222 linbinghao@vps-inport.s.ejoy.com',
        'des':'新外网机器',
    },
    'company':{
        'ssh':'ssh -p 22 -L 2080:oa:80 -L 2088:svn:80 -L 2090:rtx:8000 linbinghao@sailor.ejoy.com',
        'des':'外网连接到公司内网',
    },
}

g_color = {
    "red":"\x1b[40;31m%s\033[0m",
    "green":"\x1b[40;32m%s\033[0m",
    "yellow":"\x1b[40;33m%s\033[0m",
    "blue":"\x1b[40;34m%s\033[0m",
}

def COLOR(color, s):
    if not color in g_color:
        return s
    return (g_color[color]) % s

def choose(s, options, default = 0):
    s = COLOR("green", s)
    answer = raw_input(s)
    if 0 == len(answer) and 0 < default:
        answer = options.keys()[default - 1]
    while answer not in options:
        if isinstance(options, list):
            print("你的输入必须在 %s 中" % options)
        if isinstance(options, dict):
            print("你的输入必须在 %s 中" % options.keys())
        answer = raw_input(s)
    return options[answer], answer

def get_input(s):
    return raw_input(COLOR("yellow", s))

def show_hosts():
    for host in hosts:
        print('host: ' + host)
        print('\tssh:' + hosts[host]['ssh'])
        print('\tdes:' + hosts[host]['des'])
        print('\n')

def goto_hosts(host):
    if not host in hosts:
        print('找不到名为[%s]的机器' % host)
        return
    os.system(hosts[host]['ssh'])

def main():
    host = ''
    if 1 == len(sys.argv):
        show_hosts()
        _, host = choose("选择你要跳转的机器:", hosts)
    else:
        host = sys.argv[1]

    goto_hosts(host)

if __name__ == '__main__':
    main()
