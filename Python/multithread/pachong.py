'''下载yande网站的图片
    1.建立链接
    2.获取json
    3.下载内容
'''
import io,os,json,threading
from urllib import request

# 获取图片信息对象列表
class image(dict):
    def __init__(self,img):
        dict.__init__(self,img)
        self.__id = img["id"]
    def get_id(self):
        return self.__id

url='https://yande.re/post.json?limit=1'
images_obj = []
with request.urlopen(url) as f:
    images = json.loads(f.read().decode('ascii'))
    for img in images:
        images_obj.append(image(img))

## 以下为请求下载图片代码，需要提供imag对象列表，生成每个图像文件
## print(images_obj)
req_headers = {'Range':'bytes=0-1000'} 
for img in images_obj:
    print(img['preview_url'])
    req_obj = request.Request(img['preview_url'],headers=req_headers)
    file_tmp = io.BytesIO(b'')
    with request.urlopen(req_obj) as f:
        print(f.getheaders())
        s = f.read()
    with open(str(img.get_id())+'.jpg','wb') as f:
        f.write(s)

## 生成多线程对象

##t = threading.Thread(target=get_img,name='1',args=())
