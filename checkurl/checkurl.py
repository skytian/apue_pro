import os
import sys
import time
import getopt
import requests
import asyncio




def checkUrl(url):
    try:
        r=requests.get(url,timeout=10)
        if r.status_code == 200:
            print("connect ",url," ok")
        else:
            print("fail code:",r.status_code)
    except Exception as error:
        print("fail connect:%s"%url)
        print(error)

async def async_checkUrl(url):
    checkUrl(url)

def readtxt(path):
    try:
        urllist = []
        with open(path, buffering=1) as f:
            for url in f:
                print(url)
                urllist.append(url[:-1])
        return urllist
    except Exception as error:
        print("read url failed")
        print(error)

def daemonize (stdin='/dev/null', stdout='/dev/null', stderr='/dev/null'):
    try: 
        pid = os.fork()
        if pid > 0:
            sys.exit(0)
    except OSError as e :
        sys.stderr.write ("fork #1 failed: (%d) %s\n" % (e.errno, e.strerror) )
        sys.exit(1)
    os.chdir("/")
    os.umask(0)
    os.setsid()

    try:
        pid = os.fork()
        if pid > 0:
            sys.exit(0)
    except OSError as e:
        sys.exit(1)

    for f in sys.stdout, sys.stderr: f.flush()
    si = open(stdin, 'r')
    so = open(stdout, 'a+')
    se = open(stderr, 'a+')
    os.dup2(si.fileno(), sys.stdin.fileno())    #dup2函数原子化关闭和复制文件描述符
    os.dup2(so.fileno(), sys.stdout.fileno())
    os.dup2(se.fileno(), sys.stderr.fileno())



def main(argv):
    try:
        opts, args = getopt.getopt(argv,"hf:",["urlfile="])
    except getopt.GetoptError:
        print("checkurl.py -f <urlfile>")
        sys.exit(2)
    for opt, arg in opts:
        if opt == '-h':
            print("checkUrl.py -f <urlfile>")
            sys.exit()
        elif opt in ("-f","--urlfile"):
            urlfile = arg
            try:
                urllist = readtxt(urlfile)
                print(urllist)    

                while True:
                    loop = asyncio.get_event_loop()
                    tasks = [async_checkUrl(url) for url in urllist]
                    loop.run_until_complete(asyncio.wait(tasks))
                    loop.close
                    print("\n")
                    time.sleep(5)
            except Exception as e:
                print("connect fail")
                print(e)

if __name__ == "__main__":
    daemonize('/dev/null','/tmp/daemon_stdout.log','/tmp/daemon_error.log')
    main(sys.argv[1:])
