#! /usr/bin/env python3
import io,os,json,threading,math
from urllib import request

##获取图片数据列表

def get_img_list(url):
    print("OK!")
    with request.urlopen(url) as f:
        imgs_data = json.loads(f.read().decode('ascii'))
    return imgs_data

##获取图片部分数据
def get_img_part(img_url,data_range=(0,'')):
    '''根据data_range的范围返回图片相应部分的数据
    返回值为bytes'''
    req_header_range = {'Range':'bytes='+str(data_range[0])+'-'+str(data_range[1])}
    req_obj = request.Request(img_url,headers=req_header_range)
    with request.urlopen(req_obj,timeout=300) as f:
        return f.read()
##将(0,n)分为m份
def split_img(n,m):
    L = []
    t = math.ceil(n/m)
    L.append((0,t))
    tmp = 0
    while m > 1:
        m-=1
        n-=t
        t = math.ceil(n/m)
        L.append((L[tmp][1]+1,L[tmp][1]+t))
        tmp+=1
    return L
## 定义线程
class imgthread(threading.Thread):
    def __init__(self,part_id,img_url,size_rage):
        threading.Thread.__init__(self)
        self.part_id = part_id
        self.size_rage = size_rage
        self.img_url = img_url
    def run(self):
        '''将数据以键值的形式存储到全局变量中'''
        print('thread_id:'+str(self.part_id)+' start download!!')
        img_part_dict[self.part_id]=get_img_part(self.img_url,self.size_rage)
        print('thread_id:'+str(self.part_id)+' download finished!!')
    def get_data_part(img_url,data_range):
        part_data = get_img_part(img_url,data_range)
        return part_data


def nthread_dd(url,split_num,data_size,filename):
    data_part_dict={}
    data_range_list = split_img(data_size,split_num)
    ##3.生成线程列表
    thread_id = 0
    thread_list = []
    for size_range in data_range_list:
        thread_list.append(imgthread(thread_id,url,size_range))
        thread_id+=1
    ##4.运行线程
    for thread in thread_list:
        thread.start()
    for thread in thread_list:
        thread.join()
    with open(filename,'wb') as f:
        for i in range(split_num):
            f.write(img_part_dict[i])
    print(filename,'已经下载好了')


##生成多个线程
#-----------#
url='https://yande.re/post.json?limit=1'
imgs_data = get_img_list(url)
#url = 'http://s8.sinaimg.cn/orignal/000iyyaezy6PTqh21UPc7'
for img_data in imgs_data:
    img_part_dict = {}
    print('url:',img_data['sample_url'])
    ##1.获取size
    req_obj = request.Request(img_data['sample_url'],method='HEAD')
    with request.urlopen(req_obj) as rsp_obj:
        data_size = rsp_obj.getheader('Content-Length')
        print('data_size:',data_size)
    img_size = img_data['sample_file_size']
    print("img_size:",img_size)

    nthread_dd(img_data['sample_url'],5,img_size,'aaa.jpg')
