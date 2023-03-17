import os, sys, nester,pickle
os.chdir("../00-Datas/Chapter03")
man = []
other = []
try:
    with open('sketch.txt') as data:
        for each_line in data:
            try:
                (role, line_spoken) = each_line.split(':',1)
                line_spoken = line_spoken.strip()
                if role == 'Man':
                    man.append(line_spoken)
                elif role == 'Other Man':
                    other.append(line_spoken)
                print(role,end='')
                print(' said: ',end='')
                print(line_spoken)
            except ValueError:
                print(each_line,end='')
except FileNotFoundError as e:
    print('FileError:'+str(e))

try:
    with open('man_data.txt','wb') as out_man,open('other_data.txt','wb') as out_other:
        pickle.dump(man,out_man)
        pickle.dump(other,out_other)
##        for man_say in man:
##            print(man_say, file=out_man, end='')
##        for other_say in other:
##            print(other_say, file=out_other, end='')
except IOError as e:
    print('IOError!!'+str(e))
except pickle.PickleError as e:
    print('PickleError'+str(e))
    
