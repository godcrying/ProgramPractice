import os
os.chdir('../00-Datas/Chapter05_06')

def sanitize(time_string):
    if '-' in time_string:
        splitter = '-'
    elif ':' in time_string:
        splitter = ':'
    else:
        return(time_string)
    (mins,secs) = time_string.split(splitter)
    return(mins+'.'+secs)

## 应该起个好名字

def get_score_data(File_name):
    try:
        with open(File_name) as file:
            data = file.readline()
        return(data.strip().split(','))
    except IOError as e:
        print('IOError'+str(e))
        return(None)

        # 为了节约变量命名，可以进行改进。思考一下。
James_score_list = get_score_data('James.txt')
Julie_score_list = get_score_data('Julie.txt')
Sarah_score_list = get_score_data('Sarah.txt')
Mikey_score_list = get_score_data('Mikey.txt')

## 下面一行代码完成了以下内容：
## 1.列表推导式进行格式转换（迭代，转换并替换）
## 2.使用集合去除重复项
## 3.进行排序

James = sorted(set([sanitize(score) for score in James_score_list]))
Julie = sorted(set([sanitize(score) for score in Julie_score_list]))
Mikey = sorted(set([sanitize(score) for score in Mikey_score_list]))
Sarah = sorted(set([sanitize(score) for score in Sarah_score_list]))

print(James[0:3])
print(Julie[0:3])
print(Mikey[0:3])
print(Sarah[0:3])
