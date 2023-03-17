import os
print(os.getcwd())
data_arr=[]
try:
    with open('canshu1.txt') as data:
        for each_line in data:
            #print(each_line)
            data_item = [float(each_data) for each_data in each_line.strip().split(',')]
            #print(data_item)
            data_arr.append(data_item)
except IOError as e:
    print("IOError:"+str(e))
print(data_arr[0][0])
