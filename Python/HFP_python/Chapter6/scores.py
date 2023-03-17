import os
os.chdir('../00-Datas/Chapter05_06')

class Athlete:
    '''最好给定初始值'''
    def __init__(self,a_name,a_birth=None,a_score=[]):
        self.name = a_name
        self.birth = a_birth
        self.score = a_score

    def top3(self):
        return sorted(set([sanitize(s) for s in self.score]))[0:3]

    def add_time(self,time=None):
        self.score.append(time)

    def add_times(self,time_list=[]):
        self.score.extend(time_list)

class AthleteList(list):
    def __init__(self,a_name,a_birth=None,a_score=[]):
        list.__init__([])
        self.name = a_name
        self.birth = a_birth
        self.extend(a_score)
    def top3(self):
        return sorted(set([sanitize(s) for s in self]))[0:3]

def sanitize(time_string):
    if '-' in time_string:
        splitter = '-'
    elif ':' in time_string:
        splitter = ':'
    else:
        return(time_string)
    (mins,secs) = time_string.split(splitter)
    return(mins+'.'+secs)

def get_score_data(File_name):
    try:
        with open(File_name) as file:
            data = file.readline()
        data = data.strip().split(',')
        return AthleteList(data.pop(0),data.pop(0),data)
    except IOError as e:
        print('IOError'+str(e))
        return(None)

james = get_score_data('james2.txt')
julie = get_score_data('julie2.txt')
mikey = get_score_data('mikey2.txt')
sarah = get_score_data('sarah2.txt')
print(james.name+'\'s fastest times are: '+str(james.top3()))
print(julie.name+'\'s fastest times are: '+str(julie.top3()))
print(mikey.name+'\'s fastest times are: '+str(mikey.top3()))
print(sarah.name+'\'s fastest times are: '+str(sarah.top3()))
print('------------------')
##print('This is james\'s scores:'+str(james.score))
##james.add_time('2.55')
##print('This is james\'s scores(add_time):'+str(james.score))
##james.add_times(['2.66','2.77'])
##print('This is james\'s scores(add_times):'+str(james.score))

