#! /usr/bin/env python3
import io,os,json,threading,math,re
import split as sp
from urllib import request

#图片对象
class download_file():
    def __init__(self):
        self._size = 0
        self._data = None
    def split_size(self,split_num):
        return sp.split(self._size,split_num)
    @property
    def size(self):
        return self._size
    @size.setter
    def size(self,value):
        self._size = value

    @property
    def data(self):
        return self._data
    @data.setter
    def data(self,value):
        self.data = value

#图片缓存对象
class download_buffer():
    def __init__(self,size):
        self._data = io.BytesIO()
        for _ in range(size+1):
            self._data.write(b'\x00')

    def write(self,data,seek=0):
        self._data.seek(seek)
        self._data.write(data)
    @property
    def data(self):
        return self._data.getvalue()

#线程对象
class downloadThread(threading.Thread):
    def __init__(self,req,name=''):
        threading.Thread.__init__(self)
        self.name = name
        self.req = req
    def run(self):
        print(self.name+'start!!\n')
        pattern = re.compile(r'\d+')
        pos = pattern.search(self.req.get_header('Range'))
        print("Range",self.req.get_header('Range'))
        print("seek：",pos)
        with request.urlopen(self.req,timeout=300) as f:
            Mybuffer.write(f.read(),seek=int(pos.group(0)))
        print(self.name+'end!!\n')


if __name__ == "__main__":
    url = 'https://files.yande.re/sample/3ad7a327cae95a7b495013a141cc9000/yande.re%20395928%20sample%20animal_ears%20fate_grand_order%20naked%20shielder_%28fate_grand_order%29%20yashichii.jpg'
    #构建请求对象
    req_obj = request.Request(url,method='HEAD')
    download_obj = download_file()
    with request.urlopen(req_obj) as f:
        download_obj.size = int(f.getheader('Content-Length'))
    #获取图片大小范围
    file_splits_list = download_obj.split_size(5)

    #local_req = threading.local()
    #缓存对象
    Mybuffer = download_buffer(download_obj.size)

    #构建请求对象
    #启动线程
    threadList = []
    for data_range in file_splits_list:
        req_header_range = {'Range':'bytes='+str(data_range[0])+'-'+str(data_range[1])}
        req_obj = request.Request(url,headers=req_header_range)
        threadList.append(downloadThread(req_obj,name='thread'+str(file_splits_list.index(data_range))))
    for thread in threadList:
        thread.start()
    for thread in threadList:
        thread.join()

    with open('testimg','wb') as f:
        f.write(Mybuffer.data)
    print("finished!!")
